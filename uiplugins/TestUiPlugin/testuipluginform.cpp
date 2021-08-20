#include "testuipluginform.h"
#include "ui_testuipluginform.h"

#include <QDebug>

TestUiPluginForm::TestUiPluginForm(QWidget *parent, ICore *core) :
    WWidget(parent, core),
    ui(new Ui::TestUiPluginForm)
{
    ui->setupUi(this);
    initialize();
}

TestUiPluginForm::~TestUiPluginForm()
{
    delete ui;
}

void TestUiPluginForm::initialize()
{
    connect(ui->pushButton, &QPushButton::clicked, [this]()
    {
        emit toTPSignal(TST_TestTaskPgs2, QVariant(2222), true);
    });
}

void TestUiPluginForm::dispatchTask2UiSigSlot(QObject *sender, const TaskSigTypeEnum &tstEnum, const QVariant &var)
{
    if (this != sender)
        return;

    qDebug() << "this=" << this << "sender=" << sender << "void TestUiPluginForm::dispatchTask2UiSigSlot" << tstEnum << var;
}

void TestUiPluginForm::dispatchUi2UiSigSlot(const UiSigTypeEnum &ustEnum, const QVariant &var)
{
    qDebug() << "TestUiPluginForm::dispatchUi2UiSigSlot" << ustEnum << var;
    ui->textEdit->append(var.toString() + "\n");
}
