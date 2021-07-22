include(../wmplayer.pri)

TEMPLATE = app
TARGET = WmPlayer
DESTDIR = ../bin

#LIBS += -L../bin/ -lWmRes

win32 {
RC_ICONS = wmplayer.ico
VERSION = $$WMPLAYER_VERSION
message("=> app.pro: $$PWD VERSION = $${VERSION}")
}

QT += concurrent widgets gui

contains(DEFINES, CONSOLE) {
    CONFIG += console
}

SOURCES += \
    main.cpp \
    wmapplication.cpp \
    wmmainwindow.cpp

RESOURCES += \
    appres.qrc

HEADERS += \
    wmapplication.h \
    wmmainwindow.h

FORMS += \
    wmmainwindow.ui






