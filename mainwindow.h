/*
 *  Copyright 2013 Wang Luming <wlm199558@126.com>
 *  Copyright 2013 Miyanaga Saki <tomguts@126.com>
 *
 *  mainwindow.h is part of Kreogist-Cute-IDE.
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
 *  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QMenu>
#include <QPalette>
#include <QStatusBar>
#include <QApplication>
#include <QToolButton>
#include <QMessageBox>
#include <QSettings>
#include <QVariant>

#include "kciglobal.h"
#include "kcimainwindow.h"
#include "kcicompiledock.h"
#include "kcititlebar.h"
#include "kcitabmanager.h"

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
        mnuHelpAbout,
        mnuHelpAboutQt,
        act_count   //the number of actions.
    };

    enum MainWindowMenu
    {
        file,
        edit,
        view,
        search,
        insert,
        debug,
        run,
        plugins,
        help,
        menu_count  //the number of menus
    };

    //kciTextEditor *editor;
    kciTabManager *tabManager;
    QAction *act[act_count];
    QMenu *menu[menu_count];
    QString actStatusTips[act_count];
    QRect savedGeometry;
    kcicompiledock *compileDock;

    void saveSettings();
    void restoreSettings();

    void createActions();
    void createTitlebar();
    void createDocks();
    void createMenu();
    void createStatusbar();
};

#endif // MAINWINDOW_H
