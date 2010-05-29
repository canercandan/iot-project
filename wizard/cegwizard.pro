CONFIG += debug
TEMPLATE = app
TARGET = CegWizard
DEPENDPATH += . \
    headers \
    src \
    ui
INCLUDEPATH += . \
    headers

# Inputs
HEADERS += headers/iotwizard.h \
headers/cegwizard.h \
headers/licensepage.h

FORMS += ui/licensepage.ui

SOURCES += src/main.cpp \
src/iotwizard.cpp \
src/cegwizard.cpp \
src/licensepage.cpp

# Output
DESTDIR = .
OBJECTS_DIR = obj
MOC_DIR = moc
UI_SOURCES_DIR = ui
UI_HEADERS_DIR = headers
