#ifndef WMTESTTASKPLUGINSMANAGER_H
#define WMTESTTASKPLUGINSMANAGER_H

#include "itaskpluginsmanager.h"

#include "wmtesttaskplugin.h"

class WmTestTaskPluginsManager : public QObject, public ITaskPluginsManager
{
    Q_OBJECT
    Q_INTERFACES(ITaskPluginsManager)
    Q_PLUGIN_METADATA(IID ITaskPluginsManager_iid)

public:
    ~WmTestTaskPluginsManager()
    {
        foreach (auto var, m_taskPluginList)
        {
            delete var;
        };
    }

    virtual void initialize(ICore *core)
    {
        m_taskPluginList.append(new WmTestTaskPlugin(core));
        m_taskPluginList.append(new WmTestTaskPluginTwo(core));
    }

    virtual QList<ITaskPlugin*> taskPluginsList() const
    {
        return m_taskPluginList;
    }

private:
    QList<ITaskPlugin*> m_taskPluginList;
};


#endif // WMTESTTASKPLUGINSMANAGER_H
