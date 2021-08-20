
#ifndef ISIGNALENGINE_H
#define ISIGNALENGINE_H

#include <QObject>

/* 类声明 */
class QVariant;
class IWidget;
class ITaskProcess;
enum TaskSigTypeEnum;
enum UiSigTypeEnum;

/* 负责整个框架的自定义信号量的注册和发送工作
 * 逐渐弃用，后续代码尽量不用*/
class ISignalEngine
{
public:
    /*发送信号*/
    virtual void sendSignal(int evt, const QVariant& v, bool bThread = false) = 0;

    /*结束信号引擎*/
    virtual void finshedSig(int evt, const QVariant& v) = 0;

    /*链接信号槽*/
    virtual void connectSignalSlot(void* element) = 0;
};

/*Ui和业务层通信专用信号引擎*/
class IUiTaskSignalEngine
{
public:
    /*链接ui和task信号引擎*/
    virtual void connectUTSigSlot(IWidget* iwgt, ITaskProcess* itp) = 0;

    /*链接ui和ui信号引擎*/
    virtual void connectUUSigSlot(IWidget* iwgt1, IWidget* iwgt2) = 0;
};

#endif // ISIGNALENGINE_H
