/*
 *  Copyright 2013 Wang Luming <wlm199558@126.com>
 *
 *  gdbmivalue.h is part of Kreogist-Cute-IDE.
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

    GdbMiValue operator [](const char *_str_name) const;

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
