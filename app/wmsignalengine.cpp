#include "wmsignalengine.h"
#include "iuipluginsmanager.h"
#include "itaskpluginsmanager.h"

#include <QDebug>
#include <QString>

WmSignalEngine::WmSignalEngine()
{

}

void WmSignalEngine::sendSignal(int evt, const QVariant &v, bool bThread)
{

}

void WmSignalEngine::finshedSig(int evt, const QVariant &v)
{

}

void WmSignalEngine::connectSignalSlot(void *element)
{

}


WmUiTaskSignalEngine::WmUiTaskSignalEngine()
{

}

void WmUiTaskSignalEngine::connectUTSigSlot(IWidget *iwgt, ITaskProcess *itps)
{
    if (iwgt == NULL || itps == NULL)
    {
        qDebug() << QString("Connect iwgt:%1 and itps:%2 Failed!").arg((long)iwgt).arg((long)itps);
        return;
    }

    iwgt->connectTPSigSlot(itps);
    itps->connectUiSigSlot(iwgt);
}

void WmUiTaskSignalEngine::connectUUSigSlot(IWidget *iwgt1, IWidget *iwgt2)
{
    if (iwgt1 == NULL || iwgt2 == NULL)
    {
        qDebug() << QString("Connect iwgt1:%1 and iwgt2:%2 Failed!").arg((long)iwgt1, (long)iwgt2);
        return;
    }
    iwgt1->connectUiSigSlot(iwgt2);
}


