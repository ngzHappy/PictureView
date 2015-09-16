/* 标准c++库 */
#include <memory>
/* Qt库 */
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QDesktopServices>
#include <QSplitter>
#include <QRegExp>
/* 自定义库 */
#include "MainWindow.hpp"
#include "PictureListView.hpp"
#include "ExplorerLine.hpp"
#include "PictureView.hpp"
#include "PictureSelectedView.hpp"
#include "ExplorerNumLine.hpp"


class MainWindow::ThisPrivate{
public:
    MainWindow * super ;
    PictureListView * pictureListView ;
    PictureView * pictureView ;
    ExplorerLine * explorerLine ;
	PictureSelectedView * pictureSelectedView;
    ExplorerNumLine * explorerNumLine;

    ThisPrivate(MainWindow * p):super(p){
        p->setMinimumWidth(768);
        p->setMinimumHeight(256);
        pictureListView = new PictureListView ;
        auto * layout = new QHBoxLayout;
        p->setLayout(layout);

        layout->setMargin(0);
        layout->setSpacing(0);

        layout->addWidget(pictureListView);

        {
            auto * vlayout = new QVBoxLayout;
            layout->addLayout(vlayout);
            explorerLine = new ExplorerLine;
            explorerNumLine = new ExplorerNumLine ;
            {
                explorerNumLine->setFixedWidth(80);
                auto * layout_h_ = new QHBoxLayout;
                layout_h_->setMargin(0);
                layout_h_->setSpacing(0);
                layout_h_->addWidget(explorerLine);
                layout_h_->addWidget(explorerNumLine);
                vlayout->addLayout(layout_h_);
            }

			auto * splitter_ = new QSplitter(Qt::Vertical);
            pictureView = new PictureView;
			pictureSelectedView = new PictureSelectedView;
			splitter_->addWidget( pictureView );
			splitter_->addWidget( pictureSelectedView );
			pictureSelectedView->setMinimumHeight( 98 );
			pictureSelectedView->setMaximumHeight( 128 );
            vlayout->addWidget(splitter_);
            vlayout->setMargin(0);
            vlayout->setSpacing(0);
        }

        pictureListView->setFixedWidth(256);

        /* 连接信号槽 */
        explorerLine->connect(
			explorerLine, 
			&ExplorerLine::returnPressed, [this](){
            auto path_ = explorerLine->text() ;
            super->setPath( path_ );
        });

		explorerNumLine->connect(
			explorerNumLine,
			&ExplorerNumLine::returnPressed, [this]() {
			auto path_ = explorerNumLine->text();
			super->scrollTo( path_.toInt() );
		});

		pictureListView->connect(
			pictureListView, &PictureListView::eval,
			super, &MainWindow::eval);

		pictureListView->connect(
			pictureListView, &PictureListView::selectedChanged,
			super, &MainWindow::selectedChanged);

		super->resize(768,768);
    }

	void scrollTo(int i) {
		if (0 == pictureListView) { return; }
		auto index__ = pictureListView->createIndex(i);
		pictureListView->scrollTo(
			index__,
			QAbstractItemView::PositionAtCenter
			);

		pictureListView->setCurrentIndex(index__);

	}

    ~ThisPrivate(){

    }

    QString path ;       /* dir */
    QString picturePath ;/* picture view */

    void setPath(const QString & arg_path){
        path = arg_path;
        updatePath();
    }

    void setViewPicture(const QString & arg_picture){
        picturePath = arg_picture;
		pictureView->setPicture( arg_picture );
    }

    void updatePath(){
		pictureListView->setPath( path );
    }

};

void MainWindow::scrollTo(int i ) {
	thisp->scrollTo(i );
}

void MainWindow::selectedChanged(const QStringList & source_) {

	QString ans_;
	ans_.reserve( 1024 * 10);/* 预存10K */
	
	for (const auto & i:source_) {
		const int ans_index_ = i.lastIndexOf( QRegExp(R"([\\/])") );
		if (ans_index_ < 0) {
			ans_ += QString("\"") + i + QString("\" ");
		}
		else {
			ans_ += QString("\"") + i.mid(ans_index_+1) + QString("\" ");
		}
		
	}

	//if (ans_.isEmpty() == false){
	//	/* 删除最后一个, */
	//	ans_.resize(ans_.size() - 1);
	//}

	thisp->pictureSelectedView->setText( std::move( ans_ ) );

}

MainWindow::MainWindow(QWidget * p):SuperType(p){
    thisp = new ThisPrivate(this);
    /* 设置默认位置 */
	
}


MainWindow::~MainWindow(){
    delete thisp;
}

void MainWindow::setPath(const QString & arg_path){
    thisp->setPath(arg_path);
}

void MainWindow::setViewPicture(const QString & arg_picture){
    thisp->setViewPicture(arg_picture);
}

void MainWindow::updatePath(){
    thisp->updatePath();
}

void MainWindow::eval(const QString & command_) {

	if (command_.startsWith("viewin:")) {
		/* PictureViewButton::command */
		setViewPicture( command_.mid(7) );
		return;
	}
	

}

/* 文件结束 */

