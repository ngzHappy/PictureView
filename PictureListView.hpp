
#ifndef __0__PICTURE__LIST__VIEW__
#define __0__PICTURE__LIST__VIEW__

#include <QListView>
#include <ItemView/ItemWidgetView.hpp>

class PictureListView :
        public ItemWidgetView<QListView> {
    Q_OBJECT
public:
    class ThisPrivate ;
    typedef ItemWidgetView<QListView> SuperType ;
    typedef PictureListView ThisType ;

    explicit PictureListView( QWidget *   );
    PictureListView( ):PictureListView(nullptr){}
    ~PictureListView();

public slots:
    void setPath(const QString &);
private:
    friend class ThisPrivate ;
    ThisPrivate * thisp =0 ;
};

#endif
