/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist-Cuties.
 *
 *    Kreogist-Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gcc.h"

#ifdef Q_OS_UNIX
QString gcc::gccPath="/usr/bin/gcc";
QString gcc::gppPath="/usr/bin/g++";
#endif

#ifdef Q_OS_WIN
QString gcc::gccPath="C:/MinGW/bin/gcc.exe";
QString gcc::gppPath="C:/MinGW/bin/g++.exe";
#endif

gcc::gcc(QObject *parent) :
    compilerBase(parent)
{
    isCompileCpp=true;
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

    if(fileInfo.suffix() == "c")
        isCompileCpp=false;
    else
        isCompileCpp=true;

    arg<<filePath<<"-lm"<<"-ggdb"<<"-Wall"<<"-static";

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

void gcc::parseLine(const QString &text)
{
    QString strJudgedStr=text.left(2).toLower();
    if(strJudgedStr=="in" || strJudgedStr=="  ")
    {
        ErrInfo error;
        error.nColumnNum=-1;
        error.nLineNum=-1;
        error.strErrDescription=text;
        error.strErrDescription=error.strErrDescription.remove(
                    error.strErrDescription.length()-1,1);
        error.strFilePath="";

        emit compileError(error);
    }
    else
    {
        QRegularExpression expressMsg("(<command[ -]line>|([A-Za-z]:)?[^:]+):");
        QRegularExpressionMatch match=expressMsg.match(text);
        if(match.hasMatch())
        {
            QString FileName=match.captured();
            int NewHead=FileName.length();
            FileName.chop(1);
            //remove :
            //for example ,match.captured() is "/home/user/desktop/test.cpp:"
            //and the FileName should be "/home/user/desktop/test.cpp"

            QString ErrorDetailInfo=text.mid(NewHead);
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
