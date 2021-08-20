#ifndef WMAPPLICATION_H
#define WMAPPLICATION_H

#include <QApplication>

class ICore;
class WmMainWindow;
class WmLog;

class WmApplication : public QApplication
{
public:
    WmApplication(int &argc, char **argv, int = ApplicationFlags);

    void initialize();
};

#endif // WMAPPLICATION_H
