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

#ifndef KCCOMPILERCONFIGURE_H
#define KCCOMPILERCONFIGURE_H

#include <QString>
#include <QApplication>
#include <QDebug>

#include "kcconfigure.h"

class KCCompilerConfigure : public KCConfigure
{
    Q_OBJECT
public:
    void readConfigure();
    void writeConfigure();
    static KCCompilerConfigure *getInstance();

    QString getGccPath() const;
    void setGccPath(const QString &value);
    QString getGppPath() const;
    void setGppPath(const QString &value);
    QString getFpcPath() const;
    void setFpcPath(const QString &value);

private:
    KCCompilerConfigure();
    static KCCompilerConfigure *instance;

    QString gccPath, gppPath, fpcPath;
};

#endif // KCCOMPILERCONFIGURE_H
