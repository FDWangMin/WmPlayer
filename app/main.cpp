
#include <QSplashScreen>
#include <QThread>
#include <QLabel>
#include <QMovie>
#include <QDebug>
#include <QPixmap>

#include "Windows.h"

#include "wmapplication.h"
#include "wmmainwindow.h"

const char ccAppName[] = "WmPlayer";

static void setHighDpiEnvironmentVariable()
{
    static const char ENV_VAR_QT_DEVICE_PIXEL_RATIO[] = "QT_DEVICE_PIXEL_RATIO";
    if (!qEnvironmentVariableIsSet(ENV_VAR_QT_DEVICE_PIXEL_RATIO) // legacy in 5.6, but still functional
            && !qEnvironmentVariableIsSet("QT_AUTO_SCREEN_SCALE_FACTOR")
            && !qEnvironmentVariableIsSet("QT_SCALE_FACTOR")
            && !qEnvironmentVariableIsSet("QT_SCREEN_SCALE_FACTORS"))
    {
        qDebug() << "QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);";
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    }
}

int main(int argc, char **argv)
{
    setHighDpiEnvironmentVariable();

    WmApplication app(argc, argv);
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);

    WmMainWindow mw;
    mw.show();

    return app.exec();
}
