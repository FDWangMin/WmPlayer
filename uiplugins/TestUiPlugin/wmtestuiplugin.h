#ifndef WMTESTUIPLUGIN_H
#define WMTESTUIPLUGIN_H
#include "icore.h"
#include "iuipluginsmanager.h"

#include "testuipluginwidget.h"
#include "testuipluginform.h"

#include "wmglobal.h"

#include <QPointer>

class WmTestUiPlugin : public QObject, public IUiPlugin
{
    Q_OBJECT
    Q_INTERFACES(IUiPlugin)
    //Q_PLUGIN_METADATA(IID IUiPlugin_iid)

public:
    WmTestUiPlugin(ICore *core = 0){m_mainCore = core;}
    virtual ICore * getCore() const {return m_mainCore;}

    virtual int id() const {return UPIE_WmTestUiPluginId;}
    virtual QString name() const {return QString("WmTestUiPlugin");}
    virtual QString group() const {return QString("TestPlugin");}
    virtual QString toolTip() const {return QString("Test Plugin!");}
    virtual QString whatsThis() const {return QString("1.测试；2.还是测试");}
    virtual QList<int> connectTaskPluginIds() const
    {
        QList<int> taskIds;
        taskIds.append(TPIE_WmTestTaskPluginId);
        return taskIds;
    }
    virtual QList<int> connectUiPluginIds() const
    {
        QList<int> uiIds;
        uiIds.append(UPIE_WmTestUiPluginTwoId);
        return uiIds;
    }
    virtual IWidget *getIWidget(QWidget *parent, CreateMode mode = GetCreated)
    {
        if (mode == NewCreate)
        {
            m_curWdgt = QPointer<IWidget>((IWidget*)(new TestUiPluginWidget(parent, m_mainCore)));
//            m_mainCore->regUiSigSlot((IWidget*)m_curWdgt.data());
            return m_curWdgt.data();
        }
        else
        {
            if (m_curWdgt.isNull())
            {
                m_curWdgt = QPointer<IWidget>((IWidget*)(new TestUiPluginWidget(parent, m_mainCore)));
//                m_mainCore->regUiSigSlot((IWidget*)m_curWdgt.data());
            }
            return m_curWdgt.data();
        }
    }

private:
    ICore* m_mainCore;
    QPointer<IWidget> m_curWdgt;
};

class WmTestUiPluginTwo : public QObject, public IUiPlugin
{
    Q_OBJECT
    Q_INTERFACES(IUiPlugin)
    //Q_PLUGIN_METADATA(IID IUiPlugin_iid)
public:
    WmTestUiPluginTwo(ICore *core = 0){m_mainCore = core;}
    ICore * getCore() const {return m_mainCore;}

    int id() const {return UPIE_WmTestUiPluginTwoId;}
    QString name() const {return QString("WmTestUiPluginTwo");}
    QString group() const {return QString("TestPlugin");}
    QString toolTip() const {return QString("WmTestUiPluginTwo");}
    QString whatsThis() const {return QString("WmTestUiPluginTwo");}
    QList<int> connectTaskPluginIds() const
    {
        QList<int> taskIds;
        taskIds.append(TPIE_WmTestTaskPluginId);
        return taskIds;
    }
    QList<int> connectUiPluginIds() const
    {
        QList<int> uiIds;
        return uiIds;
    }
    IWidget *getIWidget(QWidget *parent, CreateMode mode = GetCreated)
    {
        if (mode == NewCreate)
        {
            m_curWdgt = QPointer<IWidget>((IWidget*)(new TestUiPluginForm(parent, m_mainCore)));
            return m_curWdgt.data();
        }
        else
        {
            if (m_curWdgt.isNull())
                m_curWdgt = QPointer<IWidget>((IWidget*)(new TestUiPluginForm(parent, m_mainCore)));
            return m_curWdgt.data();
        }
        return 0;
    }

private:
    ICore *m_mainCore;
    QPointer<IWidget> m_curWdgt;
};

#endif // WMTESTUIPLUGIN_H
