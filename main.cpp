#include "MainWindow.hpp"
#include <QApplication>
#include <QTextCodec>
#include <QImage>

namespace {
	void forceImagePluginLoader() {
		{
			QImage image_plugin_loader("null.png");
			(void)image_plugin_loader;
		}
		{
			QImage image_plugin_loader("null.jpeg");
			(void)image_plugin_loader;
		}
		{
			QImage image_plugin_loader("null.jpg");
			(void)image_plugin_loader;
		}
		{
			QImage image_plugin_loader("null.bmp");
			(void)image_plugin_loader;
		}
	}
}

int main(int argc, char *argv[])
{
    /* 更改此处代码,如果系统编码不是GBK */
    QTextCodec::setCodecForLocale( QTextCodec::codecForName("GBK") );

    /* 程序主循环 */
    QApplication app(argc, argv);

	/* 强制图片插件加载 */
	forceImagePluginLoader();

    MainWindow widget;
    widget.show();

    return app.exec();
	
}

/* 主文件结束 */
