﻿#ifndef _9_PICTURE__MODEL__
#define _9_PICTURE__MODEL__

#include <QAbstractItemModel>
#include <QVariant>
#include <QString>
#include <vector>

class PictureModel :
        public QAbstractItemModel {
    Q_OBJECT
public:

    typedef QAbstractItemModel SuperType ;
    typedef PictureModel ThisType ;

    explicit PictureModel( QObject *  );
    PictureModel():PictureModel(nullptr){}
    ~PictureModel();

    /* 只有1列 */
    int	columnCount(const QModelIndex &   ) const override {
        return 1;
    }

    int rowCount(const QModelIndex &  ) const override{
        return int( data_.size() );
    }

    QModelIndex	index(
            int row,
            int column,
            const QModelIndex & p ) const override {
        if(row >= rowCount(p) ){ return QModelIndex(); }
        return this->createIndex(row,column);
    }

    QModelIndex	parent(const QModelIndex &  ) const {
        return QModelIndex();
    }

	enum {
		Suffix_Role = Qt::UserRole+1,
		CompleteBaseName_Role,
	};

    QVariant data(
            const QModelIndex & index,
            int role  ) const override ;

    class PictureModelItemData
    {
    public:
        ~PictureModelItemData(){}
        PictureModelItemData() {}

        QString filePath        ;
		QString suffix          ;
		QString completeBaseName;
		QString fileName()const { return completeBaseName + "." + suffix; }
    };

    typedef std::vector<PictureModelItemData> DataPoolType ;

    void setModel(DataPoolType && );
    void setModel(const DataPoolType & );
    void clearModel();

	/* 设置为公用函数 */
	using QAbstractItemModel::createIndex;

private:
    DataPoolType data_;
};


#endif


