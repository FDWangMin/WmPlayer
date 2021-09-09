#include "wtaskprocess.h"
#include "iuipluginsmanager.h"
#include "icommonsignal.h"
#include <QDebug>
#include <QMetaMethod>

WTaskProcess::WTaskProcess(QObject *parent) :
    ITaskProcess(parent)
{

}

void WTaskProcess::initialize()
{
    qDebug() << "void WTaskProcess::initialize";
}

QList<TaskSigTypeEnum> WTaskProcess::getAvailableTaskIds() const
{
    QList<TaskSigTypeEnum> tstList;
    return tstList;
}

bool WTaskProcess::connectUiSigSlot(IWidget *iwgt)
{
    static const QMetaMethod mMethod = QMetaMethod::fromSignal(&WTaskProcess::returnUiSignal);
    bool bConnected = isSignalConnected(mMethod);
    int iConnectedNum = receivers(SIGNAL(returnUiSignal(const TaskSigTypeEnum &tstEnum, const QVariant &var, QObject *sender = NULL)));
    qDebug() << "void WTaskProcess::connectUiSigSlot" << bConnected << iConnectedNum;
    return connect(this, &WTaskProcess::returnUiSignal, iwgt, &IWidget::dispatchTask2UiSigSlot, Qt::ConnectionType(Qt::AutoConnection|Qt::UniqueConnection));
}

bool WTaskProcess::connectCommonSigSlot(ICommonSignal *iCom)
{
    static const QMetaMethod mMethod = QMetaMethod::fromSignal(&WTaskProcess::returnUiSignal);
    bool bConnected = isSignalConnected(mMethod);
    int iConnectedNum = receivers(SIGNAL(returnUiSignal(const TaskSigTypeEnum &tstEnum, const QVariant &var, QObject *sender = NULL)));
    qDebug() << "void WTaskProcess::connectCommonSigSlot" << bConnected << iConnectedNum;
    return connect(this, &WTaskProcess::returnUiSignal, iCom, &ICommonSignal::dispatchReturnSigSlot, Qt::ConnectionType(Qt::AutoConnection|Qt::UniqueConnection));
}

void WTaskProcess::dispatchTaskSigSlot(const TaskSigTypeEnum &tstEnum, const QVariant &var, bool bThread)
{
    qDebug() << "void WTaskProcess::dispatchTaskSigSlot";
}
