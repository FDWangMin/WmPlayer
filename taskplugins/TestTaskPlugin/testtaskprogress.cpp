#include "testtaskprogress.h"
#include "iuipluginsmanager.h"
#include <QThread>
#include <QEventLoop>
#include <QDebug>

LongRunningOperationsWork::~LongRunningOperationsWork()
{
    qDebug() << "LongRunningOperationsWork::~LongRunningOperationsWork()";
}

void LongRunningOperationsWork::LongRunningFun1(const QVariant &var)
{
    qDebug() << "LongRunningFun1 New Thread:" << QThread::currentThread() << QThread::currentThreadId();
    for (m_i = 0; m_i < var.toInt(); m_i++)
    {
        QMutexLocker locker(&m_mutex);
        qDebug() << "TestTaskProgress::dispatchTaskSigSlot LongRunningFun1 bThread==true m_i = " << m_i;
    }
    QMutexLocker locker(&m_mutex);
    emit LongRunningFinished(m_i);
}

void LongRunningOperationsWork::LongRunningFun2(const QVariant &var)
{
    qDebug() << "LongRunningFun2 New Thread:" << QThread::currentThread() << QThread::currentThreadId();
    for (m_i = 0; m_i < var.toInt(); m_i++)
    {
        QMutexLocker locker(&m_mutex);
        qDebug() << "TestTaskProgress::dispatchTaskSigSlot LongRunningFun2 bThread==true m_i = " << m_i;
    }
    QMutexLocker locker(&m_mutex);
    emit LongRunningFinished(m_i);
}

TestTaskProgress::TestTaskProgress(QObject *parent) : WTaskProcess(parent)
{
    initialize();
}

TestTaskProgress::~TestTaskProgress()
{
    m_workerThread.wait();
    m_workerThread.quit();
}

void TestTaskProgress::initialize()
{
    m_worker.moveToThread(&m_workerThread);
    connect(this, &TestTaskProgress::operateLTSignalOne, &m_worker, &LongRunningOperationsWork::LongRunningFun1);
    connect(this, &TestTaskProgress::operateLTSignalTwo, &m_worker, &LongRunningOperationsWork::LongRunningFun2);
    connect(&m_worker, &LongRunningOperationsWork::LongRunningFinished, this, &TestTaskProgress::longRunningFinishedSlot);
    connect(&m_workerThread, &QThread::finished, [this]()
    {qDebug() << "m_workerThread, &QThread::finished";});
}

void TestTaskProgress::taskProcessOne(const QVariant &var, bool bThread)
{
    if (bThread == true)
    {
        if (m_workerThread.wait(2000))
        {
            m_workerThread.start();
            emit operateLTSignalOne(var);
            qDebug() << "emit operateLTSignal() Old Thread:" << QThread::currentThread() << QThread::currentThreadId();
        }
        else
        {
            qDebug() << "m_workerThread.wait()==false";
        }
    }
    else
    {
        for (int i = 0; i < 1000; i++)
        {
            qDebug() << "TestTaskProgress::taskProcessOne bThread==false i = " << i;
        }
    }
}

void TestTaskProgress::taskProcessTwo(const QVariant &var, bool bThread)
{
    if (bThread == true)
    {
        if (m_workerThread.wait(2000))
        {
            m_workerThread.start();
            emit operateLTSignalTwo(var);
            qDebug() << "emit operateLTSignal() Old Thread:" << QThread::currentThread() << QThread::currentThreadId();
        }
        else
        {
            qDebug() << "m_workerThread.wait()==false";
        }
    }
    else
    {
        for (int i = 0; i < 1000; i++)
        {
            qDebug() << "TestTaskProgress::taskProcessTwo bThread==false i = " << i;
        }
    }
}

void TestTaskProgress::dispatchTaskSigSlot(const TaskSigTypeEnum &tstEnum, const QVariant &var, bool bThread)
{
    qDebug() << "void TestTaskProgress::dispatchTaskSigSlot" << tstEnum << var << bThread;

    qDebug() << sender() << sender()->objectName();

    if (tstEnum != TST_TestTaskPgs1 && tstEnum != TST_TestTaskPgs2)
    {
        m_curTaskId = TST_UnknowTaskSig;
        return;
    }

    m_curSender = sender();
    m_curTaskId = tstEnum;//可以不记录
    switch (tstEnum)
    {
    case TST_TestTaskPgs1:
        taskProcessOne(var, bThread);
        break;
    case TST_TestTaskPgs2:
        taskProcessTwo(var, bThread);
        break;
    default:
        m_curTaskId = TST_UnknowTaskSig;
        break;
    }
}

void TestTaskProgress::longRunningFinishedSlot(int i)
{
    qDebug() << "longRunningFinishedSlot Old Thread:" << QThread::currentThread() << QThread::currentThreadId();
    m_workerThread.quit();
    qDebug() << "void TestTaskProgress::longRunningFinishedSlot" << i << m_workerThread.wait(2000);

    emit returnUiSignal(m_curSender, m_curTaskId, i);
}


