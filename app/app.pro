include(../wmplayer.pri)

TEMPLATE = app

TARGET = WmPlayer

DESTDIR = ../bin

contains(DEFINES, CONSOLE) {
    message("=> app.pro: CONFIG += console")
    CONFIG += console
}

win32:{
    message("=> app.pro: RC_ICON = app.ico")
    RC_ICONS = app.ico
}

SOURCES += \
    main.cpp


