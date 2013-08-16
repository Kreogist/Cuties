/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *      Wang Luming <wlm199558@126.com>
 *      Miyanaga Saki <tomguts@126.com>
 *      Zhang Jiayi <bf109g2@126.com>
 *
 *  This file is part of Kreogist-Cute-IDE.
 *
 *    Kreogist-Cute-IDE is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cute-IDE is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cute-IDE.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gcc.h"

#ifdef Q_OS_UNIX
QString gcc::gccPath="/usr/bin/g++";
#endif

#ifdef Q_OS_WIN
QString gcc::gccPath="C:/MinGW/bin/g++.exe";
#endif

gcc::gcc(QObject *parent) :
    compilerBase(parent)
{
    setReadChannelMode(QProcess::MergedChannels);
}

QStringList gcc::getVersionArg()
{
    QStringList arg;
    arg<<"-dumpversion";
    return arg;
}

QStringList gcc::getCompileArg(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    QStringList arg;
    arg<<filePath<<"-g"<<"-Wall"<<"-lm"<<"-static";

    QString programName;

    //unix/unix-like system
    if(fileInfo.absolutePath().right(1)=="/")
    {
        programName=fileInfo.absolutePath()
                +fileInfo.completeBaseName();
    }
    else
    {
        programName=fileInfo.absolutePath() + "/"
                +fileInfo.completeBaseName();
    }

#ifdef Q_OS_WIN
    //Windows
    programName+=".exe";
#endif

    arg<<"-o"<<programName;

    return arg;
}

QStringList gcc::getcompileEnv()
{
    QStringList env;

#ifdef Q_OS_WIN
    env<<gccPath;
#endif

    return env;
}

void gcc::setCompilerPath(const QString &path)
{
    gccPath=path;
}

void gcc::onOutputReady()
{
    char str_msg[1024];
    while(readLine(str_msg,1024))
    {
        QString msg=QString::fromUtf8(str_msg);
        emit output(msg);
        parseMessage(msg);
    }
}

void gcc::parseMessage(const QString &msg)
{
    QString strJudgedStr=msg.left(2).toLower();
    if(strJudgedStr=="in" || strJudgedStr=="  ")
    {
        ErrInfo error;
        error.nColumnNum=-1;
        error.nLineNum=-1;
        error.strErrDescription=msg;
        error.strErrDescription=error.strErrDescription.remove(
                    error.strErrDescription.length()-1,1);
        error.strFilePath="";

        emit compileError(error);
    }
    else
    {
        QRegularExpression expressMsg("(<command[ -]line>|([A-Za-z]:)?[^:]+):");
        QRegularExpressionMatch match=expressMsg.match(msg);
        if(match.hasMatch())
        {
            QString FileName=match.captured();
            int NewHead=FileName.length();
            FileName.chop(1);
            //remove :
            //for example ,match.captured() is "/home/user/desktop/test.cpp:"
            //and the FileName should be "/home/user/desktop/test.cpp"

            QString ErrorDetailInfo=msg.mid(NewHead);
            ErrorDetailInfo.chop(1);    //remove :


            expressMsg.setPattern("(\\d+):(\\d+)");
            match=expressMsg.match(ErrorDetailInfo);

            ErrInfo error;
            error.strFilePath=FileName;
            error.strErrDescription=ErrorDetailInfo;

            if(match.hasMatch())
            {
                error.nLineNum=match.captured(1).toInt();
                error.nColumnNum=match.captured(2).toInt();
            }
            else
            {
                //some message may not contian line/column number
                //for example: the message may be " in function ‘int main()’ "
                error.nLineNum=-1;
                error.nColumnNum=-1;
            }

            emit compileError(error);
        }
    }
}
