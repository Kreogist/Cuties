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
    arg<<filePath<<"-g";
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

void fpc::parseLine(const QString &text)
{
    QRegularExpression regexp("([A-Za-z]+\\.pas)\\((\\d+),(\\d+)\\)");

    QRegularExpressionMatch match=regexp.match(text);

    if(match.hasMatch())
    {
        ErrInfo error;
        error.strFilePath=match.captured(1);
        error.nLineNum=match.captured(2).toInt();
        error.nColumnNum=match.captured(3).toInt();
        error.strErrDescription=text.mid(match.capturedLength());

        emit compileError(error);
    }
    else
    {
        regexp.setPattern("(Fatal|Error|Warning|Hint|Note)");
        match=regexp.match(text);

        if(match.hasMatch())
        {
            ErrInfo error;
            error.strFilePath.clear();
            error.nLineNum=-1;
            error.nColumnNum=-1;
            error.strErrDescription=text;
        }
    }

    return ;
}
