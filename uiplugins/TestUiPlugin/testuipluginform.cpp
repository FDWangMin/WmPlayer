#include "testuipluginform.h"
#include "ui_testuipluginform.h"
#include "icommonsignal.h"
#include "icore.h"
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
    return;
    connect(ui->pushButton_2, &QPushButton::clicked, [this]()
    {
        static ICommonSignal *iCom = m_mainCore->getCommonSignal("test1", TPIE_WmTestTaskPluginId);
        qDebug() << "-------" << TST_TestTaskPgs1;
        iCom->emitCommonSignal(TST_TestTaskPgs1, QVariant(6666), true);
        TaskSigTypeEnum iEnum = TST_UnknowTaskSig;
        int iRet = iCom->execWaitResult(5000, iEnum).toInt();
        qDebug() << "=======" << iEnum << iRet;
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
