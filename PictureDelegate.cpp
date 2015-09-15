
#include "PictureDelegate.hpp"

PictureDelegate::~PictureDelegate(){
   delete objectManager ;
}

PictureDelegate::PictureDelegate(QWidget *p):
    SuperType(p){

    button = new QPushButton;
    QHBoxLayout * l = new QHBoxLayout;
    this->setLayout(l);
    l->addWidget(button);
    backGroundColor = QColor(rand() % 255, rand() % 255, rand() % 255, 255);
    this->setMouseTracking(true);
    objectManager = new QObject;

}

void PictureDelegate::setEditorData(
    const QModelIndex & index
    )   {
    auto model = index.model();
    if (0 == model) { return; }
    stringData = model->data(index, Qt::DisplayRole).toString();
}

void PictureDelegate::paintEvent(QPaintEvent *)  {

    {
        QPainter painter(this);
        painter.drawImage(0, 0, backGroundImage);
    }

    if(stringData.isEmpty()){return ;}
    QPainter painter(this);
    int g_ = 255 - backGroundColor.green();
    QColor color_ = QColor(rand() % 255, g_, rand() % 255, 255);

    painter.setBrush(color_);
    painter.setPen(color_);
    painter.drawText(20, 20, stringData);

    isFirstPainted = true;

}

void PictureDelegate::beforePaint(
    const QStyleOptionViewItem & option,
    const QModelIndex & index)   {

    QImage backGroundImage_(option.rect.size(), QImage::Format_ARGB32_Premultiplied);
    /*如果被选中*/
    if (option.state&QStyle::State_Selected) {
        backGroundImage_.fill(QColor(11, 111, 11));
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

void PictureDelegate::enterEvent(QEvent *)  {

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

void PictureDelegate::beforeWidgetDelete()  {
    delete objectManager;
    objectManager = 0;
}

/*  */
