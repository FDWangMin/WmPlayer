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

    virtual const QVariant& execWaitResult(int iMs, TaskSigTypeEnum &iEnum);

signals:
    void toTPSignal(const TaskSigTypeEnum &iEnum, const QVariant& v, bool bThread = false);

public slots:
    virtual void dispatchReturnSigSlot(QObject *sender, int iEnum, const QVariant &var);

public:
    virtual bool connectTPSigSlot(ITaskProcess *itp);

private:
    QEventLoop m_eLoop;
    QTimer m_timer;
    int m_retEnum;
    QVariant m_retVar;
};


#endif // WCOMMONSIGNAL_H
