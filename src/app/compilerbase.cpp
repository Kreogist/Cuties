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

#include "compilerbase.h"

compilerBase::compilerBase(QObject *parent) :
    QObject(parent)
{
}

void compilerBase::emitCompileCmd(const QString &compilerPath,
                                   const QStringList &arg)
{
    QString CompileCmdLine;
    CompileCmdLine=compilerPath;
    for(int i=0; i<arg.count(); i++)
    {
        CompileCmdLine += QString(" ") + arg.at(i);
    }
    CompileCmdLine+="\n";

    emit compileCmd(CompileCmdLine);
}

QString compilerBase::version()
{
    //Initalize Values:
    QString strReturnValue;

    compiler.reset(new QProcess(this));
    compiler->start(path(),getVersionArg());
    compiler->waitForFinished();

    //Save Second Part Of Compiler:
    strReturnValue=QString::fromUtf8(compiler->readAllStandardOutput().constData());
    return strReturnValue;
}

void compilerBase::startCompile(const QString &filePath)
{
    QStringList arg=getCompileArg(filePath);
    QString compilerPath=path();
    /* Note: path() shouldn't be called before getCompileArg(), because
     * some subclass may need filePath to select the right compiler. For
     * example, gcc class use gcc(program name) to compile c files and use
     * g++ to compile cpp files.
     */

    emitCompileCmd(compilerPath,getCompileArg(filePath));

    compiler.reset(new QProcess(this));
    compiler->setReadChannelMode(QProcess::MergedChannels);

    connectionHandles+=connect(compiler.data(),SIGNAL(readyRead()),
                               this,SLOT(onOutputReady()));
    connectionHandles+=connect(compiler.data(),SIGNAL(finished(int)),
                               this,SLOT(onFinished(int)));

    QStringList env=getcompileEnv();
    if(!env.isEmpty())
        compiler->setEnvironment(env);

    compiler->start(compilerPath,getCompileArg(filePath));
}

bool compilerBase::checkCompilerPath(const QString& path)
{
    QFileInfo _fileInfo(path);

    if(_fileInfo.exists() && _fileInfo.isExecutable())
    {
        return true;
    }

    return false;
}

void compilerBase::onFinished(int exitNum)
{
    connectionHandles.disConnectAll();

    bool hasErr=checkHasErrorByExitNum(exitNum);
    emit compileFinished(hasErr);
}

void compilerBase::onOutputReady()
{
    char str_msg[1024];
    while(compiler->readLine(str_msg,1024))
    {
        QString msg=QString::fromUtf8(str_msg);
        emit output(msg);
        parseLine(msg);
    }
}
