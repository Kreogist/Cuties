#include "fpc.h"

#ifdef Q_OS_WIN32
//TODO: need fpc's default path on Windows
QString fpc::fpcPath="c:/fpc/fpc.exe";
#else
QString fpc::fpcPath="/usr/bin/fpc";
#endif

fpc::fpc(QObject *parent) :
    compilerBase(parent)
{
}

QStringList fpc::getVersionArg()
{
    QStringList arg;
    arg<<"-iW";
    return arg;
}

QStringList fpc::getCompileArg(const QString &filePath)
{
    QStringList arg;
    arg<<filePath;
    return arg;
}

QStringList fpc::getcompileEnv()
{
    QStringList env;
    return env;
}

void fpc::setCompilerPath(const QString &path)
{
    fpcPath=path;
}

void fpc::onOutputReady()
{
    char str_msg[1024];
    while(readLine(str_msg,1024))
    {
        QString msg=QString::fromUtf8(str_msg);
        emit output(msg);
        parseMessage(msg);
    }
}

void fpc::parseMessage(const QString &msg)
{
    return ;
}
