/*
 *  Copyright 2013 Wang Luming
 *
 *  kcitexteditor.h is part of Kreogist-Cute-IDE.
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

#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPalette>
#include <QFile>
#include <QPlainTextEdit>
#include <QFileInfo>
#include <QFileDevice>
#include <QFileDialog>
#include <QTextStream>
#include <QString>
#include <QMessageBox>

#include "kcicodeeditor.h"
#include "kcilinenumpanel.h"
#include "cpphighlighter.h"

class kciTextEditor : public QWidget
{
    Q_OBJECT
public:
    explicit kciTextEditor(QWidget *parent = 0);

    QFileDevice::FileError error();
    
signals:
    
public slots:
    bool open();
    bool open(const QString& fileName);
    bool save();
    bool saveAs();
    bool saveAs(const QString& fileName);

protected:
    void closeEvent(QCloseEvent *e);

private:
    QHBoxLayout *mainLayout;
    kciCodeEditor *editor;
    kciLinenumPanel *linePanel;
    cppHighlighter *highlighter;

    QString filePath,strFileFilter;
    QFileDevice::FileError fileError;
};

#endif // TEXTEDITOR_H
