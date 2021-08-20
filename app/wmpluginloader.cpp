#include "wmpluginloader.h"

#include <QPluginLoader>
#include <QDebug>

template <typename IPluginInstance>
QMap<QString, QPluginLoader*> WmPluginLoader<IPluginInstance>::sm_loadedPluginsMap;

template <typename IPluginInstance>
bool WmPluginLoader<IPluginInstance>::loadPluginDll(const QString &strPath)
{
    QString strDllName = strPath.split("/").last();
    if (!sm_loadedPluginsMap.keys().contains(strDllName))
    {
        QPluginLoader *pLoader = new QPluginLoader(strPath);

        if (!pLoader->load())
        {
            qDebug() << QString("QPluginLoader::load(%1) Failed!").arg(strPath) << pLoader->errorString();
            delete pLoader;
            pLoader = NULL;
            return false;
        }

        m_ipluginInstance = qobject_cast<IPluginInstance*>(pLoader->instance());
        if (m_ipluginInstance == NULL)
        {
            qDebug() << strPath << " pLoader->instance() is not valid (qobject_cast<IPluginInstance*> == NULL)";
            pLoader->unload();
            delete pLoader;
            pLoader = NULL;
            return false;
        }

        sm_loadedPluginsMap.insert(strDllName, pLoader);
        qDebug() << QString("QPluginLoader::load(%1) Success ^_^").arg(strDllName);
        qDebug() << qobject_interface_iid<IPluginInstance*>() << pLoader->metaData();
    }
    else
    {
        qDebug() << QString("(%1) Already Loaded! >_<").arg(strPath);
    }

    return true;
}


