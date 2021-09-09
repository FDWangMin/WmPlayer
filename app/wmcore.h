#ifndef WMCORE_H
#define WMCORE_H
#include <QObject>
#include <QHash>
#include <QMultiHash>
#include "icore.h"

class ISignalEngine;
class IUiTaskSignalEngine;
class WmApplication;
class WmMainWindow;
class WmLog;
class QSplashScreen;
class ICommonSignal;

//ToDo:全局单例
class WmCore : public QObject, public ICore
{
    Q_OBJECT

public:
    WmCore();
    ~WmCore();

    void initCore(WmApplication *app);
    void initSignalEngine();
    void initSplashScreen();
    void initMainWindow();

    void uninitCore(void);

    void loadPlugins();
    void loadUiPlugins(const QString& strPath);
    void loadTaskPlugins(const QString& strPath);

    WmApplication* getAppInfo();

    WmMainWindow* getMainWindow();

    ICommonSignal* getCommonSignal(const PluginIdEnum &piEnum);

    void dynamicConnectSigSlot();

private:
    WmApplication *m_app;
    WmLog *m_log;
    QScopedPointer<WmMainWindow> m_mainWindow;

    QScopedPointer<QSplashScreen> m_splashScreen;

    QScopedPointer<ISignalEngine> m_sigEngine;
//    ISignalEngine *m_sigEngine;
    QScopedPointer<IUiTaskSignalEngine> m_uiTaskSigEngine;

    QHash<int, IUiPlugin*> m_hashIUiPlugin;
    QHash<int, ITaskPlugin*> m_hashITaskPlugin;
};

#endif // WMCORE_H
