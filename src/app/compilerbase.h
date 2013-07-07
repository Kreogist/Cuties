/*
 *  Copyright 2013 Wang Luming <wlm199558@126.com>
 *  Copyright 2013 Ye Haolei(Miyanaga Saki) <tomguts@126.com>
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

class compilerBase : public QProcess
{
    Q_OBJECT
public:
    explicit compilerBase(QObject *parent = 0);

    void setCompilerName(QString newCompilerName);
    virtual void startCompile(const QString& ) = 0;
    virtual QString version() = 0;
    virtual QString path(){return "";}
    virtual bool checkCompilerPath(const QString& ) = 0;
    virtual QString compilerName(){return currentCompilerName;}

signals:
    void compileinfo(QString msg);
    void output(QString msg);

private:
    QString currentCompilerName;

};

#endif // COMPILERBASE_H
