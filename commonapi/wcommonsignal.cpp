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
    m_retEnum = TST_UnknowTaskSig;
    m_retVar = QVariant();
    emit toTPSignal(iEnum, var, bThread);
}

const QVariant& WCommonSignal::execWaitResult(TaskSigTypeEnum &iEnum, int iMs)
{
    m_timer.start(iMs);
    m_eLoop.exec();
    iEnum = (TaskSigTypeEnum)m_retEnum;
    return m_retVar;
}

void WCommonSignal::dispatchReturnSigSlot(int iEnum, const QVariant &var, QObject *sender)
{
    //sender如果不是自己并且不为NULL直接返回
    //为NULL值说明这个信号是业务层发送给所有链接对象的
    if (sender != this && sender != NULL)
        return;

    m_retEnum = iEnum;
    m_retVar = var;
    m_timer.stop();
    m_eLoop.quit();

    qDebug() << "void WCommonSignal::dispatchReturnSigSlot" << sender << iEnum << var;
    emit fromTaskSignal((TaskSigTypeEnum)iEnum, var, sender);
}

bool WCommonSignal::connectTPSigSlot(ITaskProcess *itp)
{
    static const QMetaMethod mMethod = QMetaMethod::fromSignal(&WCommonSignal::toTPSignal);
    bool bConnected = isSignalConnected(mMethod);
    int iConnectedNum = receivers(SIGNAL(toTPSignal(const TaskSigTypeEnum &iEnum, const QVariant& v, bool bThread = false)));
    qDebug() << "void WCommonSignal::connectTPSigSlot" << bConnected << iConnectedNum;
    return connect(this, &WCommonSignal::toTPSignal, itp, &ITaskProcess::dispatchTaskSigSlot,
                   Qt::ConnectionType(Qt::AutoConnection|Qt::UniqueConnection));
}

bool WCommonSignal::connectFromTaskSigSlot(const QObject *receiver, const char *method)
{
    static const QMetaMethod mMethod = QMetaMethod::fromSignal(&WCommonSignal::fromTaskSignal);
    bool bConnected = isSignalConnected(mMethod);
    int iConnectedNum = receivers(SIGNAL(fromTaskSignal(const TaskSigTypeEnum &iEnum, const QVariant &var, QObject *sender)));
    qDebug() << "void WCommonSignal::connectFromTaskSigSlot(const QObject *receiver, const char *method)"
             << bConnected << iConnectedNum;
    return connect(this, SIGNAL(fromTaskSignal(TaskSigTypeEnum,QVariant,QObject*)), receiver, method,
                   Qt::ConnectionType(Qt::AutoConnection|Qt::UniqueConnection));
}
