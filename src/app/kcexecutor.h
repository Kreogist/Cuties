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


#ifndef KCEXECUTOR_H
#define KCEXECUTOR_H

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

#include <fstream>

#include "kcglobal.h"
#include "fpc.h"

using namespace std;

struct Terminal
{
    char terminal_name[50];
    char arg[10];
    Terminal()
    {
        terminal_name[0]=0;
        arg[0]=0;
    }
    Terminal(const char *str_ter, const char *str_arg)
    {
        strcpy(terminal_name,str_ter);
        strcpy(arg,str_arg);
    }
};

class KCExecutor;

class KCRunner : public QThread
{
    Q_OBJECT
public:
    explicit KCRunner(QObject *parent = 0);
    ~KCRunner();

    static Terminal getDefaultTerminal();
    void setTestCase(const QByteArray &input,const QByteArray &output);
    void setBackgroundExec(bool enabled);
    bool isBackgroundExec() const;
    bool isEnabledAutoInput() const;
    void setEnabledAutoInput(bool value);
    QByteArray getUserOutput();

    QString getPath() const;
    void setPath(const QString &value);

public slots:
    void onReadyRead();

protected:
    void run();

private:
    QReadWriteLock lock;

    QByteArray m_input;
    QByteArray m_output;

    QReadWriteLock output_lock;
    QByteArray user_output;

    QString path;

    QProcess *process;
    bool enabledBackExec;
    bool enabledAutoInput;
};

class KCExecutor : public QObject
{
    Q_OBJECT
public:
    explicit KCExecutor(QObject *parent = 0);
    ~KCExecutor();

    static void setDefaultTerminal(const int &num);
    static QStringList getSupportTerminalList();
    static KCExecutor *getInstance();

public slots:
    void exec(const QString &programPath);

private:
    QReadWriteLock lock;
    QList<KCRunner *> runnerList;

    static KCExecutor *instance;
};

#endif // KCEXECUTOR_H
