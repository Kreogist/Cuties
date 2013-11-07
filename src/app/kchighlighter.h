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

#ifndef KCHIGHLIGHTER_H
#define KCHIGHLIGHTER_H

#include <QSyntaxHighlighter>

#include "kctextblockdata.h"

class KCHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit KCHighlighter(QObject *parent = 0);

protected:
    void highlightBlock(const QString &text);
    void parseParenthesesInfo(const QString &text,
                              KCTextBlockData *data,
                              char character);
    int parseQuotationInfo(const QString &text,
                           KCTextBlockData *data);
    virtual void KCHighlightBlock(const QString &text)
    {
        Q_UNUSED(text);
    }

private:
    int quotationPaired;
};

#endif // KCHIGHLIGHTER_H
