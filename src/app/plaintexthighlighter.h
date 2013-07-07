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

#ifndef PLAINTEXTHIGHLIGHTER_H
#define PLAINTEXTHIGHLIGHTER_H

#include <QList>
#include <QFont>
#include <QSyntaxHighlighter>
#include <QRegularExpression>

#include "highlighterGlobal.h"
#include "textcharformatmap.h"

class plaintextHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit plaintextHighlighter(QObject *parent = 0);

    static QRegularExpression suffixFilter();

signals:

public slots:

protected:
    void highlightBlock(const QString &text);

private:
};

#endif // PASCALHIGHLIGHTER_H
