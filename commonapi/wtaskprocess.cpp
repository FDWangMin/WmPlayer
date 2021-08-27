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

bool WTaskProcess::connectUiSigSlot(IWidget *iwgt)
{
    static const QMetaMethod mMethod = QMetaMethod::fromSignal(&WTaskProcess::returnUiSignal);
    bool bConnected = isSignalConnected(mMethod);
    qDebug() << "void WTaskProcess::connectUiSigSlot" << bConnected;
    return connect(this, &WTaskProcess::returnUiSignal, iwgt, &IWidget::dispatchTask2UiSigSlot, Qt::ConnectionType(Qt::AutoConnection|Qt::UniqueConnection));
}

bool WTaskProcess::connectCommonSigSlot(ICommonSignal *iCom)
{
    static const QMetaMethod mMethod = QMetaMethod::fromSignal(&WTaskProcess::returnUiSignal);
    bool bConnected = isSignalConnected(mMethod);
    qDebug() << "void WTaskProcess::connectCommonSigSlot" << bConnected;
    return connect(this, &WTaskProcess::returnUiSignal, iCom, &ICommonSignal::dispatchReturnSigSlot, Qt::ConnectionType(Qt::AutoConnection|Qt::UniqueConnection));
}

void WTaskProcess::dispatchTaskSigSlot(const TaskSigTypeEnum &tstEnum, const QVariant &var, bool bThread)
{
    qDebug() << "void WTaskProcess::dispatchTaskSigSlot";
}
