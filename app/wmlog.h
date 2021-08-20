#ifndef WMLOG_H
#define WMLOG_H

#include <QObject>
#include <QDebug>

class QFile;

class WmLog : public QObject
{
    Q_OBJECT
private:
    explicit WmLog(QObject *parent = nullptr);
    ~WmLog();

public:
    static WmLog *instance();

    //日志再处理
    void reprocessing(const QString &logmsg);

    //添加删除过滤日志类型
    void addFilterLogType(const QtMsgType &msgType);
    void removeFilterLogType(const QtMsgType &msgType);
    //获取过滤日志类型
    const QList<QtMsgType> & filterLogTypeList() const;

    //设置日志文件存放路径
    void setPath(const QString &path);
    //设置日志文件名称
    void setName(const QString &name);

    //设置重定向到信号槽
    bool bToSigSLot() const;
    void setBToSigSLot(bool bToSigSLot);
    //是否输出日志文件
    bool bToFile() const;
    void setBToFile(bool bToFile);
    //是否显示日志时间
    bool bShowTime() const;
    void setBShowTime(bool bShowTime);
    //是否显示文件名
    bool bShowFileName() const;
    void setBShowFileName(bool bShowFileName);
    //是否显示函数名
    bool bShowFuncName() const;
    void setBShowFuncName(bool bShowFuncName);
    //是否换行显示日志
    bool bShowNewLine() const;
    void setBShowNewLine(bool bShowNewLine);

signals:
    void sendLogMsg(const QString &content);

public slots:
    //启动日志服务
    void startLog();
    //暂停日志服务
    void stopLog();

private:
    class DestroyWmLogInstance
    {
    public:
        ~DestroyWmLogInstance()
        {
            if (sm_self != NULL)
            {
                delete sm_self;
                sm_self = NULL;
            }
        }
    };
    static DestroyWmLogInstance sm_dwi;
    static WmLog* sm_self;

    //是否重定向到信号槽
    bool m_bToSigSLot;
    //是否将日志写文件
    bool m_bToFile;
    //是否显示日志时间
    bool m_bShowTime;
    //是否显示日志文件名
    bool m_bShowFileName;
    //是否显示日志函数名
    bool m_bShowFuncName;
    //是否日志换行显示
    bool m_bShowNewLine;
    //需要过滤的日志类型（为空不过滤）
    QList<QtMsgType> m_filterLogTypeList;

    //文件对象
    QScopedPointer<QFile> m_file;
    //日志文件路径
    QString m_logPath;
    //日志文件名称
    QString m_logName;
    //日志文件完整名称
    QString m_fileName;
};

#endif // WMLOG_H
