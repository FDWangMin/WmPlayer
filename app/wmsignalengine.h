#ifndef WMSIGNALENGINE_H
#define WMSIGNALENGINE_H

#include "isignalengine.h"
#include "wmglobal.h"
#include <QObject>

class ICommonSignal;

class WmSignalEngine : public ISignalEngine
{
public:
    ~WmSignalEngine();

    ICommonSignal* getCommonSignal(const PluginIdEnum &piEnum);

    void sendSignal(const PluginIdEnum &piEnum, const TaskSigTypeEnum &tstEnum, const QVariant &v, bool bThread = false);

    const QVariant& execWaitResult(const PluginIdEnum &piEnum, TaskSigTypeEnum &tstEnum, int iMs = 2000);


    void connectSignalSlot(ICommonSignal *iCom, ITaskProcess *itps);

    void insertHashITaskProcess(int pluginId, ITaskProcess *iTp);

    QHash<int, ITaskProcess *> hashITaskProcess() const;

    QHash<int, ICommonSignal *> getHashICommonSignal() const;

private:
    QHash<int, ICommonSignal *> m_hashICommonSignal;
    QHash<int, ITaskProcess *> m_hashITaskProcess;
};

class WmUiTaskSignalEngine : public IUiTaskSignalEngine
{
public:
    void connectUTSigSlot(IWidget *iwgt, ITaskProcess *itps);

    void connectUUSigSlot(IWidget *iwgt1, IWidget *iwgt2);

    void connectUTByIdSigSlot(int iwgtId, int itpsId);

    void connectUUByIdSigSlot(int iwgtId1, int iwgtId2);

    void insertMultiHashIWidget(int pluginId, IWidget *iWgt);

    void insertHashITaskProcess(int pluginId, ITaskProcess *iTp);

    QMultiHash<int, IWidget *> multiHashIWidget() const;

    QHash<int, ITaskProcess *> hashITaskProcess() const;

private:
    QMultiHash<int, IWidget *> m_multiHashIWidget;
    QHash<int, ITaskProcess *> m_hashITaskProcess;
};

#endif // WMSIGNALENGINE_H
