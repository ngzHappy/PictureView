#include "PictureView.hpp"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QResizeEvent>
#include <QDebug>

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
    ThisPrivate(PictureView * s):super(s){
        scene_ = new QGraphicsScene(s);
        s->setScene(scene_);
    }

    ~ThisPrivate(){

    }

    QGraphicsPixmapItem * item_ = 0;
    QGraphicsScene * scene_ = 0;
    QSize pictureSize_ ;
	QPixmap pixmap_;

    void setPicture(const QString &  image__ ){
		/* 由于是主线程,也许不用创建独立拷贝 */
        const QPixmap pmap_ = QPixmap( image__ );
        pictureSize_ = pmap_.size() ;

        auto * it_ = new QGraphicsPixmapItem(pmap_);
        scene_->addItem(it_);

        if(item_){
            scene_->removeItem( item_ );
            delete item_;
        }

        item_ = it_;
		pixmap_ = pmap_;
        fitToSize( super->size() );

    }

    void fitToSize(const QSize & size_){

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
			pixmap_.scaled(
				bsize_,
				Qt::IgnoreAspectRatio,
				Qt::SmoothTransformation
				)
			);
		item_->setPos( tl );
		
    }

};

void PictureView::resizeEvent(QResizeEvent *event){
    SuperType::resizeEvent(event);
    thisp->fitToSize( event->size() );
}

void PictureView::setPicture(const QString &  v) {
    thisp->setPicture(v);
}

PictureView::PictureView(QWidget * p):
SuperType(p){
    thisp = new ThisPrivate(this);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

PictureView::~PictureView(){
    delete thisp ;
}


/*  */


