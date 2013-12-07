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

#include <QFileInfo>
#include <QMessageBox>

#include "kccompilerbase.h"

KCCompilerBase::KCCompilerBase(QObject *parent) :
    QObject(parent)
{
}

//Emit the compile command signal
void KCCompilerBase::emitCompileCommand(const QString &compilerPath,
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

    emitCompileCommand(compilerPath, arg);

    compiler.reset(new QProcess(this));
    compiler->setReadChannelMode(QProcess::MergedChannels);

    connectionHandles+=connect(compiler.data(), &QProcess::readyRead,
                               this, &KCCompilerBase::readyForOutput);
    connectionHandles+=connect(compiler.data(), SIGNAL(finished(int)),
                               this, SLOT(onFinished(int)));

    if(!getCompileEnv().isEmpty())
    {
        QStringList compilerEnvironment=QProcess::systemEnvironment();
        compilerEnvironment.replaceInStrings(QRegExp("^PATH=(.*)", Qt::CaseInsensitive), QString("PATH=\\1;"+getCompileEnv()));
        compiler->setEnvironment(compilerEnvironment);
    }
    compiler->start(compilerPath, arg);
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

void KCCompilerBase::readyForOutput()
{
    char outputLineMessage[1024];
    while(compiler->readLine(outputLineMessage,1024))
    {
        QString stringOutputLineMessage=QString::fromUtf8(outputLineMessage);
        emit compileMessage(stringOutputLineMessage);
        parseLine(stringOutputLineMessage);
    }
}
