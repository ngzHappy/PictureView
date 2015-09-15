
#ifndef __DEleGATE__ITEM__PICTURE__VIEW_0_
#define __DEleGATE__ITEM__PICTURE__VIEW_0_

/*
 * 此文件应当为私有文件
*/

#include <ItemView/AbstractItemWidget.hpp>
#include <QApplication>
#include <QStringListModel>
#include <QPainter>
#include <QImage>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QEventLoop>
#include <QDebug>
#include <QTimer>


class PictureDelegate :public  AbstractItemWidget{
    Q_OBJECT
public:
    typedef AbstractItemWidget SuperType ;
    typedef PictureDelegate ThisType ;

    ~PictureDelegate();
    explicit PictureDelegate(QWidget *);
    PictureDelegate():PictureDelegate(nullptr){}

protected:
    virtual void setEditorData(
        const QModelIndex & index
        )   override ;
    virtual void paintEvent(QPaintEvent *)override ;
    virtual void beforePaint(
        const QStyleOptionViewItem & option,
        const QModelIndex & index) override ;
    virtual void enterEvent(QEvent *)override ;
    virtual void beforeWidgetDelete() override;
private:
    QColor backGroundColor;
    QImage backGroundImage;
    QString stringData;
    QPushButton * button;
    bool isFirstPainted = false;
    QObject * objectManager = 0;
    bool isEnterEvent = false;
};


#endif

