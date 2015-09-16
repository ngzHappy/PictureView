#include "ExplorerNumLine.hpp"


ExplorerNumLine::~ExplorerNumLine(){

}

ExplorerNumLine::ExplorerNumLine(QWidget * v):
SuperType(v){
	this->setToolTip(trUtf8(u8R"(定位到图片索引)"));
}

/**/

