/*
 *  Copyright 2013 Wang Luming<wlm199558@126.com>
 *  Copyright 2013 Ye Haolei(Miyanaga Saki) <tomguts@126.com>
 *
 *  kcitabmanager.h is part of Kreogist-Cute-IDE.
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
#include <QPropertyAnimation>
#include <QErrorMessage>
#include <QSettings>
#include <QPalette>

#include "compilerbase.h"
#include "compilerbasefactor.h"
#include "kciglobal.h"
#include "kcisearchwindow.h"
#include "kcitexteditor.h"

class kciTabManager : public QTabWidget
{
    Q_OBJECT
public:
    explicit kciTabManager(QWidget *parent = 0);

signals:
    void cursorDataChanged(int nCursorLine, int nCursorCol);
    void tabAdded();
    void tabClear();

public slots:
    void open();
    void new_file();
    void save();
    void save_as();
    void save_all();
    //void text_changed();
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
    void renameTabTitle(QString title);
    void currentTextCursorChanged();
    void showSearchBar();
    QString textNowSelect();

protected:
    void closeEvent(QCloseEvent *e);
    void tabInserted(int index);
    void resizeEvent(QResizeEvent *e);

private:
    int tab_count;
    int new_file_count;
    QString strFileFilter;
    QTextCursor currentTextCursor;
    bool isEditor;  //is current widget a widget
    kciSearchWindow *searchBar;
};

#endif // TABMANAGER_H
