
#ifndef _2num_WXPLORER__LINW__
#define _2num_WXPLORER__LINW__

#include <QLineEdit>

class ExplorerNumLine :public QLineEdit{
    Q_OBJECT
public:

    ~ExplorerNumLine();
    explicit ExplorerNumLine(QWidget *);
    ExplorerNumLine():ExplorerNumLine(nullptr){}

    typedef ExplorerNumLine ThisType ;
    typedef QLineEdit SuperType ;
private:
};

#endif
