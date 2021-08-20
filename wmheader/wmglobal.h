#ifndef WMGLOBAL_H
#define WMGLOBAL_H

#define LOG_PATH "/wmlog"
#define UIPLUGINS_PATH      "./wmuiplugins"
#define TASKPLUGINS_PATH    "./wmtaskplugins"

#define SPLASH_PIXMAP_PATH "./resource/app/wmplayer1.png"

enum PluginIdEnum
{
    //Ui插件ID
    UPIE_ReservedId = 0,
    /*预留Ui插件ID 100个*/
    UPIE_WmTestUiPluginsManagerId = 101,
    UPIE_WmTestUiPluginId,       // 102
    UPIE_WmTestUiPluginTwoId,    // 103



    //业务插件ID从10000开始
    TPIE_ReservedId = 10000,
    /*预留业务插件ID 100个*/
    TPIE_WmTestTaskPluginsManagerId = 10101,
    TPIE_WmTestTaskPluginId,       // 10102
    TPIE_WmTestTaskPluginTwoId     // 10103
};

enum UiSigTypeEnum
{
    UST_UnknowUiSig         = 0,
    UST_TestUiPluginWgt1,   //1
    UST_TestUiPluginWgt2    //2
};


enum TaskSigTypeEnum
{
    TST_UnknowTaskSig       = 0,
    TST_TestTaskPgs1,       //1
    TST_TestTaskPgs2        //2
};

#endif
