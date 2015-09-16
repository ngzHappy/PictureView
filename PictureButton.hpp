
#ifndef __PICTURE__BUTTOIN__s_
#define __PICTURE__BUTTOIN__s_

/*
 * 这应该是一个私有文件
*/

class PictureListView;

#include <QToolButton>

class PictureButton :
        public QToolButton {
    Q_OBJECT
public:

    typedef PictureButton ThisType ;
    typedef QToolButton SuperType ;

    explicit PictureButton(
            const QString & pictureName_,
            PictureListView*
            );
    ~PictureButton();

    const QString & getPictureName()const{return pictureName;}
    virtual void setPictureName(const QString &v){
		this->setToolTip( toolTipWord() +" : "+v );
		pictureName=v;
	}

	/* 需要重写的函数 */
	virtual QString toolTipWord()const { return  trUtf8(u8R"(视图)"); }
	virtual QString command() const { return ""; }
private:
	PictureListView * super;
    QString pictureName ;
};



#endif


