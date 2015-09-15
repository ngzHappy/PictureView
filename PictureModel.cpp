
#include "PictureModel.hpp"
#include <QSize>

PictureModel::PictureModel( QObject *  p):
SuperType(p){

}

PictureModel::~PictureModel(){

}

void PictureModel::setModel(DataPoolType && d_){
    /* 删掉无用元素 */
    d_.shrink_to_fit();
    /* 重新设置模型 */
    this->beginResetModel();
    data_ = std::move(d_);
    this->endResetModel();
 
}

void PictureModel::setModel(const DataPoolType & d_){
    DataPoolType d__ = d_;
    setModel( std::move(d__) );
}

void PictureModel::clearModel(){
    this->beginResetModel();
    data_.clear();
    this->endResetModel();
}


QVariant PictureModel::data(
        const QModelIndex & index,
        int role  ) const{
    if(index.isValid()==false){ return QVariant(); }
    auto row_ = index.row();
    if(row_ >= rowCount(index) ){ return QVariant(); }
    const PictureModelItemData & id_ = data_[row_];
    switch (role) {
		case Qt::DisplayRole : return id_.filePath ;
		case Qt::SizeHintRole:return QSize(32,32);
    }
    return QVariant() ;
}

/*  */
