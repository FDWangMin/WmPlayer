#include "wmcore.h"
#include "wmlog.h"
#include "wmapplication.h"
#include "wmmainwindow.h"
#include "wmsignalengine.h"
#include "wmpluginloader.h"
#include "iuipluginsmanager.h"
#include "itaskpluginsmanager.h"

#include <QSplashScreen>
#include <QDebug>
#include <QDir>
#include <QDockWidget>
#include <QGridLayout>
#include <QMenu>

WmCore::WmCore()
{

}

WmCore::~WmCore()
{
    WmPluginLoader<IUiPluginsManager>::unloadPluginsMap();
    WmPluginLoader<ITaskPluginsManager>::unloadPluginsMap();
}

void WmCore::initCore(WmApplication *app)
{
    m_app = app;

    WmLog::instance()->startLog();
    m_log = WmLog::instance();

    initSignalEngine();
    initSplashScreen();
    initMainWindow();

    loadPlugins();

    dynamicConnectSigSlot();
}

void WmCore::initSignalEngine()
{
    m_sigEngine.reset(new WmSignalEngine);
    m_uiTaskSigEngine.reset(new WmUiTaskSignalEngine);
}

void WmCore::initSplashScreen()
{
    //???：无法加载资源文件内图片,暂且先加载exe同目录下文件
    QPixmap pixmap(SPLASH_PIXMAP_PATH);
    qDebug() << "WmCore::initSplashScreen:" << pixmap.size();
    m_splashScreen.reset(new QSplashScreen(pixmap));
    m_splashScreen->show();
    m_splashScreen->showMessage("Loading Plugins...... ", Qt::AlignLeft|Qt::AlignBottom);
}

void WmCore::initMainWindow()
{
    m_mainWindow.reset(new WmMainWindow);
}

void WmCore::uninitCore()
{

}

void WmCore::loadPlugins()
{
    loadTaskPlugins(TASKPLUGINS_PATH);
    loadUiPlugins(UIPLUGINS_PATH);
    m_splashScreen->finish(m_mainWindow.data());
}

void WmCore::loadUiPlugins(const QString &strPath)
{
    QDir pluginPath(strPath);
    QStringList strPluginDlls;
    qDebug() << strPath << pluginPath.absolutePath();
    if (pluginPath.exists())
    {
        strPluginDlls = pluginPath.entryList(QStringList("*dll"), QDir::Files);
        qDebug() << strPluginDlls;
    }

    foreach (auto strUiplugin, strPluginDlls)
    {
        m_splashScreen->showMessage(QString("Loading Plugin : %1").arg(strUiplugin), Qt::AlignLeft|Qt::AlignBottom);
        WmPluginLoader<IUiPluginsManager> pLoader;
        if (!pLoader.loadPluginDll(strPath+"/"+QString(strUiplugin)))
            continue;
        IUiPluginsManager *uiPluginManager = pLoader.pluginInstance();
        if (uiPluginManager == NULL)
            continue;
        uiPluginManager->initialize(this);
        foreach (auto var, uiPluginManager->uiPluginsList())
        {
            qDebug() << var->id() << var->name();

            m_mainWindow->m_uiMenu->addAction(var->name(), [this, var]()
            {
                QDockWidget *newDWgt = new QDockWidget(m_mainWindow.data());
                IWidget *iWgt = var->getIWidget(newDWgt, IUiPlugin::NewCreate);
                newDWgt->setWidget(iWgt);
                newDWgt->setWindowTitle(var->name());
                if (var->id()%2 == true)
                    m_mainWindow->addDockWidget(Qt::LeftDockWidgetArea, newDWgt);
                else
                    m_mainWindow->addDockWidget(Qt::RightDockWidgetArea, newDWgt);
                //放入对应哈希表中
                m_uiTaskSigEngine->insertMultiHashIWidget(var->id(), iWgt);
                m_hashIUiPlugin.insert(var->id(), var);
                dynamicConnectSigSlot();
            });
        }
    }
}

void WmCore::loadTaskPlugins(const QString &strPath)
{
    QDir pluginPath(strPath);
    QStringList strPluginDlls;
    qDebug() << strPath << pluginPath.absolutePath();
    if (pluginPath.exists())
    {
        strPluginDlls = pluginPath.entryList(QStringList("*dll"), QDir::Files);
        qDebug() << strPluginDlls;
    }
    foreach (auto strTaskplugin, strPluginDlls)
    {
        m_splashScreen->showMessage(QString("Loading Plugin : %1").arg(strTaskplugin), Qt::AlignLeft|Qt::AlignBottom);
        WmPluginLoader<ITaskPluginsManager> pLoader;
        if (!pLoader.loadPluginDll(strPath+"/"+QString(strTaskplugin)))
            continue;
        ITaskPluginsManager *taskPluginManager = pLoader.pluginInstance();
        if (taskPluginManager == NULL)
            continue;
        taskPluginManager->initialize(this);
        foreach (auto var, taskPluginManager->taskPluginsList())
        {
            qDebug() << var->id() << var->name();
            ITaskProcess *iTP = var->getTaskProcessing(this);
            //放入对应哈希表中
            m_uiTaskSigEngine->insertHashITaskProcess(var->id(), iTP);
            m_sigEngine->insertHashITaskProcess(var->id(), iTP);
            m_hashITaskPlugin.insert(var->id(), var);
            m_mainWindow->m_taskMenu->addAction(var->name(), [this, var]()
            {
                qDebug() << var->id() << var->name() << var->group() << var->toolTip() << var->whatsThis();
            });
        }
    }
}

WmApplication* WmCore::getAppInfo()
{
    return m_app;
}

WmMainWindow* WmCore::getMainWindow()
{
    return m_mainWindow.data();
}

ICommonSignal *WmCore::getCommonSignal(const QString &strKey, const PluginIdEnum &piEnum)
{
    return m_sigEngine->getCommonSignal(strKey, piEnum);
}

void WmCore::dynamicConnectSigSlot()
{
    foreach (auto var, m_hashIUiPlugin.values())
    {
        foreach (auto id, var->connectTaskPluginIds())
        {
            m_uiTaskSigEngine->connectUTByIdSigSlot(var->id(), id);
        }
        foreach (auto id, var->connectUiPluginIds())
        {
            m_uiTaskSigEngine->connectUUByIdSigSlot(var->id(), id);
        }
    }
}

//bool WmCore::regUiSigSlot(IWidget *wgt)
//{
//    return false;
//}

//bool WmCore::regTaskSigSlot(ITaskProcess *tprocess)
//{
//    return false;
//}

