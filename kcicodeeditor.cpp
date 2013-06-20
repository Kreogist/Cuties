/*
 *  Copyright 2013 Wang Luming<wlm199558@126.com>
 *
 *  kcicodeeditor.cpp is part of Kreogist-Cute-IDE.
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
    setFont(QFont(QString("Inconsolata"),11));

    connect(this,&kciCodeEditor::cursorPositionChanged,
            this,&kciCodeEditor::highlightCurrentLine);

    lineColor = QColor(0x64,0x64,0x64);

    QPalette pal = palette();
    pal.setColor(QPalette::Base,QColor(0x38,0x38,0x38));
    pal.setColor(QPalette::Text,QColor(255,255,255));
    setPalette(pal);

    setFrameStyle(0);
}

void kciCodeEditor::highlightCurrentLine()
{\
    QList<QTextEdit::ExtraSelection> extraSelections;

        if (!isReadOnly()) {
            QTextEdit::ExtraSelection selection;

            selection.format.setBackground(lineColor);
            selection.format.setProperty(QTextFormat::FullWidthSelection, true);
            selection.cursor = textCursor();
            selection.cursor.clearSelection();
            extraSelections.append(selection);
        }

        setExtraSelections(extraSelections);
}
