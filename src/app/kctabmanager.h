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

#ifndef KCTABMANAGER_H
#define KCTABMANAGER_H

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
#include <QPalette>
#include <QUrl>

#include "kcgeneralconfigure.h"
#include "kceditorconfigure.h"
#include "kchistoryconfigure.h"
#include "kccolorconfigure.h"
#include "kcsearchwindow.h"
#include "kccodeeditor.h"

class KCTabManager : public QTabWidget
{
    Q_OBJECT
public:
    explicit KCTabManager(QWidget *parent = 0);
    int getCurrentLineCount() const;
    int getCurrentLineNum() const;
    void restoreUnclosedFiles();

    KCCodeEditor *getCurrentEditor() const;

signals:
    void cursorDataChanged(int nCursorLine, int nCursorCol);
    void rewriteDataChanged(bool bRewriteMode);
    void rewriteDisVisible();
    void tabAdded();
    void tabClear();

public slots:
    void openAndJumpTo(const QString &filePath);
    int open(const QString &filePath);
    void open();
    void newFile();
    void save();
    void saveAs();
    void saveAll();
    void redo();
    void undo();
    void copy();
    void cut();
    void paste();
    void selectAll();
    void onTabCloseRequested(int index);
    void onCurrentTabChange(int index);
    void closeCurrentTab();
    void closeAllTab();
    void closeAllOtherTab();
    void switchNextTab();
    void switchPrevTab();
    void renameTabTitle(QString title);
    void currentTextCursorChanged();
    void showSearchBar();
    void showReplaceBar();
    void setFocus();
    void switchCurrentToLine(int nLineNum, int nColNum);
    void insertToCurrentEditor(QString insertText);
    QString textNowSelect();

protected:
    void closeEvent(QCloseEvent *e);
    void tabInserted(int index);

private slots:
    void setTabMoveableValue(bool newValue);
    void setTabCloseable(bool newValue);

private:
    int newFileCount;
    QTextCursor currentTextCursor;
    KCCodeEditor *currentEditor;
    KCEditorConfigure *editorConfigureInstance;
    QTabBar *tabBarControl;
};

#endif // KCTABMANAGER_H
