/*
 *  Copyright 2013 Wang Luming <wlm199558@126.com>
 *  Copyright 2013 Miyanaga Saki <tomguts@126.com>
 *
 *  mainwindow.cpp is part of Kreogist-Cute-IDE.
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
    QMainWindow(parent)
{
    setWindowTitle(tr("Kreogist Cute IDE"));

    tabManager=new kciTabManager(this);
    setCentralWidget(tabManager);
    setContentsMargins(0,0,0,0);
    setMinimumSize(400,150);

    QPalette QPpal = palette();
    QPpal.setBrush(QPalette::Window, QBrush(QColor(83,83,83)));
    setPalette(QPpal);

    setWindowFlags(Qt::FramelessWindowHint);

    restoreSettings();

    createActions();
    createDocks();
    createTitlebar();
    createMenu();
    createStatusbar();
}

void MainWindow::createActions()
{
    //File -> New
    act[mnuFileNewFile]=new QAction(tr("new file"),this);
    act[mnuFileNewFile]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_N));
    actStatusTips[mnuFileNewFile]=QString(tr("Create a new document."));
    connect(act[mnuFileNewFile],SIGNAL(triggered()),
            tabManager,SLOT(new_file()));

    //File -> Open
    act[mnuFileOpen]=new QAction(tr("open"),this);
    act[mnuFileOpen]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_O));
    actStatusTips[mnuFileOpen]=QString(tr("Open an exsisting document."));
    connect(act[mnuFileOpen],SIGNAL(triggered()),tabManager,SLOT(open()));

    //File -> Save
    act[mnuFileSave]=new QAction(tr("save"),this);
    act[mnuFileSave]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_S));
    actStatusTips[mnuFileSave]=QString(tr("Save active document."));
    connect(act[mnuFileSave],SIGNAL(triggered()),tabManager,SLOT(save()));

    //File -> Save As
    act[mnuFileSaveAs]=new QAction(tr("save as"),this);
    act[mnuFileSaveAs]->setShortcut(QKeySequence(Qt::CTRL+Qt::ALT+Qt::Key_S));
    actStatusTips[mnuFileSaveAs]=QString(tr("Save as different file name."));
    connect(act[mnuFileSaveAs],SIGNAL(triggered()),tabManager,SLOT(save_as()));

    //File -> Save All
    act[mnuFileSaveAll]=new QAction(tr("save all"),this);
    act[mnuFileSaveAll]->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_S));
    actStatusTips[mnuFileSaveAll]=QString(tr("Save all modified documents."));
    connect(act[mnuFileSaveAll],SIGNAL(triggered()),tabManager,SLOT(save_all()));

    //File -> Close
    act[mnuFileClose]=new QAction(tr("close"),this);
    actStatusTips[mnuFileClose]=QString(tr("Close the active document."));
    connect(act[mnuFileClose],SIGNAL(triggered()),tabManager,SLOT(close_current_tab()));

    //File -> Close All
    act[mnuFileCloseAll]=new QAction(tr("close all"),this);
    actStatusTips[mnuFileCloseAll]=QString(tr("Close all files."));

    //File -> Close All Except This
    act[mnuFileCloseAllExceptThis]=new QAction(tr("close all other file"),this);
    actStatusTips[mnuFileCloseAllExceptThis]=QString(tr("Close all files except active file."));

    //File -> Exit
    act[mnuFileExit]=new QAction(tr("quit"),this);
    actStatusTips[mnuFileExit]=QString(tr("Quit applications; prompts to save documents."));
    connect(act[mnuFileExit],SIGNAL(triggered()),this,SLOT(close()));

    //Edit -> Undo
    act[mnuEditUndo]=new QAction(tr("undo"),this);
    act[mnuEditUndo]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Z));
    actStatusTips[mnuEditUndo]=QString(tr("Undo the last action."));
    connect(act[mnuEditUndo],SIGNAL(triggered()),tabManager,SLOT(undo()));

    //Edit -> Redo
    act[mnuEditRedo]=new QAction(tr("redo"),this);
    actStatusTips[mnuEditRedo]=QString(tr("Redo the previously undone action."));

    //Edit -> Cut
    act[mnuEditCut]=new QAction(tr("cut"),this);
    actStatusTips[mnuEditCut]=QString(tr("Cut the selection and put it on the clipboard."));

    //Edit -> Copy
    act[mnuEditCopy]=new QAction(tr("copy"),this);
    actStatusTips[mnuEditCopy]=QString(tr("Copy the selection and put it on the clipboard."));

    //Edit -> Paste
    act[mnuEditPaste]=new QAction(tr("paste"),this);
    actStatusTips[mnuEditPaste]=QString(tr("Paste clipboard contents."));

    //Edit -> Select All
    act[mnuEditSelectAll]=new QAction(tr("select all"),this);
    actStatusTips[mnuEditSelectAll]=QString(tr("Select the entire document."));

    //Edit -> Preference
    act[mnuEditPreference]=new QAction(tr("preference"),this);
    actStatusTips[mnuEditPreference]=QString(tr("Customize your IDE."));

    //Search -> Search
    act[mnuSearchFind]=new QAction(tr("searchinfile"),this);
    actStatusTips[mnuSearchFind]=QString(tr("Find the specified text."));

    //Search -> Find In Files
    act[mnuSearchFindInFiles]=new QAction(tr("searchallfile"),this);
    actStatusTips[mnuSearchFindInFiles]=QString(tr("Find text in files."));

    //Search -> Replace
    act[mnuSearchReplace]=new QAction(tr("replaceinfile"),this);
    actStatusTips[mnuSearchReplace]=QString(tr("Replace specfic text with different text."));

    //Search -> Replace In Files
    act[mnuSearchReplaceInFiles]=new QAction(tr("replaceallfile"),this);
    actStatusTips[mnuSearchReplaceInFiles]=QString(tr("Replace in files."));

    //Search -> Search Online
    act[mnuSearchSearchOnline]=new QAction(tr("searchonline"),this);
    actStatusTips[mnuSearchSearchOnline]=QString(tr("Search text online."));

    //Search -> Go To Line
    act[mnuSearchGoto]=new QAction(tr("gotoline"),this);
    actStatusTips[mnuSearchGoto]=QString(tr("Goto line."));

    //Run -> Comile And Run
    act[mnuRunCompileAndRun]=new QAction(tr("Compile & Run"),this);
    actStatusTips[mnuRunCompileAndRun]=QString(tr("Compile the active file and run."));

    //Run -> Compile
    act[mnuRunCompile]=new QAction(tr("compile"),this);
    actStatusTips[mnuRunCompile]=QString(tr("Compile the active file."));

    //Run -> Compile All File
    act[mnuRunCompileAllFiles]=new QAction(tr("Complie all file"),this);
    actStatusTips[mnuRunCompileAllFiles]=QString(tr("Compile all files."));

    //Run -> Run
    act[mnuRunRun]=new QAction(tr("Runexe"),this);
    actStatusTips[mnuRunRun]=QString(tr("Run the compiled execution."));

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

    //about
    act[mnuHelpAbout]=new QAction(tr("about"),this);
    actStatusTips[mnuHelpAbout]=QString(tr("Display the Kreogist Cuties information."));
    connect(act[mnuHelpAbout],SIGNAL(triggered()),this,SLOT(aboutKCI()));

    //about_qt
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
    setMenuWidget(titlebar);
    titlebar->setMainButtonIcon(":/img/image/MainMenuButton.png");
}

void MainWindow::createDocks()
{
    compileDock=new kcicompiledock(this);
    addDockWidget(Qt::BottomDockWidgetArea,compileDock);
}

void MainWindow::createMenu()
{
    int i;

    QMenu *_mainMenu=new QMenu;
    _mainMenu->setWindowOpacity(50);
    QIcon *MenuIconAddor=new QIcon;
    //file menu
    MenuIconAddor->addFile(QString(":/img/image/FileMenuIcon.png"));
    menu[file] = _mainMenu->addMenu(tr("file"));
    menu[file]->setIcon(*MenuIconAddor);
    //from new_file to quit add into file menu
    for(i=mnuFileNewFile;i<=mnuFileExit;i++)
    {
        act[i]->setIcon(*MenuIconAddor);
        act[i]->setStatusTip(actStatusTips[i]);
        menu[file]->addAction(act[i]);
    }

    //edit menu
    MenuIconAddor->addFile(QString(":/img/image/EditMenuIcon.png"));
    menu[edit] = _mainMenu->addMenu(tr("edit"));
    menu[edit]->setIcon(*MenuIconAddor);
    //from redo to paste add into edit menu
    for(i=mnuEditUndo;i<=mnuEditPreference;i++)
    {
        act[i]->setIcon(*MenuIconAddor);
        act[i]->setStatusTip(actStatusTips[i]);
        menu[edit]->addAction(act[i]);
    }

    //view menu
    MenuIconAddor->addFile(QString(":/img/image/ViewMenuIcon.png"));
    menu[view] = _mainMenu->addMenu(tr("view"));
    menu[view]->setIcon(*MenuIconAddor);

    //search menu
    MenuIconAddor->addFile(QString(":/img/image/SearchMenuIcon.png"));
    menu[search] = _mainMenu->addMenu(tr("search"));
    menu[search]->setIcon(*MenuIconAddor);
    for(i=mnuSearchFind;i<=mnuSearchGoto;i++)
    {
        menu[search]->addAction(act[i]);
        act[i]->setStatusTip(actStatusTips[i]);
        act[i]->setIcon(*MenuIconAddor);
    }

    //insert menu
    MenuIconAddor->addFile(QString(":/img/image/InsertMenuIcon.png"));
    menu[insert] = _mainMenu->addMenu(tr("insert"));
    menu[insert]->setIcon(*MenuIconAddor);

    //run menu
    MenuIconAddor->addFile(QString(":/img/image/RunMenuIcon.png"));
    menu[run] = _mainMenu->addMenu(tr("run"));
    menu[run]->setIcon(*MenuIconAddor);
    for(i=mnuRunCompileAndRun;i<=mnuRunSetInputRunShowOutput;i++)
    {
        act[i]->setIcon(*MenuIconAddor);
        act[i]->setStatusTip(actStatusTips[i]);
        menu[run]->addAction(act[i]);
    }

    //debug menu
    MenuIconAddor->addFile(QString(":/img/image/DebugMenuIcon.png"));
    menu[debug] = _mainMenu->addMenu(tr("debug"));
    menu[debug]->setIcon(*MenuIconAddor);
    for(i=mnuDebugStart;i<=mnuDebugRemoveWatch;i++)
    {
        act[i]->setIcon(*MenuIconAddor);
        act[i]->setStatusTip(actStatusTips[i]);
        menu[debug]->addAction(act[i]);
    }

    //plugins menu
    MenuIconAddor->addFile(QString(":/img/image/PluginMenuIcon.png"));
    menu[plugins] = _mainMenu->addMenu(tr("plugins"));
    menu[plugins]->setIcon(*MenuIconAddor);

    //help menu
    MenuIconAddor->addFile(QString(":/img/image/HelpMenuIcon.png"));
    menu[help] = _mainMenu->addMenu(tr("help"));
    menu[help]->setIcon(*MenuIconAddor);
    //from about to about_qt add into help menu
    for(i=mnuHelpAbout;i<=mnuHelpAboutQt;i++)
    {
        act[i]->setIcon(*MenuIconAddor);
        act[i]->setStatusTip(actStatusTips[i]);
        menu[help]->addAction(act[i]);
    }

    titlebar->setMenu(_mainMenu);
}

void MainWindow::createStatusbar()
{
    QStatusBar *statusbar=statusBar();

    QPalette pal=statusbar->palette();
    pal.setColor(QPalette::Window,QColor(0x89,0x89,0x89));
    pal.setColor(QPalette::Foreground,QColor(255,255,255));
    statusbar->setPalette(pal);
}

void MainWindow::restoreSettings()
{
    QSettings settings(kciGlobal::settingsFileName,QSettings::IniFormat);

    settings.beginGroup("MainWindow");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("state").toByteArray());
    settings.endGroup();

}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    if(this->isMaximized())
    {
        savedGeometry.setSize(e->oldSize());

    }
    else
    {
        savedGeometry.setSize(e->size());
    }
    savedGeometry.setX(x());
    savedGeometry.setY(y());
    QMainWindow::resizeEvent(e);
}

void MainWindow::saveSettings()
{
    QSettings settings(kciGlobal::settingsFileName,QSettings::IniFormat);

    settings.beginGroup("MainWindow");
    settings.setValue("geometry",saveGeometry());
    settings.setValue("state",saveState());
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
