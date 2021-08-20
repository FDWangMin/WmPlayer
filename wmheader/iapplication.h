#ifndef IAPPLICATION_H
#define IAPPLICATION_H

#include <QApplication>

class ICore;
class IMainWindow;

class IApplication
{
public:
    virtual void initialize() = 0;

    virtual ICore* getCore() = 0;

    virtual IMainWindow* getMainWindow() = 0;
};

#endif // IAPPLICATION_H
