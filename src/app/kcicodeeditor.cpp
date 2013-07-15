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

#include "kcicodeeditor.h"

kciCodeEditor::kciCodeEditor(QWidget *parent) :
    QPlainTextEdit(parent)
{
    setFrameStyle(QFrame::NoFrame);
    setFont(QString("Monaco"));
    setAcceptDrops(false);

    QPalette pal = palette();
    pal.setColor(QPalette::Base,QColor(0x38,0x38,0x38));
    pal.setColor(QPalette::Text,QColor(255,255,255));
    pal.setColor(QPalette::Button,QColor(83,83,83));
    setPalette(pal);
    setFrameStyle(0);

    lineColor = QColor(0x64,0x64,0x64);
    searchResultColor = QColor(0xf7,0xcf,0x3d);

    //Solve the default line's bug.
    updateHighlights();

    connect(this,&kciCodeEditor::cursorPositionChanged,
            this,&kciCodeEditor::updateHighlights);
}

void kciCodeEditor::paintEvent(QPaintEvent *e)
{
    QPlainTextEdit::paintEvent(e);
    emit updated();
}

void kciCodeEditor::showSearchResultAt(int num)
{
    searchResult result=resultList[num];
    setDocumentCursor(result.lineNum,result.startPos);
}

void kciCodeEditor::setDocumentCursor(int nLine, int linePos)
{
     QTextCursor cursor = textCursor();
     cursor.setPosition(document()->findBlockByNumber(nLine).position());
     cursor.movePosition(QTextCursor::NextCharacter,
                          QTextCursor::MoveAnchor,
                          linePos);
     setTextCursor(cursor);
}

void kciCodeEditor::updateHighlights()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    highlightCurrentLine(extraSelections);
    highlightSearchResult(extraSelections);

    setExtraSelections(extraSelections);
}

void kciCodeEditor::highlightCurrentLine(QList<QTextEdit::ExtraSelection>& selections)
{
    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        selections.append(selection);
    }
}

void kciCodeEditor::highlightSearchResult(QList<QTextEdit::ExtraSelection>& selections)
{
    int l=resultList.size();
    QTextCursor _cursor(document());

    int lastLineNum=0;
    for(int i=0;i<l;i++)
    {
        const searchResult r=resultList.at(i);

        QTextEdit::ExtraSelection selection;

        _cursor.clearSelection();
        _cursor.movePosition(QTextCursor::NextBlock,
                             QTextCursor::MoveAnchor,
                             r.lineNum-lastLineNum);
        _cursor.movePosition(QTextCursor::StartOfBlock,
                             QTextCursor::MoveAnchor);
        _cursor.movePosition(QTextCursor::NextCharacter,
                             QTextCursor::MoveAnchor,
                             r.startPos);
        _cursor.movePosition(QTextCursor::NextCharacter,
                             QTextCursor::KeepAnchor,
                             r.length);
        selection.cursor=_cursor;

        selection.format.setBackground(searchResultColor);
        selections.append(selection);

        lastLineNum=r.lineNum;
    }
}

void kciCodeEditor::setSearchResults(QList<searchResult> *results)
{
    resultList=*results;
    updateHighlights();
}
