#include "PictureDelegate.hpp"
#include "PictureListView.hpp"
#include "PictureModel.hpp"
#include <QFileInfo>
#include <QStandardPaths>
#include <QDir>
#include <set>
 
class PictureListView::ThisPrivate{
public:
    typedef PictureModel::DataPoolType DataPoolType;
    PictureListView * super ;
    PictureModel * model ;
    AbstractItemWidgetDelegate * delegate ;
    ThisPrivate(PictureListView * s):super(s){
		super->thisp = this;
        model = new PictureModel(super);
        delegate = new AbstractItemWidgetDelegate(
                    super,
                    [s]()->AbstractItemWidget*{
                        return new PictureDelegate(s) ;
                    },
                    super
                    );
				
        super->setItemDelegate(delegate);
		super->setItemWidgetModel(model);

    }

    ~ThisPrivate(){

    }

    void initData(
            DataPoolType & dataPool,
            const QString & path_){

        QDir dir_( path_ );
        dir_.setFilter( QDir::NoDot|QDir::NoDotDot|QDir::AllEntries );
        const auto && all_list_ = dir_.entryInfoList();
        typedef PictureModel::PictureModelItemData DT_;

        static const std::set<QString> pictureTypes=[](){
            std::set<QString> ans ;
            ans.insert("jpeg");
            ans.insert("jpg");
            ans.insert("png");
            ans.insert("bmp");
            return std::move(ans);
        }();

        dataPool.reserve( all_list_.size() );

        for(const QFileInfo & i:all_list_){
            if(i.isFile()==false){continue;}
            auto && suffix = i.suffix().trimmed().toLower() ;
            if(pictureTypes.count(suffix)<=0){continue;}
            DT_ item_ ;
            item_.filePath = i.absoluteFilePath();
            dataPool.push_back(item_);
        }

    }

    void setModel(const QString & arg_path){

        typedef PictureModel::DataPoolType DT_;
        DT_ data_pool ;
        initData(data_pool,arg_path);
		auto * model_ = new PictureModel(super);
		model_->setModel(data_pool);
	 
		super->setItemWidgetModel( model_ );
		
		if (model) {
			/* 立即删除model */
			delete model ;
		}
		model = model_;

    }

};


PictureListView::PictureListView( QWidget * p ):
SuperType(p){
    thisp = new ThisPrivate(this);
}

PictureListView::~PictureListView(){
    delete thisp;
}

void PictureListView::setPath(const QString & arg_path){
    thisp->setModel(arg_path);
}



/*  */

