
#include "PictureDelegate.hpp"
#include "ImageReaderObject.hpp"
#include "PictureListView.hpp"
#include <cstdlib>
#include <ctime>
#include <QTextLayout>
#include <QFontMetrics>
#include <QSpacerItem>
#include "PictureViewButton.hpp"

PictureDelegate::~PictureDelegate(){
	beforeWidgetDelete();
}

PictureDelegate::PictureDelegate(PictureListView *p):
    SuperType( (QWidget *)(p) ){

	objectManager = new QObject;

	static bool _ = []() {
		std::srand((unsigned int)(std::time(0)));
		return bool( rand()&1 );
	}();

	super = p;

	readedPicture = std::shared_ptr<QPixmap>(new QPixmap);
	onDestoryData_ = std::shared_ptr<bool>(new bool(false));
	onDestoryMutex_ = std::shared_ptr<std::mutex>(new std::mutex);
	readedPictureMutex = std::shared_ptr<std::shared_timed_mutex>( new std::shared_timed_mutex);

	QVBoxLayout * vl = new QVBoxLayout;
    this->setLayout(vl);

	auto getRand = []() {
		return rand() % 150 + 50; //[50,175]
	};

    backGroundColor = QColor(getRand(), getRand(), getRand(), 255);
    this->setMouseTracking(true);
    
	if (super) {
		auto * imageReader_ = super->getImageReader();
		if (imageReader_) {
			this->connect(this, &PictureDelegate::getAPicture,
				imageReader_, &ImageReaderObject::getAPicture,
				Qt::ConnectionType::QueuedConnection
				);
		}
	}

	/* 设置layout */
	QHBoxLayout * l = new QHBoxLayout;
	_initButtons();
	vl->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Minimum,QSizePolicy::MinimumExpanding));
	vl->addLayout(l);
	l->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::MinimumExpanding));
	for ( auto * i:buttons ) {
		l->addWidget( i );
	}

	l->setMargin(0);
	l->setSpacing(0);
	vl->setMargin(0);
	vl->setSpacing(0);
	isPainting = false;

    (void) _;
}

void PictureDelegate::setEditorData(
    const QModelIndex & index
    )   {
	if (objectManager == 0) { return; }
	this->setToolTip(stringData);

    auto model = index.model();
    if (0 == model) { return; }
    stringData = model->data(index, Qt::DisplayRole).toString();

	/* 更新button数据 */
	for (auto * i : buttons) {
		i->setPictureName( stringData );
	}

}

AbstractItemWidget * PictureDelegate::instance(
	QWidget * parent,
	const QStyleOptionViewItem & option,
	const QModelIndex & index
	) {
	if (objectManager == 0) { 
		qDebug() << "core error!!";
		return this;
	}
	this->setParent(parent);
	this->beforePaint(option, index);
	 
	/* 获取图片 */
	emit getAPicture(
		option.rect.size(),
		stringData,
		onDestoryMutex_,
		onDestoryData_,
		this,
		readedPictureMutex,
		readedPicture
		);

	return this;
}


void PictureDelegate::paintEvent(QPaintEvent *) {
	if (isPainting) { return; }
	if (objectManager == 0) { return; }

	//isPainting
	class PaintingLocker {
		bool * data__;
	public:
		~PaintingLocker() { *data__ = false; }
		PaintingLocker(bool * d) :data__(d) { *data__ = true; }
	};

	PaintingLocker _1x_(&(this->isPainting));

	if (this->underMouse() == false) {
		leaveEvent(0);
	}

	{
		/* 绘制背景 */
		QPainter painter(this);
		painter.drawImage(0, 0, backGroundImage);
	}

	do{
		/* 尝试绘制图片 */
		if ( false == readedPictureMutex->try_lock_shared() ) { break; }
		QPixmap readedPicture_s_;
		{
			std::shared_lock< std::shared_timed_mutex >
				_lock_pixmap_(*readedPictureMutex, std::adopt_lock);
			/*
			隐式数据共享
			增加一份拷贝
			*/
			readedPicture_s_ = (*readedPicture);
		}
		const auto & readedPicture_ = readedPicture_s_;
		if ( (readedPicture_.width() > 0) && (readedPicture_.height() > 0 ) ) {
			/* 绘制图片 */
			QPainter painter(this);
			int x = readedPicture_.width();
			int y = readedPicture_.height();
			x -= this->width();
			y -= this->height();
			x /= -2;
			y /= -2;

			painter.drawPixmap((x > 0 ? x : 0), (y > 0 ? y : 0), readedPicture_);

			if (false == isFirstPainted) {
				/* 记录第一次绘制完成 */
				isFirstPainted = true;
				return _mouse_enter();
			}

			return;
		}
		else {
			break;
		}
	} while (0);

    /* 如果图片不存在绘制字符 */
    if(stringData.isEmpty()){return ;}
    QPainter painter(this);
 
    QColor color_ = QColor(0, 0, 0, 255);

    painter.setBrush(color_);
    painter.setPen(color_);
	
	/* 文本布局 */
	QTextLayout textLayout( stringData );
	QFontMetrics fontMetrics( painter.font() );
	int leading = fontMetrics.leading();
	qreal height = 0;
	textLayout.setCacheEnabled(true);
	textLayout.beginLayout();
	int lineWidth = this->width() - 40;
	lineWidth = lineWidth > 0 ? lineWidth : 100;

	while (1) {
		QTextLine line = textLayout.createLine();
		if (!line.isValid())
			break;

		line.setLineWidth(lineWidth);
		height += leading;
		line.setPosition(QPointF(0, height));
		height += line.height();
	}
	textLayout.endLayout();
	textLayout.draw(&painter, QPointF(20, 12));

	if (false == isFirstPainted) {
		/* 记录第一次绘制完成 */
		isFirstPainted = true;
		return _mouse_enter();
	}
    
}

void PictureDelegate::beforePaint(
    const QStyleOptionViewItem & option,
    const QModelIndex & index)   {
	if (0 == objectManager) { return; }
	const auto && size_ = option.rect.size();
    QImage backGroundImage_( size_, QImage::Format_ARGB32_Premultiplied );
    /*如果被选中*/
    if (option.state&QStyle::State_Selected) {
        backGroundImage_.fill(QColor(222, 222, 222));
    }
    else {
        backGroundImage_.fill(backGroundColor);
    }
    backGroundImage = backGroundImage_;

    if (false == isEnterEvent) {
        updateEditorGeometry(option, index);
    }
    else {
        finalRect_ = option.rect;
    }

    setEditorData(index);

}

void PictureDelegate::_mouse_enter() {

	if (objectManager == 0) { return; }
    if (isFirstPainted == false) { return; }
    if (isEnterEvent) { return; }

    isEnterEvent = true;
    const auto && finalPos = this->geometry().topLeft();
    auto * animation = new QPropertyAnimation(this, "pos", objectManager);
    animation->setDuration(100);
    animation->setStartValue(finalPos - QPoint(3, 3));
    animation->setEndValue(finalPos);
    animation->connect(animation, &QPropertyAnimation::finished,
        [this]() {
        this->isEnterEvent = false;
        this->setGeometry(finalRect_);
    });
    animation->start(QPropertyAnimation::DeleteWhenStopped);

}

void PictureDelegate::leaveEvent(QEvent *) {
	if (objectManager == 0) { return; }
	for (auto * i : buttons) {
		i->hide() ;
	}
}

void PictureDelegate::enterEvent(QEvent *)  {
	if (0 == objectManager) { return; }
	for ( auto * i:buttons ) {
		i->show();
	}

	return _mouse_enter();
}

void PictureDelegate::beforeWidgetDelete()  {
	
	if (0 == objectManager) { return; }
	std::unique_lock<std::mutex> __locker__(*onDestoryMutex_);
	*onDestoryData_ = true;
    delete objectManager;
    objectManager = 0;

}

void PictureDelegate::_initButtons() {

	buttons[int(ButtonIndex::ViewButton)] = new PictureViewButton( stringData,this->super );


}

/*  */
