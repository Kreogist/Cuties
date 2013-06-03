/*
 *  Copyright 2013 Wang Luming
 *
 *  kcitexteditor.cpp is part of Kreogist-Cute-IDE.
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

#include "kcitexteditor.h"

kciTextEditor::kciTextEditor(QWidget *parent) :
    QWidget(parent)
{
    mainLayout=new QHBoxLayout(this);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    linePanel=new kciLinenumPanel(this);
    mainLayout->addWidget(linePanel);

    editor=new kciCodeEditor(this);
    linePanel->setPlainTextEdit(editor);
    mainLayout->addWidget(editor);
}
