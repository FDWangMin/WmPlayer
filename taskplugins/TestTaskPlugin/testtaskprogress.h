#ifndef TESTTASKPROGRESS_H
#define TESTTASKPROGRESS_H
#include "wtaskprocess.h"
#include <QMutex>
#include <QThread>
#include <QThreadPool>

class LongRunningOperationsWork : public QObject
{
    Q_OBJECT

public :
    LongRunningOperationsWork(){m_i = 0;}
    ~LongRunningOperationsWork();

public slots:
    void LongRunningFun1(const QVariant &var);
    void LongRunningFun2(const QVariant &var);

signals:
    void LongRunningFinished(int i);

private:
    QMutex m_mutex;
    int m_i;
};

class TestTaskProgress : public WTaskProcess
{
    Q_OBJECT

public:
    TestTaskProgress(QObject *parent = 0);
    ~TestTaskProgress();

    void initialize();

    void taskProcessOne(const QVariant &var, bool bThread);
    void taskProcessTwo(const QVariant &var, bool bThread);

signals:
    void operateLTSignalOne(const QVariant &var);
    void operateLTSignalTwo(const QVariant &var);

public slots:
    void dispatchTaskSigSlot(const TaskSigTypeEnum &tstEnum, const QVariant &var, bool bThread = false);

    void longRunningFinishedSlot(int i);

private:
    QThreadPool m_workerThreadPool;
    QThread m_workerThread;//最好用一个线程池
    LongRunningOperationsWork m_worker;
    QObject *m_curSender;
    TaskSigTypeEnum m_curTaskId;
};

#endif // TESTTASKPROGRESS_H
