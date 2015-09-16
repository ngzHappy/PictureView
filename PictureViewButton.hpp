#ifndef _view_PICTURE__BUTTOIN__s_
#define _view_PICTURE__BUTTOIN__s_

/*
 * 这应该是一个私有文件
*/
#include "PictureButton.hpp"

class PictureViewButton :
        public PictureButton {
    Q_OBJECT
public:

    PictureViewButton(const QString &, PictureListView* );
    ~PictureViewButton(  );

	virtual QString toolTipWord()const override{ return  trUtf8(u8R"(视图)"); }
	virtual QString command() const { 
		return QString("viewin:")+getPictureName();
	}

};


#endif

