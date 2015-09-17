
#ifndef __LINE__PLAY__num__hpp__
#define __LINE__PLAY__num__hpp__

class QToolButton;
class QLineEdit;
#include <QTimer>
#include <QWidget>


class PlayNumLine : public QWidget {
    Q_OBJECT
public:

    typedef PlayNumLine ThisType ;
    typedef QWidget SuperType    ;

    PlayNumLine( QWidget * =0 );
    ~PlayNumLine();

signals:
    void start( int );
	
public slots:
    void startPlay();
	void stopPlay() {
		if (timer) { timer->stop(); }
	}

private:
    QToolButton * button_;
    QLineEdit   * numline_;
	QTimer      * timer;
};


#endif

