
#include <QToolButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QTimer>
#include "PlayerNumLine.hpp"

namespace  {

class PlayNumLineStartButton :
        public QToolButton{
public:

};

class PlayNumLineEdit:
        public QLineEdit
{
public:

};

}

void PlayNumLine::startPlay() {

	if (timer) {
		timer->stop();
		timer->deleteLater();
		timer = 0;
	}


	int value__ = numline_->text().toInt();
	if ( value__>0 ) {
		int fps_t_ = 1000 / value__;
		if (fps_t_ <= 0) { fps_t_ = 1; }
		timer = new QTimer(this);
		typedef void(QTimer::* TT)();
		timer->connect(
			timer,TT(&QTimer::timeout),
			[this, value__]() { this->start(value__); }
			);
		timer->start(fps_t_);
	}

}

PlayNumLine::PlayNumLine(QWidget * s):
	SuperType(s){

    auto * layout_ = new QHBoxLayout;
    this->setLayout(layout_);
    layout_->setMargin(0);
    layout_->setSpacing(0);
    button_ = new PlayNumLineStartButton;
    numline_ = new PlayNumLineEdit      ;
	timer =   0 ;
    layout_->addWidget( numline_ );
	layout_->addWidget( button_ );
    /*  */
    typedef void(QToolButton::* TTT)();
    button_->connect(
                button_,
                TTT(&QToolButton::clicked),
                this,
                &PlayNumLine::startPlay
                );
    numline_->setFixedWidth(100);
    numline_->setFixedHeight(20);
    button_->setFixedSize(QSize(20,20));
	this->setFixedWidth( 20+100 );
	this->setFixedHeight( 20 );
	numline_->setText( "25" );
}

PlayNumLine::~PlayNumLine(){

}

/*   */
