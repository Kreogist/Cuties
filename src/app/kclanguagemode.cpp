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

#include "kclanguagemode.h"

KCLanguageMode::KCLanguageMode(QWidget *parent) :
    QObject(parent)
{
    m_parent=qobject_cast<KCCodeEditor *>(parent);
    compilerReceiver=NULL;
    dbgReceiver=NULL;
    gdbInstance=NULL;

    setCompileState(uncompiled);
    m_type=Invalid;
    setFileSuffix(KCGeneralConfigure::getInstance()->getDefaultLanguageModeString());

    Q_ASSERT(m_parent!=NULL);
}

bool KCLanguageMode::compilerIsNull()
{
    return compiler.isNull();
}

void KCLanguageMode::setMode(const modeType &type)
{
    m_type=type;
}

void KCLanguageMode::compile()
{
    if(compiler.isNull())
    {
        qDebug()<<"compiler is NULL";
        return ;
    }

    if(compilerReceiver==NULL)
    {
        compilerReceiver=new KCCompileOutputReceiver(this);
        connectCompilerAndOutputReceiver();
    }

    if(checkIfIsCompiling())
    {
        return ;
    }

    setCompileState(compiling);

    compilerReceiver->addBeginCompileText();

    compilerFinishedConnection=connect(compiler.data(),&KCCompilerBase::compileFinished,
                                       this,&KCLanguageMode::onCompileFinished);
    compiler->startCompile(m_parent->filePath);
}

void KCLanguageMode::setFileSuffix(const QString &suffix)
{
    QRegularExpression _regexp_cpp("(h|hpp|rh|hh|c|cpp|cc|cxx|c++|cp)",
                                   QRegularExpression::CaseInsensitiveOption);
    QRegularExpression _regexp_pascal("pas",
                                      QRegularExpression::CaseInsensitiveOption);

    if(suffix.contains(_regexp_cpp))
    {
        if(m_type==Cpp) //file type doesn't change,so return.
        {
            return ;
        }

        m_type=Cpp;
        compiler.reset(new gcc(this));
        m_highlighter.reset(new KCCppHighlighter(this));
    }
    else if(suffix.contains(_regexp_pascal))
    {
        if(m_type==Pascal) //file type doesn't change,so return.
        {
            return ;
        }

        m_type=Pascal;
        compiler.reset(new fpc(this));
        m_highlighter.reset(new KCPascalHighlighter(this));
    }
    else
    {
        if(m_type==PlainText) //file type doesn't change,so return.
        {
            return ;
        }

        m_type=PlainText;
        compiler.reset();
        m_highlighter.reset(new KCHighlighter(this));
    }


    Q_ASSERT(!m_highlighter.isNull());
    m_highlighter->setDocument(m_parent->document());
}

KCCompileOutputReceiver *KCLanguageMode::getCompilerReceiver() const
{
    return compilerReceiver;
}

dbgOutputReceiver *KCLanguageMode::getDbgReceiver() const
{
    return dbgReceiver;
}

gdb *KCLanguageMode::getGdbInstance() const
{
    return gdbInstance;
}

gdb *KCLanguageMode::startDebug()
{
    if(gdbInstance == NULL)
    {
        gdbInstance=new gdb(this);
    }

    if(dbgReceiver == NULL)
    {
        dbgReceiver=new dbgOutputReceiver(this);
    }

    connectGDBAndDbgReceiver();
    gdbInstance->runGDB(m_parent->execFileName);

    return gdbInstance;
}

void KCLanguageMode::onCompileFinished(bool hasError)
{
    if((bool)compilerFinishedConnection)
    {
        disconnect(compilerFinishedConnection);
    }

    setCompileState(compiled);

    if(!hasError)
    {
        emit compileSuccessfully(m_parent->execFileName);
    }
}

void KCLanguageMode::connectCompilerAndOutputReceiver()
{
    compilerConnectionHandles.disConnectAll();

    compilerReceiver->setCompilerVersionString(compiler->compilerName()+
            " "+
            compiler->compilerVersion());

    //Output Compile Message:
    compilerConnectionHandles+=connect(compiler.data(),&KCCompilerBase::compileCommandLine,
                                       compilerReceiver,&KCCompileOutputReceiver::addCompilerOutputText);
    compilerConnectionHandles+=connect(compiler.data(),&KCCompilerBase::compileMessage,
                                       compilerReceiver,&KCCompileOutputReceiver::addCompilerOutputText);
    compilerConnectionHandles+=connect(compiler.data(),&KCCompilerBase::compileError,
                                       compilerReceiver,&KCCompileOutputReceiver::onCompileMessageReceived);
    compilerConnectionHandles+=connect(compiler.data(),&KCCompilerBase::compileFinished,
                                       compilerReceiver,&KCCompileOutputReceiver::onCompileFinished);
}

void KCLanguageMode::connectGDBAndDbgReceiver()
{
    gdbConnectionHandles.disConnectAll();

    gdbConnectionHandles+=connect(gdbInstance,&gdb::errorOccured,
                                  dbgReceiver,&dbgOutputReceiver::receiveError);
    gdbConnectionHandles+=connect(gdbInstance,&gdb::consoleOutputStream,
                                  dbgReceiver,&dbgOutputReceiver::receiveconsoleOutput);
    gdbConnectionHandles+=connect(gdbInstance,&gdb::targetOutputStream,
                                  dbgReceiver,&dbgOutputReceiver::receivetargetOutput);
    gdbConnectionHandles+=connect(gdbInstance,&gdb::logOutputStream,
                                  dbgReceiver,&dbgOutputReceiver::receivelogOutput);
    gdbConnectionHandles+=connect(gdbInstance,&gdb::locals,
                                  dbgReceiver,&dbgOutputReceiver::receiveLocals);
}

bool KCLanguageMode::checkIfIsCompiling()
{
    bool ret=false;

    stateLock.lockForRead();
    if(state==compiling)
    {
        ret=true;
    }
    stateLock.unlock();

    return ret;
}

void KCLanguageMode::setCompileState(const compileState &state)
{
    stateLock.lockForWrite();
    this->state=state;
    stateLock.unlock();
}
