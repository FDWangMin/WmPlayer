#ifndef WMMAINWINDOW_H
#define WMMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class WmMainWindow;
}

class WmMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WmMainWindow(QWidget *parent = 0);
    ~WmMainWindow();

private:
    Ui::WmMainWindow *ui;
};

#endif // WMMAINWINDOW_H
