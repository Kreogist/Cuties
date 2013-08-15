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

#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPalette>
#include <QFile>
#include <QPlainTextEdit>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
#include <QTextCursor>
#include <QErrorMessage>
#include <QSettings>
#include <QIcon>
#include <QPropertyAnimation>
#include <QTimeLine>
#include <QGraphicsOpacityEffect>
#include <QDebug>

#include "kciglobal.h"
#include "kcitexteditor.h"
#include "kcilinenumpanel.h"
#include "kcimarkpanel.h"
#include "kcisearchwindow.h"
#include "kcilanguagemode.h"

class kciSearchWindow;
class kciLanguageMode;

class kciCodeEditor : public QWidget
{
    Q_OBJECT
public:
    explicit kciCodeEditor(QWidget *parent = 0);

    QFileDevice::FileError error();
    void setDocumentTitle(const QString& title);
    QString getDocumentTitle();
    void setDocumentCursor(int nLine, int linePos);
    void setTextFocus();
    QString getFilePath();
    QString getExecFileName();
    QTextCursor getTextCursor();
    int getTextLines();
    bool isModified();

    QTextDocument *document;

    kciLanguageMode *langMode() const;

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
    void computeExecFileName();
    void fileInfoChanged(const QFile& file);
    bool dosaveas(const QString& Caption);

    QGraphicsOpacityEffect *initEffect;

    kciLanguageMode *m_langMode;

    QHBoxLayout *mainLayout;
    kciTextEditor *editor;
    kciLinenumPanel *linePanel;
    kciMarkPanel *markPanel;

    QString filePath,strFileFilter;
    QString execFileName;
    QFileDevice::FileError fileError;
    QTextCursor fileTextCursor;

    kciSearchWindow *searchBar;

    friend class kciLanguageMode;
};

#endif // TEXTEDITOR_H
