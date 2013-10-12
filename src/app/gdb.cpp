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

#include "gdb.h"

#ifdef Q_OS_UNIX
QString gdb::gdbPath="/usr/bin/gdb";
#endif

#ifdef Q_OS_WIN32
QString gdb::gdbPath="c:\\MinGW\\bin\\gdb";
#endif

bool gdb::checkResult=false;

static bool isAnsycChar(const char &c)
{
    return (c >= 'a' && c <= 'z') || c == '-';
}

gdb::gdb(QObject *parent) :
    QProcess(parent)
{
    checkGDB();
    connect(this,
            SIGNAL(readyReadStandardOutput()),
            SLOT(readGdbStandardOutput()));
    connect(this,
            SIGNAL(readyReadStandardError()),
            SLOT(readGdbStandardError()));
}

void gdb::readGdbStandardOutput()
{
    char buf[1000];
    while(readLine(buf,1000)>0)
    {
        QString _msg=QString::fromUtf8(buf);
        _msg.remove('\n');

        qDebug()<<_msg;

        parseLine(_msg);
    }
}

void gdb::parseLine(const QString &_msg)
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
                emit locals(result);
                break;
            }
            if(result.getName() == "value")
            {
                emit exprValue(result.getValue());
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

            emit errorOccured(result.getValue()+"\n");
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
        emit consoleOutputStream(parseOutputStream(begin,end));

        break;
    }
    case '@':
    {
        begin++;
        emit targetOutputStream(parseOutputStream(begin,end));

        break;
    }
    case '&':
    {
        begin++;
        emit logOutputStream(parseOutputStream(begin,end));

        break;
    }
    case '=':
    {
        //ignore this information
        break;
    }
    default:
        //program that is being debuged outputs
        emit targetOutputStream(_msg+'\n');
    }
}

QString gdb::parseOutputStream(const QChar *begin, const QChar *end)
{
    GdbMiValue result;
    result.build(begin,end);

    return result.getValue();
}

void gdb::parseBkpt(const GdbMiValue &gmvBkpt)
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

const QVector<bkpt_struct>* gdb::getBkptVec() const
{
    return &bkptVec;
}

void gdb::setGDBPath(const QString &path)
{
    gdbPath=path;
    checkGDB();
}

bool gdb::checkGDB()
{
    QFileInfo _fileInfo(gdbPath);

    return checkResult=_fileInfo.exists() && _fileInfo.isExecutable();
}

bool gdb::runGDB(const QString &filePath)
{
    if(checkResult)
    {
        QStringList _arg;
        _arg<<filePath<<"--interpreter"<<"mi";

        start(gdbPath,_arg);

        return true;
    }
    else
    {
        return false;
    }
}

void gdb::quitGDB()
{
    write(qPrintable(QString("-gdb-exit\n")));
    //! TODO: too long waitting time if gdb doesn't quit.
    waitForFinished();

    if(state() == QProcess::Running)
    {
        //gdb doesn't quit till now, so we have to kill it.
        this->kill();
    }
}

void gdb::readGdbStandardError()
{
    QByteArray err = readAllStandardError();

    emit errorOccured(QString(err));
}

/*!
 *! * \brief set the break point by line number.
 *!
 *!The breakpoint number is not in effect until it has been hit count times.
 *! */
void gdb::setBreakPoint(const QString &fileName,
                        const int &lineNum,
                        const int &count)
{
    write(qPrintable(QString("-break-insert ")+
                     fileName+":"+
                     QString::number(lineNum)+" "+
                     QString::number(count)+"\n"));
}

/*!
 * \brief set the break point by the function's name.
 * \param functionName  the name of the function
 */
void gdb::setBreakPoint(const QString &functionName)
{
    write(qPrintable(QString("-break-insert ")+
                     functionName+"\n"));
}


/*!
 * \brief Breakpoint number will stop the program only if the condition in expr is true.
 */
void gdb::setBreakCondition(const int &number, const QString &expr)
{
    write(qPrintable(QString("-break-condition ")+
                     QString::number(number)+" "
                     +expr+"\n"));
}

/*!
 * \brief Create a watchpoint
 * \param var
 */
void gdb::setWatchPoint(const QString &var)
{
    write(qPrintable(QString("-break-watch ")+
                     var+"\n"));
}


/*!
 * \brief Asynchronous command. Starts execution of the inferior from the beginning. The inferior executes until either a breakpoint is encountered or the program exits.
 */
void gdb::execRun()
{
    write(qPrintable(QString("-exec-run\n")));
}

/*!
 * \brief kill the inferior running program.
 */
void gdb::execAbort()
{
    write(qPrintable(QString("-exec-abort\n")));
}

/*!
 * \brief Asynchronous command. Resumes the execution of the inferior program until a breakpoint is encountered, or until the inferior exits.
 */
void gdb::execContinue()
{
    write(qPrintable(QString("-exec-continue\n")));
}

/*!
 * \brief Asynchronous command. Resumes the execution of the inferior program until the current function is exited. Displays the results returned by the function.
 */
void gdb::execFinish()
{
    write(qPrintable(QString("-exec-continue\n")));
}

/*!
 * \brief Asynchronous command. Asynchronous command. Resumes execution of the inferior program, stopping when the beginning of the next source line is reached.
 */
void gdb::execNext()
{
    write(qPrintable(QString("-exec-next\n")));
}

/*!
 * \brief Makes current function return immediately. Doesn't execute the inferior. Displays the new current frame.
 */
void gdb::execReturn()
{
    write(qPrintable(QString("-exec-return\n")));
}

/*!
 * \brief Makes current function return immediately. Doesn't execute the inferior. Displays the new current frame.
 */
void gdb::execStepi()
{
    write(qPrintable(QString("-exec-step-instruction\n")));
}

/*!
 * \brief Asynchronous command. Executes the inferior until the location specified in the argument is reached. If there is no argument, the inferior executes until a source line greater than the current one is reached. The reason for stopping in this case will be `location-reached'.
 *
 *example: -exec-until recursive2.c:6
 */
void gdb::execUntil(const QString &location)
{
    write(qPrintable(QString("-exec-until ")+location+"\n"));
}

void gdb::stackListLocals()
{
    write(qPrintable(QString("-stack-list-locals 1\n")));
}

void gdb::evaluate(const QString &expr)
{
    write(qPrintable(QString("-data-evaluate-expression ")+expr+"\n"));
}
