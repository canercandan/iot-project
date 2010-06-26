TEMPLATE = app
QT += network \
    xml
LANGUAGE = C++
TARGET =
DEPENDPATH += . \
    includes \
    includes/Action \
    src \
    src/Action
INCLUDEPATH += . \
    includes \
    includes/Action
FORMS += forms/settings.ui
HEADERS += AbstractItem.h \
    AbstractScene.h \
    DefaultItem.h \
    Layer.h \
    Window.h \
    GraphicItemFactory.h \
    ICommunicationGraphicalServer.h \
    IAction.h \
    ZoomAction.h \
    ClickAction.h \
    View.h \
    MoveAction.h \
    ReadAction.h \
    ActionFactory.h \
    Menu.h \
    MenuItem.h \
    Utils.h \
    Settings.h \
    Systray.h \
    Box.h \
    IDomFactory.h \
    BoxStyle.h \
    CegTcpServer.h \
    CustomItem.h \
    MainController.h \
    BoxController.h \
    PopMenuAction.h \
    ExecMenuAction.h
SOURCES += AbstractItem.cpp \
    AbstractScene.cpp \
    DefaultItem.cpp \
    Layer.cpp \
    main.cpp \
    Window.cpp \
    GraphicItemFactory.cpp \
    ZoomAction.cpp \
    ClickAction.cpp \
    View.cpp \
    MoveAction.cpp \
    ReadAction.cpp \
    ActionFactory.cpp \
    Menu.cpp \
    MenuItem.cpp \
    Utils.cpp \
    Settings.cpp \
    Systray.cpp \
    Box.cpp \
    BoxStyle.cpp \
    CegTcpServer.cpp \
    CustomItem.cpp \
    BoxController.cpp \
    MainController.cpp \
    PopMenuAction.cpp \
    ExecMenuAction.cpp
unix {
    HEADERS += XWindowSystem.h
    SOURCES += XWindowSystem.cpp
    CONFIG += link_pkgconfig
    PKGCONFIG += xmu liblog4cxx
}
win32 {
    HEADERS += Win32Adaptor.h \
	Win32Explorer.h
    SOURCES += Win32Adaptor.cpp \
	Win32Explorer.cpp
    //LIBS += "C:\Program Files\Microsoft SDKs\Windows\v7.0A\Lib\Psapi.Lib"
}
CONFIG += warn_on
DESTDIR = build
OBJECTS_DIR = build
MOC_DIR = moc
UI_SOURCES_DIR = ui_src
UI_HEADERS_DIR = ui_includes
RESOURCES += resources/application.qrc
