
#ifndef __DEleGATE__ITEM__PICTURE__VIEW_0_
#define __DEleGATE__ITEM__PICTURE__VIEW_0_

/*
 * 此文件应当为私有文件
*/
#include <QEvent>
#include <ItemView/AbstractItemWidget.hpp>
#include <QApplication>
#include <QStringListModel>
#include <QPainter>
#include <QImage>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QEventLoop>
#include <QDebug>
#include <QTimer>
#include <QMovie>
#include <memory>
#include "ImageReaderObject.hpp"
#include "PictureButton.hpp"
#include <array>

class PictureListView;

class PictureDelegateUpdateEvent :public QEvent  {
public:

    PictureDelegateUpdateEvent():
        QEvent( QEvent::Type(QEvent::MaxUser) ){

    }
    virtual ~PictureDelegateUpdateEvent(){

    }

};

class PictureDelegateMovie : 
	public QMovie,
	public std::enable_shared_from_this<PictureDelegateMovie>{
	Q_OBJECT
public:
	
	PictureDelegateMovie( 
		const QString  fileName/*文件名*/ ,
		Namespace::ImageReaderObject::SMutex onDestoryMutex1 /* 防止对象析构 */,
	    Namespace::ImageReaderObject::SBool onDestoryData1   /* 查看对象是否已经析构 */
		);

	~PictureDelegateMovie();
	PictureDelegateMovie * instance();

	static int count();

protected:

	Namespace::ImageReaderObject::SMutex onDestoryMutex /* 防止对象析构 */;
	Namespace::ImageReaderObject::SBool onDestoryData   /* 查看对象是否已经析构 */;
	 
	void timerEvent(QTimerEvent * event) override;
signals:
	void updateFrame( QPixmap );

private slots:
    void _updateFrame( int );
	void _error( QImageReader::ImageReaderError );
	void _destory();
	void _check_destory();
public:
	std::shared_ptr< PictureDelegateMovie > movie;
	
};

class PictureDelegate :
	public  AbstractItemWidget{
    Q_OBJECT
public:
    typedef AbstractItemWidget SuperType ;
    typedef PictureDelegate ThisType ;

    ~PictureDelegate();
    explicit PictureDelegate(PictureListView *);
    PictureDelegate():PictureDelegate(nullptr){}

signals:
	 
    void getAPicture(
		const QSize & imageSize                             /* 读取图片的大小 */,
		const QString & picturePath                         /* 读取图片的路径 */,
		Namespace::ImageReaderObject::SMutex onDestoryMutex /* 防止对象析构 */,
		Namespace::ImageReaderObject::SBool onDestoryData   /* 查看对象是否已经析构 */,
		PictureDelegate * pictureDelegate                   /* 回调对象 */,
		Namespace::ImageReaderObject::SSMutex ansMutex      /* 函数返回值锁 */,
		Namespace::ImageReaderObject::SPixmap ans           /* 函数运行结果 */
            );

	void getAMovie(
		const QSize   imageSize                             /* 读取图片的大小 */,
		const QString   picturePath                         /* 读取图片的路径 */,
		Namespace::ImageReaderObject::SMutex onDestoryMutex /* 防止对象析构 */,
		Namespace::ImageReaderObject::SBool onDestoryData   /* 查看对象是否已经析构 */,
		PictureDelegate * pictureDelegate                   /* 回调对象 */
		);

protected:

    virtual void setEditorData(
        const QModelIndex & index
        )   override ;
    virtual void paintEvent( QPaintEvent * )override ;
    virtual void beforePaint(
        const QStyleOptionViewItem & option,
        const QModelIndex & index) override ;
    virtual void enterEvent(QEvent *)override ;
	virtual void leaveEvent(QEvent *)override;
    virtual void beforeWidgetDelete() override;
    AbstractItemWidget * instance(
		QWidget * parent,
		const QStyleOptionViewItem & option,
		const QModelIndex & index
		)override;

	enum class ButtonIndex : int {
		ViewButton = 0,
		ButtonSize
	};

private:
    QColor backGroundColor;
    QImage backGroundImage;
    QString stringData;
    QObject * objectManager = 0;
    bool isEnterEvent = false;
	bool isPainting = false;

private:
	PictureListView * super;
	bool  isMoive_ = false  /*gif*/;

	Namespace::ImageReaderObject::SMutex  onDestoryMutex_    /* 防止对象析构 */;
	Namespace::ImageReaderObject::SBool   onDestoryData_     /* 查看对象是否已经析构 */;
	Namespace::ImageReaderObject::SPixmap readedPicture      /* 已经读取的图片 */;
	Namespace::ImageReaderObject::SSMutex readedPictureMutex /* 返回图片锁 */;

	//std::shared_ptr< PictureDelegateMovie > movie;
	QPixmap movieFrame;

	std::array< PictureButton * ,int(ButtonIndex::ButtonSize) > buttons;
	void _initButtons();
private:
	void _mouse_enter();
protected:
    bool event(QEvent * ) override;
public slots:
	void updateFrame(QPixmap);
};


#endif

