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

#include "kciglobal.h"
#include "kcicompiledock.h"
#include "kcijudgedock.h"
#include "kcidebugdock.h"
#include "kcititlebar.h"
#include "kcistatusbar.h"
#include "kcitabmanager.h"
#include "kcitexteditor.h"
#include "kcimainwindow.h"
#include "kcicontrolcenter.h"
#include "kciexecutor.h"
#include "kreogistcutestyle.h"

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
    void startDebug();
    void run();
    void compileAndRun();
    void searchOnline();
    void diffVisibleCompileDock();
    void diffVisibleDebugDock();
    void diffVisibleJudgeDock();
    void statusShowGoto();

    void setNoDocOpenMenuEnabled();
    void setDocOpenMenuEnabled();
    void setCurrentTextCursorLine(int NewLineNumber);

    void onCurrentTabChanged();

private slots:
    void showPreference();

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
        mnuEditPreference,
        mnuViewCompileDock,
        mnuViewDebugDock,
        //mnuViewJudgeDock,
        mnuSearchFind,
        mnuSearchFindInFiles,
        mnuSearchReplace,
        mnuSearchReplaceInFiles,
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
        mnuDebugNextStep,
        mnuDebugIntoInstruction,
        mnuDebugSkipInstruction,
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
    kcicompiledock *compileDock;
    kciDebugDock *debugDock;
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


};

#endif // MAINWINDOW_H
