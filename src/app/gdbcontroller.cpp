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

#include "gdbcontroller.h"

#ifdef Q_OS_UNIX
QString GdbController::gdbPath="/usr/bin/gdb";
#endif

#ifdef Q_OS_WIN32
QString GdbController::gdbPath="c:\\MinGW\\bin\\gdb";
#endif

bool GdbController::checkResult=false;

static bool isAnsycChar(const char &c)
{
    return (c >= 'a' && c <= 'z') || c == '-';
}

GdbController::GdbController(QObject *parent) :
    QObject(parent)
{
    dbgOutputs.reset(new dbgOutputReceiver(this));
    checkGDB();
}

void GdbController::readGdbStandardOutput()
{
    char buf[1000];
    while(gdbProcess->readLine(buf,1000)>0)
    {
        QString _msg=QString::fromUtf8(buf);
        _msg.remove('\n');

        parseLine(_msg);
    }
}

void GdbController::parseLine(const QString &_msg)
{
    if(_msg.isEmpty() || _msg.contains("(gdb)"))
    {
        return ;
    }

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

            if(result.getName() == "bkpt")
            {
                parseBkpt(result);
                break;
            }
            if(result.getName() == "locals")
            {
                dbgOutputs->addLocals(result);
                break;
            }
            if(result.getName() == "value")
            {
                dbgOutputs->addExprValue(result.getValue());
                break;
            }
        }
        else if(_str_async == "running")
        {

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

        begin++;    //skip ,

        GdbMiValue result;

        for(; begin<end; begin++)
        {
            GdbMiValue child;
            child.build(begin,end);

            result+=child;
        }

        if(_str_async == "stopped")
        {
            stackListLocals();
            qDebug()<<*begin;
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
        begin++;
        dbgOutputs->addLogOutput(parseOutputStream(begin,end));

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

QString GdbController::parseOutputStream(const QChar *begin, const QChar *end)
{
    GdbMiValue result;
    result.build(begin,end);

    return result.getValue();
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
    qDebug()<<_tmp_bkpt.original_location;*/

    bkptVec<<_tmp_bkpt;

}

const QVector<bkpt_struct> *GdbController::getBkptVec() const
{
    return &bkptVec;
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
        gdbProcess.reset(new QProcess(this));
        QStringList _arg;
        _arg<<filePath<<"--interpreter"<<"mi";


        connect(gdbProcess.data(),
                SIGNAL(readyReadStandardOutput()),
                this,
                SLOT(readGdbStandardOutput()));
        connect(gdbProcess.data(),
                SIGNAL(readyReadStandardError()),
                this,
                SLOT(readGdbStandardError()));

        gdbProcess->start(gdbPath,_arg);

        return true;
    }
    else
    {
        return false;
    }
}

void GdbController::quitGDB()
{
    gdbProcess->write(qPrintable(QString("-gdb-exit\n")));
    //! TODO: too long waitting time if gdb doesn't quit.
    gdbProcess->waitForFinished();

    if(gdbProcess->state() == QProcess::Running)
    {
        //gdb doesn't quit till now, so we have to kill it.
        gdbProcess->kill();
    }
}

void GdbController::readGdbStandardError()
{
    QByteArray err = gdbProcess->readAllStandardError();

    dbgOutputs->addErrorText(QString(err));
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
    gdbProcess->write(qPrintable(QString("-break-insert ")+
                     fileName+":"+
                     QString::number(lineNum)+" "+
                     QString::number(count)+"\n"));
}

/*!
 * \brief set the break point by the function's name.
 * \param functionName  the name of the function
 */
void GdbController::setBreakPoint(const QString &functionName)
{
    gdbProcess->write(qPrintable(QString("-break-insert ")+
                     functionName+"\n"));
}


/*!
 * \brief Breakpoint number will stop the program only if the condition in expr is true.
 */
void GdbController::setBreakCondition(const int &number, const QString &expr)
{
    gdbProcess->write(qPrintable(QString("-break-condition ")+
                     QString::number(number)+" "
                     +expr+"\n"));
}

/*!
 * \brief Create a watchpoint
 * \param var
 */
void GdbController::setWatchPoint(const QString &var)
{
    gdbProcess->write(qPrintable(QString("-break-watch ")+
                     var+"\n"));
}


/*!
 * \brief Asynchronous command. Starts execution of the inferior from the beginning. The inferior executes until either a breakpoint is encountered or the program exits.
 */
void GdbController::execRun()
{
    gdbProcess->write(qPrintable(QString("-exec-run\n")));
}

/*!
 * \brief kill the inferior running program.
 */
void GdbController::execAbort()
{
    gdbProcess->write(qPrintable(QString("-exec-abort\n")));
}

/*!
 * \brief Asynchronous command. Resumes the execution of the inferior program until a breakpoint is encountered, or until the inferior exits.
 */
void GdbController::execContinue()
{
    gdbProcess->write(qPrintable(QString("-exec-continue\n")));
}

/*!
 * \brief Asynchronous command. Resumes the execution of the inferior program until the current function is exited. Displays the results returned by the function.
 */
void GdbController::execFinish()
{
    gdbProcess->write(qPrintable(QString("-exec-continue\n")));
}

/*!
 * \brief Asynchronous command. Asynchronous command. Resumes execution of the inferior program, stopping when the beginning of the next source line is reached.
 */
void GdbController::execNext()
{
    gdbProcess->write(qPrintable(QString("-exec-next\n")));
}

/*!
 * \brief Asynchronous command. Executes one machine instruction. If the instruction is a function call continues until the function returns. If the program stops at an instruction in the middle of a source line, the address will be printed as well.
 */
void GdbController::execNexti()
{
    gdbProcess->write(qPrintable(QString("-exec-next-instruction\n")));
}

/*!
 * \brief Makes current function return immediately. Doesn't execute the inferior. Displays the new current frame.
 */
void GdbController::execReturn()
{
    gdbProcess->write(qPrintable(QString("-exec-return\n")));
}
/*!
 * \brief Asynchronous command. Resumes execution of the inferior program, stopping when the beginning of the next source line is reached, if the next source line is not a function call. If it is, stop at the first instruction of the called function.
 */
void GdbController::execStep()
{
    gdbProcess->write(qPrintable(QString("-exec-step\n")));
}

/*!
 * \brief Makes current function return immediately. Doesn't execute the inferior. Displays the new current frame.
 */
void GdbController::execStepi()
{
    gdbProcess->write(qPrintable(QString("-exec-step-instruction\n")));
}

/*!
 * \brief Asynchronous command. Executes the inferior until the location specified in the argument is reached. If there is no argument, the inferior executes until a source line greater than the current one is reached. The reason for stopping in this case will be `location-reached'.
 *
 *example: -exec-until recursive2.c:6
 */
void GdbController::execUntil(const QString &location)
{
    gdbProcess->write(qPrintable(QString("-exec-until ")+location+"\n"));
}

void GdbController::stackListLocals()
{
    gdbProcess->write(qPrintable(QString("-stack-list-locals 1\n")));
}

void GdbController::evaluate(const QString &expr)
{
    gdbProcess->write(qPrintable(QString("-data-evaluate-expression ")+expr+"\n"));
}

void GdbController::execGdbCommand(const QString &command)
{
    gdbProcess->write(qPrintable(command));
}

QSharedPointer<dbgOutputReceiver> GdbController::getDbgOutputs()
{
    return dbgOutputs;
}

