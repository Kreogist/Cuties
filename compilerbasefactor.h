/*
 *  Copyright 2013 Wang Luming <wlm199558@126.com>
 *  Copyright 2013 Ye Haolei(Miyanaga Saki) <tomguts@126.com>
 *
 *  compilerbasefactor.h is part of Kreogist-Cute-IDE.
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

#ifndef COMPILERBASEFACTOR_H
#define COMPILERBASEFACTOR_H

#include <QObject>

#include "compilerbase.h"
#include "gcc.h"

class compilerBaseFactor : public QObject
{
    Q_OBJECT
public:
    explicit compilerBaseFactor(QObject *parent = 0);

    static compilerBase* createCompilerBase(const QString& fileName,
                                            QObject *parent);

    
signals:
    
public slots:
    
};

#endif // COMPILERBASEFACTOR_H
