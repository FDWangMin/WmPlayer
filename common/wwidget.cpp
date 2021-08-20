#include "wwidget.h"
#include "ui_wwidget.h"
#include "itaskpluginsmanager.h"
#include <QDebug>
#include <QPainter>

WWidget::WWidget(QWidget *parent, ICore *core) :
    IWidget(parent),
    m_mainCore(core),
    ui(new Ui::WWidget)
{
    ui->setupUi(this);
}

WWidget::~WWidget()
{
    delete ui;
}

void WWidget::initialize()
{
    qDebug() << "void WWidget::initialize()";
}

bool WWidget::connectTPSigSlot(ITaskProcess *itp)
{
    qDebug() << "void WWidget::connectTPSigSlot";
    return connect(this, &WWidget::toTPSignal, itp, &ITaskProcess::dispatchTaskSigSlot);
}

bool WWidget::connectUiSigSlot(IWidget *iwgt)
{
    qDebug() << "void WWidget::connectUiSigSlot";
    return connect(this, &WWidget::toUiSignal, iwgt, &IWidget::dispatchUi2UiSigSlot);
}

void WWidget::paintEvent(QPaintEvent *e)
{
    //解决父类为空时样式表为空
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(e);
}

void WWidget::dispatchTask2UiSigSlot(QObject *sender, const TaskSigTypeEnum &tstEnum, const QVariant &var)
{
    qDebug() << "this=" << this << "void WWidget::dispatchTask2UiSigSlot" << sender << tstEnum << var;
}

void WWidget::dispatchUi2UiSigSlot(const UiSigTypeEnum &ustEnum, const QVariant &var)
{
    qDebug() << "this=" << this << "void WWidget::dispatchUi2UiSigSlot" << sender() << ustEnum << var;
}
