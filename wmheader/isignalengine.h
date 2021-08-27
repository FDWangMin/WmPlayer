
#ifndef ISIGNALENGINE_H
#define ISIGNALENGINE_H

#include <QObject>
#include <QHash>
#include <QMultiHash>

/* 类声明 */
class QVariant;
class IWidget;
class ITaskProcess;
class ICommonSignal;
class QString;
enum TaskSigTypeEnum;
enum UiSigTypeEnum;
enum PluginIdEnum;

/* 负责整个框架的自定义信号量的注册和发送工作，随用随注册*/
class ISignalEngine
{
public:
    virtual ICommonSignal* getCommonSignal(const QString &strKey, const PluginIdEnum &piEnum) = 0;

    virtual void sendSignal(const QString &key, const TaskSigTypeEnum &evt, const QVariant &v, bool bThread = false) = 0;

    virtual const QVariant& execWaitResult(const QString &strKey, int iMs, TaskSigTypeEnum &tstEnum) = 0;

    virtual void connectSignalSlot(ICommonSignal *iCom, ITaskProcess *itps) = 0;

    virtual void insertHashITaskProcess(int pluginId, ITaskProcess *iTp) = 0;

    virtual QHash<int, ITaskProcess *> hashITaskProcess() const = 0;
};

/*Ui和业务层通信专用信号引擎*/
class IUiTaskSignalEngine
{
public:
    /*链接ui和task信号引擎*/
    virtual void connectUTSigSlot(IWidget* iwgt, ITaskProcess* itp) = 0;

    /*链接ui和ui信号引擎*/
    virtual void connectUUSigSlot(IWidget* iwgt1, IWidget* iwgt2) = 0;

    virtual void connectUTByIdSigSlot(int iwgtId, int itpsId) = 0;

    virtual void connectUUByIdSigSlot(int iwgtId1, int iwgtId2) = 0;

    virtual void insertMultiHashIWidget(int pluginId, IWidget *iWgt) = 0;

    virtual void insertHashITaskProcess(int pluginId, ITaskProcess *iTp) = 0;

    virtual QMultiHash<int, IWidget *> multiHashIWidget() const = 0;

    virtual QHash<int, ITaskProcess *> hashITaskProcess() const = 0;
};

#endif // ISIGNALENGINE_H
