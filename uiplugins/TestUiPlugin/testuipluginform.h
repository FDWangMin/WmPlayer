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

    void initialize();

    void dispatchTask2UiSigSlot(QObject *sender, const TaskSigTypeEnum &tstEnum, const QVariant &var);

    void dispatchUi2UiSigSlot(const UiSigTypeEnum &ustEnum, const QVariant &var);

private:
    Ui::TestUiPluginForm *ui;
};

#endif // TESTUIPLUGINFORM_H
