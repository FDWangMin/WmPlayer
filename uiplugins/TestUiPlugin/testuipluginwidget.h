#ifndef TESTUIPLUGINWIDGET_H
#define TESTUIPLUGINWIDGET_H

#include "wwidget.h"

namespace Ui {
class TestUiPluginWidget;
}

class TestUiPluginWidget : public WWidget
{
    Q_OBJECT

public:
    explicit TestUiPluginWidget(QWidget *parent, ICore *core = 0);
    ~TestUiPluginWidget();

    void initialize();

public slots:
    void dispatchTask2UiSigSlot(QObject *sender, const TaskSigTypeEnum &tstEnum, const QVariant &var);
    void dispatchUi2UiSigSlot(const UiSigTypeEnum &ustEnum, const QVariant &var);

private:
    Ui::TestUiPluginWidget *ui;
};

#endif // TESTUIPLUGINWIDGET_H
