#include "wmmainwindow.h"
#include "ui_wmmainwindow.h"

#include <QSplashScreen>
#include <QDebug>
#include <QDir>
#include <QLabel>
#include <QMenu>

#include "Windows.h"
#include "wmlog.h"
#include "wmpluginloader.h"
#include "iuipluginsmanager.h"

WmMainWindow::WmMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WmMainWindow)
{
    ui->setupUi(this);

    initMainWindow();
}

WmMainWindow::~WmMainWindow()
{
    delete ui;
    ui = NULL;
}

void WmMainWindow::initMainWindow()
{
    qDebug() << "WmMainWindow::initMainWindow:" << menuBar() << menuWidget();
    m_uiMenu = ui->menuBar->addMenu("ui");
    m_taskMenu = ui->menuBar->addMenu("task");

    ui->statusbar->insertWidget(0, new QPushButton("o_O", ui->statusbar));
    ui->statusbar->insertWidget(1, new QLabel("0_0", ui->statusbar));

    //TestCode
    connect(WmLog::instance(), &WmLog::sendLogMsg, this, &WmMainWindow::testSlot);
    connect(ui->pushButton, &QPushButton::clicked, [this]()
    {
        qDebug() << QString::fromLocal8Bit("测试Test0123!@#$%^&*()");
    });

    //    QDir uiPluginPath(UIPLUGINS_PATH);
    //    QStringList uiPluginDlls;
    //    qDebug() << uiPluginPath.absolutePath();
    //    if (uiPluginPath.exists())
    //    {
    //        uiPluginDlls = uiPluginPath.entryList(QStringList("*dll"), QDir::Files);
    //        qDebug() << UIPLUGINS_PATH << uiPluginDlls;
    //    }
    //    foreach (auto strUiplugin, uiPluginDlls)
    //    {
    //        qDebug() << strUiplugin;
    //        WmPluginLoader<IUiPluginsManager> pLoader;
    //        if (!pLoader.loadPluginDll(QString(UIPLUGINS_PATH)+"/"+QString(strUiplugin)))
    //            continue;
    //        IUiPluginsManager *uiPluginManager = pLoader.pluginInstance();
    //        if (uiPluginManager == NULL)
    //            continue;
    //        foreach (auto var, uiPluginManager->uiPluginsList())
    //        {
    //            qDebug() << var->id() << var->name();
    //            var->getWidget(ui->dockWidget);
    //        }
    //    }
}

void WmMainWindow::testSlot(const QVariant &var)
{
    if (ui->textEdit->toPlainText().size() > 10000)
        ui->textEdit->clear();
    if (ui != NULL)
        ui->textEdit->append(var.toString());
}
