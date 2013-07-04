/*
 *  Copyright 2013 Wang Luming <wlm199558@126.com>
 *  Copyright 2013 Miyanaga Saki <tomguts@126.com>
 *
 *  gcc.cpp is part of Kreogist-Cute-IDE.
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
    QFileInfo fileInfo(filePath);
    QStringList arg;
    arg<<filePath<<"-g"<<"-Wall";

    //unix/unix-like system
    QString programName=fileInfo.absolutePath()+"/"
            +fileInfo.completeBaseName();

#ifdef Q_OS_WIN32
    programName+=".exe";
    //Windows
#endif

    arg<<"-o"<<programName;

    qDebug()<<arg;

    connect(this,SIGNAL(readyRead()),
            this,SLOT(onOutputReady()));

    start(gccPath,arg);
}

void gcc::onOutputReady()
{
    qDebug()<<"Reach!!!";
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
