
#ifndef __0__PICTURE__LIST__VIEW__
#define __0__PICTURE__LIST__VIEW__

#include <QListView>
#include <ItemView/ItemWidgetView.hpp>
#include <QString>
#include <QList>

class ImageReaderObject;

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

	ImageReaderObject * getImageReader()const;
	QModelIndex createIndex( int i )const;

public slots:
    void setPath(const QString &);
signals:
	void eval( const QString & );
    void selectedChanged(const QStringList &);
private:
    friend class ThisPrivate ;
    ThisPrivate * thisp =0 ;
protected:
    virtual void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)override;
	virtual void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;
};

#endif
