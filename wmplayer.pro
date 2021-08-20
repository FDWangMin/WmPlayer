################################
#项目名称：
#项目构思：1.多功能 2.多内核 3.跨平台
################################
QT += core
#存放工程全局的一些预编译控制宏
include(wmplayer.pri)
include(wmheader.pri)

TEMPLATE = subdirs

SUBDIRS += \
    app \
    resource \
    common\
    commonapi \
    uiplugins \
    taskplugins

CONFIG += ordered

message("-> wmplayer.pro: CONFIG = $${CONFIG}")
message("-> wmplayer.pro: DEFINES = $${DEFINES}")
message("-> wmplayer.pro: CODECFORSRC = $${CODECFORSRC}")
message("-> wmplayer.pro: Qt Version = $${QT_VERSION}")
message("-> wmplayer.pro: VERSION = $${WMPLAYER_VERSION}")
message("-> wmplayer.pro: OUT_PWD = $${OUT_PWD}")
message("-> wmplayer.pro: PWD = $${PWD}")

