#include "wmmainwindow.h"
#include "ui_wmmainwindow.h"

#include <QSplashScreen>
#include <QDebug>

#include "Windows.h"

WmMainWindow::WmMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WmMainWindow)
{
    ui->setupUi(this);

    //???：无法加载资源文件内图片,暂且先加载exe同目录下文件
    QPixmap pixmap("./resource/app/wmplayer1.png");
//    QPixmap pixmap;
//    bool isLoad = pixmap.load(":/../resource/app/wmplayer1.png"/*"D:/JYD/QtWmDemo/WmPlayer/resource/app/wmplayer1.png*/");
    qDebug() << pixmap.size();
    //加载图片
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage("Loaded modules", Qt::AlignLeft|Qt::AlignBottom);
    Sleep(100);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            qDebug() << i << j;
            splash.showMessage(QString("Established connections %1 %2").arg(i).arg(j), Qt::AlignLeft|Qt::AlignBottom);
            Sleep(100);
        }
    }
    splash.finish(this);
}

WmMainWindow::~WmMainWindow()
{
    delete ui;
}
