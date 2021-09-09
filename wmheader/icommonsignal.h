#ifndef ICOMMONSIGNAL_H
#define ICOMMONSIGNAL_H

#include <QObject>

class ITaskProcess;
enum TaskSigTypeEnum;

class ICommonSignal : public QObject
{
    Q_OBJECT

public:
    ICommonSignal(QObject *parent) : QObject(parent){}

    virtual void initialize() = 0;

    virtual void emitCommonSignal(const TaskSigTypeEnum &iEnum, const QVariant &var, bool bThread = false) = 0;

    //第一个值是传入参数，第二个值是传出参数
    virtual const QVariant& execWaitResult(TaskSigTypeEnum &iEnum, int iMs = 2000) = 0;

public slots:
    virtual void dispatchReturnSigSlot(int iEnum, const QVariant &var, QObject *sender) = 0;

public:
    virtual bool connectTPSigSlot(ITaskProcess *itp) = 0;
    virtual bool connectFromTaskSigSlot(const QObject *receiver, const char *method) = 0;
};

#endif  //ICOMMONSIGNAL_H
