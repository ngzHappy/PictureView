
#ifndef _2_WXPLORER__LINW__
#define _2_WXPLORER__LINW__


#include <QLineEdit>

class ExplorerLine :public QLineEdit{
    Q_OBJECT
public:

    ~ExplorerLine();
    explicit ExplorerLine(QWidget *);
    ExplorerLine():ExplorerLine(nullptr){}

    typedef ExplorerLine ThisType ;
    typedef QLineEdit SuperType ;
private:
};

#endif

