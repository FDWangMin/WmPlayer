#ifndef WMPLUGINLOADER_H
#define WMPLUGINLOADER_H

#include <QMap>

class QPluginLoader;
class QString;

template <typename IPluginInstance>
class WmPluginLoader
{
public:
    WmPluginLoader()
    {
        m_ipluginInstance = NULL;
    }

    bool loadPluginDll(const QString &strPath);

    IPluginInstance* pluginInstance()
    {
        return m_ipluginInstance;
    }

    typedef QMap<QString, QPluginLoader*> LoadedPluginsMap;

    static const LoadedPluginsMap& loadedPluginsMap()
    {
        return sm_loadedPluginsMap;
    }

    static void unloadPluginsMap()
    {
        if (sm_loadedPluginsMap.size() > 0)
        {
            foreach (auto pLoader, sm_loadedPluginsMap.values())
            {
                qDebug() << "pLoader->unload()" << sm_loadedPluginsMap.key(pLoader);
                pLoader->unload();
                delete pLoader;
                pLoader = NULL;
            };
        }
    }

private:
    IPluginInstance* m_ipluginInstance;
    static LoadedPluginsMap sm_loadedPluginsMap;
};

#include "wmpluginloader.cpp"

#endif // WMPLUGINLOADER_H
