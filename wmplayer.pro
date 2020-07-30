################################
#项目名称：播放器
#项目构思：1.多功能 2.多内核 3.跨平台
#        4.
#项目版本：v1.0
################################

#存放工程全局的一些预编译控制宏
include(wmplayer.pri)

TEMPLATE = subdirs

SUBDIRS += \
    app

CONFIG += ordered

message("-> wmplayer.pro: CONFIG IS $${CONFIG}")
message("-> wmplayer.pro: DEFINES IS $${DEFINES}")
message("-> wmplayer.pro: CODECFORSRC IS $${CODECFORSRC}")
message("-> wmplayer.pro: Qt Version IS $${QT_VERSION}")
message("-> wmplayer.pro: VERSION IS $${VERSION}")
message("-> wmplayer.pro: $${OUT_PWD}")

