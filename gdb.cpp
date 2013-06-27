#include "gdb.h"

#ifdef Q_OS_UNIX
QString gdb::gdbPath="/usr/bin/gdb";
#endif

#ifdef Q_OS_WIN32
QString gdb::gdbPath="c:\\MinGW\\bin\\gdb";
#endif

bool gdb::checkResult=false;

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
        if(_msg.startsWith(QString("^done,bkpt=")))
            parseBkpt(_msg);
        else if(_msg.startsWith(QString("^error,msg=")))
        {
            QString _err_msg=_msg.mid(12);
            _err_msg.remove("\"\n");
            emit errorOccured(_err_msg);
            qDebug()<<_err_msg;
        }
        else if(_msg.startsWith(QString("*stopped")))
        {
            parseStopMsg(_msg);
        }
        else
            qDebug()<<_msg;
    }
}

void gdb::parseStopMsg(const QString &_msg)
{
    QString _stop_msg=_msg.mid(9);
    QString _var_name;
    while(!_stop_msg.isEmpty())
    {
        _var_name=_stop_msg.left(_stop_msg.indexOf('='));
        _stop_msg.remove(0,_var_name.length()+1);
    }
}

void gdb::parseBkpt(const QString &_msg)
{
    //first, remove { , "} , [ , ]
    QString _tmp_str=_msg.mid(12);
    _tmp_str.remove("\"}");
    _tmp_str.remove('[');
    _tmp_str.remove(']');
    _tmp_str.remove('\n');

    //then split by ",
    QStringList _str_list_bkpt=_tmp_str.split("\",");
    int i=_str_list_bkpt.count();

    //final, parse bkpt
    bkpt_struct _tmp_bkpt;
    qDebug()<<"bkpt start";
    while(i--)
    {
        if(_str_list_bkpt[i].startsWith("original-location"))
        {
            _tmp_bkpt.original_location=_str_list_bkpt[i].mid(19);
            qDebug()<<_tmp_bkpt.original_location;
        }
        else if(_str_list_bkpt[i].startsWith("times"))
        {
            QString _times=_str_list_bkpt[i].mid(7);
            _tmp_bkpt.times=_times.toInt();
            qDebug()<<_tmp_bkpt.times;
        }
        else if(_str_list_bkpt[i].startsWith("thread-groups"))
        {
            _tmp_bkpt.threadGroups=_str_list_bkpt[i].mid(14);
            _tmp_bkpt.threadGroups.remove('\"');
            qDebug()<<_tmp_bkpt.threadGroups;
        }
        else if(_str_list_bkpt[i].startsWith("line"))
        {
            QString _linenum=_str_list_bkpt[i].mid(6);
            _tmp_bkpt.line=_linenum.toInt();
            qDebug()<<_tmp_bkpt.line;
        }
        else if(_str_list_bkpt[i].startsWith("fullname"))
        {
            _tmp_bkpt.fullName=_str_list_bkpt[i].mid(10);
            qDebug()<<_tmp_bkpt.fullName;
        }
        else if(_str_list_bkpt[i].startsWith("file"))
        {
            _tmp_bkpt.file=_str_list_bkpt[i].mid(6);
            qDebug()<<_tmp_bkpt.file;
        }
        else if(_str_list_bkpt[i].startsWith("func"))
        {
            _tmp_bkpt.func=_str_list_bkpt[i].mid(6);
            qDebug()<<_tmp_bkpt.func;
        }
        else if(_str_list_bkpt[i].startsWith("addr"))
        {
            _tmp_bkpt.addr=_str_list_bkpt[i].mid(6);
            qDebug()<<_tmp_bkpt.addr;
        }
        else if(_str_list_bkpt[i].startsWith("enabled"))
        {
            QString _str_enabled=_str_list_bkpt[i].mid(9);
            _tmp_bkpt.enabled=_str_enabled.toLower()=="y"?true:false;
            qDebug()<<_tmp_bkpt.enabled;
        }
        else if(_str_list_bkpt[i].startsWith("disp"))
        {
            _tmp_bkpt.disp=_str_list_bkpt[i].mid(6);
            qDebug()<<_tmp_bkpt.disp;
        }
        else if(_str_list_bkpt[i].startsWith("type"))
        {
            _tmp_bkpt.type=_str_list_bkpt[i].mid(6);
            qDebug()<<_tmp_bkpt.type;
        }
        else if(_str_list_bkpt[i].startsWith("number"))
        {
            QString _num=_str_list_bkpt[i].mid(8);
            _tmp_bkpt.number=_num.toInt();
            qDebug()<<_tmp_bkpt.number;
        }
        else
        {
            qDebug()<<"kci_gdb: unknow bkpt arg";
            qDebug()<<_str_list_bkpt[i];
        }
    }
    qDebug()<<"bkpt end";
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
