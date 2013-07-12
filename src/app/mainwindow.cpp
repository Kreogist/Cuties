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

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    kciMainWindow(parent)
{
    setWindowTitle(tr("Kreogist Cuties"));

    tabManager=new kciTabManager(this);
    setCentralWidget(tabManager);
    setMinimumSize(400,150);

    QPalette QPpal = palette();
    QPpal.setBrush(QPalette::Window, QBrush(QColor(83,83,83)));
    setPalette(QPpal);

    createActions();
    createDocks();
    createTitlebar();
    createMenu();
    createStatusbar();

    restoreSettings();
}

void MainWindow::createActions()
{
    //File -> New
    act[mnuFileNewFile]=new QAction(tr("new file"),this);
    act[mnuFileNewFile]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_N));
    actMenuIconPath[mnuFileNewFile]=QString(":/menuicon/image/MenuIcons/mnuFileNew.png");
    actStatusTips[mnuFileNewFile]=QString(tr("Create a new document."));
    connect(act[mnuFileNewFile],SIGNAL(triggered()),
            tabManager,SLOT(new_file()));

    //File -> Open
    act[mnuFileOpen]=new QAction(tr("open"),this);
    act[mnuFileOpen]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_O));
    actMenuIconPath[mnuFileOpen]=QString(":/menuicon/image/MenuIcons/mnuFileOpen.png");
    actStatusTips[mnuFileOpen]=QString(tr("Open an exsisting document."));
    connect(act[mnuFileOpen],SIGNAL(triggered()),tabManager,SLOT(open()));

    //File -> Save
    act[mnuFileSave]=new QAction(tr("save"),this);
    act[mnuFileSave]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_S));
    actMenuIconPath[mnuFileSave]=QString(":/menuicon/image/MenuIcons/mnuFileSave.png");
    actStatusTips[mnuFileSave]=QString(tr("Save active document."));
    connect(act[mnuFileSave],SIGNAL(triggered()),tabManager,SLOT(save()));

    //File -> Save As
    act[mnuFileSaveAs]=new QAction(tr("save as"),this);
    act[mnuFileSaveAs]->setShortcut(QKeySequence(Qt::CTRL+Qt::ALT+Qt::Key_S));
    actMenuIconPath[mnuFileSaveAs]=QString(":/menuicon/image/MenuIcons/mnuFileSaveAs.png");
    actStatusTips[mnuFileSaveAs]=QString(tr("Save as different file name."));
    connect(act[mnuFileSaveAs],SIGNAL(triggered()),tabManager,SLOT(save_as()));

    //File -> Save All
    act[mnuFileSaveAll]=new QAction(tr("save all"),this);
    act[mnuFileSaveAll]->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_S));
    actStatusTips[mnuFileSaveAll]=QString(tr("Save all modified documents."));
    connect(act[mnuFileSaveAll],SIGNAL(triggered()),tabManager,SLOT(save_all()));

    //File -> Close
    act[mnuFileClose]=new QAction(tr("close"),this);
    act[mnuFileClose]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_F4));
    actMenuIconPath[mnuFileClose]=QString(":/menuicon/image/MenuIcons/mnuFileClose.png");
    actStatusTips[mnuFileClose]=QString(tr("Close the active document."));
    connect(act[mnuFileClose],SIGNAL(triggered()),tabManager,SLOT(close_current_tab()));

    //File -> Close All
    act[mnuFileCloseAll]=new QAction(tr("close all"),this);
    act[mnuFileCloseAll]->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_F4));
    actStatusTips[mnuFileCloseAll]=QString(tr("Close all files."));
    connect(act[mnuFileCloseAll],SIGNAL(triggered()),tabManager,SLOT(close_all_tab()));

    //File -> Close All Except This
    act[mnuFileCloseAllExceptThis]=new QAction(tr("close all other file"),this);
    act[mnuFileCloseAllExceptThis]->setShortcut(QKeySequence(Qt::CTRL+Qt::ALT+Qt::Key_F4));
    actStatusTips[mnuFileCloseAllExceptThis]=QString(tr("Close all files except active file."));
    connect(act[mnuFileCloseAllExceptThis],SIGNAL(triggered()),tabManager,SLOT(close_all_other_tab()));

    //File -> Exit
    act[mnuFileExit]=new QAction(tr("quit"),this);
    act[mnuFileExit]->setShortcut(QKeySequence(Qt::ALT+Qt::Key_F4));
    actMenuIconPath[mnuFileExit]=QString(":/menuicon/image/MenuIcons/mnuFileExit.png");
    actStatusTips[mnuFileExit]=QString(tr("Quit applications; prompts to save documents."));
    connect(act[mnuFileExit],SIGNAL(triggered()),this,SLOT(close()));

    //Edit -> Undo
    act[mnuEditUndo]=new QAction(tr("undo"),this);
    act[mnuEditUndo]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Z));
    actMenuIconPath[mnuEditUndo]=QString(":/menuicon/image/MenuIcons/mnuEditUndo.png");
    actStatusTips[mnuEditUndo]=QString(tr("Undo the last action."));
    connect(act[mnuEditUndo],SIGNAL(triggered()),tabManager,SLOT(undo()));

    //Edit -> Redo
    act[mnuEditRedo]=new QAction(tr("redo"),this);
    act[mnuEditRedo]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Y));
    actMenuIconPath[mnuEditRedo]=QString(":/menuicon/image/MenuIcons/mnuEditRedo.png");
    actStatusTips[mnuEditRedo]=QString(tr("Redo the previously undone action."));
    connect(act[mnuEditRedo],SIGNAL(triggered()),tabManager,SLOT(redo()));

    //Edit -> Cut
    act[mnuEditCut]=new QAction(tr("cut"),this);
    act[mnuEditCut]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_X));
    actMenuIconPath[mnuEditCut]=QString(":/menuicon/image/MenuIcons/mnuEditCut.png");
    actStatusTips[mnuEditCut]=QString(tr("Cut the selection and put it on the clipboard."));
    connect(act[mnuEditCut],SIGNAL(triggered()),tabManager,SLOT(cut()));

    //Edit -> Copy
    act[mnuEditCopy]=new QAction(tr("copy"),this);
    act[mnuEditCopy]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_C));
    actMenuIconPath[mnuEditCopy]=QString(":/menuicon/image/MenuIcons/mnuEditCopy.png");
    actStatusTips[mnuEditCopy]=QString(tr("Copy the selection and put it on the clipboard."));
    connect(act[mnuEditCopy],SIGNAL(triggered()),tabManager,SLOT(copy()));

    //Edit -> Paste
    act[mnuEditPaste]=new QAction(tr("paste"),this);
    act[mnuEditPaste]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_V));
    actMenuIconPath[mnuEditPaste]=QString(":/menuicon/image/MenuIcons/mnuEditPaste.png");
    actStatusTips[mnuEditPaste]=QString(tr("Paste clipboard contents."));
    connect(act[mnuEditPaste],SIGNAL(triggered()),tabManager,SLOT(paste()));

    //Edit -> Select All
    act[mnuEditSelectAll]=new QAction(tr("select all"),this);
    act[mnuEditSelectAll]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_A));
    actMenuIconPath[mnuEditSelectAll]=QString(":/menuicon/image/MenuIcons/mnuEditSelectAll.png");
    actStatusTips[mnuEditSelectAll]=QString(tr("Select the entire document."));
    connect(act[mnuEditSelectAll],SIGNAL(triggered()),tabManager,SLOT(select_all()));

    //Edit -> Preference
    act[mnuEditPreference]=new QAction(tr("preference"),this);
    act[mnuEditPreference]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Period));
    actMenuIconPath[mnuEditPreference]=QString(":/menuicon/image/MenuIcons/mnuEditPerformance.png");
    actStatusTips[mnuEditPreference]=QString(tr("Customize your IDE."));
    connect(act[mnuEditPreference],SIGNAL(triggered()),this,SLOT(showPreference()));

    //View -> Compile Dock
    act[mnuViewCompileDock]=new QAction(tr("Compile Dock"),this);
    actStatusTips[mnuViewCompileDock]=QString(tr("Show Compile Info Dock."));
    connect(act[mnuViewCompileDock],SIGNAL(triggered()),this,SLOT(diffVisibleCompileDock()));

    //View -> Judge Dock
    act[mnuViewJudgeDock]=new QAction(tr("Judge Dock"),this);
    actStatusTips[mnuViewJudgeDock]=QString(tr("Show Judge Dock."));
    connect(act[mnuViewJudgeDock],SIGNAL(triggered()),this,SLOT(diffVisibleJudgeDock()));

    //Search -> Search
    act[mnuSearchFind]=new QAction(tr("searchinfile"),this);
    act[mnuSearchFind]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_F));
    actStatusTips[mnuSearchFind]=QString(tr("Find the specified text."));
    connect(act[mnuSearchFind],SIGNAL(triggered()),tabManager,SLOT(showSearchBar()));

    //Search -> Find In Files
    act[mnuSearchFindInFiles]=new QAction(tr("searchallfile"),this);
    act[mnuSearchFindInFiles]->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_F));
    actStatusTips[mnuSearchFindInFiles]=QString(tr("Find text in files."));

    //Search -> Replace
    act[mnuSearchReplace]=new QAction(tr("replaceinfile"),this);
    act[mnuSearchReplace]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_H));
    actStatusTips[mnuSearchReplace]=QString(tr("Replace specfic text with different text."));

    //Search -> Replace In Files
    act[mnuSearchReplaceInFiles]=new QAction(tr("replaceallfile"),this);
    act[mnuSearchReplaceInFiles]->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_H));
    actStatusTips[mnuSearchReplaceInFiles]=QString(tr("Replace in files."));

    //Search -> Search Online
    act[mnuSearchSearchOnline]=new QAction(tr("searchonline"),this);
    act[mnuSearchSearchOnline]->setShortcut(QKeySequence(Qt::CTRL+Qt::ALT+Qt::Key_F));
    actStatusTips[mnuSearchSearchOnline]=QString(tr("Search text online."));
    connect(act[mnuSearchSearchOnline],SIGNAL(triggered()),this,SLOT(searchOnline()));

    //Search -> Go To Line
    act[mnuSearchGoto]=new QAction(tr("gotoline"),this);
    act[mnuSearchGoto]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_G));
    actStatusTips[mnuSearchGoto]=QString(tr("Goto line."));
    connect(act[mnuSearchGoto],SIGNAL(triggered()),
            this,SLOT(statusShowGoto()));

    //Run -> Comile And Run
    act[mnuRunCompileAndRun]=new QAction(tr("Compile & Run"),this);
    act[mnuRunCompileAndRun]->setShortcut(QKeySequence(Qt::Key_F11));
    actStatusTips[mnuRunCompileAndRun]=QString(tr("Compile the active file and run."));
    connect(act[mnuRunCompileAndRun],SIGNAL(triggered()),this,SLOT(compileAndRun()));

    //Run -> Compile
    act[mnuRunCompile]=new QAction(tr("compile"),this);
    act[mnuRunCompile]->setShortcut(QKeySequence(Qt::Key_F9));
    actStatusTips[mnuRunCompile]=QString(tr("Compile the active file."));
    connect(act[mnuRunCompile],SIGNAL(triggered()),
            this,SLOT(compileCurrentFile()));

    //Run -> Run
    act[mnuRunRun]=new QAction(tr("Runexe"),this);
    act[mnuRunRun]->setShortcut(QKeySequence(Qt::Key_F10));
    actStatusTips[mnuRunRun]=QString(tr("Run the compiled execution."));
    connect(act[mnuRunRun],SIGNAL(triggered()),this,SLOT(run()));

    //Run -> Parameters
    act[mnuRunParameters]=new QAction(tr("Parameters"),this);
    actStatusTips[mnuRunParameters]=QString(tr("Run the compiled execution with parameters."));

    //Run -> Set Input File
    act[mnuRunSetInputFile]=new QAction(tr("Set Input File"),this);
    actStatusTips[mnuRunSetInputFile]=QString(tr("Set the input file contents."));

    //Run -> Show Output File
    act[mnuRunShowOutputFile]=new QAction(tr("Show Output file"),this);
    actStatusTips[mnuRunShowOutputFile]=QString(tr("Show the output file contents."));

    //Run -> Run And Show Output File
    act[mnuRunRunAndShowOutputFile]=new QAction(tr("Run And Show Output File"),this);
    actStatusTips[mnuRunRunAndShowOutputFile]=QString(tr("Run the execution and show output file."));

    //Run -> Set Input, Run and Show Output
    act[mnuRunSetInputRunShowOutput]=new QAction(
                tr("Set Input, Run and show Output"), this);
    actStatusTips[mnuRunSetInputRunShowOutput]=
            QString(tr("Set the input file, compile and run the document, and show output file."));

    //Debug -> Debug Start
    act[mnuDebugStart]=new QAction(tr("Start Debug"),this);
    actStatusTips[mnuDebugStart]=QString(tr("Start debugging the active file."));

    //Debug -> Stop Execute
    act[mnuDebugStopExecute]=new QAction(tr("Stop execute"),this);
    actStatusTips[mnuDebugStopExecute]=QString(tr("Stop the active debugging."));

    //Debug -> Set Break Point
    act[mnuDebugSetBreakPoint]=new QAction(tr("set break point"),this);
    actStatusTips[mnuDebugSetBreakPoint]=QString(tr("Set a break point at the current line."));

    //Debug -> Next Line
    act[mnuDebugNextLine]=new QAction(tr("Next Line"),this);
    actStatusTips[mnuDebugNextLine]=QString(tr("Get into and run the next line."));

    //Debug -> Go Into line
    act[mnuDebugIntoLine]=new QAction(tr("Into Line"),this);
    actStatusTips[mnuDebugIntoLine]=QString(tr("Get into the next line."));

    //Debug -> Go Next Instruction
    act[mnuDebugNextInstruction]=new QAction(tr("Next Instruction"),this);
    actStatusTips[mnuDebugNextInstruction]=QString(tr("Get into and run the next instruction."));

    //Debug -> Go Into Instruction
    act[mnuDebugIntoInstruction]=new QAction(tr("Into Instruction"),this);
    actStatusTips[mnuDebugIntoInstruction]=QString(tr("Get into the next instruction."));

    //Debug -> Skip Line
    act[mnuDebugSkipLine]=new QAction(tr("skip line"),this);
    actStatusTips[mnuDebugSkipLine]=QString(tr("Skip the current line."));

    //Debug -> Skip Function
    act[mnuDebugSkipFunction]=new QAction(tr("skip function"),this);
    actStatusTips[mnuDebugSkipFunction]=QString(tr("Skip the current function."));

    //Debug -> Add Watch
    act[mnuDebugAddWatch]=new QAction(tr("Add Watch"),this);
    actStatusTips[mnuDebugAddWatch]=QString(tr("Add a new variable to debug watch."));

    //Debug -> Modify Watch
    act[mnuDebugModifyWatch]=new QAction(tr("Modify Watch"),this);
    actStatusTips[mnuDebugModifyWatch]=QString(tr("Modify a variable in debug watch list."));

    //Debug -> Remove Watch
    act[mnuDebugRemoveWatch]=new QAction(tr("Remove Watch"),this);
    actStatusTips[mnuDebugRemoveWatch]=QString(tr("Remove a variable in debug watch list."));

    //Window -> Window Split
    act[mnuWindowSplit]=new QAction(tr("Split Window"),this);
    actStatusTips[mnuWindowSplit]=QString(tr("Split the window into two part."));

    //Window -> Next
    act[mnuWindowNext]=new QAction(tr("Next"),this);
    act[mnuWindowNext]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Tab));
    actStatusTips[mnuWindowNext]=QString(tr("Switch to the next tab."));
    connect(act[mnuWindowNext],SIGNAL(triggered()),tabManager,SLOT(switchNextTab()));

    //Window -> Previous
    act[mnuWindowPrev]=new QAction(tr("Previous"), this);
    act[mnuWindowPrev]->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_Tab));
    actStatusTips[mnuWindowPrev]=QString(tr("Switch to the previous tab."));
    connect(act[mnuWindowPrev],SIGNAL(triggered()),tabManager,SLOT(switchPrevTab()));

    //Help -> About
    act[mnuHelpAbout]=new QAction(tr("about"),this);
    actStatusTips[mnuHelpAbout]=QString(tr("Display the Kreogist Cuties information."));
    connect(act[mnuHelpAbout],SIGNAL(triggered()),this,SLOT(aboutKCI()));

    //Help -> About Qt
    act[mnuHelpAboutQt]=new QAction(tr("about Qt"),this);
    actStatusTips[mnuHelpAboutQt]=QString(tr("Display the Qt information, version number and copyright."));
    connect(act[mnuHelpAboutQt],SIGNAL(triggered()),this,SLOT(aboutQt()));
}

void MainWindow::aboutKCI()
{
    QMessageBox::about(this,tr("about"),
                       tr("Kreogist Cute IDE is an light IDE which is designed for ACMer/OIer"));
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this,tr("about Qt"));
}

void MainWindow::createTitlebar()
{
    titlebar=new kciTitleBar(this);
    titlebar->setMainButtonIcon(":/img/image/MainMenuButton.png");

    setMenuWidget(titlebar);

    titlebar->setTitle(this->windowTitle());
    setWindowTitle(this->windowTitle());
}

void MainWindow::createDocks()
{
    //Judge Dock
    judgeDock=new kciJudgeDock(this);
    addDockWidget(Qt::RightDockWidgetArea, judgeDock);

    //Compile Dock
    compileDock=new kcicompiledock(this);
    connect(compileDock,SIGNAL(requireOpenErrFile(QString)),
            tabManager,SLOT(openAndJumpTo(QString)));
    connect(compileDock,SIGNAL(requireGotoLine(int,int)),
            tabManager,SLOT(switchCurrentToLine(int,int)));
    connect(compileDock,SIGNAL(requireSetFocus()),
            tabManager,SLOT(setFocus()));
    addDockWidget(Qt::BottomDockWidgetArea,compileDock);
    //TODO: Configure Hide.
    compileDock->hide();
}

void MainWindow::createMenu()
{
    int i;

    QMenu *_mainMenu=new QMenu;
    QIcon *MenuIconAddor=new QIcon;

    //file menu
    MenuIconAddor->addFile(QString(":/img/image/FileMenuIcon.png"));
    menu[mnuFile] = _mainMenu->addMenu(tr("file"));
    menu[mnuFile]->setIcon(*MenuIconAddor);
    for(i=mnuFileNewFile;i<=mnuFileExit;i++)
    {
        MenuIconAddor->addFile(actMenuIconPath[i]);
        act[i]->setIcon(*MenuIconAddor);
        act[i]->setStatusTip(actStatusTips[i]);
        menu[mnuFile]->addAction(act[i]);
    }

    //edit menu
    MenuIconAddor->addFile(QString(":/img/image/EditMenuIcon.png"));
    menu[mnuEdit] = _mainMenu->addMenu(tr("edit"));
    menu[mnuEdit]->setIcon(*MenuIconAddor);
    for(i=mnuEditUndo;i<=mnuEditPreference;i++)
    {
        MenuIconAddor->addFile(actMenuIconPath[i]);
        act[i]->setIcon(*MenuIconAddor);
        act[i]->setStatusTip(actStatusTips[i]);
        menu[mnuEdit]->addAction(act[i]);
    }

    //view menu
    MenuIconAddor->addFile(QString(":/img/image/ViewMenuIcon.png"));
    menu[mnuView] = _mainMenu->addMenu(tr("view"));
    menu[mnuView]->setIcon(*MenuIconAddor);
    for(i=mnuViewCompileDock;i<=mnuViewJudgeDock;i++)
    {
        MenuIconAddor->addFile(actMenuIconPath[i]);
        act[i]->setIcon(*MenuIconAddor);
        act[i]->setStatusTip(actStatusTips[i]);
        menu[mnuView]->addAction(act[i]);
    }

    //search menu
    MenuIconAddor->addFile(QString(":/img/image/SearchMenuIcon.png"));
    menu[mnuSearch] = _mainMenu->addMenu(tr("search"));
    menu[mnuSearch]->setIcon(*MenuIconAddor);
    for(i=mnuSearchFind;i<=mnuSearchGoto;i++)
    {
        MenuIconAddor->addFile(actMenuIconPath[i]);
        act[i]->setStatusTip(actStatusTips[i]);
        act[i]->setIcon(*MenuIconAddor);
        menu[mnuSearch]->addAction(act[i]);
    }

    //insert menu
    MenuIconAddor->addFile(QString(":/img/image/InsertMenuIcon.png"));
    menu[mnuInsert] = _mainMenu->addMenu(tr("insert"));
    menu[mnuInsert]->setIcon(*MenuIconAddor);

    //run menu
    MenuIconAddor->addFile(QString(":/img/image/RunMenuIcon.png"));
    menu[mnuRun] = _mainMenu->addMenu(tr("run"));
    menu[mnuRun]->setIcon(*MenuIconAddor);
    for(i=mnuRunCompileAndRun;i<=mnuRunSetInputRunShowOutput;i++)
    {
        MenuIconAddor->addFile(actMenuIconPath[i]);
        act[i]->setIcon(*MenuIconAddor);
        act[i]->setStatusTip(actStatusTips[i]);
        menu[mnuRun]->addAction(act[i]);
    }

    //debug menu
    MenuIconAddor->addFile(QString(":/img/image/DebugMenuIcon.png"));
    menu[mnuDebug] = _mainMenu->addMenu(tr("debug"));
    menu[mnuDebug]->setIcon(*MenuIconAddor);
    for(i=mnuDebugStart;i<=mnuDebugRemoveWatch;i++)
    {
        MenuIconAddor->addFile(actMenuIconPath[i]);
        act[i]->setIcon(*MenuIconAddor);
        act[i]->setStatusTip(actStatusTips[i]);
        menu[mnuDebug]->addAction(act[i]);
    }

    //Tool menu
    MenuIconAddor->addFile(QString(":/img/image/ToolMenuIcon.png"));
    menu[mnuTool] = _mainMenu->addMenu(tr("tool"));
    menu[mnuTool]->setIcon(*MenuIconAddor);

    //window menu
    MenuIconAddor->addFile(QString(":/img/image/WindowMenuItem.png"));
    menu[mnuWindow] = _mainMenu->addMenu(tr("window"));
    menu[mnuWindow]->setIcon(*MenuIconAddor);
    for(i=mnuWindowSplit;i<=mnuWindowNext;i++)
    {
        MenuIconAddor->addFile(actMenuIconPath[i]);
        act[i]->setIcon(*MenuIconAddor);
        act[i]->setStatusTip(actStatusTips[i]);
        menu[mnuWindow]->addAction(act[i]);
    }

    //help menu
    MenuIconAddor->addFile(QString(":/img/image/HelpMenuIcon.png"));
    menu[mnuHelp] = _mainMenu->addMenu(tr("help"));
    menu[mnuHelp]->setIcon(*MenuIconAddor);
    //from about to about_qt add into help menu
    for(i=mnuHelpAbout;i<=mnuHelpAboutQt;i++)
    {
        MenuIconAddor->addFile(actMenuIconPath[i]);
        act[i]->setIcon(*MenuIconAddor);
        act[i]->setStatusTip(actStatusTips[i]);
        menu[mnuHelp]->addAction(act[i]);
    }

    titlebar->setMenu(_mainMenu);
    setNoDocOpenMenuEnabled();
    connect(tabManager,SIGNAL(tabAdded()),
            this,SLOT(setDocOpenMenuEnabled()));
    connect(tabManager,SIGNAL(tabClear()),
            this,SLOT(setNoDocOpenMenuEnabled()));
}

void MainWindow::createStatusbar()
{
    myStatusBar=new kciStatusBar(this);
    setStatusBar(myStatusBar);

    QPalette pal=myStatusBar->palette();
    pal.setColor(QPalette::Window,QColor(0x89,0x89,0x89));
    pal.setColor(QPalette::Foreground,QColor(255,255,255));
    myStatusBar->setPalette(pal);

    connect(tabManager,SIGNAL(cursorDataChanged(int,int)),
            myStatusBar,SLOT(updateCursorPosition(int,int)));
    connect(myStatusBar,SIGNAL(ToNewPosition(int)),
            this,SLOT(setCurrentTextCursorLine(int)));
}

void MainWindow::setNoDocOpenMenuEnabled()
{
    //Set Enabled
    //File Menu
    act[mnuFileSave]->setEnabled(false);
    act[mnuFileSaveAs]->setEnabled(false);
    act[mnuFileSaveAll]->setEnabled(false);
    act[mnuFileClose]->setEnabled(false);
    act[mnuFileCloseAll]->setEnabled(false);
    act[mnuFileCloseAllExceptThis]->setEnabled(false);
    //Edit Menu
    act[mnuEditUndo]->setEnabled(false);
    act[mnuEditRedo]->setEnabled(false);
    act[mnuEditCut]->setEnabled(false);
    act[mnuEditCopy]->setEnabled(false);
    act[mnuEditPaste]->setEnabled(false);
    act[mnuEditSelectAll]->setEnabled(false);
    //Search Menu
    act[mnuSearchFind]->setEnabled(false);
    act[mnuSearchFindInFiles]->setEnabled(false);
    act[mnuSearchReplace]->setEnabled(false);
    act[mnuSearchReplaceInFiles]->setEnabled(false);
    act[mnuSearchSearchOnline]->setEnabled(false);
    act[mnuSearchGoto]->setEnabled(false);
    menu[mnuSearch]->menuAction()->setEnabled(false);

    //Set Visible
    //File Menu
    act[mnuFileSave]->setVisible(false);
    act[mnuFileSaveAs]->setVisible(false);
    act[mnuFileSaveAll]->setVisible(false);
    act[mnuFileClose]->setVisible(false);
    act[mnuFileCloseAll]->setVisible(false);
    act[mnuFileCloseAllExceptThis]->setVisible(false);
    //Edit Menu
    act[mnuEditUndo]->setVisible(false);
    act[mnuEditRedo]->setVisible(false);
    act[mnuEditCut]->setVisible(false);
    act[mnuEditCopy]->setVisible(false);
    act[mnuEditPaste]->setVisible(false);
    act[mnuEditSelectAll]->setVisible(false);
    //Search Menu
    act[mnuSearchFind]->setVisible(false);
    act[mnuSearchFindInFiles]->setVisible(false);
    act[mnuSearchReplace]->setVisible(false);
    act[mnuSearchReplaceInFiles]->setVisible(false);
    act[mnuSearchSearchOnline]->setVisible(false);
    act[mnuSearchGoto]->setVisible(false);
    menu[mnuSearch]->menuAction()->setVisible(false);
}

void MainWindow::setDocOpenMenuEnabled()
{
    //Set Enabled
    //File Menu
    act[mnuFileSave]->setEnabled(true);
    act[mnuFileSaveAs]->setEnabled(true);
    act[mnuFileSaveAll]->setEnabled(true);
    act[mnuFileClose]->setEnabled(true);
    act[mnuFileCloseAll]->setEnabled(true);
    act[mnuFileCloseAllExceptThis]->setEnabled(true);
    //Edit Menu
    act[mnuEditUndo]->setEnabled(true);
    act[mnuEditRedo]->setEnabled(true);
    act[mnuEditCut]->setEnabled(true);
    act[mnuEditCopy]->setEnabled(true);
    act[mnuEditPaste]->setEnabled(true);
    act[mnuEditSelectAll]->setEnabled(true);
    //Search Menu
    act[mnuSearchFind]->setEnabled(true);
    act[mnuSearchFindInFiles]->setEnabled(true);
    act[mnuSearchReplace]->setEnabled(true);
    act[mnuSearchReplaceInFiles]->setEnabled(true);
    act[mnuSearchSearchOnline]->setEnabled(true);
    act[mnuSearchGoto]->setEnabled(true);
    menu[mnuSearch]->menuAction()->setEnabled(true);

    //Set Visible
    //File Menu
    act[mnuFileSave]->setVisible(true);
    act[mnuFileSaveAs]->setVisible(true);
    act[mnuFileSaveAll]->setVisible(true);
    act[mnuFileClose]->setVisible(true);
    act[mnuFileCloseAll]->setVisible(true);
    act[mnuFileCloseAllExceptThis]->setVisible(true);
    //Edit Menu
    act[mnuEditUndo]->setVisible(true);
    act[mnuEditRedo]->setVisible(true);
    act[mnuEditCut]->setVisible(true);
    act[mnuEditCopy]->setVisible(true);
    act[mnuEditPaste]->setVisible(true);
    act[mnuEditSelectAll]->setVisible(true);
    //Search Menu
    act[mnuSearchFind]->setVisible(true);
    act[mnuSearchFindInFiles]->setVisible(true);
    act[mnuSearchReplace]->setVisible(true);
    act[mnuSearchReplaceInFiles]->setVisible(true);
    act[mnuSearchSearchOnline]->setVisible(true);
    act[mnuSearchGoto]->setVisible(true);
    menu[mnuSearch]->menuAction()->setVisible(true);
}

void MainWindow::restoreSettings()
{
    QSettings settings(kciGlobal::settingsFileName,QSettings::IniFormat);

    settings.beginGroup("MainWindow");

    int n_WindowState;
    float n_X, n_Y, n_width, n_height;
    n_X     = settings.value("x", 0.1).toFloat() * QApplication::desktop()->width();
    n_Y     = settings.value("y", 0.1).toFloat() * QApplication::desktop()->height();
    n_width = settings.value("width", 0.8).toFloat() * QApplication::desktop()->width();
    n_height= settings.value("height", 0.8).toFloat() * QApplication::desktop()->height();

    this->setGeometry(static_cast<int>(n_X),
                      static_cast<int>(n_Y),
                      static_cast<int>(n_width),
                      static_cast<int>(n_height));
    n_WindowState=settings.value("state").toInt();
    switch(n_WindowState)
    {
    case 1:
        titlebar->setWindowMin();
    case 2:
        titlebar->setWindowMax();
    }
    settings.endGroup();
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    kciMainWindow::resizeEvent(e);
    if(this->isMaximized())
    {
        savedGeometry.setSize(e->oldSize());
    }
    else
    {
        savedGeometry.setSize(e->size());

        savedGeometry.setX(x());
        savedGeometry.setY(y());
    }
}

void MainWindow::saveSettings()
{
    QSettings settings(kciGlobal::settingsFileName,QSettings::IniFormat);

    if(!this->isMaximized())
    {
        savedGeometry.setSize(this->size());
        savedGeometry.setX(x());
        savedGeometry.setY(y());
    }

    int n_WindowState;

    //Save ALL settings.

    settings.beginGroup("MainWindow");
    settings.setValue("width",float(savedGeometry.width())/QApplication::desktop()->width());
    settings.setValue("height",float(savedGeometry.height())/QApplication::desktop()->height());
    settings.setValue("x",float(savedGeometry.x())/QApplication::desktop()->width());
    settings.setValue("y",float(savedGeometry.y())/QApplication::desktop()->height());

    switch(windowState())
    {
    case Qt::WindowMinimized:n_WindowState=1;break;
    case Qt::WindowMaximized:n_WindowState=2;break;
    default:n_WindowState=0;break;
    }
    settings.setValue("state",n_WindowState);
    settings.endGroup();
}


void MainWindow::closeEvent(QCloseEvent *e)
{
    if(tabManager->close())
    {
        saveSettings();
        e->accept();
    }
    else
    {
        e->ignore();
    }
}

void MainWindow::compileCurrentFile()
{
    kciTextEditor *currentEditor=qobject_cast<kciTextEditor *>(tabManager->currentWidget());
    //Check Tab Status.
    if(currentEditor!=NULL)
    {
        //File Not Save.
        if(Q_UNLIKELY(!currentEditor->save()))
        {
            QErrorMessage error(this);
            error.showMessage(tr("Saving file failed!"));
            error.exec();
            return;
        }
        //File is Ok now, Get Dock Ready.
        //Clear All Dock Info.
        compileDock->resetCompileDock();
        //Set Compile File Path.
        compileDock->setCompileFilePath(currentEditor->getFilePath());
        //Active Compile Dock.
        compileDock->setVisible(true);
        //Set To Compile Mode.
        compileDock->animeHideError();
        //Prepare Compiler
        compileDock->addText(QTime::currentTime().toString("hh:mm:ss") +
                             " " +
                             tr("Preparing Compiler.")+
                             "\n");
        //Get a compiler ready.
        compilerBase *currentCompiler=
                compilerBaseFactor::createCompilerBase(currentEditor->getFilePath(), currentEditor);
        //Get Compiler Info.
        compileDock->addText(QTime::currentTime().toString("hh:mm:ss") +
                             " " +
                             tr("Current Compiler Details:") +
                             currentCompiler->version() +
                             "\n");
        //Output Compile Message:
        connect(currentCompiler,&compilerBase::compileinfo,compileDock,&kcicompiledock::outputCompileInfo);
        connect(currentCompiler,&compilerBase::output,compileDock,&kcicompiledock::parseMessage);
        connect(currentCompiler,SIGNAL(finished(int)),compileDock,SLOT(compileFinish(int)));
        //Output Compile Info:
        compileDock->addText(QTime::currentTime().toString("hh:mm:ss") +
                             " " +
                             tr("Compile Command:") +
                             "\n");
        currentCompiler->startCompile(currentEditor->getFilePath());
        currentCompiler->waitForFinished();
    }
}

void MainWindow::run()
{
    kciTextEditor *currentEditor=qobject_cast<kciTextEditor *>(tabManager->currentWidget());
    if(currentEditor!=NULL)
    {
        compileCurrentFile();
        kciExecutor *executor=new kciExecutor(this);
        executor->setBackgroundExec(false);
        executor->setEnabledAutoInput(false);

        //execute file name
        QFileInfo _fileInfo(currentEditor->getFilePath());
        QString execName=QString("\"")+_fileInfo.absoluteDir().path()+
                QString("/")+_fileInfo.completeBaseName();
#ifdef Q_OS_WIN32
        execName+=".exe";
#endif
        execName+="\"";
        executor->exec(execName);
    }
}

void MainWindow::compileAndRun()
{
    compileCurrentFile();
    run();
}

void MainWindow::searchOnline()
{
    QString strURL="http://www.baidu.com/s?wd="+tabManager->textNowSelect();
    QDesktopServices::openUrl(QUrl(strURL));
}

void MainWindow::diffVisibleCompileDock()
{
    compileDock->setVisible(!compileDock->isVisible());
}

void MainWindow::diffVisibleJudgeDock()
{
    judgeDock->setVisible(!judgeDock->isVisible());
}

void MainWindow::statusShowGoto()
{
    myStatusBar->showGotoBar(tabManager->getCurrentLineNum(),
                             tabManager->getCurrentLineCount());
}

void MainWindow::setCurrentTextCursorLine(int NewLineNumber)
{
    tabManager->switchCurrentToLine(NewLineNumber-1,0);
}

void MainWindow::showPreference()
{
    kciControlCenter *newControlCenter=new kciControlCenter();
    newControlCenter->show();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> fileList=event->mimeData()->urls();
    QString tmpPath;
    int i=fileList.count();
    while(i--)
    {
        tmpPath=fileList.at(i).path();
        tmpPath=tmpPath.remove(0,1);
        tabManager->openAndJumpTo(tmpPath);
    }
}
