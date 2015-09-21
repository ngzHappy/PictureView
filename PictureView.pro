
CONFIG   += c++14
QT       += core gui
QT       += widgets

#win32-msvc*{
#QMAKE_CXXFLAGS_EXCEPTIONS_ON = -EHa
#}

#QMAKE_CXXFLAGS += -g

TARGET = PictureView
TEMPLATE = app

CONFIG(debug,debug|release){
CONFIG += console
}

#sources
SOURCES += main.cpp\
        MainWindow.cpp \
    ItemView/AbstractItemWidgetDelegate.cpp \
    ItemView/AbstractItemWidgetView.cpp \
    PictureListView.cpp \
    PictureView.cpp \
    ExplorerLine.cpp \
    PictureModel.cpp \
    PictureDelegate.cpp \
    ImageReaderObject.cpp \
    PictureButton.cpp \
    PictureViewButton.cpp \
    PictureSelectedView.cpp \
    ExplorerNumLine.cpp \
    PlayerNumLine.cpp

#headers
HEADERS  += \
    ItemView/AbstractItemWidget.hpp \
    ItemView/AbstractItemWidgetDelegate.hpp \
    ItemView/AbstractItemWidgetView.hpp \
    ItemView/ItemWidgetView.hpp \
    MainWindow.hpp \
    PictureListView.hpp \
    PictureView.hpp \
    ExplorerLine.hpp \
    PictureModel.hpp \
    PictureDelegate.hpp \
    ImageReaderObject.hpp \
    PictureButton.hpp \
    PictureViewButton.hpp \
    PictureSelectedView.hpp \
    ExplorerNumLine.hpp \
    PlayerNumLine.hpp

INCLUDEPATH += $$PWD

MOC_DIR = $$PWD/moc

DISTFILES += \
    qwidgetbackingstore.zip


unix {
    QMAKE_LFLAGS += -Wl,-rpath .
}


