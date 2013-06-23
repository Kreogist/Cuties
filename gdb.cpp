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
 *!The breakpoint number lineNum is not in effect until it has been hit count times.
 *! */
void gdb::setBreakPoint(const int &lineNum, const int &count)
{
    write(qPrintable(QString("-break-after ")+
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
