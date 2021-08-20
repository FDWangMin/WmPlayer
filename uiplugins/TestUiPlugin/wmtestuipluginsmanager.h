#ifndef WMTESTUIPLUGINSMANAGER_H
#define WMTESTUIPLUGINSMANAGER_H

#include "iuipluginsmanager.h"

#include "wmtestuiplugin.h"

class WmTestUiPluginsManager : public QObject, public IUiPluginsManager
{
    Q_OBJECT
    Q_INTERFACES(IUiPluginsManager)
    Q_PLUGIN_METADATA(IID IUiPluginsManager_iid)

public:
    ~WmTestUiPluginsManager()
    {
        foreach (auto var, m_uiPluginList)
        {
            delete var;
        };
    }

    void initialize(ICore *core)
    {
        m_uiPluginList.append(new WmTestUiPlugin(core));
        m_uiPluginList.append(new WmTestUiPluginTwo(core));
    }

    QList<IUiPlugin*> uiPluginsList() const
    {
        return m_uiPluginList;
    }
private:
    QList<IUiPlugin*> m_uiPluginList;
};

#endif // WMTESTUIPLUGINSMANAGER_H
