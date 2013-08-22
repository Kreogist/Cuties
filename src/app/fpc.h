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

#ifndef FPC_H
#define FPC_H

#include <QRegularExpression>
#include <QDebug>

#include "compilerbase.h"
#include "kcicompilerconfigure.h"

class fpc : public compilerBase
{
    Q_OBJECT
public:
    explicit fpc(QObject *parent = 0);
    void startCompile(const QString &filePath);
    QString path(){return instance->getFpcPath();}
    virtual QString compilerName() { return "fpc";}
    
protected:
    QStringList getVersionArg();
    QStringList getCompileArg(const QString &filePath);
    QStringList getcompileEnv();

    void parseLine(const QString &text);

private:
    kciCompilerConfigure* instance;
};

#endif // FPC_H
