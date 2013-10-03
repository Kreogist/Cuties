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

#include "kccompilerbase.h"

KCCompilerBase::KCCompilerBase(QObject *parent) :
    QObject(parent)
{
}

void KCCompilerBase::emitCompileCmd(const QString &compilerPath,
                                    const QStringList &arg)
{
    QString compilerCommandLine;
    compilerCommandLine=compilerPath;
    for(int i=0; i<arg.count(); i++)
    {
        compilerCommandLine += QString(" ") + arg.at(i);
    }
    compilerCommandLine+="\n";

    emit compileCommandLine(compilerCommandLine);
}

//Display the version of the compiler
QString KCCompilerBase::compilerVersion()
{
    //Launch compiler to get version info
    compiler.reset(new QProcess(this));
    compiler->start(compilerPath(),getVersionArg());
    compiler->waitForFinished();
    //Return the version
    return QString::fromUtf8(compiler->readAllStandardOutput().constData());
}

void KCCompilerBase::startCompile(const QString &filePath)
{
    QStringList arg=getCompileArg(filePath);
    QString compilerPath=this->compilerPath();
    /*
     * Note: path() shouldn't be called before getCompileArg(), because
     * some subclass may need filePath to select the right compiler. For
     * example, gcc class use gcc(program name) to compile c files and use
     * g++ to compile cpp files.
     */

    //emitCompileCmd(compilerPath,getCompileArg(filePath));
    emitCompileCmd(compilerPath,arg);

    compiler.reset(new QProcess(this));
    compiler->setReadChannelMode(QProcess::MergedChannels);

    connectionHandles+=connect(compiler.data(),SIGNAL(readyRead()),
                               this,SLOT(onOutputReady()));
    connectionHandles+=connect(compiler.data(),SIGNAL(finished(int)),
                               this,SLOT(onFinished(int)));

    QStringList env=getcompileEnv();
    if(!env.isEmpty())
    {
        compiler->setEnvironment(env);
    }

    compiler->start(compilerPath,arg);
}

bool KCCompilerBase::checkCompilerPath(const QString &compilerPath)
{
    QFileInfo _fileInfo(compilerPath);

    if(_fileInfo.exists() && _fileInfo.isExecutable())
    {
        return true;
    }
    return false;
}

void KCCompilerBase::onFinished(int exitNum)
{
    connectionHandles.disConnectAll();
    emit compileFinished(checkHasErrorByExitNum(exitNum));
}

void KCCompilerBase::onOutputReady()
{
    char str_msg[1024];
    while(compiler->readLine(str_msg,1024))
    {
        QString msg=QString::fromUtf8(str_msg);
        emit output(msg);
        parseLine(msg);
    }
}
