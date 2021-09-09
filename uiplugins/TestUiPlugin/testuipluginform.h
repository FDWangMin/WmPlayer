#ifndef TESTUIPLUGINFORM_H
#define TESTUIPLUGINFORM_H

#include "wwidget.h"

namespace Ui {
class TestUiPluginForm;
}

class TestUiPluginForm : public WWidget
{
    Q_OBJECT

public:
    explicit TestUiPluginForm(QWidget *parent = 0, ICore *core = 0);
    ~TestUiPluginForm();

    void initialize() override;

    void dispatchTask2UiSigSlot(const TaskSigTypeEnum &tstEnum, const QVariant &va, QObject *sender) override;

    void dispatchUi2UiSigSlot(const UiSigTypeEnum &ustEnum, const QVariant &var) override;

public slots:
    void debugTestConnectFromTaskSigSlot(const TaskSigTypeEnum &iEnum, const QVariant &var, QObject *sender);

private:
    Ui::TestUiPluginForm *ui;
};

#endif // TESTUIPLUGINFORM_H
