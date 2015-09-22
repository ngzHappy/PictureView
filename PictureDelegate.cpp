
#include "PictureDelegate.hpp"
#include "ImageReaderObject.hpp"
#include "PictureListView.hpp"
#include <cstdlib>
#include <ctime>
#include <QTextLayout>
#include <QFontMetrics>
#include <QTimer>
#include <QSpacerItem>
#include <QDebug>
#include <atomic>
#include "PictureModel.hpp"
#include "PictureViewButton.hpp"

PictureDelegate::~PictureDelegate(){
	beforeWidgetDelete();
}

PictureDelegate::PictureDelegate(PictureListView * p):
    SuperType(  ){

	objectManager = new QObject;

	static bool _ = []() {
		std::srand((unsigned int)(std::time(0)));
		return bool( rand()&1 );
	}();

	super = p;

    readedPicture = std::shared_ptr<QImage>(new QImage);
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

			this->connect(this, &PictureDelegate::getAMovie,
				imageReader_, &ImageReaderObject::getAMovie,
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

 
namespace {
	std::atomic<int> movie_count(0);
}
 
int PictureDelegateMovie::count() {
	return movie_count.load();
}

PictureDelegateMovie::
PictureDelegateMovie( 
	const QString  fileName,
	Namespace::ImageReaderObject::SMutex onDestoryMutex1 /* 防止对象析构 */,
	Namespace::ImageReaderObject::SBool onDestoryData1  /* 查看对象是否已经析构 */
	):QMovie(fileName) {

	this->startTimer( 100 );
	onDestoryMutex = onDestoryMutex1;
	onDestoryData  = onDestoryData1;

	++movie_count;
 
}

PictureDelegateMovie * PictureDelegateMovie::instance() {
	/* 避免自身被删除 */
	movie = this->shared_from_this();

	/* 读取图片 */
	this->connect(this, &PictureDelegateMovie::frameChanged,
		this, &PictureDelegateMovie::_updateFrame);

	/* 错误删除 */
	this->connect(
		this, &PictureDelegateMovie::error,
		this, &PictureDelegateMovie::_error
		);

	this->start();

	/*  */
	return this;
}

void PictureDelegateMovie::_error(QImageReader::ImageReaderError) {
	if (false == movie) { return; }
	/* 删除自身 */
	return _destory();
}

void PictureDelegateMovie::_destory() {
	if (false == movie) { return; }
	/* 删除自身 */
	this->stop();
	movie = std::shared_ptr<PictureDelegateMovie>( );
}

void PictureDelegateMovie::_updateFrame(int) {
	if (false == movie) { return; }
	auto pixmap__ = this->currentPixmap();

	{
		/* 检查对象是否已经析构 */
		std::unique_lock< std::mutex > _mutex__( *onDestoryMutex );
		if (*onDestoryData) { 
		}
		else {
			emit updateFrame(pixmap__);
			return;
		}
	}

	/* 删除自身 */
	_destory();
	return;
}

PictureDelegateMovie::
~PictureDelegateMovie() {
	--movie_count;
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

	{
		const auto * model_ = index.model();
		if (model_) {
			isMoive_ =
				( model_->data( index ,PictureModel::Suffix_Role ).toString() == "gif");
		}

		if (isMoive_) {
			getAMovie(
				option.rect.size(),
				stringData,
				onDestoryMutex_,
				onDestoryData_,
				this
				);
			return this;
		}
	}

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

#ifdef _DEBUG
static int movie_count_ = 0;
#endif

void PictureDelegateMovie::timerEvent(QTimerEvent * event) {
	QMovie::timerEvent(event);
	_check_destory();
}

void PictureDelegateMovie::_check_destory() {
	bool need_destory_ = false;

	{
		std::unique_lock< std::mutex > _mutex__(*onDestoryMutex);
		if (*onDestoryData) {
			need_destory_ = true;
		}
	}

	if ( need_destory_ ) {
		movie = std::shared_ptr<PictureDelegateMovie>();
	}
}

void PictureDelegate::paintEvent(QPaintEvent *) {

#ifdef _DEBUG	
	{
		int movie_count_ago = movie_count_;
		movie_count_ = PictureDelegateMovie::count();
		if(movie_count_!= movie_count_ago)
		{qDebug() << movie_count_; }
	}
#endif

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

	if (isMoive_) {

		/* 绘制movie */
		const auto & readedPicture_ = movieFrame ;
		if ((readedPicture_.width() > 0) && (readedPicture_.height() > 0)) {
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

	}else do{

		/* 尝试绘制图片 */
		if ( false == readedPictureMutex->try_lock_shared() ) { break; }
        QImage readedPicture_s_;
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

            painter.drawImage((x > 0 ? x : 0), (y > 0 ? y : 0), readedPicture_);

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
	auto * objM = objectManager;
	objectManager = 0;
	delete objM;

	std::unique_lock<std::mutex> __locker__( *onDestoryMutex_ );
	*onDestoryData_ = true;
   
}

void PictureDelegate::_initButtons() {

	buttons[int(ButtonIndex::ViewButton)] = new PictureViewButton( stringData,this->super );


}

bool PictureDelegate::event(QEvent * e){

    if( dynamic_cast<PictureDelegateUpdateEvent *>(e) ){
        this->update();
		return true;
    }
    return SuperType::event(e);

}

void PictureDelegate::updateFrame(QPixmap p) {
	movieFrame = p;
	this->update();
}

/*  */
