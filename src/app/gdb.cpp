/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *      Wang Luming <wlm199558@126.com>
 *      Miyanaga Saki <tomguts@126.com>
 *      Zhang Jiayi <bf109g2@126.com>
 *
 *  This file is part of Kreogist-Cute-IDE.
 *
 *    Kreogist-Cute-IDE is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cute-IDE is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cute-IDE.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gdb.h"

#ifdef Q_OS_UNIX
QString gdb::gdbPath="/usr/bin/gdb";
#endif

#ifdef Q_OS_WIN32
QString gdb::gdbPath="c:\\MinGW\\bin\\gdb";
#endif

bool gdb::checkResult=false;

static bool isAnsycChar(const char& c)
{
    return (c >= 'a' && c <= 'z') || c == '-';
}

gdb::gdb(QObject *parent) :
    QProcess(parent)
{
    checkGDB();
    connect(this,SIGNAL(readyRead()),SLOT(onReadReady()));

    setReadChannelMode(QProcess::MergedChannels);
}

void gdb::onReadReady()
{
    char buf[1000];
    while(readLine(buf,1000)>0)
    {
        QString _msg(buf);
        _msg.remove('\n');

        qDebug()<<_msg;
        parseLine(_msg);
    }
}

void gdb::parseLine(const QString &_msg)
{
    if(_msg.isEmpty() || _msg == "(gdb)")
        return ;

    char _firstChar=_msg.begin()->toLatin1();
    const QChar* begin=_msg.begin();
    const QChar* end=_msg.end();

    switch(_firstChar)
    {
    case '^':
    {
        begin++;

        QString _str_async;
        for(;begin<end;begin++)
        {
            if(isAnsycChar(begin->toLatin1()))
                _str_async+=*begin;
            else
                break;
        }

        if(_str_async == "done")
        {
            begin++;
            GdbMiValue result;

            result.build(begin,end);

            if(result.getName() == "bkpt")
            {
                parseBkpt(result);
            }
        }
        else if(_str_async == "error")
        {
            begin++;
            GdbMiValue result;

            result.build(begin,end);

            emit errorOccured(result.getValue());
        }
    }
    case '*':
    {
        begin++;

        QString _str_async;
        for(;begin<end;begin++)
        {
            if(isAnsycChar(begin->toLatin1()))
                _str_async+=*begin;
            else
                break;
        }

        begin++;    //skip ,

        GdbMiValue result;

        for(;begin<end;begin++)
        {
            GdbMiValue child;
            child.build(begin,end);

            result+=child;
        }

        if(_str_async == "stopped")
        {
            qDebug()<<*begin;
        }
    }
    default:
        qDebug()<<_msg;
    }
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
        _arg<<filePath<<"-i"<<"mi";

        start(gdbPath,_arg);

        return true;
    }
    else
        return false;
}

void gdb::quitGDB()
{
    write(qPrintable(QString("-gdb-exit\n")));
}


/*!
 *! * \brief set the break point by line number.
 *!
 *!The breakpoint number is not in effect until it has been hit count times.
 *! */
void gdb::setBreakPoint(const int &number, const int &count)
{
    write(qPrintable(QString("-break-after ")+
                     QString::number(number)+" "+
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
void gdb::setBreakCondition(const int &lineNum, const QString &expr)
{
    write(qPrintable(QString("-break-condition ")+
                     QString::number(lineNum)+" "
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
