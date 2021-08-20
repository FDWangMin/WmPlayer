#include "testuipluginwidget.h"
#include "ui_testuipluginwidget.h"
#include "icore.h"
#include <QDebug>

TestUiPluginWidget::TestUiPluginWidget(QWidget *parent, ICore *core) :
    WWidget(parent, core),
    ui(new Ui::TestUiPluginWidget)
{
    ui->setupUi(this);
    initialize();
}

TestUiPluginWidget::~TestUiPluginWidget()
{
    delete ui;
}

void TestUiPluginWidget::initialize()
{
    connect(ui->pushButton, &QPushButton::clicked, [this]()
    {
        static int siNum = 1000;
        QVariant var(siNum);
        if (m_mainCore!=NULL)
        {
            static bool bThread = true;
//            bThread = !bThread;
            if (bThread)
                siNum += 1000;
            emit toTPSignal(TST_TestTaskPgs1, var, bThread);
        }
    });
}

void TestUiPluginWidget::dispatchTask2UiSigSlot(QObject *sender, const TaskSigTypeEnum &tstEnum, const QVariant &var)
{
    if (this != sender)
        return;

    qDebug() << "this=" << this << "sender=" << sender << "void TestUiPluginWidget::dispatchTask2UiSigSlot" << tstEnum << var;

    emit toUiSignal(UST_TestUiPluginWgt2, var);
}

void TestUiPluginWidget::dispatchUi2UiSigSlot(const UiSigTypeEnum &ustEnum, const QVariant &var)
{
    qDebug() << "void TestUiPluginWidget::dispatchUi2UiSigSlot" << ustEnum << var;
}
