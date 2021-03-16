include(../wmplayer.pri)

TEMPLATE = app
TARGET = WmPlayer
DESTDIR = ../bin

win32 {
RC_ICONS = wmplayer.ico
VERSION = $$WMPLAYER_VERSION
message("=> app.pro: $$PWD VERSION = $${VERSION}")
}

QT += concurrent widgets

contains(DEFINES, CONSOLE) {
    CONFIG += console
}

SOURCES += \
    main.cpp






