﻿#include "PictureView.hpp"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QResizeEvent>
#include <QDebug>
#include <thread>
#include <atomic>
#include <QApplication>
#include <QMovie>
#include <QFileInfo>

namespace  {
QSize bestSize( const QSize & source,const QSize & tar ){

if( (tar.width()<=source.width())&&(tar.height()<=source.height()) ){
    return tar ;
}

const double sw = source.width();
const double sh = source.height();
double tw = tar.width();
double th = tar.height();

if( (tw<=0) || (th<=0)){return QSize(0,0);}
if( (sw<=0) || (sh<=0)){return QSize(0,0);}

const double swh_ = sw/sh;
const double twh_ = tw/th;

if(swh_>twh_){
/* 宽大于高 */
    tw /= th;
    tw *= sh;
    th = sh;
}else{
/* 高大于宽 */
    th /= tw;
    th *= sw;
    tw = sw;
}

return QSize( int(tw),int(th) );

}
}

class PictureView::ThisPrivate{
public:
    PictureView * super ;

	/* movie 位于主线程 */
	QMovie * movie = 0;

    ThisPrivate(PictureView * s):super(s){
        scene_ = new QGraphicsScene(s);
        s->setScene(scene_);
    }

    ~ThisPrivate(){
		delete movie;
    }

    QGraphicsPixmapItem * item_ = 0;
    QGraphicsScene * scene_ = 0;
    QSize pictureSize_ ;
    QImage pixmap_;
    bool setPictureIng =false ;

    void setPicture(const QString  image__ ){

        if(setPictureIng){
            return ;
        }

        class Locker__{
            bool * b_;
        public:
            Locker__(bool * _b):b_(_b){*b_=true;}
            ~Locker__(){*b_=false ;}
        };

        {

			if (movie) {
				delete movie;
				movie = 0;
			}

            Locker__ _1_(&(setPictureIng));

            /* 创建独立拷贝 */
            QImage pmap_  ;
            std::atomic<bool> isLoaded(false);
            auto image_read_function = [ image__ ](
                    std::atomic<bool> * isLoaded_,
                    QImage * image_
                    ){
				isLoaded_->store( false );
                *image_ = std::move( QImage(image__) );
				image_->detach();
                isLoaded_->store( true );
            };

            std::thread thread_( image_read_function,&isLoaded,&pmap_ );
            
            while( isLoaded.load()==false ){
                QApplication::processEvents();
            }

			if (thread_.joinable()) {
				thread_.join();
			}
          
            pictureSize_ = pmap_.size() ;

            auto * it_ = new QGraphicsPixmapItem ;
            scene_->addItem(it_);

            if(item_){
                scene_->removeItem( item_ );
                delete item_;
                item_=0;
            }

            item_ = it_;
            pixmap_ = std::move( pmap_ );

        }
        fitToSize( super->size() );

    }

    void fitToSize(const QSize & size_){

        if(setPictureIng){
            return ;
        }

		class Locker__ {
			bool * b_;
		public:
			Locker__(bool * _b) :b_(_b) { *b_ = true; }
			~Locker__() { *b_ = false; }
		};
		Locker__ _1_(&(setPictureIng));

        if(0==item_){return ;}
        if(size_.width()<=0){return ;}
        if(size_.height()<=0){return ;}

		auto  sr_ =QRectF(0, 0, size_.width(), size_.height());

		scene_->setSceneRect( sr_ );
		scene_->sceneRectChanged( sr_  );
		
		const auto bsize_ = bestSize( size_ ,pictureSize_ );

		const auto tl= 
			sr_.center() - QPointF( bsize_.width()/2,bsize_.height()/2 );

		item_->setPixmap( 
                    QPixmap::fromImage(
			pixmap_.scaled(
				bsize_,
				Qt::IgnoreAspectRatio,
				Qt::SmoothTransformation
				)
                        )
			);
		item_->setPos( tl );
		
    }

	void setMoviePicture(
		const QString  image__
		) {

		if (setPictureIng) {
			return;
		}
				
		class Locker__ {
			bool * b_;
		public:
			Locker__(bool * _b) :b_(_b) { *b_ = true; }
			~Locker__() { *b_ = false; }
		};

		{
			Locker__ _1_(&(setPictureIng));
			if (movie) {
				delete movie;
				movie = 0;
			}

			movie = new QMovie( image__ );

			movie->connect(movie, &QMovie::frameChanged,
				[this](int) { updateMoviePixmap(); }
			);

			movie->start();
						
		}

	}

	void updateMoviePixmap(   ) {

		if (0 == movie) { return; }
		if (scene_ == 0) { return; }
		if (item_==0) {
			item_ = new QGraphicsPixmapItem;
			scene_->addItem( item_ );
		}

		pixmap_ = movie->currentImage() ;
		pictureSize_ = pixmap_.size();
		fitToSize( super->size() );
		
	}


};

void PictureView::resizeEvent(QResizeEvent *event){
    SuperType::resizeEvent(event);
    thisp->fitToSize( event->size() );
}

void PictureView::setPicture(const QString   v) {
	QFileInfo info( v );
	if (info.suffix().toLower().simplified() == "gif") {
		thisp->setMoviePicture(v);
	}
	else {
		thisp->setPicture(v);
	}
}

PictureView::PictureView(QWidget * p):
SuperType(p){
    thisp = new ThisPrivate(this);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

PictureView::~PictureView(){
    delete thisp ;
	thisp=0;
}


/*  */


