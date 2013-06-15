/*
 *  Copyright 2013 Wang Luming <wlm199558@126.com>
 *  Copyright 2013 Miyanaga Saki <tomguts@126.com>
 *
 *
 *  highlighterbase.h is part of Kreogist-Cute-IDE.
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

#ifndef HIGHLIGHTERBASE_H
#define HIGHLIGHTERBASE_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QMap>
#include <QString>
#include <QTextCharFormat>
#include <QFile>
#include <QString>
#include <QSet>
#include <QDebug>

struct highlight_rule
{
    QString type_name;

    QRegularExpression regexp;
};

class highlighterBase : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit highlighterBase(QObject *parent = 0);

    const QTextCharFormat& operator[] (const QString& typeName);
    const QTextCharFormat& getTextCharFormat(const QString& typeName);

private:
    static QMap<QString, QTextCharFormat> map;
    static bool isInited;

    bool parseStyleFileLine(char *str_line);
    
};

#endif // HIGHLIGHTERBASE_H
