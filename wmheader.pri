
#TARGET = WmHeader
#TEMPLATE = lib
#DESTDIR = ../bin

#QT += core
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets widgets-private
#greaterThan(QT_MAJOR_VERSION, 4) {
#    QT += designer
#} else {
#    CONFIG += designer
#}

#CONFIG += plugin debug_and_release

HEADERS += wmheader/wmglobal.h \
wmheader/iuipluginsmanager.h \
wmheader/icore.h \
wmheader/iapplication.h \
wmheader/itaskpluginsmanager.h \
wmheader/wmexport.h \
wmheader/isignalengine.h \
wmheader/icommonsignal.h
