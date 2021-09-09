#include "wmlog.h"
#include "wmglobal.h"

#include <QMutex>
#include <QFile>
#include <QDateTime>
#include <QApplication>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include <QDir>

#define DATE_FORMAT qPrintable(QDate::currentDate().toString("yyyy-MM-dd"))

//日志重定向
void RedirectLog(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    //加锁,防止多线程中qdebug太频繁导致崩溃
    static QMutex mutex;
    QMutexLocker locker(&mutex);

    if (WmLog::instance()->filterLogTypeList().contains(type))
       return;

    QString strLogmsg = msg;
    if (WmLog::instance()->bShowNewLine())
        strLogmsg = QString("\n") + strLogmsg;;
    if (WmLog::instance()->bShowTime())
        strLogmsg = QString("[%1] ").arg(QDateTime::currentDateTime().toString("hh:mm:ss")) + strLogmsg;
    if (WmLog::instance()->bShowFuncName())
        strLogmsg = QString("[%1]").arg(context.function) + strLogmsg;
    if (WmLog::instance()->bShowFileName())
        strLogmsg = QString("[%1_%2]").arg(context.file).arg(context.line) + strLogmsg;

    //这里可以根据不同的类型加上不同的头部用于区分
    /*
    switch (type)
    {
        case QtDebugMsg:
            strLogmsg = QString("%1").arg(strLogmsg);
            break;

        case QtWarningMsg:
            strLogmsg = QString("%1").arg(strLogmsg);
            break;

        case QtCriticalMsg:
            strLogmsg = QString("%1").arg(strLogmsg);
            break;

        case QtFatalMsg:
            strLogmsg = QString("%1").arg(strLogmsg);
            break;

        case QtInfoMsg:
            strLogmsg = QString("%1").arg(strLogmsg);
            break;
    }*/

    WmLog::instance()->reprocessing(strLogmsg);
}

WmLog::DestroyWmLogInstance WmLog::sm_dwi;
WmLog* WmLog::sm_self = NULL;

WmLog* WmLog::instance()
{
    if (sm_self == NULL)
    {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if (sm_self == NULL)
            sm_self = new WmLog;
    }

    return sm_self;
}

WmLog::WmLog(QObject *parent) : QObject(parent),
    m_bToSigSLot(false),
    m_bToFile(false),
    m_bShowNewLine(false),
    m_bShowTime(true),
    m_bShowFileName(false),
    m_bShowFuncName(false)
{
    m_file.reset(new QFile(this));

    //默认取应用程序根目录
    m_logPath = qApp->applicationDirPath() + LOG_PATH;
    QDir dir(m_logPath);
    if (!dir.exists())
    {
        if (!dir.mkdir(m_logPath))
            qDebug() << "dir.mkdir(m_logPath) Failed";
    }

    //默认取应用程序可执行文件名称
    m_logName = qApp->applicationName();
    m_fileName = "";
}

WmLog::~WmLog()
{
    stopLog();
    m_file->close();
    qDebug() << "WmLog::~WmLog()";
}

void WmLog::reprocessing(const QString &logmsg)
{
    //信号槽发送日志信息
    if (m_bToSigSLot)
        emit sendLogMsg(logmsg);

    if (m_bToFile)
    {
        //只有当日期改变时才新建和打开文件
        QString fileName = QString("%1/%2_log_%3.txt").arg(m_logPath).arg(m_logName).arg(DATE_FORMAT);
        if (m_fileName != fileName)
        {
            m_fileName = fileName;
            if (m_file->isOpen())
                m_file->close();

            m_file->setFileName(fileName);
            m_file->open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text);
        }

        QTextStream logStream(m_file.data());
        logStream << logmsg << "\n";
    }
}

void WmLog::addFilterLogType(const QtMsgType &msgType)
{
    if (!m_filterLogTypeList.contains(msgType))
        m_filterLogTypeList.append(msgType);
}

void WmLog::removeFilterLogType(const QtMsgType &msgType)
{
    if (m_filterLogTypeList.contains(msgType))
        m_filterLogTypeList.removeOne(msgType);
}

const QList<QtMsgType> &WmLog::filterLogTypeList() const
{
    return m_filterLogTypeList;
}

void WmLog::setPath(const QString &path)
{
    m_logPath = path;
}

void WmLog::setName(const QString &name)
{
    m_logName = name;
}

bool WmLog::bToSigSLot() const
{
    return m_bToSigSLot;
}

void WmLog::setBToSigSLot(bool bToSigSLot)
{
    m_bToSigSLot = bToSigSLot;
}

bool WmLog::bToFile() const
{
    return m_bToFile;
}

void WmLog::setBToFile(bool bToFile)
{
    m_bToFile = bToFile;
}

bool WmLog::bShowFuncName() const
{
    return m_bShowFuncName;
}

void WmLog::setBShowFuncName(bool bShowFuncName)
{
    m_bShowFuncName = bShowFuncName;
}

bool WmLog::bShowFileName() const
{
    return m_bShowFileName;
}

void WmLog::setBShowFileName(bool bShowFileName)
{
    m_bShowFileName = bShowFileName;
}

bool WmLog::bShowTime() const
{
    return m_bShowTime;
}

void WmLog::setBShowTime(bool bShowTime)
{
    m_bShowTime = bShowTime;
}

void WmLog::startLog()
{
    qInstallMessageHandler(RedirectLog);
}

void WmLog::stopLog()
{
    qInstallMessageHandler(0);
}

bool WmLog::bShowNewLine() const
{
    return m_bShowNewLine;
}

void WmLog::setBShowNewLine(bool bShowNewLine)
{
    m_bShowNewLine = bShowNewLine;
}

