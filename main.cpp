#include "MainWindow.hpp"
#include <QApplication>
#include <QTextCodec>
#include <QImage>
#include <QDebug>

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

#ifdef _MSC_VER
/* set /eha */
//sigaction
#include <Windows.h>
void se_handle( unsigned int, struct _EXCEPTION_POINTERS* ) {
	throw -12340;
}
#endif

int main(int argc, char *argv[]) try{

#ifdef _MSC_VER
	_set_se_translator( &se_handle );
#endif

    /* 更改此处代码,如果系统编码不是GBK */
    QTextCodec::setCodecForLocale( QTextCodec::codecForName("GBK") );

    /* 程序主循环 */
    QApplication app(argc, argv);

	/* 强制图片插件加载 */
	forceImagePluginLoader();

    MainWindow widget;
    widget.show();
	
    return app.exec();
	
}catch (...) {
	qDebug() << "there is some core bug!!";
    return -9999;
}

/* 主文件结束 */
