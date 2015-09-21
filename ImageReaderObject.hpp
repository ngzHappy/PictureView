
#ifndef _5_IMAGE__READER__OBJECT__
#define _5_IMAGE__READER__OBJECT__

/*
 * 这应当是一个私有文件
*/

#include <QThread>
#include <QObject>
#include <memory>
#include <QSize>
#include <QImage>
#include <QPixmap>
#include <QMetaType>
#include <mutex>
#include <shared_mutex>
#include <QRunnable>
#include <QThreadPool>

class PictureDelegate;

namespace Namespace{
	namespace ImageReaderObject {

		typedef std::shared_ptr< volatile bool > SBoolBase;
        typedef std::shared_ptr< QImage > SPixmapBase;
		typedef std::shared_ptr< std::mutex > SMutexBase;
		typedef std::shared_ptr< std::shared_timed_mutex > SSMutexBase;

		class SBool :public SBoolBase {
		public:
			using SBoolBase::SBoolBase;
		};

		class SPixmap :public SPixmapBase {
		public:
			using SPixmapBase::SPixmapBase;
		};

		class SMutex :public SMutexBase {
		public:
			using SMutexBase::SMutexBase;
		};

		class SSMutex : public SSMutexBase {
		public:
			using SSMutexBase::SSMutexBase;
		};

	}
}

Q_DECLARE_METATYPE(Namespace::ImageReaderObject::SBool)
Q_DECLARE_METATYPE(Namespace::ImageReaderObject::SPixmap)
Q_DECLARE_METATYPE(Namespace::ImageReaderObject::SMutex)
Q_DECLARE_METATYPE(Namespace::ImageReaderObject::SSMutex)

class ImageReaderObject : public QObject{
    Q_OBJECT
protected:
    class ThisThread :
            public QThread {
    public:
        ThisThread(QObject * s):QThread(s){}
        ~ThisThread(){}
        virtual void run()override{
            exec();
        }
    };
    ThisThread * thisThread = 0;
public:
    ~ImageReaderObject();
	ImageReaderObject();
public slots:
/* 
	异步调用 
	隐式数据共享
*/
    void getAPicture(
            const QSize   imageSize                             /* 读取图片的大小 */ ,
            const QString   picturePath                         /* 读取图片的路径 */ ,
		    Namespace::ImageReaderObject::SMutex onDestoryMutex /* 防止对象析构 */ ,
		    Namespace::ImageReaderObject::SBool onDestoryData   /* 查看对象是否已经析构 */ ,
            PictureDelegate * pictureDelegate                   /* 回调对象 */ ,
			Namespace::ImageReaderObject::SSMutex ansMutex      /* 函数返回值锁 */,
		    Namespace::ImageReaderObject::SPixmap ans           /* 函数运行结果 */
            );
private:

    QThreadPool threadPool ;
};

#endif
