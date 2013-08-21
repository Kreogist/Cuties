/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *      Wang Luming <wlm199558@126.com>
 *      Miyanaga Saki <tomguts@126.com>
 *      Zhang Jiayi <bf109g2@126.com>
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

#ifndef KCIGLOBAL_H
#define KCIGLOBAL_H

#include <QString>
#include <QList>
#include <QSettings>

#include "kcigeneralconfigure.h"
#include "kcieditorconfigure.h"
#include "kcicompilerconfigure.h"
#include "kcidebuggerconfigure.h"
#include "kcifileassociation.h"
#include "kcilanguageconfigure.h"

//Global Variables
class kciGlobal
{
public:
    void readSettings();
    void writeSettings();
    static kciGlobal* getInstance();

private:
    kciGlobal();

    //Environment Variables.
    QString settingsFileName;

    QSettings *kciMainConfig;
    static kciGlobal* instance;
    QList<kciConfigure*> cfgConfiger;
};

#endif // KCIGLOBAL_H
