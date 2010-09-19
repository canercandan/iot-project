# type du binaire generer
TEMPLATE = app

# les modules utilises
QT += network \
    xml

# le language utilise
LANGUAGE = C++

# le nom du binaire
TARGET = ceg
DEPENDPATH += . \
    includes \
    includes/Action \
    src \
    src/Action
INCLUDEPATH += . \
    includes \
    includes/Action
FORMS += forms/settingsDialog.ui
HEADERS += AbstractItem.h \
    AbstractScene.h \
    BoxController.h \
    Box.h \
    BoxStyle.h \
    CegTcpServer.h \
    CustomItem.h \
    DefaultItem.h \
    GraphicItemFactory.h \
    ICommunicationGraphicalServer.h \
    IDomFactory.h \
    Layer.h \
    Logger.h \
    MainController.h \
    Menu.h \
    MenuItem.h \
    SettingsDialog.h \
    Systray.h \
    Utils.h \
    View.h \
    Window.h \
    ActionFactory.h \
    CancelAction.h \
    ClickAction.h \
    KeyboardAction.h \
    ExecMenuAction.h \
    IAction.h \
    MoveAction.h \
    PopMenuAction.h \
    ReadAction.h \
    ValidAction.h \
    ZoomAction.h \
    includes/Action/QuitAction.h \
    includes/Action/Action \
    includes/Action/ExecProcessAction.h \
    includes/WindowSystem.h \
    includes/Action/CloseAction.h \
    includes/BoxType.h \
    includes/ClickType.h
SOURCES += AbstractItem.cpp \
    AbstractScene.cpp \
    BoxController.cpp \
    Box.cpp \
    BoxStyle.cpp \
    CegTcpServer.cpp \
    CustomItem.cpp \
    DefaultItem.cpp \
    GraphicItemFactory.cpp \
    Layer.cpp \
    Logger.cpp \
    MainController.cpp \
    main.cpp \
    Menu.cpp \
    MenuItem.cpp \
    SettingsDialog.cpp \
    Systray.cpp \
    Utils.cpp \
    View.cpp \
    Window.cpp \
    ActionFactory.cpp \
    CancelAction.cpp \
    ClickAction.cpp \
    KeyboardAction.cpp \
    ExecMenuAction.cpp \
    MoveAction.cpp \
    PopMenuAction.cpp \
    ReadAction.cpp \
    ValidAction.cpp \
    ZoomAction.cpp \
    src/Action/QuitAction.cpp \
    src/Action/ExecProcessAction.cpp \
    src/Action/CloseAction.cpp
unix { 
    HEADERS += XWindowSystem.h
    SOURCES += XWindowSystem.cpp
    CONFIG += link_pkgconfig
    PKGCONFIG += xmu
}
win32 { 
    HEADERS += Win32Adaptor.h \
        Win32Explorer.h
    SOURCES += Win32Adaptor.cpp \
        Win32Explorer.cpp
}
CONFIG += warn_on
DESTDIR = build
OBJECTS_DIR = build
MOC_DIR = moc
UI_SOURCES_DIR = ui_src
UI_HEADERS_DIR = ui_includes

# les fichiers de ressources utilisees par l application
RESOURCES += resources/application.qrc
