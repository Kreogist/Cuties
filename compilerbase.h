/*
 *  Copyright 2013 Wang Luming <wlm199558@126.com>
 *
 *  compilerbase.h is part of Kreogist-Cute-IDE.
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

struct compilerMessage
{
    enum msgType
    {
        error,
        warning,
        others
    };

    msgType type;
    int lineNum;
    QString msg;
};

class compilerBase : public QProcess
{
    Q_OBJECT
public:
    explicit compilerBase(QObject *parent = 0);

    virtual void startCompile(const QString& ) = 0;
    virtual QString version() = 0;
    virtual QString path(){return "";}
    virtual bool checkCompilerPath(const QString& ) = 0;
    virtual QString compilerName(){return "compilerase";}

signals:
    void output(QString msg);

};

#endif // COMPILERBASE_H
