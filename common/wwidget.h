#ifndef WWIDGET_H
#define WWIDGET_H
#include "wmexport.h"
#include "iuipluginsmanager.h"

#include <QWidget>

namespace Ui {
class WWidget;
}

class WM_EXPORT_DLL WWidget : public IWidget
{
    Q_OBJECT

public:
     WWidget(QWidget *parent, ICore *core = 0);
    ~WWidget();

    //子类需要重写
    void initialize();
public slots:
    //子类需要重写
    void dispatchTask2UiSigSlot(QObject *sender, const TaskSigTypeEnum &tstEnum, const QVariant &var);
    void dispatchUi2UiSigSlot(const UiSigTypeEnum &ustEnum, const QVariant &var);

signals:
    void toTPSignal(const TaskSigTypeEnum &tstEnum, const QVariant& v, bool bThread = false);
    void toUiSignal(const UiSigTypeEnum &ustEnum, const QVariant& v);

public:
    //不需要子类实现
    bool connectTPSigSlot(ITaskProcess *itp);
    bool connectUiSigSlot(IWidget *iwgt);
    void paintEvent(QPaintEvent *e);

protected:
    ICore *m_mainCore;

private:
    Ui::WWidget *ui;
};

#endif // WWIDGET_H
