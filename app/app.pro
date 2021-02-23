include(../wmplayer.pri)

TEMPLATE = app
TARGET = WmPlayer
VERSION = $$WMPLAYER_VERSION
DESTDIR = ../bin

QT += concurrent widgets

contains(DEFINES, CONSOLE) {
    CONFIG += console
}

win32 {
    message("=> app.pro: RC_ICON = wmplayer.ico, VERSION = $${VERSION}")
    RC_ICONS = wmplayer.ico
    COPYRIGHT = "2019-$${WMPLAYER_COPYRIGHT_YEAR} The Wm Company Ltd"
    DEFINES += RC_VERSION=$$replace(WMPLAYER_VERSION, "\\.", ","),0 \
               RC_VERSION_STRING=\"$${WMPLAYER_VERSION}\" \
               RC_COPYRIGHT=\"$$replace(COPYRIGHT, " ", "\\x20")\"
#    RC_FILE = wmplpayer.rc
}

SOURCES += \
    main.cpp

#DISTFILES += wmplayer.rc

RESOURCES +=





