#include "PictureView.hpp"


class PictureView::ThisPrivate{
public:
    PictureView * super ;
    ThisPrivate(PictureView * s):super(s){

    }

    ~ThisPrivate(){

    }



};


PictureView::PictureView(QWidget * p):
SuperType(p){
    thisp = new ThisPrivate(this);
}

PictureView::~PictureView(){
    delete thisp ;
}


/**/


