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

#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextBlock>
#include <QPalette>
#include <QScrollBar>
#include <QDebug>

#include "kcitextsearcher.h"

class kciTextEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit kciTextEditor(QWidget *parent = 0);
    void setDocumentCursor(int nLine, int linePos);
    void setSearchResults(QList<searchResult> *results);
    void showSearchResultAt(int num);
    
signals:
    void updated();

public slots:
    void updateHighlights();

protected:
    void paintEvent(QPaintEvent *e);

private:
    void highlightCurrentLine(QList<QTextEdit::ExtraSelection>& selections);
    void highlightSearchResult(QList<QTextEdit::ExtraSelection>& selections);

    QList<searchResult> resultList;
    QColor lineColor,searchResultColor;
};

#endif // CODEEDITOR_H
