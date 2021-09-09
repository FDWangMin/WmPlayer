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

    connect(ui->pushButton_2, &QPushButton::clicked, [this]()
    {
        static ICommonSignal *iCom = m_mainCore->getCommonSignal(TPIE_WmTestTaskPluginId);
        qDebug() << "-------" << TST_TestTaskPgs1;
        iCom->emitCommonSignal(TST_TestTaskPgs1, QVariant(6666), true);
        TaskSigTypeEnum iEnum = TST_UnknowTaskSig;
        int iRet = iCom->execWaitResult(iEnum, 5000).toInt();
        qDebug() << "=======" << iEnum << iRet;

        static bool bConnected = false;
        if (!bConnected)
        {
            qDebug() << iCom->connectFromTaskSigSlot(this, SLOT(debugTestConnectFromTaskSigSlot(TaskSigTypeEnum,QVariant,QObject*)));
            bConnected = true;
        }
    });
}

void TestUiPluginForm::dispatchTask2UiSigSlot(const TaskSigTypeEnum &tstEnum, const QVariant &var, QObject *sender)
{
    //sender如果不是自己并且不为NULL直接返回
    //为NULL值说明这个信号是业务层发送给所有链接过的界面层的
    if (this != sender /*&& sender != NULL*/)
        return;

    qDebug() << "this=" << this << "sender=" << sender << "void TestUiPluginForm::dispatchTask2UiSigSlot" << tstEnum << var;
}

void TestUiPluginForm::dispatchUi2UiSigSlot(const UiSigTypeEnum &ustEnum, const QVariant &var)
{
    qDebug() << "TestUiPluginForm::dispatchUi2UiSigSlot" << ustEnum << var;
    ui->textEdit->append(var.toString() + "\n");
}

void TestUiPluginForm::debugTestConnectFromTaskSigSlot(const TaskSigTypeEnum &iEnum, const QVariant &var, QObject *sender)
{
    qDebug() << "TestUiPluginForm::debugTestConnectFromTaskSigSlot" << iEnum << var << sender;
}
