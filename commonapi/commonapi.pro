include(../wmplayer.pri)

QT       += core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WmCommonApi
TEMPLATE = lib
DESTDIR = ../bin

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += WM_EXPORT_DLL

INCLUDEPATH += ../wmheader/

HEADERS += \
    ../wmheader/itaskpluginsmanager.h \
    wtaskprocess.h \
    wmstreamrwxml.h

SOURCES += \
    wtaskprocess.cpp \
    wmstreamrwxml.cpp
