
CONFIG   += c++14
QT       += core gui
QT       += widgets

TARGET = PictureView
TEMPLATE = app


#sources
SOURCES += main.cpp\
        MainWindow.cpp \
    ItemView/AbstractItemWidgetDelegate.cpp \
    ItemView/AbstractItemWidgetView.cpp \
    PictureListView.cpp \
    PictureView.cpp \
    ExplorerLine.cpp \
    PictureModel.cpp \
    PictureDelegate.cpp

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
    PictureDelegate.hpp

INCLUDEPATH += $$PWD

