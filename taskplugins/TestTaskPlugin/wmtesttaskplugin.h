#ifndef WMTESTTASKPLUGIN_H
#define WMTESTTASKPLUGIN_H
#include "testtaskprogress.h"
#include "itaskpluginsmanager.h"
#include "icore.h"
#include "wmglobal.h"

#include <QPointer>

class WmTestTaskPlugin : public QObject, public ITaskPlugin
{
    Q_OBJECT
    Q_INTERFACES(ITaskPlugin)
    //Q_PLUGIN_METADATA(IID ITaskPlugin_iid)

public:
    WmTestTaskPlugin(ICore *core = 0){m_mainCore = core;}
    ICore* getCore() const {return m_mainCore;}

    int id() const {return TPIE_WmTestTaskPluginId;}
    QString name() const {return QString("WmTestTaskPlugin");}
    QString group() const {return QString("TestTaskPlugin");}
    QString toolTip() const {return QString("TestTaskPlugin!");}
    QString whatsThis() const {return QString("1.测试；2.还是测试");}
    ITaskProcess* getTaskProcessing(QObject *parent)
    {
        if (m_curObj.isNull())
        {
            m_curObj = QPointer<ITaskProcess>((ITaskProcess*)(new TestTaskProgress(parent)));
        }
        return m_curObj.data();
    }


private:
    ICore* m_mainCore;
    QPointer<ITaskProcess> m_curObj;
};

class WmTestTaskPluginTwo : public QObject, public ITaskPlugin
{
    Q_OBJECT
    Q_INTERFACES(ITaskPlugin)
    //Q_PLUGIN_METADATA(IID ITaskPlugin_iid)
public:
    WmTestTaskPluginTwo(ICore *core = 0){m_mainCore = core;}
    ICore * getCore() const {return m_mainCore;}

    int id() const {return TPIE_WmTestTaskPluginTwoId;}
    QString name() const {return QString("WmTestTaskPluginTwo");}
    QString group() const {return QString("TestTaskPlugin");}
    QString toolTip() const {return QString("WmTestTaskPluginTwo");}
    QString whatsThis() const {return QString("WmTestTaskPluginTwo");}
    ITaskProcess* getTaskProcessing(QObject *parent)
    {
        if (m_curObj.isNull())
            m_curObj = (ITaskProcess*)(new WTaskProcess(parent));
        return m_curObj;
    }

private:
    ICore *m_mainCore;
    QPointer<ITaskProcess> m_curObj;
};


#endif // WMTESTTASKPLUGIN_H
