#ifndef _7_PICTURE__SELECTED__VIEW__
#define _7_PICTURE__SELECTED__VIEW__

#include <QTextEdit>

class PictureSelectedView :
        public QTextEdit {
    Q_OBJECT
public:

    typedef QTextEdit SuperType ;
    typedef PictureSelectedView ThisType ;

    PictureSelectedView(QWidget * =0);
    ~PictureSelectedView();

};


#endif
