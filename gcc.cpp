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
    connect(this,SIGNAL(readyRead()),SLOT(onOutputReady()));
}

QString gcc::version()
{
    //Initalize Values:
    QString strReturnValue;
    QProcess gccInfo;

    //Set Argv:
    QStringList arg;
    arg<<"--version";
    gccInfo.start(gccPath,arg);
    gccInfo.waitForFinished();
    //Save Second Part Of Compiler:
    strReturnValue=strReturnValue+"\n"+
                   QString::fromUtf8(gccInfo.readAllStandardOutput().constData());
    return strReturnValue;
}

void gcc::startCompile(const QString &filePath)
{
    QProcess *gccCompile=new QProcess(this);
    QStringList arg;
    arg<<"D:/test.cpp"<<"-o"<<"D:/test.exe";
    gccCompile->execute("c:/MinGW/bin/g++.exe", arg);
    /*QFileInfo fileInfo(filePath);


    qDebug()<<filePath;
    //arg<<filePath<<"-static"<<"-g"<<"-Wall"<<"-o";

#ifdef Q_OS_WIN32
    //arg<<fileInfo.absolutePath()+"/"+fileInfo.completeBaseName()+".exe";
    //Windows
#endif
#ifdef Q_OS_UNIX
    arg<<fileInfo.absolutePath()+"/"+fileInfo.completeBaseName();
    //unix/unix-like system
#endif
    QString teststr=QString("D:/test.cpp");// -static -g -Wall -o
    QString teststr2=QString("-o D:/test.exe");
    arg<<teststr<<teststr2;
    //connect(this,SIGNAL(started()),this,SLOT(onOutputReady()));
    //gccCompile.setArguments(arg);
    qDebug()<<arg;
    gccCompile->start(gccPath, arg);
    gccCompile->waitForFinished();*/
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
