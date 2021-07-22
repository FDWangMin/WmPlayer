#ifndef WMAPPLICATION_H
#define WMAPPLICATION_H

#include <QApplication>

class WmApplication : public QApplication
{
public:
    WmApplication(int &argc, char **argv, int = ApplicationFlags);
};

#endif // WMAPPLICATION_H
