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
#include "kctitlebar.h"
#include "kcstatusbar.h"
#include "kctabmanager.h"
#include "kctexteditor.h"
#include "kcmainwindow.h"
#include "kcpreference.h"
#include "kcexecutor.h"
#include "kreogistcutestyle.h"
#include "kcmessagebox.h"
#include "kcconnectionhandler.h"
#include "kcdebugcontrolpanel.h"
#include "kcdebugcommandio.h"
#include "kcdebugwatch.h"

/*!
 * \brief The MainWindow class is the mainwindow for program.
 *
 * MainWindow is the class which is responsible for creating actions, titlebar, docks, menus,
 * status bar, tool bar. And connect lots of signals and slots between components of program.
 */
class MainWindow : public KCMainWindow
{
    Q_OBJECT
public:
    /*!
     * \brief This is the constructor for MainWindow. It set palette,central widget and so on.
     * \param parent  the parent of MainWindow.
     */
    explicit MainWindow(QWidget *parent = 0);

signals:

public slots:
    void show();
    void startDebug();
    void onActionCompileAndRun();
    void onActionRun();
    void onActionCompile();
    void onActionSearchOnline();
    void onCurrentTabChanged();
    void statusShowGoto();
    void setNoDocOpenMenuEnabled();
    void setDocOpenMenuEnabled();
    void setCurrentTextCursorLine(int NewLineNumber);
    void retranslateAndSet();

private slots:
    void aboutQt();
    void aboutCuties();
    void changeSidebarVisibleState();
    void changeCompileDockVisibleState();
    void changeDebugControlVisibleState();
    void changeDebugCommandIOVisibleState();
    void changeDebugWatchVisibleState();
    void changeJudgeDockVisibleState();
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
        menuDebug,
        menuTools,
        menuWindow,
        menuHelp,
        menuMainItemsCount  //the number of menus
    };
    //Define MainWindow menu items
    QMenu *menuMainWindowItem[menuMainItemsCount];
    QString menuMainWindowText[menuMainItemsCount];

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
        actionViewSidebar,
        actionViewCompileDock,
        actionViewDebugControls,
        actionViewDebugCommandIO,
        actionViewDebugWatch,
        //mnuViewJudgeDock,
#ifdef Q_OS_MACX
        actionViewFullscreen,
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
        actionDebugStart,
        actionDebugStop,
        actionDebugRunToCursor,
        actionDebugNext,
        actionDebugContinue,
        actionDebugStep,
        actionDebugNexti,
        actionDebugStepi,
        actionDebugReturn,
        actionDebugAddWatch,
        actionDebugModifiedWatch,
        actionDebugRemoveWatch,
        actionToolsPreferences,
        actionWindowPrev,
        actionWindowNext,
        actionHelpAbout,
        actionHelpAboutQt,
        actionMainWindowCount   //The number of Main Menu Actions.
    };
    //Define MainWindow menu actions
    QAction *actionMainWindowItem[actionMainWindowCount];
    //Define the status tips and icon path of the actions.
    QString actionMainWindowText[actionMainWindowCount];
    QString actionStatusTips[actionMainWindowCount];
    QString stringActionIconPath[actionMainWindowCount];

    //Enumerate Toolbar button items
    enum mainToolbarButton
    {
        toolButtonNewFile,
        toolButtonOpenFile,
        toolButtonSave,
        toolButtonCut,
        toolButtonCopy,
        toolButtonPaste,
        toolButtonUndo,
        toolButtonRedo,
        toolButtonSearch,
        toolButtonCompileAndRun,
        mainToolbarButtonCount // The number of toolbar buttons
    };
    //Define MainWindow Toolbar buttons.
    QToolButton *buttonMainToolbarItem[mainToolbarButtonCount];
    QString toolButtonTips[mainToolbarButtonCount];

    //Define MainWindow last time opened position.
    int lastPositionX, lastPostionY, lastPositionHeight, lastPostionWidth;

    //All the names we need to translate.
    QString trWindowTitle="Cuties";

    KCTabManager *tabManager;
    KCSideBar *sideBar;
    KCCompileDock *compileDock;
    KCJudgeDock *judgeDock;
    KCTitleBar *titlebar;
    KCStatusBar *statusBar;
    KCConnectionHandler compileFinishedConnection;

    KCDebugControlPanel *debugControl;
    KCDebugCommandIO *debugCommandIO;
    KCDebugWatch *debugWatch;

    void compileProgram();

    void saveSettings();
    void restoreSettings();

    void createActions();
    void createTitlebar();
    void createDocks();
    void createMenu();
    void createStatusbar();
    void createToolBar();

    void setDocOpenMenuState(bool state);

    void showDebugDocks();
    void connectDebugDockWithCurrEditor();
};

#endif // MAINWINDOW_H
