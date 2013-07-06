/*
 *  Copyright 2013 Wang Luming <wlm199558@126.com>
 *  Copyright 2013 Ye Haolei(Miyanaga Saki) <tomguts@126.com>
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
#include <QTextDocument>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
#include <QTextCursor>
#include <QSettings>
#include <QIcon>
#include <QSyntaxHighlighter>
#include <QPropertyAnimation>
#include <QDebug>

#include "kciglobal.h"
#include "kcicodeeditor.h"
#include "kcilinenumpanel.h"
#include "kcimarkpanel.h"
#include "highlighterfactory.h"
#include "kcisearchwindow.h"

//default highlighter
#include "plaintexthighlighter.h"

class kciSearchWindow;

class kciTextEditor : public QWidget
{
    Q_OBJECT
public:
    explicit kciTextEditor(QWidget *parent = 0);

    QFileDevice::FileError error();
    void setDocumentTitle(const QString& title);
    QString getDocumentTitle();
    void setDocumentCursor(int nLine, int linePos);
    void setTextFocus();
    QString getFilePath();
    QTextCursor getTextCursor();
    int getTextLines();

    QTextDocument *document;

signals:
    void filenameChanged(QString newName);
    void fileTextCursorChanged();
    
public slots:
    bool open(const QString& fileName);
    bool save();
    bool saveAs();
    bool saveAs(const QString& fileName);
    void redo();
    void undo();
    void copy();
    void cut();
    void paste();
    void selectAll();
    void cursorChanged();
    QString getSelectedText();
    void showSearchBar();

private slots:
    void onModificationChanged(bool changed);

protected:
    void closeEvent(QCloseEvent *e);
    void resizeEvent(QResizeEvent *e);

private:
    QHBoxLayout *mainLayout;
    kciCodeEditor *editor;
    kciLinenumPanel *linePanel;
    kciMarkPanel *markPanel;
    QSyntaxHighlighter *highlighter;

    QString filePath,strFileFilter;
    QFileDevice::FileError fileError;
    QTextCursor fileTextCursor;

    kciSearchWindow *searchBar;
};

#endif // TEXTEDITOR_H
