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

#include "kcglobal.h"
#include "kcsidebar.h"
#include "kccompiledock.h"
#include "kcjudgedock.h"
#include "kcdebugdock.h"
#include "kcdebugwatchdock.h"
#include "kctitlebar.h"
#include "kcstatusbar.h"
#include "kctabmanager.h"
#include "kctexteditor.h"
#include "kcmainwindow.h"
#include "kccontrolcenter.h"
#include "kcexecutor.h"
#include "kreogistcutestyle.h"
#include "kcmessagebox.h"

#include "kcmessagebox.h"

class MainWindow : public KCIMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

signals:

public slots:
    void show();
    void aboutQt();
    void compileCurrentFile();
    void startDebug();
    void run();
    void compileAndRun();
    void searchOnline();
    void statusShowGoto();

    void setNoDocOpenMenuEnabled();
    void setDocOpenMenuEnabled();
    void setCurrentTextCursorLine(int NewLineNumber);

    void onCurrentTabChanged();

private slots:
    void aboutCuties();
    void diffVisibleSidebar();
    void diffVisibleCompileDock();
    void diffVisibleDebugDock();
    void diffVisibleJudgeDock();
    void diffVisibleDebugWatchDock();
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
    //Enumerate MainWindow menu items
    enum menuMainWindow
    {
        menuFile,
        menuEdit,
        menuView,
        menuSearch,
        menuExecute,
        menuTools,
        menuWindow,
        menuHelp,
        menuMainItemsCount  //the number of menus
    };
    //Define MainWindow menu items
    QMenu *menuMainWindowItem[menuMainItemsCount];

    //Enumerate MainWindow menu action items
    enum actionMainWindow
    {
        actionFileNewFile,
        actionFileOpen,
        actionFileSave,
        actionFileSaveAs,
        actionFileSaveAll,
        actionFileClose,
        actionFileCloseAll,
        actionFileCloseAllExceptThis,
        actionFileExit,
        actionEditUndo,
        actionEditRedo,
        actionEditCut,
        actionEditCopy,
        actionEditPaste,
        actionEditSelectAll,
        actionEditPreferences,
        actionViewSidebar,
        actionViewCompileDock,
        //mnuViewDebugDock,
        //mnuViewDebugWatchDock,
        //mnuViewJudgeDock,
#ifdef Q_OS_MACX
        mnuViewFullscreen,
#endif
        actionViewEnd,
        actionSearchFind,
        //mnuSearchFindInFiles,
        actionSearchReplace,
        //mnuSearchReplaceInFiles,
        actionSearchSearchOnline,
        actionSearchGoto,
        actionExecuteCompileAndRun,
        actionExecuteCompile,
        actionExecuteRun,
        /*mnuExecuteParameters,
        mnuExecuteSetInputFile,
        mnuExecuteShowOutputFile,
        mnuExecuteRunAndShowOutputFile,
        mnuExecuteSetInputRunShowOutput,*/
        actionWindowPrev,
        actionWindowNext,
        actionHelpAbout,
        actionHelpAboutQt,
        actionMainWindowCount   //The number of Main Menu Actions.
    };
    //Define MainWindow menu actions
    QAction *actionMainWindowItem[actionMainWindowCount];
    //Define the status tips and icon path of the actions.
    QString stringActionStatusTips[actionMainWindowCount];
    QString stringActionIconPath[actionMainWindowCount];

    //Enumerate Toolbar button items
    enum buttonMainToolbar
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
        buttonMainToolbarCount // The number of toolbar buttons
    };
    //Define MainWindow Toolbar buttons.
    QToolButton *buttonMainToolbarItem[buttonMainToolbarCount];

    int sgoX, sgoY, sgoH, sgoW;

    //KCTextEditor *editor;
    KCITabManager *tabManager;
    KCISideBar *sidebarDock;
    KCICompiledock *compileDock;
    KCIDebugDock *debugDock;
    KCIDebugWatchDock *debugWatchDock;
    KCIJudgeDock *judgeDock;
    KCITitleBar *titlebar;
    KCIStatusBar *myStatusBar;
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
