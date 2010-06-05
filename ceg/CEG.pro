TEMPLATE = app
QT += network \
    xml
LANGUAGE = C++
TARGET = 
DEPENDPATH += . \
    includes \
    src
INCLUDEPATH += . \
    includes
HEADERS += includes/AbstractItem.h \
    includes/AbstractScene.h \
    includes/DefaultItem.h \
    includes/Layer.h \
    includes/Window.h \
    includes/GraphicItemFactory.h \
    includes/ICommunicationGraphicalServer.h \
    includes/IAction.h \
    includes/ZoomAction.h \
    includes/ClickAction.h \
    includes/View.h \
    includes/MoveAction.h \
    includes/ReadAction.h \
    includes/ActionFactory.h \
    includes/Menu.h \
    includes/MenuItem.h \
    includes/EventMenuAction.h \
    includes/Utils.h \
    includes/Systray.h \
    includes/Box.h \
    includes/IDomFactory.h \
    includes/BoxStyle.h \
    includes/CegTcpServer.h \
    includes/CustomItem.h \
    includes/MainController.h \
    includes/BoxController.h
SOURCES += src/AbstractItem.cpp \
    src/AbstractScene.cpp \
    src/DefaultItem.cpp \
    src/Layer.cpp \
    src/main.cpp \
    src/Window.cpp \
    src/GraphicItemFactory.cpp \
    src/ZoomAction.cpp \
    src/ClickAction.cpp \
    src/View.cpp \
    src/MoveAction.cpp \
    src/ReadAction.cpp \
    src/ActionFactory.cpp \
    src/Menu.cpp \
    src/MenuItem.cpp \
    src/EventMenuAction.cpp \
    src/Utils.cpp \
    src/Systray.cpp \
    src/Box.cpp \
    src/BoxStyle.cpp \
    src/CegTcpServer.cpp \
    src/CustomItem.cpp \
    src/BoxController.cpp \
    src/MainController.cpp
unix { 
    HEADERS += includes/XWindowSystem.h
    SOURCES += src/XWindowSystem.cpp
    CONFIG += link_pkgconfig
    PKGCONFIG += xmu
}
win32 { 
    HEADERS += includes/Win32Adaptor.h \
        includes/Win32Explorer.h
    SOURCES += src/Win32Adaptor.cpp \
        src/Win32Explorer.cpp
    //LIBS += "C:\Program Files\Microsoft SDKs\Windows\v7.0A\Lib\Psapi.Lib"
}
CONFIG += warn_on
DESTDIR = build
OBJECTS_DIR = build
MOC_DIR = moc
UI_SOURCES_DIR = ui_src
UI_HEADERS_DIR = ui_includes
RESOURCES += resources/images.qrc
