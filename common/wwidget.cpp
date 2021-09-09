#include "wwidget.h"
#include "ui_wwidget.h"
#include "itaskpluginsmanager.h"

#include <QDebug>
#include <QPainter>
#include <QMetaMethod>

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
    static const QMetaMethod mMethod = QMetaMethod::fromSignal(&WWidget::toTPSignal);
    bool bConnected = isSignalConnected(mMethod);
    int iConnectedNum = receivers(SIGNAL(toTPSignal(const TaskSigTypeEnum &tstEnum, const QVariant& v, bool bThread = false)));
    qDebug() << "void WWidget::connectTPSigSlot" << bConnected << iConnectedNum;
    return connect(this, &WWidget::toTPSignal, itp, &ITaskProcess::dispatchTaskSigSlot, Qt::ConnectionType(Qt::AutoConnection|Qt::UniqueConnection));
}

bool WWidget::connectUiSigSlot(IWidget *iwgt)
{
    static const QMetaMethod mMethod = QMetaMethod::fromSignal(&WWidget::toUiSignal);
    bool bConnected = isSignalConnected(mMethod);
    int iConnectedNum = receivers(SIGNAL(toUiSignal(const UiSigTypeEnum &ustEnum, const QVariant& v)));
    qDebug() << "void WWidget::connectUiSigSlot" << bConnected << iConnectedNum;
    return connect(this, &WWidget::toUiSignal, iwgt, &IWidget::dispatchUi2UiSigSlot, Qt::ConnectionType(Qt::AutoConnection|Qt::UniqueConnection));
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

void WWidget::dispatchTask2UiSigSlot(const TaskSigTypeEnum &tstEnum, const QVariant &var, QObject *sender)
{
    qDebug() << "this=" << this << "void WWidget::dispatchTask2UiSigSlot" << sender << tstEnum << var;
}

void WWidget::dispatchUi2UiSigSlot(const UiSigTypeEnum &ustEnum, const QVariant &var)
{
    qDebug() << "this=" << this << "void WWidget::dispatchUi2UiSigSlot" << sender() << ustEnum << var;
}
