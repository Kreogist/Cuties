#include "gcc.h"

#ifdef Q_OS_UNIX
QString gcc::gccPath="/usr/bin/g++";
#endif

#ifdef Q_OS_WIN32
QString gcc::gccPath="c:/MinGW/bin/g++.exe";
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
    arg<<filePath<<"-g"<<"-Wall";

    //unix/unix-like system
    QString programName=QString("-o")+fileInfo.absolutePath()+"/"
            +fileInfo.completeBaseName();

#ifdef Q_OS_WIN32
    programName+=".exe";
    //Windows
#endif

    arg<<programName;

    connect(this,SIGNAL(readyRead()),
            this,SLOT(onOutputReady()));

    start(gccPath,arg);
}

void gcc::onOutputReady()
{
    char str_msg[1024];
    while(readLine(str_msg,1024))
    {
        QString msg=QString::fromUtf8(str_msg);
        qDebug()<<msg;
        emit output(msg);
    }
}

QRegularExpression gcc::suffixFilter()
{
    return QRegularExpression("(h|hpp|rh|hh|c|cpp|cc|cxx|c++|cp)"
                              ,QRegularExpression::CaseInsensitiveOption);
}
