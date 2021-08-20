include(../wmplayer.pri)

TEMPLATE = app
TARGET = WmPlayer
DESTDIR = ../bin

win32 {
RC_ICONS = wmplayer.ico
VERSION = $$WMPLAYER_VERSION
message("=> app.pro: $$PWD VERSION = $${VERSION}")
}

QT += concurrent widgets gui

contains(DEFINES, CONSOLE) {
    CONFIG += console
}

#LIBS += -L../bin/ -lWmCommon
INCLUDEPATH += ../wmheader/
INCLUDEPATH += ../common/

HEADERS += \
#    ../wmheader/itaskpluginsmanager.h \
#    ../wmheader/iuipluginsmanager.h \
    wmapplication.h \
    wmmainwindow.h \
    wmlog.h \
    wmpluginloader.h \
    wmcore.h \
    wmsignalengine.h

SOURCES += \
    main.cpp \
    wmapplication.cpp \
    wmmainwindow.cpp \
    wmlog.cpp \
    wmpluginloader.cpp \
    wmcore.cpp \
    wmsignalengine.cpp

FORMS += \
    wmmainwindow.ui

RESOURCES += \
    appres.qrc






