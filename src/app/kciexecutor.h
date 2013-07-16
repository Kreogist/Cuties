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

#ifndef KCIEXECUTOR_H
#define KCIEXECUTOR_H

#include <QProcess>
#include <QProcessEnvironment>
#include <QThread>
#include <QByteArray>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QReadWriteLock>
#include <QFileInfo>
#include <QApplication>
#include <QSettings>
#include <QDir>
#include <QFile>
#include <QDebug>

#include "kciglobal.h"
#include "fpc.h"

struct Terminal
{
    char terminal_name[50];
    char arg[10];
    Terminal(){terminal_name[0]=0; arg[0]=0;}
    Terminal(const char *str_ter, const char *str_arg)
    {
        strcpy(terminal_name,str_ter);
        strcpy(arg,str_arg);
    }
};

class kciExecutor;

class kciRunner : public QThread
{
    Q_OBJECT
public:
    kciExecutor *p;
    static Terminal getDefaultTerminal();

public slots:
    void onReadyRead();

protected:
    void run();
};

class kciExecutor : public QObject
{
    Q_OBJECT
public:
    explicit kciExecutor(QObject *parent = 0);
    ~kciExecutor();

    void setTestCase(const QByteArray& input,const QByteArray& output);
    void setBackgroundExec(bool enabled);
    bool getBackgroundExec() const;
    bool isEnabledAutoInput() const;
    void setEnabledAutoInput(bool value);
    void exec(const QString& programPath);
    QByteArray getUserOutput();

    static void setDefaultTerminal(const int &num);
    static QStringList getSupportTerminalList();

private:
    QString path;
    QReadWriteLock lock;
    QByteArray m_input;
    QByteArray m_output;

    QReadWriteLock output_lock;
    QByteArray user_output;

    kciRunner *worker;
    QProcess* process;
    bool enabledBackExec;
    bool enabledAutoInput;

    friend class kciRunner;
};

#endif // KCIEXECUTOR_H
