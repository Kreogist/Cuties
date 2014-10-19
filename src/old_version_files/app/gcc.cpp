/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist Cuties.
 *
 *    Kreogist Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QFileInfo>
#include <QRegularExpression>
#include <QMessageBox>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

#include "kccompilerconfigure.h"

#include "gcc.h"

gcc::gcc(QObject *parent, bool compileCpp) :
    KCCompilerBase(parent)
{
    isCompileCpp=compileCpp;
    instance=KCCompilerConfigure::getInstance();
}

QString gcc::compilerPath()
{
    return isCompileCpp?instance->getPathValue("GPP-Path"):
           instance->getPathValue("GCC-Path");
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
    {
        isCompileCpp=false;
    }
    else
    {
        isCompileCpp=true;
    }

    arg<<filePath<<"-lm"<<"-ggdb"<<"-Wall";

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

#ifdef Q_OS_WIN32
    //Windows
    programName+=".exe";
    arg<<"-static";
#endif

    arg<<"-o"<<programName;
    return arg;
}

QString gcc::getCompileEnv()
{
#ifdef Q_OS_WIN
    QString envPath;
    QDir envDir(this->compilerPath());
    envDir.setPath(envDir.absolutePath().left(envDir.absolutePath().length()-envDir.dirName().length()));
    envDir.setPath(envDir.absolutePath().left(envDir.absolutePath().length()-envDir.dirName().length()-1));
    envPath=envDir.absolutePath();
    envPath.replace("/","\\");
    return envPath + "\\Bin;" + envPath + "\\lib";
#else
    return QString("");
#endif

}

void gcc::parseLine(const QString &text)
{
    QString strJudgedStr=text.left(2).toLower();
    if(strJudgedStr=="in" || strJudgedStr=="  ")
    {
        compileErrorInfo newCompilerErrorInfo;
        newCompilerErrorInfo.errorColumn=-1;
        newCompilerErrorInfo.errorLine=-1;
        newCompilerErrorInfo.errorDescription=text;
        newCompilerErrorInfo.errorDescription=newCompilerErrorInfo.errorDescription.remove(
                newCompilerErrorInfo.errorDescription.length()-1,1);
        newCompilerErrorInfo.errorFilePath="";

        emit compileError(newCompilerErrorInfo);
    }
    else
    {
        QRegularExpression errorMessageExpression("(<command[ -]line>|([A-Za-z]:)?[^:]+):");
        QRegularExpressionMatch errorMatcher=errorMessageExpression.match(text);
        if(errorMatcher.hasMatch())
        {
            QString errorFileName=errorMatcher.captured();
            int NewHead=errorFileName.length();
            errorFileName.chop(1);
            //remove :
            //for example ,match.captured() is "/home/user/desktop/test.cpp:"
            //and the FileName should be "/home/user/desktop/test.cpp"

            QString errorDetailInfo=text.mid(NewHead);
            errorDetailInfo.chop(1);    //remove :

            errorMessageExpression.setPattern("(\\d+):(\\d+): ");
            errorMatcher=errorMessageExpression.match(errorDetailInfo);

            compileErrorInfo newCompilerErrorInfo;
            newCompilerErrorInfo.errorFilePath=errorFileName;
            newCompilerErrorInfo.errorDescription=errorDetailInfo;

            if(errorMatcher.hasMatch())
            {
                newCompilerErrorInfo.errorLine=errorMatcher.captured(1).toInt();
                newCompilerErrorInfo.errorColumn=errorMatcher.captured(2).toInt();
            }
            else
            {
                errorMessageExpression.setPattern("(\\d+): ");
                errorMatcher=errorMessageExpression.match(errorDetailInfo);

                if(errorMatcher.hasMatch())
                {
                    newCompilerErrorInfo.errorLine=errorMatcher.captured(1).toInt();
                    newCompilerErrorInfo.errorColumn=-1;
                }
                else
                {
                    //some message may not contain line/column number
                    //for example: the message may be " in function ‘int main()’ "
                    newCompilerErrorInfo.errorLine=-1;
                    newCompilerErrorInfo.errorColumn=-1;
                }
            }

            emit compileError(newCompilerErrorInfo);
        }
    }
}
