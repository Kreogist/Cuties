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

#include <QTimer>
#include <QApplication>

#include <stdlib.h>
#include <stdio.h>

#include "gdbcontroller.h"
#include <kcexecutor.h>

#ifdef Q_OS_UNIX
QString GdbController::gdbPath="/usr/bin/gdb";
#endif

#ifdef Q_OS_WIN32
QString GdbController::gdbPath="C:/MinGW/bin/gdb.exe";
#endif

bool GdbController::checkResult=false;

static bool isAnsycChar(const char &c)
{
    return (c >= 'a' && c <= 'z') || c == '-';
}

GdbThread::GdbThread(QObject *parent) :
    QThread(parent)
{
    messageCache.clear();
}

GdbThread::~GdbThread()
{
    quitGDB();
}

void GdbThread::run()
{
    readProcessData.disConnectAll();
    gdbProcess.reset(new QProcess(this));
    QStringList _arg;
    _arg<<filePath<<"--interpreter"<<"mi"
#ifdef Q_OS_WIN32
          ;
#else
       <<"-tty"<<(tty=KCExecutor::getInstance()->getNewConsole());
#endif
    readProcessData+=connect(gdbProcess.data(),
                             SIGNAL(readyReadStandardOutput()),
                             this,
                             SLOT(readGdbStandardOutput()));
    readProcessData+=connect(gdbProcess.data(),
                             SIGNAL(readyReadStandardError()),
                             this,
                             SLOT(readGdbStandardError()));
    gdbProcess->start(gdbPath, _arg);
}

QString GdbThread::getFilePath() const
{
    return filePath;
}

void GdbThread::setFilePath(const QString &value)
{
    filePath = value;
}

void GdbThread::quitGDB()
{
    if(gdbProcess->state()==QProcess::NotRunning)
    {
        return;
    }
    int timeout=100; //Timeout to kill;
    execGdbCommand("q");
    execGdbCommand("y");

    //Read wait for finished document, this is the right way.
    if(!gdbProcess->waitForFinished(timeout))
    {
        //gdb doesn't quit till now, so we have to kill it.
        gdbProcess->kill();
    }
    KCExecutor::getInstance()->releaseConsole(tty);
}

void GdbThread::execGdbCommand(const QString &command)
{
    emit addSystemMessage(QString("(gdb): "+command+"\n"));
    gdbProcess->write(qPrintable(QString(command+"\n")));
}

QString GdbThread::getGdbPath() const
{
    return gdbPath;
}

void GdbThread::setGdbPath(const QString &value)
{
    gdbPath = value;
}

bool GdbThread::isGdbRunning()
{
    return (gdbProcess->state()==QProcess::Running);
}


void GdbThread::readGdbStandardError()
{
    QByteArray err = gdbProcess->readAllStandardError();

    emit parseError(err);
}

void GdbThread::readGdbStandardOutput()
{
    char buf[2004];

    QString _msg;
    while(gdbProcess->readLine(buf,2000)>0)
    {
        _msg=QString(buf);
        _msg.remove("\n");
        _msg.remove("\r");
        //If is empty, finish a part!
        if(_msg.isEmpty())
        {
            return;
        }
        if(_msg.contains("(gdb)"))
        {
            //Here means we have finished a part.
            if(!messageCache.isEmpty())
            {
                emit parseMessage(messageCache);
                messageCache.clear();
            }
            return;
        }
        char firstLetter=_msg.begin()->toLatin1();
        switch(firstLetter)
        {
        case '^':
        case '*':
        case '~':
        case '@':
        case '&':
        case '=':
            if(!messageCache.isEmpty())
            {
                emit parseMessage(messageCache);
            }
            messageCache=_msg;
            break;
        default:
            messageCache.append(_msg);
            break;
        }
    }
}

GdbController::GdbController(QObject *parent) :
    QObject(parent)
{
    instance=KCDebuggerConfigure::getInstance();
    setGDBPath(instance->getGdbPath());
    dbgOutputs.reset(new dbgOutputReceiver(this));
    checkGDB();

    requestForceUpdateLocal=false;

    debugCodec=QTextCodec::codecForLocale();
}

void GdbController::parseLine(const QString &_msg)
{
    char _firstChar=_msg.begin()->toLatin1();
    const QChar *begin=_msg.begin();
    const QChar *end=_msg.end();

    switch(_firstChar)
    {
    case '^':
    {
        begin++;

        QString _str_async;
        for(; begin<end; begin++)
        {
            if(isAnsycChar(begin->toLatin1()))
            {
                _str_async+=*begin;
            }
            else
            {
                break;
            }
        }

        if(_str_async == "done")
        {
            begin++;
            if(begin>=end)
            {
                return ;
            }

            GdbMiValue result;
            result.build(begin,end);

            if(result.getName() == "locals")
            {
                dbgOutputs->addLocals(result);
                break;
            }
            else if(result.getName() == "value")
            {
                if(!customIndexList.isEmpty())
                {
                    dbgOutputs->addExprValue(customIndexList.at(0), result.getValue());
                    customIndexList.removeFirst();
                }
                break;
            }
            else if(result.getName() == "bkpt")
            {
                parseBkpt(result);
                emit requireLineJump(result["line"].getValue().toInt());
                //Refresh stack list
                if(!requestForceUpdateLocal)
                {
                    updateDockInfos();
                }
                break;
            }
        }
        else if(_str_async == "running")
        {
            dbgOutputs->addConsoleOutput("  -> Cuties: Running program.\n");
            break;
        }
        else if(_str_async == "error")
        {
            begin++;
            if(begin>=end)
            {
                return ;
            }

            GdbMiValue result;

            result.build(begin,end);

            dbgOutputs->addErrorText(result.getValue()+"\n");
            break;
        }
        else
        {
            qWarning()<<"Unknow gdbmi result records!";
            qWarning()<<qPrintable(_msg);
        }

        break;
    }
    case '*':
    {
        begin++;

        QString _str_async;
        for(; begin<end; begin++)
        {
            if(isAnsycChar(begin->toLatin1()))
            {
                _str_async+=*begin;
            }
            else
            {
                break;
            }
        }
        if(_str_async == "stopped")
        {
            QString stoppedDetails;
            dbgOutputs->addConsoleOutput("  -> Cuties: GDB stopped.\n");
            //Here we have to display many many details.
            stoppedDetails="Details:\n";
            begin++;
            if(begin>=end)
            {
                return ;
            }

            GdbMiValue result;
            for(; begin<end; begin++)
            {
                GdbMiValue child;
                child.build(begin,end);
                if(child.getName()=="reason")
                {
                    stoppedDetails+=QString("Reason: " + child.getValue() + "\n");
                }
                else if(child.getName()=="func")
                {
                    stoppedDetails+=QString("At function: " + child.getValue() + "\n");
                }
                else if(child.getName()=="frame")
                {
                    emit requireLineJump(child["line"].getValue().toInt());
                    stoppedDetails+=QString("Frame Details: address  :" + child["addr"].getValue() + "\n" +
                                            "               function :" + child["func"].getValue() + "\n" +
                                            "               args     :" + child["args"].getValue() + "\n" +
                                            "               file     :" + child["file"].getValue() + "\n" +
                                            "               fullname :" + child["fullname"].getValue() + "\n" +
                                            "               line     :" + child["line"].getValue()) + "\n";
                }
                else if(child.getName()=="disp")
                {
                    stoppedDetails+=QString("disp: " + child.getValue() + "\n");
                }
                else if(child.getName()=="thread-id")
                {
                    stoppedDetails+=QString("thread-id: " + child.getValue() + "\n");
                }
                else if(child.getName()=="bkptno")
                {
                    stoppedDetails+=QString("bkptno: " + child.getValue() + "\n");
                }
                else if(child.getName()=="stopped-threads")
                {
                    stoppedDetails+=QString("stopped-threads: "+child.getValue()+"\n");
                }
                result+=child;
            }
            stoppedDetails.append("\n");
            dbgOutputs->addText(stoppedDetails);

            //Refresh stack list
            if(!requestForceUpdateLocal)
            {
                updateDockInfos();
            }
            break;
        }
        break;
    }
    case '~':
    {
        begin++;
        dbgOutputs->addConsoleOutput(parseOutputStream(begin,end));

        break;
    }
    case '@':
    {
        begin++;
        dbgOutputs->addTargetOutput(parseOutputStream(begin,end));

        break;
    }
    case '&':
    {
        //begin++;
        //dbgOutputs->addLogOutput(parseOutputStream(begin,end));
        break;
    }
    case '=':
    {
        //ignore this information
        break;
    }
    default:
        //program that is being debuged outputs
        dbgOutputs->addTargetOutput(_msg+'\n');
    }
}

void GdbController::parseError(const QString &_error)
{
    dbgOutputs->addErrorText(_error);
}

void GdbController::parseCommand(const QString &_cmd)
{
    dbgOutputs->addTargetOutput(_cmd);
}

QString GdbController::parseOutputStream(const QChar *begin,const QChar *end)
{
    GdbMiValue result;
    result.build(begin,end);

    return result.getValue();
}

QString GdbController::getFileType() const
{
    return fileType;
}

void GdbController::setFileType(const QString &value)
{
    fileType = value;
}

void GdbController::parseBkpt(const GdbMiValue &gmvBkpt)
{
    bkpt_struct _tmp_bkpt;

    _tmp_bkpt.number=gmvBkpt["number"].getValue().toInt();
    _tmp_bkpt.type=gmvBkpt["type"].getValue();
    _tmp_bkpt.disp=gmvBkpt["disp"].getValue();
    _tmp_bkpt.enabled=gmvBkpt["enabled"].getValue()=="y"?true:false;
    _tmp_bkpt.addr=gmvBkpt["addr"].getValue();
    _tmp_bkpt.func=gmvBkpt["func"].getValue();
    _tmp_bkpt.file=gmvBkpt["file"].getValue();
    _tmp_bkpt.fullName=gmvBkpt["fullname"].getValue();
    _tmp_bkpt.line=gmvBkpt["line"].getValue().toInt();
    _tmp_bkpt.threadGroups=gmvBkpt["thread-groups"][""].getValue();
    _tmp_bkpt.times=gmvBkpt["times"].getValue().toInt();
    _tmp_bkpt.original_location=gmvBkpt["original-location"].getValue();

    /*qDebug()<<_tmp_bkpt.number;
    qDebug()<<_tmp_bkpt.type;
    qDebug()<<_tmp_bkpt.disp;
    qDebug()<<_tmp_bkpt.enabled;
    qDebug()<<_tmp_bkpt.addr;
    qDebug()<<_tmp_bkpt.func;
    qDebug()<<_tmp_bkpt.file;
    qDebug()<<_tmp_bkpt.fullName;
    qDebug()<<_tmp_bkpt.line;
    qDebug()<<_tmp_bkpt.threadGroups;
    qDebug()<<_tmp_bkpt.times;
    qDebug()<<_tmp_bkpt.original_location;
    */

    bkptVec<<_tmp_bkpt;;
}

void GdbController::setGDBPath(const QString &path)
{
    gdbPath=path;
    checkGDB();
}

bool GdbController::checkGDB()
{
    QFileInfo _fileInfo(gdbPath);

    return checkResult=_fileInfo.exists() && _fileInfo.isExecutable();
}

bool GdbController::runGDB(const QString &filePath)
{
    if(checkResult)
    {
        createGDBThread();
        gdbProcessThread->setGdbPath(gdbPath);
        gdbProcessThread->setFilePath(filePath);
        gdbProcessThread->run();
        configureGDB();
        return true;
    }
    return false;
}

void GdbController::quitGDB()
{
    gdbProcessThread->quitGDB();
    gdbProcessThread->quit();
    //emit requireDisconnectDebug();
}

void GdbController::setBreakPointList(QList<int> breakpointLine)
{
    for(int i=0; i<breakpointLine.count(); i++)
    {
        setBreakPoint(breakpointLine.at(i)+1);
    }
}

/*!
 *! * \brief set the break point by line number.
 *!
 *!The breakpoint number is not in effect until it has been hit count times.
 *! */
void GdbController::setBreakPoint(const QString &fileName,
                        const int &lineNum,
                        const int &count)
{
    execGdbCommand(QString("-break-insert ")+
                     fileName+":"+
                     QString::number(lineNum)+" "+
                   QString::number(count));
}

void GdbController::setBreakPoint(const int &lineNum)
{
    execGdbCommand(QString("-break-insert ") + QString::number(lineNum));
}

/*!
 * \brief set the break point by the function's name.
 * \param functionName  the name of the function
 */
void GdbController::setBreakPoint(const QString &functionName)
{
    execGdbCommand(QString("-break-insert ")+functionName);
}


/*!
 * \brief Breakpoint number will stop the program only if the condition in expr is true.
 */
void GdbController::setBreakCondition(const int &number, const QString &expr)
{
    execGdbCommand(QString("-break-condition ")+
                     QString::number(number)+" "
                     +expr);
}

/*!
 * \brief Create a watchpoint
 * \param var
 */
void GdbController::setWatchPoint(const QString &var)
{
    execGdbCommand(QString("-break-watch ")+var+"\n");
}

/*!
 * \brief Asynchronous command. Starts execution of the inferior from the beginning. The inferior executes until either a breakpoint is encountered or the program exits.
 */
void GdbController::execRun()
{
    execGdbCommand("-exec-run");
}

/*!
 * \brief kill the inferior running program.
 */
void GdbController::execAbort()
{
    execGdbCommand("-exec-abort");
}

/*!
 * \brief Asynchronous command. Resumes the execution of the inferior program until a breakpoint is encountered, or until the inferior exits.
 */
void GdbController::execContinue()
{
    execGdbCommand("-exec-continue");
}

/*!
 * \brief Asynchronous command. Resumes the execution of the inferior program until the current function is exited. Displays the results returned by the function.
 */
void GdbController::execFinish()
{
    execGdbCommand("-exec-continue");
}

/*!
 * \brief Asynchronous command. Asynchronous command. Resumes execution of the inferior program, stopping when the beginning of the next source line is reached.
 */
void GdbController::execNext()
{
    execGdbCommand("-exec-next");
}

/*!
 * \brief Asynchronous command. Executes one machine instruction. If the instruction is a function call continues until the function returns. If the program stops at an instruction in the middle of a source line, the address will be printed as well.
 */
void GdbController::execNexti()
{
    execGdbCommand("-exec-next-instruction");
}

/*!
 * \brief Makes current function return immediately. Doesn't execute the inferior. Displays the new current frame.
 */
void GdbController::execReturn()
{
    execGdbCommand("-exec-return");
}
/*!
 * \brief Asynchronous command. Resumes execution of the inferior program, stopping when the beginning of the next source line is reached, if the next source line is not a function call. If it is, stop at the first instruction of the called function.
 */
void GdbController::execStep()
{
    execGdbCommand("-exec-step");
}

/*!
 * \brief Makes current function return immediately. Doesn't execute the inferior. Displays the new current frame.
 */
void GdbController::execStepi()
{
    execGdbCommand("-exec-step-instruction");
}

/*!
 * \brief Asynchronous command. Executes the inferior until the location specified in the argument is reached. If there is no argument, the inferior executes until a source line greater than the current one is reached. The reason for stopping in this case will be `location-reached'.
 *
 *example: -exec-until recursive2.c:6
 */
void GdbController::execUntil(const QString &location)
{
    execGdbCommand(QString("-exec-until ")+location);
}

void GdbController::updateDockInfos()
{
    requestForceUpdateLocal=true;
    //Updates local watch
    stackListLocals();
    //Update watch
    QStringList customWatchList=dbgOutputs->getWatchExpList();
    for(int i=0; i<customWatchList.count(); i++)
    {
        customIndexList.append(i);
        evaluate(customWatchList.at(i));
    }
    requestForceUpdateLocal=false;
}

void GdbController::stackListLocals()
{
    execGdbCommand("-stack-list-locals 1");
}

void GdbController::evaluate(const QString &expr)
{
    execGdbCommand(QString("-data-evaluate-expression ")+expr);
}

void GdbController::execGdbCommand(const QString &command)
{
    gdbProcessThread->execGdbCommand(command);
}

void GdbController::configureGDB()
{
#ifdef Q_OS_WIN32
    execGdbCommand("set new-console on");
#endif
    if(!fileType.isEmpty())
    {
        execGdbCommand(QString("set language " + fileType));
    }
}

void GdbController::createGDBThread()
{
    gdbProcessThread=new GdbThread(this);
    connect(gdbProcessThread, SIGNAL(parseMessage(QString)),
            this, SLOT(parseLine(QString)));
    connect(gdbProcessThread, SIGNAL(parseError(QString)),
            this, SLOT(parseError(QString)));
    connect(gdbProcessThread, SIGNAL(addSystemMessage(QString)),
            this, SLOT(parseCommand(QString)));
}

QSharedPointer<dbgOutputReceiver> GdbController::getDbgOutputs()
{
    return dbgOutputs;
}
