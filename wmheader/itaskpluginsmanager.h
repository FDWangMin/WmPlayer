#ifndef ITASKPLUGIN_H
#define ITASKPLUGIN_H

#include "qobject.h"
#include "qlist.h"
#include "wmglobal.h"

class QString;
class QVariant;
class IWidget;
class ICommonSignal;
class ICore;

class ITaskProcess : public QObject
{
    Q_OBJECT
public:
    ITaskProcess(QObject *parent = 0) : QObject(parent){}

    virtual void initialize() = 0;

public slots:
    virtual void dispatchTaskSigSlot(const TaskSigTypeEnum &tstEnum, const QVariant &var, bool bThread = false) = 0;

public:
    virtual bool connectUiSigSlot(IWidget *iwgt) = 0;
    virtual bool connectCommonSigSlot(ICommonSignal *iCom) = 0;
};

class ITaskPlugin
{
public:
    virtual ~ITaskPlugin() {}
    virtual ICore* getCore() const = 0;

    virtual int id() const = 0;
    virtual QString name() const = 0;
    virtual QString group() const = 0;
    virtual QString toolTip() const = 0;
    virtual QString whatsThis() const = 0;
//    virtual QIcon icon() const = 0;

    virtual ITaskProcess* getTaskProcessing(QObject *parent) = 0;
};
#define ITaskPlugin_iid "wm.ITaskPlugin"
Q_DECLARE_INTERFACE(ITaskPlugin, ITaskPlugin_iid)

class ITaskPluginsManager
{
public:
    virtual ~ITaskPluginsManager() {}
    virtual void initialize(ICore *core) = 0;
    virtual QList<ITaskPlugin*> taskPluginsList() const = 0;
};
#define ITaskPluginsManager_iid "wm.ITaskPluginsManager"
Q_DECLARE_INTERFACE(ITaskPluginsManager, ITaskPluginsManager_iid)

#endif
