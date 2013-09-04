/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *      Wang Luming <wlm199558@126.com>
 *      Miyanaga Saki <tomguts@126.com>
 *      Zhang Jiayi <bf109g2@126.com>
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMenu>
#include <QPalette>
#include <QApplication>
#include <QToolButton>
#include <QMessageBox>
#include <QDesktopServices>
#include <QSettings>
#include <QSize>
#include <QRect>
#include <QDesktopWidget>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QVariant>

#ifdef Q_OS_MACX
#include <QMenuBar>
#endif

#include "kciglobal.h"
#include "kcisidebar.h"
#include "kcicompiledock.h"
#include "kcijudgedock.h"
#include "kcidebugdock.h"
#include "kcidebugwatchdock.h"
#include "kcititlebar.h"
#include "kcistatusbar.h"
#include "kcitabmanager.h"
#include "kcitexteditor.h"
#include "kcimainwindow.h"
#include "kcicontrolcenter.h"
#include "kciexecutor.h"
#include "kreogistcutestyle.h"
#include "kcimessagebox.h"

class MainWindow : public kciMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    
signals:
    

public slots:
    void show();
    void aboutQt();
    void aboutKCI();
    void compileCurrentFile();
    void startDebug();
    void run();
    void compileAndRun();
    void searchOnline();
    void diffVisibleSidebar();
    void diffVisibleCompileDock();
    void diffVisibleDebugDock();
    void diffVisibleJudgeDock();
    void diffVisibleDebugWatchDock();
    void statusShowGoto();

    void setNoDocOpenMenuEnabled();
    void setDocOpenMenuEnabled();
    void setCurrentTextCursorLine(int NewLineNumber);

    void onCurrentTabChanged();

private slots:
    void showPreference();
#ifdef Q_OS_MACX
    void setFullScreen();
#endif

protected:
    void closeEvent(QCloseEvent *e);
    void resizeEvent(QResizeEvent *e);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

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
        mnuEditPreferences,
        //mnuViewSidebar,
        mnuViewCompileDock,
        mnuViewDebugDock,
        mnuViewDebugWatchDock,
        //mnuViewJudgeDock,
#ifdef Q_OS_MACX
        mnuViewFullscreen,
#endif
        mnuViewEnd,
        mnuSearchFind,
        //mnuSearchFindInFiles,
        mnuSearchReplace,
        //mnuSearchReplaceInFiles,
        mnuSearchSearchOnline,
        mnuSearchGoto,
        mnuExecuteCompileAndRun,
        mnuExecuteCompile,
        mnuExecuteRun,
        mnuExecuteParameters,
        mnuExecuteSetInputFile,
        mnuExecuteShowOutputFile,
        mnuExecuteRunAndShowOutputFile,
        mnuExecuteSetInputRunShowOutput,
        mnuDebugStart,
        mnuDebugStopExecute,
        mnuDebugSetBreakPoint,
        mnuDebugNextLine,
        mnuDebugIntoLine,
        mnuDebugNextInstruction,
        mnuDebugIntoInstruction,
        mnuDebugContinue,
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
        mnuExecute,
        mnuDebug,
        mnuTools,
        mnuWindow,
        mnuHelp,
        menu_count  //the number of menus
    };

    enum MainToolBarButton
    {
        tlbNewFile,
        tlbOpenFile,
        tlbSaveFile,
        tlbCut,
        tlbCopy,
        tlbPaste,
        tlbUndo,
        tlbRedo,
        tlbSearch,
        tlbCompileAndRun,
        tlbbutton_count // the number of toolbar buttons
    };

    int sgoX, sgoY, sgoH, sgoW;

    //kciTextEditor *editor;
    kciTabManager *tabManager;
    QAction *act[act_count];
    QMenu *menu[menu_count];
    QString actStatusTips[act_count], actMenuIconPath[act_count];
    QToolButton *tblMainButton[tlbbutton_count];
    kciSideBar *sidebarDock;
    kcicompiledock *compileDock;
    kciDebugDock *debugDock;
    kciDebugWatchDock *debugWatchDock;
    kciJudgeDock *judgeDock;
    kciTitleBar *titlebar;
    kciStatusBar *myStatusBar;
    QMetaObject::Connection compileFinishedConnection;

    void saveSettings();
    void restoreSettings();

    void createActions();
    void createTitlebar();
    void createDocks();
    void createMenu();
    void createStatusbar();
    void createToolBar();

    void setDocOpenMenuState(bool state);

    void connectDebugDockWithCurrEditor();


};

#endif // MAINWINDOW_H
