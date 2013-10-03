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

#ifndef KCCOMPILERBASE_H
#define KCCOMPILERBASE_H

#include <QScopedPointer>
#include <QProcess>
#include <QFileInfo>

#include "kcconnectionhandler.h"

//A structure to record compiler error
struct compileErrorInfo
{
    int errorLine;
    int errorColumn;
    QString errorFilePath;
    QString errorDescription;
};

class KCCompilerBase : public QObject
{
    Q_OBJECT
public:
    explicit KCCompilerBase(QObject *parent = 0);
    //Get compiler version.
    QString compilerVersion();
    void startCompile(const QString &filePath);
    virtual QString compilerPath()=0;
    virtual bool checkCompilerPath(const QString &compilerPath);
    virtual QString compilerName() = 0;

signals:
    void compileCommandLine(QString cmd);
    void compileError(compileErrorInfo errInfo);
    void output(QString msg);
    void compileFinished(int exitNum);

public slots:
    void onOutputReady();

protected:
    void emitCompileCmd(const QString &compilerPath,
                        const QStringList &arg);
    virtual QStringList getVersionArg() = 0;
    virtual QStringList getCompileArg(const QString &filePath) = 0;
    virtual QStringList getcompileEnv() = 0;

    virtual bool checkHasErrorByExitNum(const int &exitNum)
    {
        return exitNum > 0;
    }

    virtual void parseLine(const QString &text) = 0;

private slots:
    void onFinished(int exitNum);

private:
    KCConnectionHandler connectionHandles;
    QScopedPointer<QProcess> compiler;
};

#endif // KCCOMPILERBASE_H
