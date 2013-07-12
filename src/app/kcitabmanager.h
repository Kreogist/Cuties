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

#ifndef TABMANAGER_H
#define TABMANAGER_H

#include <QWidget>
#include <QTabWidget>
#include <QFile>
#include <QFileInfo>
#include <QTabBar>
#include <QFileDialog>
#include <QTextCursor>
#include <QPropertyAnimation>
#include <QTextDocument>
#include <QErrorMessage>
#include <QSettings>
#include <QMimeData>
#include <QPalette>
#include <QList>
#include <QUrl>

#include "compilerbase.h"
#include "kciglobal.h"
#include "kcisearchwindow.h"
#include "kcitexteditor.h"

class kciTabManager : public QTabWidget
{
    Q_OBJECT
public:
    explicit kciTabManager(QWidget *parent = 0);
    int getCurrentLineCount();
    int getCurrentLineNum();

    kciTextEditor* getCurrentEditor();

signals:
    void cursorDataChanged(int nCursorLine, int nCursorCol);
    void tabAdded();
    void tabClear();

public slots:
    void openAndJumpTo(const QString& filePath);
    int open(const QString& filePath);
    void open();
    void new_file();
    void save();
    void save_as();
    void save_all();
    void redo();
    void undo();
    void copy();
    void cut();
    void paste();
    void select_all();
    void on_tab_close_requested(int index);
    void on_current_tab_change(int index);
    void close_current_tab();
    void close_all_tab();
    void close_all_other_tab();
    void switchNextTab();
    void switchPrevTab();
    void renameTabTitle(QString title);
    void currentTextCursorChanged();
    void showSearchBar();
    void setFocus();
    void switchCurrentToLine(int nLineNum, int nColNum);
    QString textNowSelect();

protected:
    void closeEvent(QCloseEvent *e);
    void tabInserted(int index);

private:
    int tab_count;
    int new_file_count;
    QString strFileFilter;
    QTextCursor currentTextCursor;
    kciTextEditor *currentEditor;
};

#endif // TABMANAGER_H
