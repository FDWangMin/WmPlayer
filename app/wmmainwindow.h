#ifndef WMMAINWINDOW_H
#define WMMAINWINDOW_H

#include <QMainWindow>

class QMenu;

namespace Ui {
class WmMainWindow;
}

class WmMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WmMainWindow(QWidget *parent = 0);
    ~WmMainWindow();

    void initMainWindow();

    QMenu *m_uiMenu;
    QMenu *m_taskMenu;

public slots:
    void testSlot(const QVariant &var);

private:
    Ui::WmMainWindow *ui;
};

#endif // WMMAINWINDOW_H
