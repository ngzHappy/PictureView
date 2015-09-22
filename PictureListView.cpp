#include "PictureDelegate.hpp"
#include "PictureListView.hpp"
#include "PictureModel.hpp"
#include "ImageReaderObject.hpp"
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
	ImageReaderObject * imageReader;

    ThisPrivate(PictureListView * s):super(s){
		super->thisp = this;

		imageReader = new ImageReaderObject ;
        model = new PictureModel(super)     ;
        delegate = new AbstractItemWidgetDelegate(
                    super,
                    [ s ]()->AbstractItemWidget*{
                        return new PictureDelegate(s )  ;
                    },
                    super
                    );
				
        super->setItemDelegate(delegate);
		super->setItemWidgetModel(model);

    }

    ~ThisPrivate(){

		/* 隐藏主窗口 */
		super->hide() ;

		/* 删除所有widgets */
		auto * layout_ = super->layout();
		delete layout_ ;

		/* 删除 image reader */
		delete imageReader;
        imageReader =0;

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
			ans.insert("dds");
			ans.insert("gif");
			ans.insert("ico");
			ans.insert("mng");
			ans.insert("svg");
			ans.insert("tga");
			ans.insert("tiff");
			ans.insert("ebp");
            return std::move(ans);
        }();

        dataPool.reserve( all_list_.size() );

        for(const QFileInfo & i:all_list_){
            if(i.isFile()==false){continue;}
            auto && suffix = i.suffix().trimmed().toLower() ;
            if(pictureTypes.count(suffix)<=0){continue;}
            DT_ item_ ;
			item_.suffix = suffix                        ;
            item_.filePath = i.absoluteFilePath()        ;
			item_.completeBaseName = i.completeBaseName();
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
			model->clearModel()  ;
			model->deleteLater() ;
            model=0;
		}
		model = model_;

    }

};

 

PictureListView::PictureListView( QWidget * p ):
SuperType(p){
	/* 加快布局 */
	this->setUniformItemSizes(true);
	/* 竖直滚动条一直显示 */
	this->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	/* 水平滚动条永不显示 */
	this->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	/*  */
	{
		auto * vsb_ = this->verticalScrollBar();
		vsb_->setStyleSheet(R"(QScrollBar:vertical {width: 16px;})");
	}
	/* 初始化私有数据 */
    thisp = new ThisPrivate(this);
	/* 设置选择模式 */
	this->setSelectionMode( QListView::SelectionMode::ExtendedSelection );
}

void PictureListView::currentChanged(const QModelIndex &current, const QModelIndex &previous) {
	SuperType::currentChanged(current,previous);
	QString fileNamePath_0_ = thisp->model->data( current,Qt::DisplayRole ).toString();
	eval( QString("viewin:")+ fileNamePath_0_);
}

PictureListView::~PictureListView(){
    delete thisp;
}

void PictureListView::setPath(const QString & arg_path){
    thisp->setModel(arg_path);
	/* 加快布局 */
	this->setUniformItemSizes(true);
}
ImageReaderObject * PictureListView::getImageReader()const {
	return thisp->imageReader;
}

void PictureListView::selectionChanged(
        const QItemSelection &s_,
        const QItemSelection &d_){
    SuperType::selectionChanged(s_,d_);
    {
        QStringList ans_;
        const auto && source_ = this->selectedIndexes();
        auto * model__ = thisp->model ;
        for(const auto & i:source_){
           auto && tmp_ =
                   model__->data(i,Qt::DisplayRole).toString();
           ans_.push_back( std::move(tmp_) );
        }
        emit selectedChanged(ans_);
    }
}

QModelIndex PictureListView::createIndex(int i)const {
	
	if (0 == thisp) { return QModelIndex(); }
	if (0 == thisp->model) {return QModelIndex();}

	if ( i<0 ) {
		i += thisp->model->rowCount( QModelIndex() );
	}

	if (i<0) {
		return QModelIndex();
	}

	return thisp->model->createIndex(i,0);

}

/*  */

