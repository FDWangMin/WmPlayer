#ifndef WTASKPROCESS_H
#define WTASKPROCESS_H
#include "wmexport.h"
#include "itaskpluginsmanager.h"

class ICommonSignal;

class WM_EXPORT_DLL WTaskProcess : public ITaskProcess
{
    Q_OBJECT

public:
    WTaskProcess(QObject *parent);

    //需要子类重写
    void initialize();
public slots:
    //需要子类重写
    void dispatchTaskSigSlot(const TaskSigTypeEnum &tstEnum, const QVariant &var, bool bThread = false);

signals:
    void returnUiSignal(QObject *sender, const TaskSigTypeEnum &tstEnum, const QVariant& v);

public:
    //不需要子类实现
    bool connectUiSigSlot(IWidget *iwgt);
    //不需要子类实现
    bool connectCommonSigSlot(ICommonSignal *iCom);
};

#endif // WTASKPROCESS_H
