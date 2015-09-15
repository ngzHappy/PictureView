#include "MainWindow.hpp"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    /* 更改此处代码,如果系统编码不是GBK */
    QTextCodec::setCodecForLocale( QTextCodec::codecForName("GBK") );

    /* 程序主循环 */
    QApplication app(argc, argv);

    MainWindow widget;
    widget.show();

    return app.exec();

}

/* 主文件结束 */
