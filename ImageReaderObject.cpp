
#include "ImageReaderObject.hpp"
#include "PictureDelegate.hpp"
#include <QImageReader>
#include <thread>
#include <QDebug> 
#include <QFile>

ImageReaderObject::ImageReaderObject( ) :
	QObject( nullptr ){

    const static int thread_count_ = []() {
        int ans = QThread::idealThreadCount();
        if (ans > 0) { return ans; }
        return 1;
    }();
    threadPool.setMaxThreadCount(thread_count_);


    auto * thread__ = new ThisThread(this);
    this->moveToThread(thread__);
    thisThread = thread__;
	thisThread->start();
}

ImageReaderObject::~ImageReaderObject(){
    thisThread->exit(     );
    threadPool.clear(     );
    threadPool.waitForDone(100);

	if (thisThread->wait(100)==false) {
		/* 等待100ms用于退出 */
		/* 失败则杀死线程 */
		thisThread->terminate();
	}
}

namespace  {
QSize bestSize( const QSize & source,const QSize & tar ){

	if ((tar.width() <= source.width()) && (tar.height() <= source.height())) {
		return tar;
	}

	const double sw = source.width();
	const double sh = source.height();
	double tw = tar.width();
	double th = tar.height();

	if ((tw <= 0) || (th <= 0)) { return QSize(0, 0); }
	if ((sw <= 0) || (sh <= 0)) { return QSize(0, 0); }

	const double swh_ = sw / sh;
	const double twh_ = tw / th;

	if (swh_>twh_) {
		/* 宽大于高 */
		tw /= th;
		tw *= sh;
		th = sh;
	}
	else {
		/* 高大于宽 */
		th /= tw;
		th *= sw;
		tw = sw;
	}

	return QSize( int(tw),int(th) );

}//~bestSize
}


namespace  {
class Runnable :public QRunnable {
public:
    const QSize   imageSize                              /* 读取图片的大小 */;
    const QString   picturePath                          /* 读取图片的路径 */;
    Namespace::ImageReaderObject::SMutex onDestoryMutex  /* 防止对象析构 */;
    Namespace::ImageReaderObject::SBool onDestoryData    /* 查看对象是否已经析构 */;
    PictureDelegate * pictureDelegate                    /* 回调对象 */;
    Namespace::ImageReaderObject::SSMutex   ansMutex     /* 函数运行结果锁 */;
    Namespace::ImageReaderObject::SPixmap ans            /* 函数运行结果 */;

    Runnable(const QSize   imageSize_                             /* 读取图片的大小 */,
             const QString   picturePath_                         /* 读取图片的路径 */,
             Namespace::ImageReaderObject::SMutex onDestoryMutex_ /* 防止对象析构 */,
             Namespace::ImageReaderObject::SBool onDestoryData_   /* 查看对象是否已经析构 */,
             PictureDelegate * pictureDelegate_                   /* 回调对象 */,
             Namespace::ImageReaderObject::SSMutex   ansMutex_    /* 函数运行结果锁 */,
             Namespace::ImageReaderObject::SPixmap ans_           /* 函数运行结果 */)
    :imageSize (imageSize_),
      picturePath (picturePath_),
      onDestoryMutex (onDestoryMutex_),
      onDestoryData (onDestoryData_),
      pictureDelegate (pictureDelegate_),
      ansMutex (ansMutex_),
      ans (ans_)
    {

    }

    virtual void run() override{

        {
            /* 检查对象是否已经析构 */
            std::unique_lock< std::mutex > _mutex__(*onDestoryMutex);
            if (*onDestoryData) { return; }
        }

        if (imageSize.width() <= 0) { return; }
        if (imageSize.height() <= 0) { return; }

        QFile file__( picturePath );
        if ( false == file__.open(QIODevice::ReadOnly) ) {
            return;
        }

        QImageReader reader__( &file__ /*picturePath*/ );
        auto iSize_ = reader__.size();
        iSize_= bestSize( imageSize,iSize_ );
        reader__.setScaledSize( iSize_ );
        QImage temp__ = reader__.read() ;

        /* 强制创建独立拷贝 */
        temp__.detach();

        /* 关闭文件 */
        file__.close();

        /* 强制创建独立拷贝 */
        auto temp__ans =  std::move(temp__) ;
        temp__ans.detach();

        {
            std::unique_lock< std::shared_timed_mutex > _0set_( *ansMutex );
            *ans =std::move( temp__ans );
        }

        {
            /* 检查对象是否已经析构 */
            std::unique_lock< std::mutex > _mutex__(*onDestoryMutex);
            if (*onDestoryData) { return; }
            /* 异步调用更新图片 */
            pictureDelegate->update();
        }

    }

};
}

void ImageReaderObject::getAPicture(
	const QSize   imageSize                             /* 读取图片的大小 */,
	const QString   picturePath                         /* 读取图片的路径 */,
	Namespace::ImageReaderObject::SMutex onDestoryMutex /* 防止对象析构 */,
	Namespace::ImageReaderObject::SBool onDestoryData   /* 查看对象是否已经析构 */,
	PictureDelegate * pictureDelegate                   /* 回调对象 */,
	Namespace::ImageReaderObject::SSMutex   ansMutex    /* 函数运行结果锁 */,
	Namespace::ImageReaderObject::SPixmap ans           /* 函数运行结果 */
	) {

	{
		/* 检查对象是否已经析构 */
		std::unique_lock< std::mutex > _mutex__(*onDestoryMutex);
		if (*onDestoryData) { return; }
	}
	   
    Runnable * run_ = new Runnable(
                imageSize,
                picturePath,
                onDestoryMutex,
                onDestoryData,
                pictureDelegate ,
                ansMutex,
                ans
                );

     threadPool.start( run_ );

}


/*  */
