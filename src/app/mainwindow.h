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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QMenu>
#include <QTime>
#include <QPalette>
#include <QApplication>
#include <QToolButton>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileInfo>
#include <QSettings>
#include <QSize>
#include <QDesktopWidget>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QVariant>

#include "kciglobal.h"
#include "kcicompiledock.h"
#include "kcijudgedock.h"
#include "kcititlebar.h"
#include "kcistatusbar.h"
#include "kcitabmanager.h"
#include "kcimainwindow.h"
#include "kcicontrolcenter.h"
#include "kciexecutor.h"

class MainWindow : public kciMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    void aboutQt();
    void aboutKCI();
    void compileCurrentFile();
    void run();
    void compileAndRun();
    void searchOnline();
    void diffVisibleCompileDock();
    void diffVisibleJudgeDock();
    void statusShowGoto();

    void setNoDocOpenMenuEnabled();
    void setDocOpenMenuEnabled();
    void setCurrentTextCursorLine(int NewLineNumber);

private slots:
    void showPreference();

protected:
    void closeEvent(QCloseEvent *e);
    void resizeEvent(QResizeEvent *e);

private:
    enum MainWindowActions
    {
        mnuFileNewFile,
        mnuFileOpen,
        mnuFileSave,
        mnuFileSaveAs,
        mnuFileSaveAll,
        mnuFileClose,
        mnuFileCloseAll,
        mnuFileCloseAllExceptThis,
        mnuFileExit,
        mnuEditUndo,
        mnuEditRedo,
        mnuEditCut,
        mnuEditCopy,
        mnuEditPaste,
        mnuEditSelectAll,
        mnuEditPreference,
        mnuViewCompileDock,
        mnuViewJudgeDock,
        mnuSearchFind,
        mnuSearchFindInFiles,
        mnuSearchReplace,
        mnuSearchReplaceInFiles,
        mnuSearchSearchOnline,
        mnuSearchGoto,
        mnuRunCompileAndRun,
        mnuRunCompile,
        mnuRunRun,
        mnuRunParameters,
        mnuRunSetInputFile,
        mnuRunShowOutputFile,
        mnuRunRunAndShowOutputFile,
        mnuRunSetInputRunShowOutput,
        mnuDebugStart,
        mnuDebugStopExecute,
        mnuDebugSetBreakPoint,
        mnuDebugNextLine,
        mnuDebugIntoLine,
        mnuDebugNextInstruction,
        mnuDebugIntoInstruction,
        mnuDebugSkipLine,
        mnuDebugSkipFunction,
        mnuDebugAddWatch,
        mnuDebugModifyWatch,
        mnuDebugRemoveWatch,
        mnuWindowSplit,
        mnuWindowPrev,
        mnuWindowNext,
        mnuHelpAbout,
        mnuHelpAboutQt,
        act_count   //the number of actions.
    };

    enum MainWindowMenu
    {
        mnuFile,
        mnuEdit,
        mnuView,
        mnuSearch,
        mnuInsert,
        mnuRun,
        mnuDebug,
        mnuTool,
        mnuWindow,
        mnuHelp,
        menu_count  //the number of menus
    };

    //kciTextEditor *editor;
    kciTabManager *tabManager;
    QAction *act[act_count];
    QMenu *menu[menu_count];
    QString actStatusTips[act_count], actMenuIconPath[act_count];
    QRect savedGeometry;
    kcicompiledock *compileDock;
    kciJudgeDock *judgeDock;
    kciTitleBar *titlebar;
    kciStatusBar *myStatusBar;

    void saveSettings();
    void restoreSettings();

    void createActions();
    void createTitlebar();
    void createDocks();
    void createMenu();
    void createStatusbar();
};

#endif // MAINWINDOW_H
