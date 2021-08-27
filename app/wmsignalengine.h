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

    ICommonSignal* getCommonSignal(const QString &strKey, const PluginIdEnum &piEnum);

    void sendSignal(const QString &key, const TaskSigTypeEnum &tstEnum, const QVariant &v, bool bThread = false);

    const QVariant& execWaitResult(const QString &strKey, int iMs, TaskSigTypeEnum &tstEnum);

    void connectSignalSlot(ICommonSignal *iCom, ITaskProcess *itps);

    QHash<QString, ICommonSignal *> getHashICommonSignal() const;

    void insertHashITaskProcess(int pluginId, ITaskProcess *iTp);

    QHash<int, ITaskProcess *> hashITaskProcess() const;

private:
    QHash<QString, ICommonSignal *> m_hashICommonSignal;
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
