
#ifndef _1_PICTURE__VIEW__
#define _1_PICTURE__VIEW__

#include <QGraphicsView>

class PictureView : public QGraphicsView {
    Q_OBJECT
public:

    typedef PictureView ThisType ;
    typedef QGraphicsView SuperType ;
    class ThisPrivate ;

    explicit PictureView(QWidget *);
    PictureView():PictureView(nullptr){}
    ~PictureView();
public slots:
	void setPicture( const QString & );
protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    friend class ThisPrivate ;
    ThisPrivate * thisp =0;
};


#endif

