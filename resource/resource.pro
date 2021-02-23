include(../wmplayer.pri)

TEMPLATE = lib
TARGET = WmResource
VERSION = $$WMPLAYER_VERSION
DESTDIR = ../bin

RESOURCES += \
    resource.qrc

