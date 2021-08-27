#include "wmsignalengine.h"
#include "iuipluginsmanager.h"
#include "itaskpluginsmanager.h"
#include "icommonsignal.h"
#include "wcommonsignal.h"
#include <QDebug>
#include <QString>

WmSignalEngine::~WmSignalEngine()
{
    foreach (auto var, m_hashICommonSignal.values())
    {
        m_hashICommonSignal.remove(m_hashICommonSignal.key(var));
        delete var;
    };
}

ICommonSignal *WmSignalEngine::getCommonSignal(const QString &strKey, const PluginIdEnum &piEnum)
{
    if (m_hashICommonSignal.contains(strKey))
        return m_hashICommonSignal.value(strKey);
    else
    {
        ICommonSignal *newComSig = new WCommonSignal;
        m_hashICommonSignal.insert(strKey, newComSig);
        connectSignalSlot(newComSig, m_hashITaskProcess.value(piEnum));
        return newComSig;
    }
}

void WmSignalEngine::sendSignal(const QString &strKey, const TaskSigTypeEnum &tstEnum, const QVariant &var, bool bThread)
{
    m_hashICommonSignal.value(strKey)->emitCommonSignal(tstEnum, var, bThread);
}

const QVariant& WmSignalEngine::execWaitResult(const QString &strKey, int iMs, TaskSigTypeEnum &tstEnum)
{
    return m_hashICommonSignal.value(strKey)->execWaitResult(iMs, tstEnum);
}

void WmSignalEngine::connectSignalSlot(ICommonSignal *iCom, ITaskProcess *itps)
{
    if (iCom == NULL || itps == NULL)
    {
        qDebug() << QString("Connect iCom:%1 and itps:%2 Failed!").arg((long)iCom).arg((long)itps);
        return;
    }

    iCom->connectTPSigSlot(itps);
    itps->connectCommonSigSlot(iCom);
}

QHash<QString, ICommonSignal *> WmSignalEngine::getHashICommonSignal() const
{
    return m_hashICommonSignal;
}

void WmSignalEngine::insertHashITaskProcess(int pluginId, ITaskProcess *iTp)
{
    m_hashITaskProcess.insert(pluginId, iTp);
}

QHash<int, ITaskProcess *> WmSignalEngine::hashITaskProcess() const
{
    return m_hashITaskProcess;
}


void WmUiTaskSignalEngine::connectUTSigSlot(IWidget *iwgt, ITaskProcess *itps)
{
    if (iwgt == NULL || itps == NULL)
    {
        qDebug() << QString("Connect iwgt:%1 and itps:%2 Failed!").arg((long)iwgt).arg((long)itps);
        return;
    }

    iwgt->connectTPSigSlot(itps);
    itps->connectUiSigSlot(iwgt);
}

void WmUiTaskSignalEngine::connectUTByIdSigSlot(int iwgtId, int itpsId)
{
   qDebug() << QString("connectUTSigSlotById : %1 %2").arg(iwgtId).arg(itpsId);
   foreach (auto iwgtPtr, m_multiHashIWidget.values(iwgtId))
   {
       connectUTSigSlot(iwgtPtr, m_hashITaskProcess.value(itpsId));
   }
}


void WmUiTaskSignalEngine::connectUUSigSlot(IWidget *iwgt1, IWidget *iwgt2)
{
    if (iwgt1 == NULL || iwgt2 == NULL)
    {
        qDebug() << QString("Connect iwgt1:%1 and iwgt2:%2 Failed!").arg((long)iwgt1, (long)iwgt2);
        return;
    }

    iwgt1->connectUiSigSlot(iwgt2);
}

void WmUiTaskSignalEngine::connectUUByIdSigSlot(int iwgtId1, int iwgtId2)
{
    qDebug() << QString("connectUUSigSlotById : %1 %2").arg(iwgtId1).arg(iwgtId2);
    foreach (auto iwgt2Ptr, m_multiHashIWidget.values(iwgtId2))
    {
        foreach (auto iwgt1Ptr, m_multiHashIWidget.values(iwgtId1))
        {
            connectUUSigSlot(iwgt1Ptr, iwgt2Ptr);
        }
    }
}

void WmUiTaskSignalEngine::insertMultiHashIWidget(int pluginId, IWidget *iWgt)
{
    m_multiHashIWidget.insert(pluginId, iWgt);
}

void WmUiTaskSignalEngine::insertHashITaskProcess(int pluginId, ITaskProcess *iTp)
{
    m_hashITaskProcess.insert(pluginId, iTp);
}

QMultiHash<int, IWidget *> WmUiTaskSignalEngine::multiHashIWidget() const
{
    return m_multiHashIWidget;
}

QHash<int, ITaskProcess *> WmUiTaskSignalEngine::hashITaskProcess() const
{
    return m_hashITaskProcess;
}


