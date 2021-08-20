#include "wtaskprocess.h"
#include "iuipluginsmanager.h"
#include <QDebug>

WTaskProcess::WTaskProcess(QObject *parent) :
    ITaskProcess(parent)
{

}

void WTaskProcess::initialize()
{
    qDebug() << "void WTaskProcess::initialize";
}

bool WTaskProcess::connectUiSigSlot(IWidget *iwgt)
{
    qDebug() << "void WTaskProcess::connectUiSigSlot";
    return connect(this, &WTaskProcess::returnUiSignal, iwgt, &IWidget::dispatchTask2UiSigSlot);
}

void WTaskProcess::dispatchTaskSigSlot(const TaskSigTypeEnum &tstEnum, const QVariant &var, bool bThread)
{
    qDebug() << "void WTaskProcess::dispatchTaskSigSlot";
}
