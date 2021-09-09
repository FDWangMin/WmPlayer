#ifndef WCOMMONSIGNAL_H
#define WCOMMONSIGNAL_H
#include "wmexport.h"
#include "icommonsignal.h"

#include <QEventLoop>
#include <QTimer>
#include <QVariant>

class ITaskProcess;
enum TaskSigTypeEnum;

class WM_EXPORT_DLL WCommonSignal : public ICommonSignal
{
    Q_OBJECT

public:
    WCommonSignal(QObject *parent = 0) : ICommonSignal(parent){initialize();}

    virtual void initialize();

    virtual void emitCommonSignal(const TaskSigTypeEnum &iEnum, const QVariant &var, bool bThread = false);

    virtual const QVariant& execWaitResult(TaskSigTypeEnum &iEnum, int iMs = 2000);

signals:
    void toTPSignal(const TaskSigTypeEnum &iEnum, const QVariant& v, bool bThread = false);

    void fromTaskSignal(const TaskSigTypeEnum &iEnum, const QVariant &var, QObject *sender);

public slots:
    virtual void dispatchReturnSigSlot(int iEnum, const QVariant &var, QObject *sender);

public:
    virtual bool connectTPSigSlot(ITaskProcess *itp) final;
    virtual bool connectFromTaskSigSlot(const QObject *receiver, const char *method) final;

private:
    QEventLoop m_eLoop;
    QTimer m_timer;
    int m_retEnum;
    QVariant m_retVar;
};


#endif // WCOMMONSIGNAL_H
