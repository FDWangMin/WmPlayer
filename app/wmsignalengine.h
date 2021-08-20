#ifndef WMSIGNALENGINE_H
#define WMSIGNALENGINE_H

#include "isignalengine.h"
#include "wmglobal.h"
#include <QObject>

class WmSignalEngine : public ISignalEngine
{
public:
    WmSignalEngine();

    void sendSignal(int evt, const QVariant& v, bool bThread = false);

    void finshedSig(int evt, const QVariant& v);

    void connectSignalSlot(void* element);
};

class WmUiTaskSignalEngine : public IUiTaskSignalEngine
{
public:
    WmUiTaskSignalEngine();

    void connectUTSigSlot(IWidget* iwgt, ITaskProcess* itps);

    void connectUUSigSlot(IWidget* iwgt1, IWidget* iwgt2);

//signals:
//    void uiToTaskSignal(const TaskSigTypeEnum& tsteId, const QVariant& v, bool bThread = false);
//    void taskToUiSignal(const UiSigTypeEnum& usteId, const QVariant& v, bool bThread = false);

//    void uiToUiSignal(const UiSigTypeEnum& usteId, const QVariant& v, bool bThread = false);
};

#endif // WMSIGNALENGINE_H
