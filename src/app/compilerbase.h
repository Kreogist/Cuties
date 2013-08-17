/*
 *  Copyright 2013 Kreogist Dev Team
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

#ifndef COMPILERBASE_H
#define COMPILERBASE_H

#include <QScopedPointer>
#include <QProcess>
#include <QFileInfo>

#include "connectionhandler.h"

struct ErrInfo
{
    int nLineNum;
    int nColumnNum;
    QString strFilePath;
    QString strErrDescription;
};

class compilerBase : public QObject
{
    Q_OBJECT
public:
    explicit compilerBase(QObject *parent = 0);

    QString version();
    void startCompile(const QString& filePath);
    virtual void setCompilerPath(const QString& ) = 0;
    virtual QString path()=0;
    virtual bool checkCompilerPath(const QString& path);
    virtual QString compilerName() = 0;

signals:
    void compileCmd(QString cmd);
    void compileError(ErrInfo errInfo);
    void output(QString msg);
    void compileFinished(int exitNum);

public slots:
    void onOutputReady();

protected:
    void emitCompileCmd(const QString& compilerPath,
                         const QStringList &arg);
    virtual QStringList getVersionArg() = 0;
    virtual QStringList getCompileArg(const QString& filePath) = 0;
    virtual QStringList getcompileEnv() = 0;

    virtual bool checkHasErrorByExitNum(const int& exitNum){return exitNum > 0;}

    virtual void parseLine(const QString& text) = 0;

private slots:
    void onFinished(int exitNum);

private:
    connectionHandler connectionHandles;
    QScopedPointer<QProcess> compiler;
};

#endif // COMPILERBASE_H
