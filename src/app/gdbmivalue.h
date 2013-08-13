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

#ifndef GDBMIVALUE_H
#define GDBMIVALUE_H

#include <QString>
#include <QList>

#include <QDebug>

class GdbMiValue
{
public:
    enum ValueType
    {
        Invalid,
        Const,
        Tuple,
        List
    };

    GdbMiValue():type(Invalid){}

    void build(const QChar* &begin, const QChar* &end);
    QString getName() const;
    inline ValueType getType(){return type;}
    QString getValue() const;
    inline QList<GdbMiValue>::iterator begin(){return children.begin();}
    inline QList<GdbMiValue>::iterator end(){return children.end();}
    inline int size(){return children.size();}

    GdbMiValue at(const int& i) const;
    GdbMiValue operator [](const char *_str_name) const;
    GdbMiValue& operator += (const GdbMiValue& child);

private:
    void parseConst(const QChar* &begin, const QChar* &end);
    void parseList(const QChar* &begin, const QChar* &end);
    void parseTuple(const QChar* &begin, const QChar* &end);

    ValueType type;
    QString name;
    QString value;
    QList<GdbMiValue> children;
};

#endif // GDBMIVALUE_H
