#ifndef IUIPLUGIN_H
#define IUIPLUGIN_H

#include "qwidget.h"
#include "qobject.h"
#include "qlist.h"
#include "wmglobal.h"

class QObject;
class QString;
class ICore;
class ITaskProcess;

class IWidget : public QWidget
{
    Q_OBJECT

public:
    IWidget(QWidget *parent, ICore *core = 0) : QWidget(parent){}

    virtual void initialize() = 0;

public slots:
    virtual void dispatchTask2UiSigSlot(const TaskSigTypeEnum &tstEnum, const QVariant &var, QObject *sender) = 0;
    virtual void dispatchUi2UiSigSlot(const UiSigTypeEnum &ustEnum, const QVariant &var) = 0;

public:
    virtual bool connectTPSigSlot(ITaskProcess *itp) = 0;
    virtual bool connectUiSigSlot(IWidget *iwgt) = 0;
};

class IUiPlugin
{
public:
    enum CreateMode{GetCreated, NewCreate};

    virtual ~IUiPlugin() {}
    virtual ICore* getCore() const = 0;

    virtual int id() const = 0;
    virtual QString name() const = 0;
    virtual QString group() const = 0;
    virtual QString toolTip() const = 0;
    virtual QString whatsThis() const = 0;
//    virtual QIcon icon() const = 0;
    virtual QList<int> connectTaskPluginIds() const = 0;
    virtual QList<int> connectUiPluginIds() const = 0;

    virtual IWidget* getIWidget(QWidget *parent, CreateMode mode = GetCreated) = 0;
};
#define IUiPlugin_iid "wm.IUiPlugin"
Q_DECLARE_INTERFACE(IUiPlugin, IUiPlugin_iid)

class IUiPluginsManager
{
public:
    virtual ~IUiPluginsManager() {}
    virtual void initialize(ICore *core) = 0;
    virtual QList<IUiPlugin*> uiPluginsList() const = 0;
};
#define IUiPluginsManager_iid "wm.IUiPluginsManager"
Q_DECLARE_INTERFACE(IUiPluginsManager, IUiPluginsManager_iid)

#endif
