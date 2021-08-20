
#ifndef ICORE_H
#define ICORE_H

#include "wmglobal.h"

/* 类声明 */
class QString;
class QVariant;

class ILayOutElementBase;
class IFrameLayoutBase;
class IUiPlugin;
class ITaskPlugin;
class CSystem;

class WmApplication;
class WmMainWindow;

class IWidget;
class ITaskProcess;

/**
* @brief 程序调度引擎接口类
* 负责整个框架的调度，注册、显示
* 是IApp和子模块的桥梁
*/
class ICore
{
public:
    /*系统初始化,加载操作*/
    virtual void initCore(WmApplication *app) = 0;

    /*释放回收*/
    virtual void uninitCore(void) = 0;

    /*加载插件*/
    virtual void loadPlugins() = 0;

    //当前引擎所在App
    virtual WmApplication* getAppInfo() = 0;

    /*获取主窗体*/
    virtual WmMainWindow* getMainWindow() = 0;

//    /*注册Ui类插件*/
//    virtual bool regUiSigSlot(IWidget* wgt) = 0;

//    /*注册业务类插件*/
//    virtual bool regTaskSigSlot(ITaskProcess* tprocess) = 0;

    /*动态链接信号槽*/
    virtual void dynamicConnectSigSlot() = 0;

    /*注册布局窗口*/
    //virtual bool RegLayout(const QString &akey, IFrameLayoutBase *layoyut)=0;

    /*获取元素接口实例*/
    //virtual ILayOutElementBase* Getelemnet(const QString &akey)=0;

    /*获取窗口布局实例*/
    //virtual IFrameLayoutBase* GetLayout(const QString &akey)=0;

    /* 获取应用程序系统共享接口*/
    //virtual CSystem* GetSystem() = 0;

    /*创建布局窗口*/
    //virtual bool createFrame(enAppType enType) = 0;

    //线程池用于添加工作类
    //virtual void AddWorkItem(WorkItem * data_source, const QByteArray &  data)=0;

    /*发送自定义信号*/
    //virtual void sendGlobalSignal(int ete, QVariant v) = 0;
};

#endif // IMAINENGINE_H

