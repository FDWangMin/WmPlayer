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
    virtual QList<TaskSigTypeEnum> getAvailableTaskIds() const override;

public slots:
    void dispatchTaskSigSlot(const TaskSigTypeEnum &tstEnum, const QVariant &var, bool bThread = false) override;

signals:
    void returnUiSignal(const TaskSigTypeEnum &tstEnum, const QVariant &var, QObject *sender = NULL);

public:
    //不需要子类实现
    bool connectUiSigSlot(IWidget *iwgt) final;
    bool connectCommonSigSlot(ICommonSignal *iCom) final;
};

#endif // WTASKPROCESS_H
