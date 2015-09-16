

#include "PictureButton.hpp"
#include "PictureListView.hpp"

PictureButton::PictureButton(
        const QString & pictureName_,
        PictureListView* v)
    :SuperType( (QWidget *)v ){
	super = v;
	setPictureName( pictureName_ );

	/* size */
	this->setFixedHeight(20);
	this->setFixedWidth(20);

	typedef void(QToolButton::* TBT)();
	this->connect( this, TBT(&QToolButton::clicked),
		[this]() {
		QString command__ = this->command();
		super->eval( command__ );
	}
		);

}

PictureButton::~PictureButton(){

}

/**/
