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

#ifndef COMPILERBASE_H
#define COMPILERBASE_H

#include <QProcess>
#include <QFileInfo>

struct ErrInfo
{
    int nLineNum;
    int nColumnNum;
    QString strFilePath;
    QString strErrDescription;
};

class compilerBase : public QProcess
{
    Q_OBJECT
public:
    explicit compilerBase(QObject *parent = 0);

    QString version();
    void startCompile(const QString& filePath);
    virtual void setCompilerPath(const QString& ) = 0;
    virtual QString path(){return "";}
    virtual bool checkCompilerPath(const QString& path);
    virtual QString compilerName() = 0;

signals:
    void compileinfo(QString msg);
    void compileError(ErrInfo errInfo);
    void output(QString msg);

public slots:
    virtual void onOutputReady() = 0;

protected:
    void emitCompileInfo(const QString& compilerPath,
                         const QStringList& arg);
    virtual QStringList getVersionArg() = 0;
    virtual QStringList getCompileArg(const QString& filePath) = 0;
    virtual QStringList getcompileEnv() = 0;

private slots:
    void onFinished();

private:
    QMetaObject::Connection connectionHandle;
};

#endif // COMPILERBASE_H
