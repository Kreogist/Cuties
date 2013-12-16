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
#include <QDebug>
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
    //Use the current configure start compile process.
    void startCompile(const QString &filePath);
    /*
     * Some virtual functions.
     * These functions must be provided by the inherit class.
     */
    virtual QString compilerPath()=0;
    virtual bool checkCompilerPath(const QString &compilerPath);
    virtual QString compilerName()=0;
    bool compilerExsist();

signals:
    void compileCommandLine(QString compileCommand);
    void compileError(compileErrorInfo compileErrorInfo);
    void compileMessage(QString compileMessage);
    void compileFinished(int exitNumber);

public slots:
    void readyForOutput();

protected:
    void emitCompileCommand(const QString &compilerPath,
                            const QStringList &arg);
    virtual QStringList getVersionArg() = 0;
    virtual QStringList getCompileArg(const QString &filePath) = 0;
    virtual QString getCompileEnv() = 0;

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
