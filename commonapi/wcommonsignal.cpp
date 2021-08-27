#include "wcommonsignal.h"
#include "itaskpluginsmanager.h"
#include <QMetaMethod>
#include <QDebug>

void WCommonSignal::initialize()
{
    m_timer.setSingleShot(true);
    connect(&m_timer, &QTimer::timeout, &m_eLoop, &QEventLoop::quit);
}

void WCommonSignal::emitCommonSignal(const TaskSigTypeEnum &iEnum, const QVariant &var, bool bThread)
{
    m_retEnum = -1;
    m_retVar = QVariant();
    emit toTPSignal(iEnum, var, bThread);
}

const QVariant& WCommonSignal::execWaitResult(int iMs, TaskSigTypeEnum &iEnum)
{
    m_timer.start(iMs);
    m_eLoop.exec();
    iEnum = (TaskSigTypeEnum)m_retEnum;
    return m_retVar;
}

void WCommonSignal::dispatchReturnSigSlot(QObject *sender, int iEnum, const QVariant &var)
{
    if (sender != this)
        return;

    m_retEnum = iEnum;
    m_retVar = var;
    m_timer.stop();
    m_eLoop.quit();

    qDebug() << "void WCommonSignal::dispatchReturnSigSlot" << sender << iEnum << var;
}

bool WCommonSignal::connectTPSigSlot(ITaskProcess *itp)
{
    static const QMetaMethod mMethod = QMetaMethod::fromSignal(&WCommonSignal::toTPSignal);
    bool bConnected = isSignalConnected(mMethod);
    qDebug() << "void WCommonSignal::connectTPSigSlot" << bConnected;
    return connect(this, &WCommonSignal::toTPSignal, itp, &ITaskProcess::dispatchTaskSigSlot, Qt::ConnectionType(Qt::AutoConnection|Qt::UniqueConnection));
}
