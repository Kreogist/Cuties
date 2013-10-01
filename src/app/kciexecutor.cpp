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


#include "kciexecutor.h"

#ifdef Q_OS_WIN32
const QString console_runner_path("KciConsoleRunner.exe");
#else
const QString console_runner_path("KciConsoleRunner");
#endif

#ifdef Q_OS_UNIX
static const int terminalCount = 8;
static const Terminal knownTerminals[terminalCount] =
{
    {"xterm", "-e"},
    {"gnome-terminal", "-x"},
    {"konsole", "-e"},
    {"aterm", "-e"},
    {"Eterm", "-e"},
    {"rxvt", "-e"},
    {"urxvt", "-e"},
    {"xfce4-terminal", "-x"}
};
#else
static const int terminalCount = 1;
static const Terminal knownTerminals[terminalCount] =
{
    {"cmd", "/c"}
};
#endif

Terminal kciRunner::getDefaultTerminal()
{
    QSettings settings(kciGlobal::getInstance()->getSettingsFileName(),QSettings::IniFormat);
    settings.beginGroup("DefaultTerminal");
    Terminal ret(
                settings.value("name", knownTerminals[0].terminal_name).toByteArray().constData(),
            settings.value("arg",knownTerminals[0].arg).toByteArray().constData());
    settings.endGroup();

    return ret;
}

QStringList kciExecutor::getSupportTerminalList()
{
    QStringList ret;
    for(int i=0;i<terminalCount;i++)
        ret<<knownTerminals[i].terminal_name;
    return ret;
}

void kciExecutor::setDefaultTerminal(const int& num)
{
    if(Q_LIKELY(num<terminalCount))
    {
        QSettings settings(kciGlobal::getInstance()->getSettingsFileName(),QSettings::IniFormat);
        settings.beginGroup("DefaultTerminal");
        settings.setValue("name",knownTerminals[num].terminal_name);
        settings.value("arg",knownTerminals[num].arg);
        settings.endGroup();
    }
}

kciRunner::kciRunner(QObject *parent):
    QThread(parent)
{
    process=NULL;
}

kciRunner::~kciRunner()
{
    if(process==NULL)
        return ;

    if(process->state() != QProcess::NotRunning)
    {
        process->kill();
        process->waitForFinished();
    }
}

void kciRunner::run()
{
        process=new QProcess;
        process->setReadChannelMode(QProcess::MergedChannels);
        if(enabledBackExec)
        {
            connect(process,SIGNAL(readyRead()),
                    this,SLOT(onReadyRead()));
            process->start(path);
        }
        else
        {
            QStringList arg;
            QFileInfo info(path);

            process->setWorkingDirectory(info.absoluteDir().absolutePath());
#ifdef Q_OS_MACX
            arg
#else
            Terminal terminal=getDefaultTerminal();
            arg<<terminal.arg
#endif
#ifdef Q_OS_WIN32
               <<"start"
#endif
               <<qApp->applicationDirPath()+'/'+console_runner_path<<path;

            connect(process,SIGNAL(finished(int)),
                    this,SLOT(quit()));
            connect(this,SIGNAL(finished()),
                    this,SLOT(deleteLater()));
#ifdef Q_OS_MACX
            process->start(qApp->applicationDirPath() + "/openTerminal.command",arg);
#else
            process->start(QLatin1String(terminal.terminal_name),arg);
#endif
        }

        if(enabledAutoInput)
            process->write(m_input);

    exec();
}

void kciRunner::onReadyRead()
{
    output_lock.lockForWrite();

    user_output+=process->readAll();

    output_lock.unlock();
}

void kciRunner::setTestCase(const QByteArray &input, const QByteArray &output)
{
    m_input=input;
    m_output=output;
}

bool kciRunner::isBackgroundExec() const
{
    return enabledBackExec;
}

void kciRunner::setBackgroundExec(bool value)
{
    lock.lockForWrite();
    enabledBackExec = value;
    lock.unlock();
}

bool kciRunner::isEnabledAutoInput() const
{
    return enabledAutoInput;
}

void kciRunner::setEnabledAutoInput(bool value)
{
    lock.lockForWrite();
    enabledAutoInput = value;
    lock.unlock();
}

QByteArray kciRunner::getUserOutput()
{
    output_lock.lockForRead();
    QByteArray ret = user_output;
    output_lock.unlock();
    return ret;
}

QString kciRunner::getPath() const
{
    return path;
}

void kciRunner::setPath(const QString &value)
{
    path = value;
}

kciExecutor* kciExecutor::instance=NULL;

kciExecutor::kciExecutor(QObject *parent) :
    QObject(parent)
{
}

kciExecutor::~kciExecutor()
{
    /*for(auto i=runnerList.begin(),e=runnerList.end();
        i!=e;
        i++)
    {
        delete i;
    }*/
}

void kciExecutor::exec(const QString &programPath)
{
    kciRunner* runner=new kciRunner;
#ifdef Q_OS_WIN32
    QString winPath;
    winPath=programPath;
    winPath=winPath.replace("//","/");
    runner->setPath(winPath);
#else
    runner->setPath(programPath);
#endif
    runner->setBackgroundExec(false);
    runner->setEnabledAutoInput(false);
    runner->start();
}

kciExecutor* kciExecutor::getInstance()
{
    if(instance==NULL)
    {
        return instance=new kciExecutor;
    }

    return instance;
}
