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


#ifndef TEXTCHARFORMATMAP_H
#define TEXTCHARFORMATMAP_H

#include <QFile>
#include <QTextCharFormat>
#include <QApplication>
#include <QDebug>

#include "kceditorconfigure.h"

class textCharFormatMap : public QObject
{
    Q_OBJECT
public:
    explicit textCharFormatMap(QObject *parent = 0);

    static textCharFormatMap *getInstance();
    const QTextCharFormat &getTextCharFormat(const QString &typeName);

private:
    static textCharFormatMap *instance;
    QMap<QString, QTextCharFormat> map;

    bool parseStyleFileLine(char *str_line);

};

#endif // TEXTCHARFORMATMAP_H
