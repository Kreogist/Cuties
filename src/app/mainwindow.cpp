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

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    kciMainWindow(parent)
{
    setWindowTitle(tr("Kreogist Cuties"));

    tabManager=new kciTabManager(this);
    connect(tabManager,SIGNAL(currentChanged(int)),
            this,SLOT(onCurrentTabChanged()));

    setCentralWidget(tabManager);
    setMinimumSize(500,450);

    QPalette QPpal = palette();
    QPpal.setBrush(QPalette::Window, QBrush(QColor(83,83,83)));
    setPalette(QPpal);

    createActions();
    createDocks();
    createTitlebar();
    createMenu();
    createToolBar();
    createStatusbar();

    restoreSettings();
}

void MainWindow::createActions()
{
    //File -> New
    act[mnuFileNewFile]=new QAction(tr("&New Source File"),this);
    act[mnuFileNewFile]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_N));
    actMenuIconPath[mnuFileNewFile]=QString(":/menuicon/image/MenuIcons/mnuFileNew.png");
    actStatusTips[mnuFileNewFile]=QString(tr("Create a new document."));
    connect(act[mnuFileNewFile],SIGNAL(triggered()),tabManager,SLOT(new_file()));

    //File -> Open
    act[mnuFileOpen]=new QAction(tr("&Open..."),this);
    act[mnuFileOpen]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_O));
    actMenuIconPath[mnuFileOpen]=QString(":/menuicon/image/MenuIcons/mnuFileOpen.png");
    actStatusTips[mnuFileOpen]=QString(tr("Open an exsisting document."));
    connect(act[mnuFileOpen],SIGNAL(triggered()),tabManager,SLOT(open()));

    //File -> Save
    act[mnuFileSave]=new QAction(tr("&Save"),this);
    act[mnuFileSave]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_S));
    actMenuIconPath[mnuFileSave]=QString(":/menuicon/image/MenuIcons/mnuFileSave.png");
    actStatusTips[mnuFileSave]=QString(tr("Save the active document with a new name."));
    connect(act[mnuFileSave],SIGNAL(triggered()),tabManager,SLOT(save()));

    //File -> Save As
    act[mnuFileSaveAs]=new QAction(tr("Save &As..."),this);
    act[mnuFileSaveAs]->setShortcut(QKeySequence(Qt::CTRL+Qt::ALT+Qt::Key_S));
    actMenuIconPath[mnuFileSaveAs]=QString(":/menuicon/image/MenuIcons/mnuFileSaveAs.png");
    actStatusTips[mnuFileSaveAs]=QString(tr("Save as different file name."));
    connect(act[mnuFileSaveAs],SIGNAL(triggered()),tabManager,SLOT(save_as()));

    //File -> Save All
    act[mnuFileSaveAll]=new QAction(tr("Sa&ve All"),this);
    act[mnuFileSaveAll]->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_S));
    actStatusTips[mnuFileSaveAll]=QString(tr("Save all modified documents."));
    connect(act[mnuFileSaveAll],SIGNAL(triggered()),tabManager,SLOT(save_all()));

    //File -> Close
    act[mnuFileClose]=new QAction(tr("&Close"),this);
    act[mnuFileClose]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_F4));
    actMenuIconPath[mnuFileClose]=QString(":/menuicon/image/MenuIcons/mnuFileClose.png");
    actStatusTips[mnuFileClose]=QString(tr("Close the active document."));
    connect(act[mnuFileClose],SIGNAL(triggered()),tabManager,SLOT(close_current_tab()));

    //File -> Close All
    act[mnuFileCloseAll]=new QAction(tr("C&lose All"),this);
    act[mnuFileCloseAll]->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_F4));
    actStatusTips[mnuFileCloseAll]=QString(tr("Close all documents."));
    connect(act[mnuFileCloseAll],SIGNAL(triggered()),tabManager,SLOT(close_all_tab()));

    //File -> Close All Except This
    act[mnuFileCloseAllExceptThis]=new QAction(tr("Clos&e All Other File"),this);
    act[mnuFileCloseAllExceptThis]->setShortcut(QKeySequence(Qt::CTRL+Qt::ALT+Qt::Key_F4));
    actStatusTips[mnuFileCloseAllExceptThis]=QString(tr("Close all documents except the active document."));
    connect(act[mnuFileCloseAllExceptThis],SIGNAL(triggered()),tabManager,SLOT(close_all_other_tab()));

    //File -> Exit
    act[mnuFileExit]=new QAction(tr("E&xit"),this);
    act[mnuFileExit]->setShortcut(QKeySequence(Qt::ALT+Qt::Key_F4));
    act[mnuFileExit]->setMenuRole(QAction::QuitRole);
    actMenuIconPath[mnuFileExit]=QString(":/menuicon/image/MenuIcons/mnuFileExit.png");
    actStatusTips[mnuFileExit]=QString(tr("Quit applications; prompts to save documents."));
    connect(act[mnuFileExit],SIGNAL(triggered()),this,SLOT(close()));

    //Edit -> Undo
    act[mnuEditUndo]=new QAction(tr("&Undo"),this);
    act[mnuEditUndo]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Z));
    actMenuIconPath[mnuEditUndo]=QString(":/menuicon/image/MenuIcons/mnuEditUndo.png");
    actStatusTips[mnuEditUndo]=QString(tr("Undo the last action."));
    connect(act[mnuEditUndo],SIGNAL(triggered()),tabManager,SLOT(undo()));

    //Edit -> Redo
    act[mnuEditRedo]=new QAction(tr("&Redo"),this);
    act[mnuEditRedo]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Y));
    actMenuIconPath[mnuEditRedo]=QString(":/menuicon/image/MenuIcons/mnuEditRedo.png");
    actStatusTips[mnuEditRedo]=QString(tr("Redo the previously undone action."));
    connect(act[mnuEditRedo],SIGNAL(triggered()),tabManager,SLOT(redo()));

    //Edit -> Cut
    act[mnuEditCut]=new QAction(tr("Cu&t"),this);
    act[mnuEditCut]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_X));
    actMenuIconPath[mnuEditCut]=QString(":/menuicon/image/MenuIcons/mnuEditCut.png");
    actStatusTips[mnuEditCut]=QString(tr("Cut the selection to the Clipboard."));
    connect(act[mnuEditCut],SIGNAL(triggered()),tabManager,SLOT(cut()));

    //Edit -> Copy
    act[mnuEditCopy]=new QAction(tr("&Copy"),this);
    act[mnuEditCopy]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_C));
    actMenuIconPath[mnuEditCopy]=QString(":/menuicon/image/MenuIcons/mnuEditCopy.png");
    actStatusTips[mnuEditCopy]=QString(tr("Copy the selection to the Clipboard."));
    connect(act[mnuEditCopy],SIGNAL(triggered()),tabManager,SLOT(copy()));

    //Edit -> Paste
    act[mnuEditPaste]=new QAction(tr("&Paste"),this);
    act[mnuEditPaste]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_V));
    actMenuIconPath[mnuEditPaste]=QString(":/menuicon/image/MenuIcons/mnuEditPaste.png");
    actStatusTips[mnuEditPaste]=QString(tr("Insert Clipboard contents."));
    connect(act[mnuEditPaste],SIGNAL(triggered()),tabManager,SLOT(paste()));

    //Edit -> Select All
    act[mnuEditSelectAll]=new QAction(tr("&Select All"),this);
    act[mnuEditSelectAll]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_A));
    actMenuIconPath[mnuEditSelectAll]=QString(":/menuicon/image/MenuIcons/mnuEditSelectAll.png");
    actStatusTips[mnuEditSelectAll]=QString(tr("Select the entire document."));
    connect(act[mnuEditSelectAll],SIGNAL(triggered()),tabManager,SLOT(select_all()));

    //Edit -> Preferences
    act[mnuEditPreferences]=new QAction(tr("Preferences"),this);
    act[mnuEditPreferences]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Period));
    act[mnuEditPreferences]->setMenuRole(QAction::PreferencesRole);
    actMenuIconPath[mnuEditPreferences]=QString(":/menuicon/image/MenuIcons/mnuEditPerformance.png");
    actStatusTips[mnuEditPreferences]=QString(tr("Customize your Cuties."));
    connect(act[mnuEditPreferences],SIGNAL(triggered()),this,SLOT(showPreference()));

    //View -> Sidebar
    act[mnuViewSidebar]=new QAction(tr("Sidebar"), this);
    actStatusTips[mnuViewSidebar]=QString(tr("Show or hide the Sidebar."));
    connect(act[mnuViewSidebar],SIGNAL(triggered()),this,SLOT(diffVisibleSidebar()));

    //View -> Compile Dock
    act[mnuViewCompileDock]=new QAction(tr("Compiler Dock"),this);
    actStatusTips[mnuViewCompileDock]=QString(tr("Show or hide the Compile Dock."));
    connect(act[mnuViewCompileDock],SIGNAL(triggered()),this,SLOT(diffVisibleCompileDock()));

    //View -> Debug Dock
    /*act[mnuViewDebugDock]=new QAction(tr("Debug Dock"),this);
    actStatusTips[mnuViewDebugDock]=QString(tr("Show or hide the Debug Dock."));
    connect(act[mnuViewDebugDock],SIGNAL(triggered()),this,SLOT(diffVisibleDebugDock()));

    //View -> Debug Watch Dock
    act[mnuViewDebugWatchDock]=new QAction(tr("Debug Watch Dock"),this);
    actStatusTips[mnuViewDebugWatchDock]=QString(tr("Show or hide the Debug Watch Dock."));
    connect(act[mnuViewDebugWatchDock],SIGNAL(triggered()),this,SLOT(diffVisibleDebugWatchDock()));

    //View -> Judge Dock
    act[mnuViewJudgeDock]=new QAction(tr("Judge Dock"),this);
    actStatusTips[mnuViewJudgeDock]=QString(tr("Show Judge Dock."));
    connect(act[mnuViewJudgeDock],SIGNAL(triggered()),this,SLOT(diffVisibleJudgeDock()));*/

#ifdef Q_OS_MACX
    //View -> Fullscreen
    act[mnuViewFullscreen]=new QAction(tr("Enter Full Screen"), this);
    act[mnuViewFullscreen]->setShortcut(Qt::CTRL+Qt::META+Qt::Key_F);
    actStatusTips[mnuViewFullscreen]=QString(tr("Show or hide fullscreen mode of Cuties."));
    connect(act[mnuViewFullscreen], SIGNAL(triggered()),
            this, SLOT(setFullScreen()));
#endif

    //Search -> Search
    act[mnuSearchFind]=new QAction(tr("&Find"),this);
    act[mnuSearchFind]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_F));
    actStatusTips[mnuSearchFind]=QString(tr("Search for text in the active document."));
    connect(act[mnuSearchFind],SIGNAL(triggered()),tabManager,SLOT(showSearchBar()));
/*
    //Search -> Find In Files
    act[mnuSearchFindInFiles]=new QAction(tr("Fin&d In Files"),this);
    act[mnuSearchFindInFiles]->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_F));
    actStatusTips[mnuSearchFindInFiles]=QString(tr("Search for a text partten in multiple files."));
*/
    //Search -> Replace
    act[mnuSearchReplace]=new QAction(tr("&Replace"),this);
    act[mnuSearchReplace]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_R));
    actStatusTips[mnuSearchReplace]=QString(tr("Replace occurrences of search string."));
    connect(act[mnuSearchReplace],SIGNAL(triggered()),tabManager,SLOT(showReplaceBar()));
/*
    //Search -> Replace In Files
    act[mnuSearchReplaceInFiles]=new QAction(tr("R&eplace In Files"),this);
    act[mnuSearchReplaceInFiles]->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_H));
    actStatusTips[mnuSearchReplaceInFiles]=QString(tr("Replace occurrences of a text partten in multiple files."));
*/
    //Search -> Search Online
    act[mnuSearchSearchOnline]=new QAction(tr("&Search Online"),this);
    act[mnuSearchSearchOnline]->setShortcut(QKeySequence(Qt::CTRL+Qt::ALT+Qt::Key_F));
    actStatusTips[mnuSearchSearchOnline]=QString(tr("Search the text via online search engine."));
    connect(act[mnuSearchSearchOnline],SIGNAL(triggered()),this,SLOT(searchOnline()));

    //Search -> Go To Line
    act[mnuSearchGoto]=new QAction(tr("&Goto Line"),this);
    act[mnuSearchGoto]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_G));
    actStatusTips[mnuSearchGoto]=QString(tr("Go to specified line."));
    connect(act[mnuSearchGoto],SIGNAL(triggered()),
            this,SLOT(statusShowGoto()));

    //Execute -> Comile And Run
    act[mnuExecuteCompileAndRun]=new QAction(tr("C&ompile and Run"),this);
    act[mnuExecuteCompileAndRun]->setShortcut(QKeySequence(Qt::Key_F11));
    actStatusTips[mnuExecuteCompileAndRun]=QString(tr("Compile the active file and run."));
    connect(act[mnuExecuteCompileAndRun],SIGNAL(triggered()),this,SLOT(compileAndRun()));

    //Execute -> Compile
    act[mnuExecuteCompile]=new QAction(tr("&Compile"),this);
    act[mnuExecuteCompile]->setShortcut(QKeySequence(Qt::Key_F9));
    actStatusTips[mnuExecuteCompile]=QString(tr("Compile the active file."));
    connect(act[mnuExecuteCompile],SIGNAL(triggered()),
            this,SLOT(compileCurrentFile()));

    //Execute -> Run
    act[mnuExecuteRun]=new QAction(tr("&Run"),this);
    act[mnuExecuteRun]->setShortcut(QKeySequence(Qt::Key_F10));
    actStatusTips[mnuExecuteRun]=QString(tr("Run the compiled execution."));
    connect(act[mnuExecuteRun],SIGNAL(triggered()),this,SLOT(run()));
/*
    //Execute -> Parameters
    act[mnuExecuteParameters]=new QAction(tr("P&arameters"),this);
    actStatusTips[mnuExecuteParameters]=QString(tr("Run the compiled execution with parameters."));

    //Execute -> Set Input File
    act[mnuExecuteSetInputFile]=new QAction(tr("&Set Input File"),this);
    actStatusTips[mnuExecuteSetInputFile]=QString(tr("Set the input file contents."));

    //Execute -> Show Output File
    act[mnuExecuteShowOutputFile]=new QAction(tr("S&how Output file"),this);
    actStatusTips[mnuExecuteShowOutputFile]=QString(tr("Show the output file contents."));

    //Execute -> Run And Show Output File
    act[mnuExecuteRunAndShowOutputFile]=new QAction(tr("R&un And Show Output File"),this);
    actStatusTips[mnuExecuteRunAndShowOutputFile]=QString(tr("Run the execution and show output file."));

    //Execute -> Set Input, Run and Show Output
    act[mnuExecuteSetInputRunShowOutput]=new QAction(
                tr("Se&t Input, Run and show Output"), this);
    actStatusTips[mnuExecuteSetInputRunShowOutput]=
            QString(tr("Set the input file, compile and run the document, and show output file."));
*/
/*
    //Debug -> Debug Start
    act[mnuDebugStart]=new QAction(tr("Start &Debug"),this);
    act[mnuDebugStart]->setShortcut(QKeySequence(Qt::Key_F5));
    actStatusTips[mnuDebugStart]=QString(tr("Start debugging the active file."));
    connect(act[mnuDebugStart],SIGNAL(triggered()),
            this,SLOT(startDebug()));

    //Debug -> Stop Execute
    act[mnuDebugStopExecute]=new QAction(tr("&Stop Execute"),this);
    act[mnuDebugStopExecute]->setShortcut(QKeySequence(Qt::Key_F6));
    actStatusTips[mnuDebugStopExecute]=QString(tr("Stop the active debugging."));

    //Debug -> Set Break Point
    act[mnuDebugSetBreakPoint]=new QAction(tr("Set Breakpoint"),this);
    actStatusTips[mnuDebugSetBreakPoint]=QString(tr("Set a break point at the current line."));

    //Debug -> Next Line
    act[mnuDebugNextLine]=new QAction(tr("&Next Line"),this);
    act[mnuDebugNextLine]->setShortcut(QKeySequence(Qt::Key_F7));
    actStatusTips[mnuDebugNextLine]=QString(tr("Get into and run the next line."));

    //Debug -> Into line
    act[mnuDebugIntoLine]=new QAction(tr("&Into Line"),this);
    act[mnuDebugIntoLine]->setShortcut(QKeySequence(Qt::Key_F8));
    actStatusTips[mnuDebugIntoLine]=QString(tr("Get into and run the next step."));

    //Debug -> Next Instruction
    act[mnuDebugNextInstruction]=new QAction(tr("N&ext Instruction"),this);
    actStatusTips[mnuDebugNextInstruction]=QString(tr("???????????? Next Instruction"));

    //Debug -> Into Instruction
    act[mnuDebugIntoInstruction]=new QAction(tr("In&to Instruction"),this);
    actStatusTips[mnuDebugIntoInstruction]=QString(tr("???????????? mnuDebugIntoInstruction"));

    //Debug -> Continue
    act[mnuDebugContinue]=new QAction(tr("&Continue"),this);
    actStatusTips[mnuDebugContinue]=QString(tr("????????????? Continue"));

    //Debug -> Skip Function
    act[mnuDebugSkipFunction]=new QAction(tr("S&kip Function"),this);
    actStatusTips[mnuDebugSkipFunction]=QString(tr("Skip the current function."));

    //Debug -> Add Watch
    act[mnuDebugAddWatch]=new QAction(tr("&Add Watch"),this);
    actStatusTips[mnuDebugAddWatch]=QString(tr("Add a new variable to debug watch."));

    //Debug -> Modify Watch
    act[mnuDebugModifyWatch]=new QAction(tr("&Modify Watch"),this);
    actStatusTips[mnuDebugModifyWatch]=QString(tr("Modify a variable in debug watch list."));

    //Debug -> Remove Watch
    act[mnuDebugRemoveWatch]=new QAction(tr("&Remove Watch"),this);
    actStatusTips[mnuDebugRemoveWatch]=QString(tr("Remove a variable in debug watch list."));
*/
    //Window -> Window Split
    /*act[mnuWindowSplit]=new QAction(tr("&Split Window"),this);
    actStatusTips[mnuWindowSplit]=QString(tr("Split the window into two part."));*/

    //Window -> Next
    act[mnuWindowNext]=new QAction(tr("&Next"),this);
    act[mnuWindowNext]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Tab));
    actStatusTips[mnuWindowNext]=QString(tr("Switch to the next tab."));
    connect(act[mnuWindowNext],SIGNAL(triggered()),tabManager,SLOT(switchNextTab()));

    //Window -> Previous
    act[mnuWindowPrev]=new QAction(tr("&Previous"), this);
    act[mnuWindowPrev]->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_Tab));
    actStatusTips[mnuWindowPrev]=QString(tr("Switch to the previous tab."));
    connect(act[mnuWindowPrev],SIGNAL(triggered()),tabManager,SLOT(switchPrevTab()));

    //Help -> About
    act[mnuHelpAbout]=new QAction(tr("&About..."),this);
    act[mnuHelpAbout]->setMenuRole(QAction::AboutRole);
    actStatusTips[mnuHelpAbout]=QString(tr("Display the Kreogist Cuties information."));
    connect(act[mnuHelpAbout],SIGNAL(triggered()),this,SLOT(aboutKCI()));

    //Help -> About Qt
    act[mnuHelpAboutQt]=new QAction(tr("A&bout Qt..."),this);
    actStatusTips[mnuHelpAboutQt]=QString(tr("Display the Qt information, version number and copyright."));
    connect(act[mnuHelpAboutQt],SIGNAL(triggered()),this,SLOT(aboutQt()));
}

void MainWindow::aboutKCI()
{
    QMessageBox::about(this,tr("About Cuties"),
                           tr("Kreogist Cute IDE is an light IDE which is designed for ACMer/OIer"));
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this,tr("About Qt"));
}

void MainWindow::createTitlebar()
{
    titlebar=titleBar();

#ifndef Q_OS_MACX
    setMainButtonIcon(":/img/image/MainMenuButton.png");
    setWindowTitle(windowTitle());
#endif
}

void MainWindow::createToolBar()
{
    //Set Icons.
    QString strIconPath[tlbbutton_count];
    strIconPath[tlbNewFile]=":/ToolBar/image/ToolBar/new.png";
    strIconPath[tlbOpenFile]=":/ToolBar/image/ToolBar/open.png";
    strIconPath[tlbSaveFile]=":/ToolBar/image/ToolBar/save.png";
    strIconPath[tlbCut]=":/ToolBar/image/ToolBar/cut.png";
    strIconPath[tlbCopy]=":/ToolBar/image/ToolBar/copy.png";
    strIconPath[tlbPaste]=":/ToolBar/image/ToolBar/paste.png";
    strIconPath[tlbUndo]=":/ToolBar/image/ToolBar/undo.png";
    strIconPath[tlbRedo]=":/ToolBar/image/ToolBar/redo.png";
    strIconPath[tlbSearch]=":/ToolBar/image/ToolBar/search.png";
    strIconPath[tlbCompileAndRun]=":/ToolBar/image/ToolBar/compileandrun.png";

    //Set Other Buttons.
    for(int i=tlbNewFile;i<tlbbutton_count;i++)
    {
        tblMainButton[i]=new QToolButton(titlebar);
        //tblMainButton[i]->setPalette(pal);
        tblMainButton[i]->setFixedSize(25,25);
        tblMainButton[i]->setIcon(QIcon(strIconPath[i]));
        titlebar->addToolButton(tblMainButton[i]);
        if(i==tlbSaveFile || i==tlbPaste || i==tlbRedo || i==tlbSearch)
        {
            titlebar->addToolSeparator();
        }
    }

    connect(tblMainButton[tlbNewFile],SIGNAL(clicked()),
            tabManager,SLOT(new_file()));
    connect(tblMainButton[tlbOpenFile],SIGNAL(clicked()),
            tabManager,SLOT(open()));
    connect(tblMainButton[tlbSaveFile],SIGNAL(clicked()),
            tabManager,SLOT(save()));
    connect(tblMainButton[tlbCut],SIGNAL(clicked()),
            tabManager,SLOT(cut()));
    connect(tblMainButton[tlbCopy],SIGNAL(clicked()),
            tabManager,SLOT(copy()));
    connect(tblMainButton[tlbPaste],SIGNAL(clicked()),
            tabManager,SLOT(paste()));
    connect(tblMainButton[tlbUndo],SIGNAL(clicked()),
            tabManager,SLOT(undo()));
    connect(tblMainButton[tlbRedo],SIGNAL(clicked()),
            tabManager,SLOT(redo()));
    connect(tblMainButton[tlbSearch],SIGNAL(clicked()),
            tabManager,SLOT(showSearchBar()));
    connect(tblMainButton[tlbCompileAndRun],SIGNAL(clicked()),
            this,SLOT(compileAndRun()));

}

void MainWindow::createDocks()
{

    /*
    //Judge Dock
    judgeDock=new kciJudgeDock(this);
    addDockWidget(Qt::RightDockWidgetArea, judgeDock);
    */

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

    //Debug Dock
    debugDock=new kciDebugDock(this);
    addDockWidget(Qt::BottomDockWidgetArea,debugDock);
    connect(debugDock,SIGNAL(requireStartDebug()),
            this,SLOT(startDebug()));
    debugDock->hide();

    //Debug Watch Dock
    debugWatchDock=new kciDebugWatchDock(this);
    addDockWidget(Qt::RightDockWidgetArea,debugWatchDock);
    debugWatchDock->hide();

    //Sidebar Dock
    sidebarDock=new kciSideBar(this);
    sidebarDock->hide();
    addDockWidget(Qt::LeftDockWidgetArea,sidebarDock);
    connect(sidebarDock, SIGNAL(historyRequiredOpenFiles(QString)),
            tabManager, SLOT(openAndJumpTo(QString)));
    connect(sidebarDock, SIGNAL(clipboardRequiredInsertText(QString)),
            tabManager, SLOT(insertToCurrentEditor(QString)));
}

void MainWindow::createMenu()
{
    int i;

#ifdef Q_OS_MACX
    QMenuBar *_mainMenu=new QMenuBar(0);
#else
    QMenu *_mainMenu=new QMenu(this);
    QIcon *MenuIconAddor=new QIcon;
#endif

    menu[mnuFile]   = _mainMenu->addMenu(tr("&File"));
    menu[mnuEdit]   = _mainMenu->addMenu(tr("&Edit"));
    menu[mnuView]   = _mainMenu->addMenu(tr("&View"));
    menu[mnuSearch] = _mainMenu->addMenu(tr("&Search"));
    menu[mnuExecute]= _mainMenu->addMenu(tr("E&xecute"));
    //menu[mnuDebug]  = _mainMenu->addMenu(tr("&Debug"));
    menu[mnuTools]  = _mainMenu->addMenu(tr("&Tools"));
    menu[mnuWindow] = _mainMenu->addMenu(tr("&Window"));
    menu[mnuHelp]   = _mainMenu->addMenu(tr("&Help"));

    //Create File Menu
#ifndef Q_OS_MACX
    MenuIconAddor->addFile(QString(":/img/image/FileMenuIcon.png"));
    menu[mnuFile]->setIcon(*MenuIconAddor);
#endif
    for(i=mnuFileNewFile;i<=mnuFileExit;i++)
    {
#ifndef Q_OS_MACX
        MenuIconAddor->addFile(actMenuIconPath[i]);
        act[i]->setIcon(*MenuIconAddor);
#endif
        act[i]->setStatusTip(actStatusTips[i]);
        menu[mnuFile]->addAction(act[i]);
#ifdef Q_OS_MACX
        switch(i)
        {
        case mnuFileOpen:
        case mnuFileSaveAll:
        case mnuFileCloseAllExceptThis:
            menu[mnuFile]->addSeparator();
            break;
        }
#endif
    }

    //Create Edit Menu
#ifndef Q_OS_MACX
    MenuIconAddor->addFile(QString(":/img/image/EditMenuIcon.png"));
    menu[mnuEdit]->setIcon(*MenuIconAddor);
#endif
    for(i=mnuEditUndo;i<=mnuEditPreferences;i++)
    {
#ifndef Q_OS_MACX
        MenuIconAddor->addFile(actMenuIconPath[i]);
        act[i]->setIcon(*MenuIconAddor);
#endif
        act[i]->setStatusTip(actStatusTips[i]);
        menu[mnuEdit]->addAction(act[i]);
#ifdef Q_OS_MACX
        switch(i)
        {
        case mnuEditRedo:
        case mnuEditPaste:
            menu[mnuEdit]->addSeparator();
            break;
        }
#endif
    }

    //Create View Menu
#ifndef Q_OS_MACX
    MenuIconAddor->addFile(QString(":/img/image/ViewMenuIcon.png"));
    menu[mnuView]->setIcon(*MenuIconAddor);
#endif
    for(i=mnuViewSidebar;i<mnuViewEnd;i++)
    {
#ifndef Q_OS_MACX
        MenuIconAddor->addFile(actMenuIconPath[i]);
        act[i]->setIcon(*MenuIconAddor);
#endif
        act[i]->setStatusTip(actStatusTips[i]);
        menu[mnuView]->addAction(act[i]);
#ifdef Q_OS_MACX
        switch(i)
        {
        case mnuViewCompileDock:
            menu[mnuView]->addSeparator();
        }

#endif
    }

    //Create Search Menu
#ifndef Q_OS_MACX
    MenuIconAddor->addFile(QString(":/img/image/SearchMenuIcon.png"));
    menu[mnuSearch]->setIcon(*MenuIconAddor);
#endif
    for(i=mnuSearchFind;i<=mnuSearchGoto;i++)
    {
        act[i]->setStatusTip(actStatusTips[i]);
#ifndef Q_OS_MACX
        MenuIconAddor->addFile(actMenuIconPath[i]);
        act[i]->setIcon(*MenuIconAddor);
#endif
        menu[mnuSearch]->addAction(act[i]);
#ifdef Q_OS_MACX
        switch(i)
        {
        case mnuSearchFind:
        //case mnuSearchReplaceInFiles:
        case mnuSearchSearchOnline:
            menu[mnuSearch]->addSeparator();
            break;
        }

#endif
    }

    //Create Execute Menu
#ifndef Q_OS_MACX
    MenuIconAddor->addFile(QString(":/img/image/RunMenuIcon.png"));
    menu[mnuExecute]->setIcon(*MenuIconAddor);
#endif
    for(i=mnuExecuteCompileAndRun;i<=mnuExecuteRun/*mnuExecuteSetInputRunShowOutput*/;i++)
    {
#ifndef Q_OS_MACX
        MenuIconAddor->addFile(actMenuIconPath[i]);
        act[i]->setIcon(*MenuIconAddor);
#endif
        act[i]->setStatusTip(actStatusTips[i]);
        menu[mnuExecute]->addAction(act[i]);
#ifdef Q_OS_MACX
        switch(i)
        {
        case mnuExecuteRun:
        //case mnuExecuteParameters:
            menu[mnuExecute]->addSeparator();
            break;
        }
#endif
    }

    //Create Debug Menu
    /*
#ifndef Q_OS_MACX
    MenuIconAddor->addFile(QString(":/img/image/DebugMenuIcon.png"));
    menu[mnuDebug]->setIcon(*MenuIconAddor);
#endif
    for(i=mnuDebugStart;i<=mnuDebugRemoveWatch;i++)
    {
#ifndef Q_OS_MACX
        MenuIconAddor->addFile(actMenuIconPath[i]);
        act[i]->setIcon(*MenuIconAddor);
#endif
        act[i]->setStatusTip(actStatusTips[i]);
        menu[mnuDebug]->addAction(act[i]);
#ifdef Q_OS_MACX
        switch(i)
        {
        case mnuDebugStopExecute:
        case mnuDebugSetBreakPoint:
        case mnuDebugSkipFunction:
            menu[mnuDebug]->addSeparator();
            break;
        }

#endif
    }*/

    //Create Tool Menu
#ifndef Q_OS_MACX
    MenuIconAddor->addFile(QString(":/img/image/ToolMenuIcon.png"));
    menu[mnuTools]->setIcon(*MenuIconAddor);
#endif

    //Create Window Menu
#ifndef Q_OS_MACX
    MenuIconAddor->addFile(QString(":/img/image/WindowMenuItem.png"));
    menu[mnuWindow]->setIcon(*MenuIconAddor);
#endif
    for(i=mnuWindowPrev;i<=mnuWindowNext;i++)
    {
#ifndef Q_OS_MACX
        MenuIconAddor->addFile(actMenuIconPath[i]);
        act[i]->setIcon(*MenuIconAddor);
#endif
        act[i]->setStatusTip(actStatusTips[i]);
        menu[mnuWindow]->addAction(act[i]);
    }

    //Create Help Menu
#ifndef Q_OS_MACX
    MenuIconAddor->addFile(QString(":/img/image/HelpMenuIcon.png"));
    menu[mnuHelp]->setIcon(*MenuIconAddor);
#endif
    //from about to about_qt add into help menu
    for(i=mnuHelpAbout;i<=mnuHelpAboutQt;i++)
    {
#ifndef Q_OS_MACX
        MenuIconAddor->addFile(actMenuIconPath[i]);
        act[i]->setIcon(*MenuIconAddor);
#endif
        act[i]->setStatusTip(actStatusTips[i]);
        menu[mnuHelp]->addAction(act[i]);
    }

#ifndef Q_OS_MACX
    titlebar->setMenu(_mainMenu);
#endif

    setNoDocOpenMenuEnabled();
    connect(tabManager,SIGNAL(tabAdded()),
            this,SLOT(setDocOpenMenuEnabled()));
    connect(tabManager,SIGNAL(tabAdded()),
            titlebar,SLOT(showToolBar()));
    connect(tabManager,SIGNAL(tabClear()),
            this,SLOT(setNoDocOpenMenuEnabled()));
    connect(tabManager,SIGNAL(tabClear()),
            titlebar,SLOT(hideToolBar()));
#ifndef Q_OS_MACX
    delete MenuIconAddor;
#endif
}

void MainWindow::createStatusbar()
{
    myStatusBar=new kciStatusBar(this);
    setStatusBar(myStatusBar);

    QPalette pal=myStatusBar->palette();
    pal.setColor(QPalette::Window,QColor(0x89,0x89,0x89));
    pal.setColor(QPalette::Foreground,QColor(255,255,255));
    myStatusBar->setPalette(pal);

    connect(tabManager,SIGNAL(rewriteDataChanged(bool)),
            myStatusBar,SLOT(updateRewriteMode(bool)));
    connect(tabManager, SIGNAL(rewriteDisVisible()),
            myStatusBar,SLOT(hideRewriteDisplay()));
    connect(tabManager,SIGNAL(cursorDataChanged(int,int)),
            myStatusBar,SLOT(updateCursorPosition(int,int)));
    connect(myStatusBar,SIGNAL(ToNewPosition(int)),
            this,SLOT(setCurrentTextCursorLine(int)));
}

void MainWindow::setDocOpenMenuState(bool state)
{
    int i;
    //File Menu
    for(i=mnuFileSave;i<=mnuFileCloseAllExceptThis;i++)
    {
        act[i]->setEnabled(state);
        act[i]->setVisible(state);
    }

    //Edit Menu
    for(i=mnuEditUndo;i<=mnuEditSelectAll;i++)
    {
        act[i]->setEnabled(state);
        act[i]->setVisible(state);
    }
#ifdef Q_OS_MACX
    menu[mnuEdit]->menuAction()->setEnabled(state);
    menu[mnuEdit]->menuAction()->setVisible(state);
#endif

    //View Menu
    /*for(i=mnuViewCompileDock;i<=mnuViewDebugWatchDock;i++)
    {
        act[i]->setEnabled(state);
        act[i]->setVisible(state);
    }*/
    act[mnuViewCompileDock]->setEnabled(state);
    act[mnuViewCompileDock]->setVisible(state);

    //Search Menu
    for(i=mnuSearchFind;i<=mnuSearchGoto;i++)
    {
        act[i]->setEnabled(state);
        act[i]->setVisible(state);
    }
    menu[mnuSearch]->menuAction()->setEnabled(state);
    menu[mnuSearch]->menuAction()->setVisible(state);

    //Execute Menu
    for(i=mnuExecuteCompileAndRun;i<=mnuExecuteRun/*mnuExecuteSetInputRunShowOutput*/;i++)
    {
        act[i]->setEnabled(state);
        act[i]->setVisible(state);
    }
    menu[mnuExecute]->menuAction()->setEnabled(state);
    menu[mnuExecute]->menuAction()->setVisible(state);
/*
    //Debug Menu
    for(i=mnuDebugStart;i<=mnuDebugRemoveWatch;i++)
    {
        act[i]->setEnabled(state);
        act[i]->setVisible(state);
    }
    menu[mnuDebug]->menuAction()->setEnabled(state);
    menu[mnuDebug]->menuAction()->setVisible(state);
*/
    //Window Menu
    for(i=mnuWindowNext;i<=mnuWindowNext;i++)
    {
        act[i]->setEnabled(state);
        act[i]->setVisible(state);
    }
    menu[mnuWindow]->menuAction()->setEnabled(state);
    menu[mnuWindow]->menuAction()->setVisible(state);
}

void MainWindow::setNoDocOpenMenuEnabled()
{
    setDocOpenMenuState(false);
}

void MainWindow::setDocOpenMenuEnabled()
{
    setDocOpenMenuState(true);
}

void MainWindow::restoreSettings()
{
    QSettings settings(kciGlobal::getInstance()->getSettingsFileName(),QSettings::IniFormat);

    settings.beginGroup("MainWindow");

#ifndef Q_OS_MACX
    int n_WindowState;
#endif
    float n_X, n_Y, n_width, n_height;

    float deskWidth=float(QApplication::desktop()->width()),
          deskHeight=float(QApplication::desktop()->height());

    n_X     = settings.value("x", 0.1).toFloat();
    n_X     = (n_X>1 || n_X<0)?0.1*deskWidth:n_X*deskWidth;
    n_Y     = settings.value("y", 0.1).toFloat();
    n_Y     = (n_Y>1 || n_Y<0)?0.1*deskHeight:n_Y*deskHeight;
    n_width = settings.value("width", 0.8).toFloat();
    n_width = (n_width>1||n_width<0)?0.8*deskWidth:n_width*deskWidth;
    n_height= settings.value("height", 0.8).toFloat();
    n_height= (n_height>1||n_height<0)?0.8*deskHeight:n_height*deskHeight;

    this->setGeometry(static_cast<int>(n_X),
                      static_cast<int>(n_Y),
                      static_cast<int>(n_width),
                      static_cast<int>(n_height));
#ifndef Q_OS_MACX
    n_WindowState=settings.value("state").toInt();
    switch(n_WindowState)
    {
    case 1:
        titlebar->setWindowMin();
    case 2:
        titlebar->setWindowMax();
    }
#endif
    settings.endGroup();
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    kciMainWindow::resizeEvent(e);
    if(this->isMaximized())
    {
        sgoH=e->oldSize().height();
        sgoW=e->oldSize().width();
    }
    else
    {
        sgoX=this->x();
        sgoY=this->y();
        sgoH=this->height();
        sgoW=this->width();
    }
}

void MainWindow::saveSettings()
{
    QSettings settings(kciGlobal::getInstance()->getSettingsFileName(),QSettings::IniFormat);

    if(!(this->isMaximized() || this->isFullScreen()))
    {
        sgoX=this->x();
        sgoY=this->y();
        sgoH=this->height();
        sgoW=this->width();
    }
#ifndef Q_OS_MACX
    int n_WindowState;
#endif

    //Save ALL settings.
    float deskWidth=float(QApplication::desktop()->width()),
          deskHeight=float(QApplication::desktop()->height());

    settings.beginGroup("MainWindow");
    settings.setValue("width",float(sgoW)/deskWidth);
    settings.setValue("height",float(sgoH)/deskHeight);
    settings.setValue("x",float(sgoX)/deskWidth);
    settings.setValue("y",float(sgoY)/deskHeight);

#ifndef Q_OS_MACX
    switch(windowState())
    {
    case Qt::WindowMinimized:n_WindowState=1;break;
    case Qt::WindowMaximized:n_WindowState=2;break;
    default:n_WindowState=0;break;
    }
    settings.setValue("state",n_WindowState);
#endif
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

void MainWindow::show()
{
    kciMainWindow::show();
    if(kciGeneralConfigure::getInstance()->getRememberUnclosedFile())
    {
        tabManager->openHistoryFiles();
    }
}

void MainWindow::compileCurrentFile()
{
    kciCodeEditor *currentEditor=tabManager->getCurrentEditor();

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

        //Active Compile Dock.
        compileDock->setVisible(true);
        //Set To Compile Mode.
        compileDock->animeHideError();

        //if the file has been compiled,
        //then we clean the text of last compiling.
        compileOutputReceiver *receiver=currentEditor->langMode()->getCompilerReceiver();
        if(receiver!=NULL)
        {
            receiver->reset();
        }

        currentEditor->langMode()->compile();
        //The receiver is NULL if we didn't compile the file before.
        //And if receiver is NULL, setReceiver() will cause the program crash.
        //So we getReceiver() again to avoid this.
        receiver=currentEditor->langMode()->getCompilerReceiver();

        compileDock->setReceiver(receiver);
    }
}

void MainWindow::run()
{
    kciCodeEditor *currentEditor=tabManager->getCurrentEditor();
    if(currentEditor!=NULL)
    {
        //execute file name
        kciExecutor::getInstance()->exec(currentEditor->getExecFileName());
    }
}

void MainWindow::compileAndRun()
{\
    kciCodeEditor *currentEditor=tabManager->getCurrentEditor();

    //Check Tab Status.
    if(currentEditor!=NULL)
    {
        //when compile successfully, executor will run the program.
        if((bool)compileFinishedConnection)
            disconnect(compileFinishedConnection);

        compileFinishedConnection=connect(currentEditor->langMode(),SIGNAL(compileSuccessfully(QString)),
                kciExecutor::getInstance(),SLOT(exec(QString)));

        compileCurrentFile();
    }
}

void MainWindow::searchOnline()
{
    QString strURL="http://www.baidu.com/s?wd="+tabManager->textNowSelect();
    QDesktopServices::openUrl(QUrl(strURL));
}

void MainWindow::diffVisibleSidebar()
{
    if(sidebarDock->isVisible())
    {
        sidebarDock->hideAnime();
    }
    else
    {
        sidebarDock->showAnime();
    }
}

void MainWindow::diffVisibleCompileDock()
{
    compileDock->setVisible(!compileDock->isVisible());
}

void MainWindow::diffVisibleDebugDock()
{
    debugDock->setVisible(!debugDock->isVisible());
}

void MainWindow::diffVisibleDebugWatchDock()
{
    debugWatchDock->setVisible(!debugWatchDock->isVisible());
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
    kciControlCenter *newControlCenter=new kciControlCenter(this);
    newControlCenter->exec();
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

#ifdef Q_OS_WIN32
        tmpPath=tmpPath.remove(0,1);
#endif

        tabManager->openAndJumpTo(tmpPath);
    }
}

void MainWindow::onCurrentTabChanged()
{
    kciCodeEditor* currEditor=tabManager->getCurrentEditor();
    if(currEditor==NULL)
        return ;

    kciLanguageMode* currLangMode=currEditor->langMode();

    compileOutputReceiver *compilerReceiver=currLangMode->getCompilerReceiver();
    if(compilerReceiver!=NULL)
    {
        compileDock->setReceiver(compilerReceiver);
    }

    connectDebugDockWithCurrEditor();
}

void MainWindow::startDebug()
{
    kciCodeEditor* currEditor=tabManager->getCurrentEditor();
    kciLanguageMode* currLangMode=currEditor->langMode();
    currLangMode->startDebug();

    connectDebugDockWithCurrEditor();
    debugDock->show();
}

void MainWindow::connectDebugDockWithCurrEditor()
{
    kciLanguageMode* currLangMode=tabManager->getCurrentEditor()->langMode();

    dbgOutputReceiver *dbgReceiver=currLangMode->getDbgReceiver();
    if(dbgReceiver!=NULL)
    {
        debugDock->setDbgReceiver(dbgReceiver);
    }

    gdb *gdbInstance=currLangMode->getGdbInstance();
    if(gdbInstance!=NULL)
    {
        debugDock->setGdbInstance(gdbInstance);
    }
}

#ifdef Q_OS_MACX
void MainWindow::setFullScreen()
{
    if(this->isFullScreen())
    {
        //TODO: The title of the menu can be replaced by a QString.
        act[mnuViewFullscreen]->setText(tr("Enter Full Screen"));
        this->showNormal();
    }
    else
    {
        act[mnuViewFullscreen]->setText(tr("Exit Full Screen"));
        this->showFullScreen();
    }
}
#endif
