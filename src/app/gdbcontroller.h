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

#ifndef GDBCONTROLLER_H
#define GDBCONTROLLER_H

#include <QProcess>
#include <QFileInfo>
#include <QString>
#include <QStringList>
#include <QCharRef>
#include <QVector>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QLocalServer>
#include <QLocalSocket>
#include <QSocketNotifier>
#include <QDebug>
#include <QTextCodec>
#include <QThread>

#include "gdbmivalue.h"
#include "dbgoutputreceiver.h"
#include "kcdebuggerconfigure.h"
#include "kcconnectionhandler.h"

struct bkpt_struct
{
    int number;
    QString type;
    bool enabled;
    QString disp;
    QString addr;
    QString func;
    QString file;
    QString fullName;
    int line;
    QString threadGroups;
    int times;
    QString original_location;
};

class GdbThread : public QThread
{
    Q_OBJECT
public:
    explicit GdbThread(QObject * parent = 0);
    ~GdbThread();
    void run() Q_DECL_OVERRIDE;

    QString getFilePath() const;
    void setFilePath(const QString &value);
    void quitGDB();
    QString getGdbPath() const;
    void setGdbPath(const QString &value);
    bool isGdbRunning();

signals:
    void readyReadStandardError();
    void readyReadStandardOutput();
    void parseMessage(QString value);
    void parseError(QString value);
    void addSystemMessage(QString value);

public slots:
    void readGdbStandardError();
    void readGdbStandardOutput();
    void execGdbCommand(const QString &command);

private:
    QScopedPointer<QProcess> gdbProcess;
    KCConnectionHandler readProcessData;
    QString filePath;
    QString gdbPath;
    QString messageCache;
};

class GdbController : public QObject
{
    Q_OBJECT
public:
    explicit GdbController(QObject *parent = 0);

    static void setGDBPath(const QString &path);
    static bool checkGDB();
    static void isGDBPathRight();

    const QVector<bkpt_struct> *getBkptVec() const;

    QSharedPointer<dbgOutputReceiver> getDbgOutputs();

signals:
    void requireDisconnectDebug();
    void requireLineJump(int lineNum);

public slots:
    bool runGDB(const QString &filePath);
    void quitGDB();

    //breakpoint
    void setBreakPointList(QList<int> breakpointLine);
    void setBreakPoint(const QString &fileName,
                       const int &lineNum,
                       const int &count);
    void setBreakPoint(const int &lineNum);
    void setBreakPoint(const QString &functionName);
    void setBreakCondition(const int &number, const QString &expr);

    //watchpoint
    void setWatchPoint(const QString &var);

    //Program Control
    void execRun();
    void execAbort();
    void execContinue();
    void execFinish();
    void execNext();
    void execReturn();
    void execStep();
    void execStepi();
    void execNexti();
    void execUntil(const QString &location);

    //Stack Manipulation
    void stackListLocals();

    //Data Evaluate
    void evaluate(const QString &expr);

    //run gdb command
    void execGdbCommand(const QString &command);

private slots:
    void parseLine(const QString &_msg);
    void parseError(const QString &_error);
    void parseCommand(const QString &_cmd);

private:
    void configureGDB();

    void parseBkpt(const GdbMiValue &gmvBkpt);
    QString parseOutputStream(const QChar *begin, const QChar *end);

    static QString gdbPath;
    static bool checkResult;
    bool exitedNormally=false;
    QVector<bkpt_struct> bkptVec;

    GdbThread *gdbProcessThread;
    QSharedPointer<dbgOutputReceiver> dbgOutputs;
    QTextCodec *debugCodec;
    QTextCodec::ConverterState debugCodecState;
    KCDebuggerConfigure *instance;
};

#endif // GDBCONTROLLER_H
