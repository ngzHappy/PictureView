/* 标准c++库 */
#include <memory>
/* Qt库 */
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
/* 自定义库 */
#include "MainWindow.hpp"
#include "PictureListView.hpp"
#include "ExplorerLine.hpp"
#include "PictureView.hpp"


class MainWindow::ThisPrivate{
public:
    MainWindow * super ;
    PictureListView * pictureListView ;
    PictureView * pictureView ;
    ExplorerLine * explorerLine ;

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
            vlayout->addWidget(explorerLine);
            pictureView = new PictureView;
            vlayout->addWidget(pictureView);
            vlayout->setMargin(0);
            vlayout->setSpacing(0);
        }

        pictureListView->setFixedWidth(256);

        /* 连接信号槽 */
        explorerLine->connect(explorerLine, &ExplorerLine::editingFinished,
                              [this](){
            auto path_ = explorerLine->text() ;
            super->setPath( path_ );
            pictureListView->setPath( path_ );
        });

    }

    ~ThisPrivate(){

    }

    QString path ;
    QString picturePath ;

    void setPath(const QString & arg_path){
        path = arg_path;
        updatePath();
    }
    void setViewPicture(const QString & arg_picture){
        picturePath = arg_picture;
    }
    void updatePath(){

    }
};

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

/* 文件结束 */

