#include "gcc.h"

#ifdef Q_OS_UNIX
QString gcc::gccPath="/usr/bin/g++";
#endif

#ifdef Q_OS_WIN32
QString gcc::gccPath="c:\\MinGW\\bin\\g++";
#endif

gcc::gcc(QObject *parent) :
    compilerBase(parent)
{
    setReadChannelMode(QProcess::MergedChannels);
}

QString gcc::version()
{
    QStringList arg;
    arg<<"-dumpversion";
    start(gccPath,arg);
    waitForFinished();
    return QString("g++ ")+
            QString::fromUtf8(readAllStandardOutput().constData());
}

void gcc::startCompile(const QString &filePath)
{
    QFileInfo fileInfo(filePath);

    qDebug()<<filePath;

    QStringList arg;
    arg<<filePath<<"-g"<<"-Wall"<<"-o";

#ifdef Q_OS_WIN32
    arg<<fileInfo.absolutePath()+fileInfo.completeBaseName()+".exe";
    //windows
#endif
#ifdef Q_OS_UNIX
    arg<<fileInfo.absolutePath()+"/"+fileInfo.completeBaseName();
    //unix/unix-like system
#endif

    qDebug()<<arg;

    start(gccPath,arg);

    connect(this,SIGNAL(readyRead()),this,SLOT(onOutputReady()));
}

void gcc::onOutputReady()
{
    char str_msg[1024];
    while(readLine(str_msg,1024))
    {
        QString msg=QString::fromUtf8(str_msg);
        emit output(msg);
    }
}
