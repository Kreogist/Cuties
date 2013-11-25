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
#include "mainwindow.h"
#include "kcfontconfigure.h"
#include "kclanguageconfigure.h"

MainWindow::MainWindow(QWidget *parent) :
    KCMainWindow(parent)
{
    //Set MainWindow properties.
    setObjectName("MainWindow");
    //Set MainWindow title.
    setWindowTitle(tr(trWindowTitle.toLatin1()));
    //Minimum Window Size.
    setMinimumSize(500,450);

    //Set Palette.
    QPalette pal = palette();
    KCColorConfigure::getInstance()->getPalette(pal,objectName());
    setPalette(pal);

    //Set Central Widget.
    tabManager=new KCTabManager(this);
    connect(tabManager,SIGNAL(currentChanged(int)),
            this,SLOT(onCurrentTabChanged()));
    setCentralWidget(tabManager);

    //Create All Window Contents
    createActions();
    createDocks();
    createTitlebar();
    createMenu();
    createToolBar();
    createStatusbar();

    //Restore the last time running states
    restoreSettings();
    retranslateAndSet();
    connect(KCLanguageConfigure::getInstance(), &KCLanguageConfigure::newLanguageSet,
            this, &MainWindow::retranslateAndSet);
}

void MainWindow::createActions()
{

    //File -> New
    for(int i=actionFileNewFile; i<actionMainWindowCount; i++)
    {
        actionMainWindowItem[i]=new QAction(tr(actionMainWindowText[i].toLatin1()),this);
    }
    actionMainWindowItem[actionFileNewFile]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_N));
    stringActionIconPath[actionFileNewFile]=QString(":/menuicon/image/MenuIcons/mnuFileNew.png");
    connect(actionMainWindowItem[actionFileNewFile],SIGNAL(triggered()),tabManager,SLOT(newFile()));

    //File -> Open
    actionMainWindowItem[actionFileOpen]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_O));
    stringActionIconPath[actionFileOpen]=QString(":/menuicon/image/MenuIcons/mnuFileOpen.png");
    connect(actionMainWindowItem[actionFileOpen],SIGNAL(triggered()),tabManager,SLOT(open()));

    //File -> Save
    actionMainWindowItem[actionFileSave]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_S));
    stringActionIconPath[actionFileSave]=QString(":/menuicon/image/MenuIcons/mnuFileSave.png");
    connect(actionMainWindowItem[actionFileSave],SIGNAL(triggered()),tabManager,SLOT(save()));

    //File -> Save As
    actionMainWindowItem[actionFileSaveAs]->setShortcut(QKeySequence(Qt::CTRL+Qt::ALT+Qt::Key_S));
    stringActionIconPath[actionFileSaveAs]=QString(":/menuicon/image/MenuIcons/mnuFileSaveAs.png");
    connect(actionMainWindowItem[actionFileSaveAs],SIGNAL(triggered()),tabManager,SLOT(saveAs()));

    //File -> Save All
    actionMainWindowItem[actionFileSaveAll]->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_S));
    connect(actionMainWindowItem[actionFileSaveAll],SIGNAL(triggered()),tabManager,SLOT(saveAll()));

    //File -> Close
    actionMainWindowItem[actionFileClose]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_W));
    stringActionIconPath[actionFileClose]=QString(":/menuicon/image/MenuIcons/mnuFileClose.png");
    connect(actionMainWindowItem[actionFileClose],SIGNAL(triggered()),tabManager,SLOT(closeCurrentTab()));

    //File -> Close All
    actionMainWindowItem[actionFileCloseAll]->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_W));
    connect(actionMainWindowItem[actionFileCloseAll],SIGNAL(triggered()),tabManager,SLOT(closeAllTab()));

    //File -> Close All Except This
    actionMainWindowItem[actionFileCloseAllExceptThis]->setShortcut(QKeySequence(Qt::CTRL+Qt::ALT+Qt::Key_W));
    connect(actionMainWindowItem[actionFileCloseAllExceptThis],SIGNAL(triggered()),tabManager,SLOT(closeAllOtherTab()));

    //File -> Exit
    actionMainWindowItem[actionFileExit]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Q));
    actionMainWindowItem[actionFileExit]->setMenuRole(QAction::QuitRole);
    stringActionIconPath[actionFileExit]=QString(":/menuicon/image/MenuIcons/mnuFileExit.png");
    connect(actionMainWindowItem[actionFileExit],SIGNAL(triggered()),this,SLOT(close()));

    //Edit -> Undo
    stringActionIconPath[actionEditUndo]=QString(":/menuicon/image/MenuIcons/mnuEditUndo.png");
    connect(actionMainWindowItem[actionEditUndo],SIGNAL(triggered()),tabManager,SLOT(undo()));

    //Edit -> Redo
    actionMainWindowItem[actionEditRedo]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Y));
    stringActionIconPath[actionEditRedo]=QString(":/menuicon/image/MenuIcons/mnuEditRedo.png");
    connect(actionMainWindowItem[actionEditRedo],SIGNAL(triggered()),tabManager,SLOT(redo()));

    //Edit -> Cut
    stringActionIconPath[actionEditCut]=QString(":/menuicon/image/MenuIcons/mnuEditCut.png");
    connect(actionMainWindowItem[actionEditCut],SIGNAL(triggered()),tabManager,SLOT(cut()));

    //Edit -> Copy
    stringActionIconPath[actionEditCopy]=QString(":/menuicon/image/MenuIcons/mnuEditCopy.png");
    connect(actionMainWindowItem[actionEditCopy],SIGNAL(triggered()),tabManager,SLOT(copy()));

    //Edit -> Paste
    stringActionIconPath[actionEditPaste]=QString(":/menuicon/image/MenuIcons/mnuEditPaste.png");
    connect(actionMainWindowItem[actionEditPaste],SIGNAL(triggered()),tabManager,SLOT(paste()));

    //Edit -> Select All
    stringActionIconPath[actionEditSelectAll]=QString(":/menuicon/image/MenuIcons/mnuEditSelectAll.png");
    connect(actionMainWindowItem[actionEditSelectAll],SIGNAL(triggered()),tabManager,SLOT(selectAll()));

    //View -> Sidebar
    connect(actionMainWindowItem[actionViewSidebar], &QAction::triggered,
            this, &MainWindow::changeSidebarVisibleState);

    //View -> Compile Dock
    connect(actionMainWindowItem[actionViewCompileDock],SIGNAL(triggered()),this,SLOT(changeCompileDockVisibleState()));

    //View -> Debug Controls
    connect(actionMainWindowItem[actionViewDebugControls], &QAction::triggered,
            this, &MainWindow::changeDebugControlVisibleState);

    //View -> Debug Watch Dock
    connect(actionMainWindowItem[actionViewDebugCommandIO], &QAction::triggered,
            this, &MainWindow::changeDebugCommandIOVisibleState);

    //View -> Judge Dock
    /*act[mnuViewJudgeDock]=new QAction(tr("Judge Dock"),this);
    actStatusTips[mnuViewJudgeDock]=QString(tr("Show Judge Dock."));
    connect(act[mnuViewJudgeDock],SIGNAL(triggered()),this,SLOT(diffVisibleJudgeDock()));*/

#ifdef Q_OS_MACX
    //View -> Fullscreen
    actionMainWindowItem[actionViewFullscreen]->setShortcut(Qt::CTRL+Qt::META+Qt::Key_F);
    connect(actionMainWindowItem[actionViewFullscreen], SIGNAL(triggered()),
            this, SLOT(setFullScreen()));
#endif

    //Search -> Search
    actionMainWindowItem[actionSearchFind]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_F));
    connect(actionMainWindowItem[actionSearchFind],SIGNAL(triggered()),tabManager,SLOT(showSearchBar()));
    /*
        //Search -> Find In Files
        act[mnuSearchFindInFiles]=new QAction(tr("Find In Files"),this);
        act[mnuSearchFindInFiles]->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_F));
        actStatusTips[mnuSearchFindInFiles]=QString(tr("Search for a text partten in multiple files."));
    */
    //Search -> Replace
    actionMainWindowItem[actionSearchReplace]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_R));
    connect(actionMainWindowItem[actionSearchReplace],SIGNAL(triggered()),tabManager,SLOT(showReplaceBar()));
    /*
        //Search -> Replace In Files
        act[mnuSearchReplaceInFiles]=new QAction(tr("Replace In Files"),this);
        act[mnuSearchReplaceInFiles]->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_H));
        actStatusTips[mnuSearchReplaceInFiles]=QString(tr("Replace occurrences of a text partten in multiple files."));
    */
    //Search -> Search Online
    actionMainWindowItem[actionSearchSearchOnline]->setShortcut(QKeySequence(Qt::CTRL+Qt::ALT+Qt::Key_F));
    connect(actionMainWindowItem[actionSearchSearchOnline],SIGNAL(triggered()),this,SLOT(onActionSearchOnline()));

    //Search -> Go To Line
    actionMainWindowItem[actionSearchGoto]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_G));
    connect(actionMainWindowItem[actionSearchGoto],SIGNAL(triggered()),
            this,SLOT(statusShowGoto()));

    //Execute -> Comile And Run
    actionMainWindowItem[actionExecuteCompileAndRun]->setShortcut(QKeySequence(Qt::Key_F11));
    connect(actionMainWindowItem[actionExecuteCompileAndRun],SIGNAL(triggered()),this,SLOT(onActionCompileAndRun()));

    //Execute -> Compile
    actionMainWindowItem[actionExecuteCompile]->setShortcut(QKeySequence(Qt::Key_F9));
    connect(actionMainWindowItem[actionExecuteCompile],SIGNAL(triggered()),
            this,SLOT(onActionCompile()));

    //Execute -> Run
    actionMainWindowItem[actionExecuteRun]->setShortcut(QKeySequence(Qt::Key_F10));
    connect(actionMainWindowItem[actionExecuteRun],SIGNAL(triggered()),this,SLOT(onActionRun()));
    /*
        //Execute -> Parameters
        act[mnuExecuteParameters]=new QAction(tr("Parameters"),this);
        actStatusTips[mnuExecuteParameters]=QString(tr("Run the compiled execution with parameters."));

        //Execute -> Set Input File
        act[mnuExecuteSetInputFile]=new QAction(tr("Set Input File"),this);
        actStatusTips[mnuExecuteSetInputFile]=QString(tr("Set the input file contents."));

        //Execute -> Show Output File
        act[mnuExecuteShowOutputFile]=new QAction(tr("Show Output file"),this);
        actStatusTips[mnuExecuteShowOutputFile]=QString(tr("Show the output file contents."));

        //Execute -> Run And Show Output File
        act[mnuExecuteRunAndShowOutputFile]=new QAction(tr("Run And Show Output File"),this);
        actStatusTips[mnuExecuteRunAndShowOutputFile]=QString(tr("Run the execution and show output file."));

        //Execute -> Set Input, Run and Show Output
        act[mnuExecuteSetInputRunShowOutput]=new QAction(
                    tr("Set Input, Run and show Output"), this);
        actStatusTips[mnuExecuteSetInputRunShowOutput]=
                QString(tr("Set the input file, compile and run the document, and show output file."));
    */

    //Tools -> Preferences
    actionMainWindowItem[actionToolsPreferences]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Period));
    actionMainWindowItem[actionToolsPreferences]->setMenuRole(QAction::PreferencesRole);
    stringActionIconPath[actionToolsPreferences]=QString(":/menuicon/image/MenuIcons/mnuEditPerformance.png");
    connect(actionMainWindowItem[actionToolsPreferences],SIGNAL(triggered()),this,SLOT(showPreference()));

    //Window -> Window Split
    /*act[mnuWindowSplit]=new QAction(tr("Split Window"),this);
    actStatusTips[mnuWindowSplit]=QString(tr("Split the window into two part."));*/

    //Window -> Next
    actionMainWindowItem[actionWindowNext]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Tab));
    connect(actionMainWindowItem[actionWindowNext],SIGNAL(triggered()),tabManager,SLOT(switchNextTab()));

    //Window -> Previous
    actionMainWindowItem[actionWindowPrev]->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_Tab));
    connect(actionMainWindowItem[actionWindowPrev],SIGNAL(triggered()),tabManager,SLOT(switchPrevTab()));

    //Help -> About
    actionMainWindowItem[actionHelpAbout]->setMenuRole(QAction::AboutRole);
    connect(actionMainWindowItem[actionHelpAbout],SIGNAL(triggered()),this,SLOT(aboutCuties()));

    //Help -> About Qt
    actionMainWindowItem[actionHelpAboutQt]->setMenuRole(QAction::AboutQtRole);
    connect(actionMainWindowItem[actionHelpAboutQt],SIGNAL(triggered()),this,SLOT(aboutQt()));
}

void MainWindow::aboutCuties()
{
    /*QMessageBox::about(this,tr("About Cuties"),
                       tr("Kreogist Cute IDE is an light IDE which is designed for ACMer/OIer"));*/
    KCMessageBox *test=new KCMessageBox(this);
    test->setTitle("About");
    test->addText(tr("Kreogist Cute IDE is an light IDE which is designed for ACMer/OIer"));
    test->show();
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this, actionMainWindowText[actionHelpAboutQt]);
}

void MainWindow::createTitlebar()
{
    titlebar=getTitleBar();

#ifndef Q_OS_MACX
    setMainButtonIcon(":/img/image/MainMenuButton.png");
    setWindowTitle(windowTitle());
#endif
}

void MainWindow::createToolBar()
{
    //Set Icons.
    QString toolButtonIcon[mainToolbarButtonCount];
    toolButtonIcon[toolButtonNewFile]=":/ToolBar/image/ToolBar/new.png";
    toolButtonIcon[toolButtonOpenFile]=":/ToolBar/image/ToolBar/open.png";
    toolButtonIcon[toolButtonSave]=":/ToolBar/image/ToolBar/save.png";
    toolButtonIcon[toolButtonCut]=":/ToolBar/image/ToolBar/cut.png";
    toolButtonIcon[toolButtonCopy]=":/ToolBar/image/ToolBar/copy.png";
    toolButtonIcon[toolButtonPaste]=":/ToolBar/image/ToolBar/paste.png";
    toolButtonIcon[toolButtonUndo]=":/ToolBar/image/ToolBar/undo.png";
    toolButtonIcon[toolButtonRedo]=":/ToolBar/image/ToolBar/redo.png";
    toolButtonIcon[toolButtonSearch]=":/ToolBar/image/ToolBar/search.png";
    toolButtonIcon[toolButtonCompileAndRun]=":/ToolBar/image/ToolBar/compileandrun.png";

    titlebar->addToolSeparator();
    //Set Other Buttons.
    for(int i=toolButtonNewFile; i<mainToolbarButtonCount; i++)
    {
        buttonMainToolbarItem[i]=new QToolButton(titlebar);
        buttonMainToolbarItem[i]->setFixedSize(25,25);
        buttonMainToolbarItem[i]->setIcon(QIcon(toolButtonIcon[i]));
        titlebar->addToolButton(buttonMainToolbarItem[i]);
        if(i==toolButtonSave || i==toolButtonPaste || i==toolButtonRedo || i==toolButtonSearch)
        {
            titlebar->addToolSeparator();
        }
    }

    connect(buttonMainToolbarItem[toolButtonNewFile],SIGNAL(clicked()),
            tabManager,SLOT(newFile()));
    connect(buttonMainToolbarItem[toolButtonOpenFile],SIGNAL(clicked()),
            tabManager,SLOT(open()));
    connect(buttonMainToolbarItem[toolButtonSave],SIGNAL(clicked()),
            tabManager,SLOT(save()));
    connect(buttonMainToolbarItem[toolButtonCut],SIGNAL(clicked()),
            tabManager,SLOT(cut()));
    connect(buttonMainToolbarItem[toolButtonCopy],SIGNAL(clicked()),
            tabManager,SLOT(copy()));
    connect(buttonMainToolbarItem[toolButtonPaste],SIGNAL(clicked()),
            tabManager,SLOT(paste()));
    connect(buttonMainToolbarItem[toolButtonUndo],SIGNAL(clicked()),
            tabManager,SLOT(undo()));
    connect(buttonMainToolbarItem[toolButtonRedo],SIGNAL(clicked()),
            tabManager,SLOT(redo()));
    connect(buttonMainToolbarItem[toolButtonSearch],SIGNAL(clicked()),
            tabManager,SLOT(showSearchBar()));
    connect(buttonMainToolbarItem[toolButtonCompileAndRun],SIGNAL(clicked()),
            this,SLOT(onActionCompileAndRun()));

}

void MainWindow::createDocks()
{

    /*
    //Judge Dock
    judgeDock=new KCJudgeDock(this);
    addDockWidget(Qt::RightDockWidgetArea, judgeDock);
    */

    setDockNestingEnabled(true);
    //Compile Dock
    compileDock=new KCCompileDock(this);
    connect(compileDock,SIGNAL(requireOpenErrFile(QString)),
            tabManager,SLOT(openAndJumpTo(QString)));
    connect(compileDock,SIGNAL(requireGotoLine(int,int)),
            tabManager,SLOT(switchCurrentToLine(int,int)));
    connect(compileDock,SIGNAL(requireSetFocus()),
            tabManager,SLOT(setFocus()));
    addDockWidget(Qt::BottomDockWidgetArea,compileDock);
    //TODO: Configure Hide.
    compileDock->hide();

    //Sidebar Dock
    sideBar=new KCSideBar(this);
    addDockWidget(Qt::LeftDockWidgetArea,sideBar);
    connect(sideBar, SIGNAL(historyRequiredOpenFiles(QString)),
            tabManager, SLOT(openAndJumpTo(QString)));
    connect(sideBar, SIGNAL(clipboardRequiredInsertText(QString)),
            tabManager, SLOT(insertToCurrentEditor(QString)));

    //Debug Panel
    debugControl=new KCDebugControlPanel(this);
    addDockWidget(Qt::BottomDockWidgetArea, debugControl, Qt::Horizontal);
    connect(debugControl,&KCDebugControlPanel::debugStarted,
            this,&MainWindow::startDebug);
    debugControl->hide();

    //Debug Command IO
    debugCommandIO=new KCDebugCommandIO(this);
    addDockWidget(Qt::BottomDockWidgetArea, debugCommandIO, Qt::Horizontal);
    debugCommandIO->hide();
}

void MainWindow::showDebugDocks()
{
    debugControl->show();
    debugCommandIO->show();
}

void MainWindow::createMenu()
{
    int i;

#ifdef Q_OS_MACX
    QMenuBar *_mainMenu=new QMenuBar(0);
#else
    QMenu *_mainMenu=new QMenu(this);
    QIcon *MenuIconAddor=new QIcon;

    QFont menuFont=KCFontConfigure::getInstance()->getMenuFont();
    _mainMenu->setFont(menuFont);
#endif
    for(i=menuFile; i<menuMainItemsCount; i++)
    {
        menuMainWindowItem[i]= _mainMenu->addMenu(tr(menuMainWindowText[i].toLatin1()));
    }

    //Create File Menu
#ifndef Q_OS_MACX
    MenuIconAddor->addFile(QString(":/img/image/FileMenuIcon.png"));
    menuMainWindowItem[menuFile]->setIcon(*MenuIconAddor);
#endif
    for(i=actionFileNewFile; i<=actionFileExit; i++)
    {
#ifndef Q_OS_MACX
        MenuIconAddor->addFile(stringActionIconPath[i]);
        actionMainWindowItem[i]->setIcon(*MenuIconAddor);
        actionMainWindowItem[i]->setFont(menuFont);
#endif
        menuMainWindowItem[menuFile]->addAction(actionMainWindowItem[i]);
#ifdef Q_OS_MACX
        switch(i)
        {
        case actionFileOpen:
        case actionFileSaveAll:
        case actionFileCloseAllExceptThis:
            menuMainWindowItem[menuFile]->addSeparator();
            break;
        }
#endif
    }

    //Create Edit Menu
#ifndef Q_OS_MACX
    MenuIconAddor->addFile(QString(":/img/image/EditMenuIcon.png"));
    menuMainWindowItem[menuEdit]->setIcon(*MenuIconAddor);
#endif
    for(i=actionEditUndo; i<=actionEditSelectAll; i++)
    {
#ifndef Q_OS_MACX
        MenuIconAddor->addFile(stringActionIconPath[i]);
        actionMainWindowItem[i]->setIcon(*MenuIconAddor);
        actionMainWindowItem[i]->setFont(menuFont);
#endif
        menuMainWindowItem[menuEdit]->addAction(actionMainWindowItem[i]);
#ifdef Q_OS_MACX
        switch(i)
        {
        case actionEditRedo:
        case actionEditPaste:
            menuMainWindowItem[menuEdit]->addSeparator();
            break;
        }
#endif
    }

    //Create View Menu
#ifndef Q_OS_MACX
    MenuIconAddor->addFile(QString(":/img/image/ViewMenuIcon.png"));
    menuMainWindowItem[menuView]->setIcon(*MenuIconAddor);
#endif
    for(i=actionViewSidebar; i<actionViewEnd; i++)
    {
#ifndef Q_OS_MACX
        MenuIconAddor->addFile(stringActionIconPath[i]);
        actionMainWindowItem[i]->setIcon(*MenuIconAddor);
        actionMainWindowItem[i]->setFont(menuFont);
#endif
        menuMainWindowItem[menuView]->addAction(actionMainWindowItem[i]);
#ifdef Q_OS_MACX
        switch(i)
        {
        case actionViewDebugCommandIO:
            menuMainWindowItem[menuView]->addSeparator();
        }

#endif
    }

    //Create Search Menu
#ifndef Q_OS_MACX
    MenuIconAddor->addFile(QString(":/img/image/SearchMenuIcon.png"));
    menuMainWindowItem[menuSearch]->setIcon(*MenuIconAddor);
#endif
    for(i=actionSearchFind; i<=actionSearchGoto; i++)
    {
#ifndef Q_OS_MACX
        MenuIconAddor->addFile(stringActionIconPath[i]);
        actionMainWindowItem[i]->setIcon(*MenuIconAddor);
        actionMainWindowItem[i]->setFont(menuFont);
#endif
        menuMainWindowItem[menuSearch]->addAction(actionMainWindowItem[i]);
#ifdef Q_OS_MACX
        switch(i)
        {
        case actionSearchFind:
        case actionSearchReplace:
        case actionSearchSearchOnline:
            menuMainWindowItem[menuSearch]->addSeparator();
            break;
        }

#endif
    }

    //Create Execute Menu
#ifndef Q_OS_MACX
    MenuIconAddor->addFile(QString(":/img/image/RunMenuIcon.png"));
    menuMainWindowItem[menuExecute]->setIcon(*MenuIconAddor);
#endif
    for(i=actionExecuteCompileAndRun; i<=actionExecuteRun/*mnuExecuteSetInputRunShowOutput*/; i++)
    {
#ifndef Q_OS_MACX
        MenuIconAddor->addFile(stringActionIconPath[i]);
        actionMainWindowItem[i]->setIcon(*MenuIconAddor);
        actionMainWindowItem[i]->setFont(menuFont);
#endif
        menuMainWindowItem[menuExecute]->addAction(actionMainWindowItem[i]);
#ifdef Q_OS_MACX
        switch(i)
        {
        case actionExecuteRun:
            //case mnuExecuteParameters:
            menuMainWindowItem[menuExecute]->addSeparator();
            break;
        }
#endif
    }

    //Create Debug Menu
#ifndef Q_OS_MACX
    MenuIconAddor->addFile(QString(":/img/image/DebugMenuIcon.png"));
    menuMainWindowItem[menuDebug]->setIcon(*MenuIconAddor);
#endif
    for(i=actionDebugStart; i<=actionDebugRemoveWatch/*mnuExecuteSetInputRunShowOutput*/; i++)
    {
#ifndef Q_OS_MACX
        MenuIconAddor->addFile(stringActionIconPath[i]);
        actionMainWindowItem[i]->setIcon(*MenuIconAddor);
        actionMainWindowItem[i]->setFont(menuFont);
#endif
        menuMainWindowItem[menuDebug]->addAction(actionMainWindowItem[i]);
#ifdef Q_OS_MACX
        switch(i)
        {
        case actionDebugRunToCursor:
        case actionDebugReturn:
            menuMainWindowItem[menuDebug]->addSeparator();
            break;
        }
#endif
    }

    //Create Tool Menu
#ifndef Q_OS_MACX
    MenuIconAddor->addFile(QString(":/img/image/ToolMenuIcon.png"));
    menuMainWindowItem[menuTools]->setIcon(*MenuIconAddor);
#endif
    for(i=actionToolsPreferences; i<=actionToolsPreferences; i++)
    {
#ifndef Q_OS_MACX
        MenuIconAddor->addFile(stringActionIconPath[i]);
        actionMainWindowItem[i]->setIcon(*MenuIconAddor);
        actionMainWindowItem[i]->setFont(menuFont);
#endif
        menuMainWindowItem[menuTools]->addAction(actionMainWindowItem[i]);
    }

    //Create Window Menu
#ifndef Q_OS_MACX
    MenuIconAddor->addFile(QString(":/img/image/WindowMenuItem.png"));
    menuMainWindowItem[menuWindow]->setIcon(*MenuIconAddor);
#endif
    for(i=actionWindowPrev; i<=actionWindowNext; i++)
    {
#ifndef Q_OS_MACX
        MenuIconAddor->addFile(stringActionIconPath[i]);
        actionMainWindowItem[i]->setIcon(*MenuIconAddor);
        actionMainWindowItem[i]->setFont(menuFont);
#endif
        menuMainWindowItem[menuWindow]->addAction(actionMainWindowItem[i]);
    }

    //Create Help Menu
#ifndef Q_OS_MACX
    MenuIconAddor->addFile(QString(":/img/image/HelpMenuIcon.png"));
    menuMainWindowItem[menuHelp]->setIcon(*MenuIconAddor);
#endif
    //from about to about_qt add into help menu
    for(i=actionHelpAbout; i<=actionHelpAboutQt; i++)
    {
#ifndef Q_OS_MACX
        MenuIconAddor->addFile(stringActionIconPath[i]);
        actionMainWindowItem[i]->setIcon(*MenuIconAddor);
        actionMainWindowItem[i]->setFont(menuFont);
#endif
        menuMainWindowItem[menuHelp]->addAction(actionMainWindowItem[i]);
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
    statusBar=new KCStatusBar(this);
    setStatusBar(statusBar);

    QPalette pal=statusBar->palette();
    pal.setColor(QPalette::Window,QColor(0x89,0x89,0x89));
    pal.setColor(QPalette::Foreground,QColor(255,255,255));
    statusBar->setPalette(pal);

    connect(tabManager,SIGNAL(rewriteDataChanged(bool)),
            statusBar,SLOT(updateRewriteMode(bool)));
    connect(tabManager, SIGNAL(rewriteDisVisible()),
            statusBar,SLOT(hideRewriteDisplay()));
    connect(tabManager,SIGNAL(cursorDataChanged(int,int)),
            statusBar,SLOT(updateCursorPosition(int,int)));
    connect(statusBar,SIGNAL(toNewLinePosition(int)),
            this,SLOT(setCurrentTextCursorLine(int)));
}

void MainWindow::setDocOpenMenuState(bool state)
{
    int i;
    //File Menu
    for(i=actionFileSave; i<=actionFileCloseAllExceptThis; i++)
    {
        actionMainWindowItem[i]->setEnabled(state);
        actionMainWindowItem[i]->setVisible(state);
    }

    //Edit Menu
    for(i=actionEditUndo; i<=actionEditSelectAll; i++)
    {
        actionMainWindowItem[i]->setEnabled(state);
        actionMainWindowItem[i]->setVisible(state);
    }
#ifdef Q_OS_MACX
    menuMainWindowItem[menuEdit]->menuAction()->setEnabled(state);
    menuMainWindowItem[menuEdit]->menuAction()->setVisible(state);
#endif

    //View Menu
    for(i=actionViewCompileDock;i<=actionViewDebugCommandIO;i++)
    {
        actionMainWindowItem[i]->setEnabled(state);
        actionMainWindowItem[i]->setVisible(state);
    }

    //Search Menu
    for(i=actionSearchFind; i<=actionSearchGoto; i++)
    {
        actionMainWindowItem[i]->setEnabled(state);
        actionMainWindowItem[i]->setVisible(state);
    }
    menuMainWindowItem[menuSearch]->menuAction()->setEnabled(state);
    menuMainWindowItem[menuSearch]->menuAction()->setVisible(state);

    //Execute Menu
    for(i=actionExecuteCompileAndRun; i<=actionExecuteRun/*mnuExecuteSetInputRunShowOutput*/; i++)
    {
        actionMainWindowItem[i]->setEnabled(state);
        actionMainWindowItem[i]->setVisible(state);
    }
    menuMainWindowItem[menuExecute]->menuAction()->setEnabled(state);
    menuMainWindowItem[menuExecute]->menuAction()->setVisible(state);

    //Debug Menu
    for(i=actionDebugStart;i<=actionDebugRemoveWatch;i++)
    {
        actionMainWindowItem[i]->setEnabled(state);
        actionMainWindowItem[i]->setVisible(state);
    }
    menuMainWindowItem[menuDebug]->menuAction()->setEnabled(state);
    menuMainWindowItem[menuDebug]->menuAction()->setVisible(state);

    //Window Menu
    for(i=actionWindowNext; i<=actionWindowNext; i++)
    {
        actionMainWindowItem[i]->setEnabled(state);
        actionMainWindowItem[i]->setVisible(state);
    }
    menuMainWindowItem[menuWindow]->menuAction()->setEnabled(state);
    menuMainWindowItem[menuWindow]->menuAction()->setVisible(state);
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
    QSettings settings(KCGlobal::getInstance()->getSettingsFileName(),QSettings::IniFormat);

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
        setWindowState(Qt::WindowMinimized);
    case 2:
        setWindowState(Qt::WindowMaximized);
    }
#endif
    settings.endGroup();
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    KCMainWindow::resizeEvent(e);
    if(this->isMaximized())
    {
        lastPositionHeight=e->oldSize().height();
        lastPostionWidth=e->oldSize().width();
    }
    else
    {
        lastPositionX=x();
        lastPostionY=y();
        lastPositionHeight=height();
        lastPostionWidth=width();
    }
}

void MainWindow::saveSettings()
{
    QSettings settings(KCGlobal::getInstance()->getSettingsFileName(),QSettings::IniFormat);

    if(!(isMaximized() || isFullScreen()))
    {
        lastPositionX=x();
        lastPostionY=y();
        lastPositionHeight=height();
        lastPostionWidth=width();
    }
#ifndef Q_OS_MACX
    int lastPositionWindowState;
#endif

    //Save ALL settings.
    float deskWidth=float(QApplication::desktop()->width()),
          deskHeight=float(QApplication::desktop()->height());

    settings.beginGroup("MainWindow");
    settings.setValue("x",float(lastPositionX)/deskWidth);
    settings.setValue("y",float(lastPostionY)/deskHeight);
    settings.setValue("width",float(lastPostionWidth)/deskWidth);
    settings.setValue("height",float(lastPositionHeight)/deskHeight);

#ifndef Q_OS_MACX
    switch(windowState())
    {
    case Qt::WindowMinimized:
        lastPositionWindowState=1;
        break;
    case Qt::WindowMaximized:
        lastPositionWindowState=2;
        break;
    default:
        lastPositionWindowState=0;
        break;
    }
    settings.setValue("state",lastPositionWindowState);
#endif
    settings.endGroup();

    KCColorConfigure::getInstance()->writeConfigure();
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
    KCMainWindow::show();
    if(KCGeneralConfigure::getInstance()->getRememberUnclosedFile())
    {
        tabManager->restoreUnclosedFiles();
    }
}

void MainWindow::onActionCompile()
{
    compileFinishedConnection.disConnectAll();
    compileProgram();
}

void MainWindow::compileProgram()
{
    KCCodeEditor *currentEditor=tabManager->getCurrentEditor();
//    currentEditor->showCompileBar ();
 //   return;

    //Check Tab Status.
    if(currentEditor!=NULL)
    {
        //File Not Save.
        if(Q_UNLIKELY(!currentEditor->save()))
        {
            return;
        }
        //if the file has been compiled,
        //then we clean the text of last compiling.
        KCCompileOutputReceiver *receiver=currentEditor->langMode()->getCompilerReceiver();
        if(receiver!=NULL)
        {
            receiver->resetCompilerOutputReceiver();
        }
        if(!currentEditor->langMode()->compilerIsNull())
        {
            //Active Compile Dock.
            compileDock->setVisible(true);
            //Set To Compile Mode.
            compileDock->animeHideCompileError();
            currentEditor->langMode()->compile();
            //The receiver is NULL if we didn't compile the file before.
            //And if receiver is NULL, setReceiver() will cause the program crash.
            //So we getReceiver() again to avoid this.
            receiver=currentEditor->langMode()->getCompilerReceiver();
            compileDock->setCompileOutputReceiver(receiver);
        }
        else
        {
            //Invisible compile dock
            compileDock->setVisible(false);
        }
    }
}

void MainWindow::onActionRun()
{
    KCCodeEditor *currentEditor=tabManager->getCurrentEditor();
    if(currentEditor!=NULL)
    {
        //execute file name
        KCExecutor::getInstance()->exec(currentEditor->getExecFileName());
    }
}

void MainWindow::onActionCompileAndRun()
{
    KCCodeEditor *currentEditor=tabManager->getCurrentEditor();

    //Check Tab Status.
    if(currentEditor!=NULL)
    {
        //when compile successfully, executor will run the program, and hide compile dock.
        compileFinishedConnection.disConnectAll();
        compileFinishedConnection+=connect(currentEditor->langMode(), SIGNAL(requireHideCompileDock()),
                                           compileDock, SLOT(hideCompileDock()));
        compileFinishedConnection+=connect(currentEditor->langMode(),SIGNAL(compileSuccessfully(QString)),
                                           KCExecutor::getInstance(),SLOT(exec(QString)));
        compileProgram();
    }
}

void MainWindow::onActionSearchOnline()
{
    KCGeneralConfigure *instance=KCGeneralConfigure::getInstance();
    QDesktopServices::openUrl(QUrl(instance->getSearchEngineList().at(instance->getSearchEngineIndex()).engineURL +
                                   tabManager->textNowSelect()));
}

void MainWindow::changeSidebarVisibleState()
{
    sideBar->setUnlockState(!sideBar->getUnlockState());
}

void MainWindow::changeCompileDockVisibleState()
{
    compileDock->setVisible(!compileDock->isVisible());
}

void MainWindow::changeDebugControlVisibleState()
{
    debugControl->setVisible(!debugControl->isVisible());
}

void MainWindow::changeDebugCommandIOVisibleState()
{
    debugCommandIO->setVisible(!debugCommandIO->isVisible());
}

void MainWindow::changeJudgeDockVisibleState()
{
    judgeDock->setVisible(!judgeDock->isVisible());
}

void MainWindow::statusShowGoto()
{
    statusBar->showGotoBar(tabManager->getCurrentLineNum(),
                           tabManager->getCurrentLineCount());
}

void MainWindow::setCurrentTextCursorLine(int NewLineNumber)
{
    tabManager->switchCurrentToLine(NewLineNumber-1,0);
}

void MainWindow::retranslateAndSet()
{
    menuMainWindowText[menuFile]=tr("File");
    menuMainWindowText[menuEdit]=tr("Edit");
    menuMainWindowText[menuView]=tr("View");
    menuMainWindowText[menuSearch]=tr("Search");
    menuMainWindowText[menuExecute]=tr("Execute");
    menuMainWindowText[menuDebug]=tr("Debug");
    menuMainWindowText[menuTools]=tr("Tools");
    menuMainWindowText[menuWindow]=tr("Tab");
    menuMainWindowText[menuHelp]=tr("Help");

    actionStatusTips[actionFileNewFile]=tr("Create a new document.");
    actionStatusTips[actionFileOpen]=tr("Open an exsisting document.");
    actionStatusTips[actionFileSave]=tr("Save the active document with a new name.");
    actionStatusTips[actionFileSaveAs]=tr("Save as different file name.");
    actionStatusTips[actionFileSaveAll]=tr("Save all modified documents.");
    actionStatusTips[actionFileClose]=tr("Close the active document.");
    actionStatusTips[actionFileCloseAll]=tr("Close all documents.");
    actionStatusTips[actionFileCloseAllExceptThis]=tr("Close all documents except the active document.");
    actionStatusTips[actionFileExit]=tr("Quit applications; prompts to save documents.");
    actionStatusTips[actionEditUndo]=tr("Undo the last action.");
    actionStatusTips[actionEditRedo]=tr("Redo the previously undone action.");
    actionStatusTips[actionEditCut]=tr("Cut the selection to the Clipboard.");
    actionStatusTips[actionEditCopy]=tr("Copy the selection to the Clipboard.");
    actionStatusTips[actionEditPaste]=tr("Insert Clipboard contents.");
    actionStatusTips[actionEditSelectAll]=tr("Select the entire document.");
    actionStatusTips[actionViewSidebar]=tr("Show or hide the Sidebar.");
    actionStatusTips[actionViewCompileDock]=tr("Show or hide the Compile Dock.");
    actionStatusTips[actionViewDebugControls]=tr("Show or hide the Debug Controls.");
    actionStatusTips[actionViewDebugCommandIO]=tr("Show or hide the Debug Command Input/Output Dock.");
    #ifdef Q_OS_MACX
    actionStatusTips[actionViewFullscreen]=tr("Show or hide fullscreen mode of Cuties.");
    #endif
    actionStatusTips[actionSearchFind]=tr("Search for text in the active document.");
    actionStatusTips[actionSearchReplace]=tr("Replace occurrences of search string.");
    actionStatusTips[actionSearchSearchOnline]=tr("Search the text via online search engine.");
    actionStatusTips[actionSearchGoto]=tr("Go to specified line.");
    actionStatusTips[actionExecuteCompileAndRun]=tr("Compile the active file and run.");
    actionStatusTips[actionExecuteCompile]=tr("Compile the active file.");
    actionStatusTips[actionExecuteRun]=tr("Run the compiled execution.");
    actionStatusTips[actionDebugStart]=tr("Start GNU Debugger to debug your program.");
    actionStatusTips[actionDebugStop]=tr("Stop debugging");
    actionStatusTips[actionDebugRunToCursor]=tr("Run to the current cursor line.");
    actionStatusTips[actionDebugNext]=tr("Continue to the next source line in the current (innermost) stack frame.");
    actionStatusTips[actionDebugContinue]=tr("Resume program execution, at the address where your program last stopped; any breakpoints set at that address are bypassed. ");
    actionStatusTips[actionDebugStep]=tr("Continue running your program until control reaches a different source line, then stop it and return control to GDB.");
    actionStatusTips[actionDebugNexti]=tr("Execute one machine instruction, but if it is a function call, proceed until the function returns.");
    actionStatusTips[actionDebugStepi]=tr("Execute one machine instruction, then stop and return to the debugger.");
    actionStatusTips[actionDebugReturn]=tr("Cancel execution of a function call.");
    actionStatusTips[actionDebugAddWatch]=tr("Add a new variable or expression to watch.");
    actionStatusTips[actionDebugModifiedWatch]=tr("Modified a variable or expression in watching");
    actionStatusTips[actionDebugRemoveWatch]=tr("Remove a variable or expression from watching");
    actionStatusTips[actionToolsPreferences]=tr("Customize your Cuties.");
    actionStatusTips[actionWindowNext]=tr("Switch to the next tab.");
    actionStatusTips[actionWindowPrev]=tr("Switch to the previous tab.");
    actionStatusTips[actionHelpAbout]=tr("Display the Kreogist Cuties information.");
    actionStatusTips[actionHelpAboutQt]=tr("Display the Qt information, version number and copyright.");

    actionMainWindowText[actionFileNewFile]=tr("New Source File");
    actionMainWindowText[actionFileOpen]=tr("Open");
    actionMainWindowText[actionFileSave]=tr("Save");
    actionMainWindowText[actionFileSaveAs]=tr("Save As");
    actionMainWindowText[actionFileSaveAll]=tr("Save All");
    actionMainWindowText[actionFileClose]=tr("Close");
    actionMainWindowText[actionFileCloseAll]=tr("Close All");
    actionMainWindowText[actionFileCloseAllExceptThis]=tr("Close All Other File");
    actionMainWindowText[actionFileExit]=tr("Exit");
    actionMainWindowText[actionEditUndo]=tr("Undo");
    actionMainWindowText[actionEditRedo]=tr("Redo");
    actionMainWindowText[actionEditCut]=tr("Cut");
    actionMainWindowText[actionEditCopy]=tr("Copy");
    actionMainWindowText[actionEditPaste]=tr("Paste");
    actionMainWindowText[actionEditSelectAll]=tr("Select All");
    actionMainWindowText[actionViewSidebar]=tr("Sidebar");
    actionMainWindowText[actionViewCompileDock]=tr("Compiler Dock");
    actionMainWindowText[actionViewDebugControls]=tr("Debug Controls");
    actionMainWindowText[actionViewDebugCommandIO]=tr("Debug Command Dock");
#ifdef Q_OS_MACX
    actionMainWindowText[actionViewFullscreen]=tr("Enter Full Screen");
#endif
    actionMainWindowText[actionSearchFind]=tr("Find");
    actionMainWindowText[actionSearchReplace]=tr("Replace");
    actionMainWindowText[actionSearchSearchOnline]=tr("Search Online");
    actionMainWindowText[actionSearchGoto]=tr("Goto Line");
    actionMainWindowText[actionExecuteCompileAndRun]=tr("Compile and Run");
    actionMainWindowText[actionExecuteCompile]=tr("Compile");
    actionMainWindowText[actionExecuteRun]=tr("Run");
    actionMainWindowText[actionDebugStart]=tr("Start Debug");
    actionMainWindowText[actionDebugStop]=tr("Stop Debug");
    actionMainWindowText[actionDebugRunToCursor]=tr("Run to Cursor");
    actionMainWindowText[actionDebugNext]=tr("Next Line");
    actionMainWindowText[actionDebugContinue]=tr("Continue");
    actionMainWindowText[actionDebugStep]=tr("Step Into");
    actionMainWindowText[actionDebugNexti]=tr("Next Instruction");
    actionMainWindowText[actionDebugStepi]=tr("Into Instruction");
    actionMainWindowText[actionDebugReturn]=tr("Step Over");
    actionMainWindowText[actionDebugAddWatch]=tr("Add Watch");
    actionMainWindowText[actionDebugModifiedWatch]=tr("Modified Watch");
    actionMainWindowText[actionDebugRemoveWatch]=tr("Remove Watch");
    actionMainWindowText[actionToolsPreferences]=tr("Preferences");
    actionMainWindowText[actionWindowNext]=tr("Next");
    actionMainWindowText[actionWindowPrev]=tr("Previous");
    actionMainWindowText[actionHelpAbout]=tr("About");
    actionMainWindowText[actionHelpAboutQt]=tr("About Qt");

    toolButtonTips[toolButtonNewFile]=actionMainWindowText[actionFileNewFile]+"\n"+actionStatusTips[actionFileNewFile];
    toolButtonTips[toolButtonOpenFile]=actionMainWindowText[actionFileOpen]+"\n"+actionStatusTips[actionFileOpen];
    toolButtonTips[toolButtonSave]=actionMainWindowText[actionFileSave]+"\n"+actionStatusTips[actionFileSave];
    toolButtonTips[toolButtonCut]=actionMainWindowText[actionEditCut]+"\n"+actionStatusTips[actionEditCut];
    toolButtonTips[toolButtonCopy]=actionMainWindowText[actionEditCopy]+"\n"+actionStatusTips[actionEditCopy];
    toolButtonTips[toolButtonPaste]=actionMainWindowText[actionEditPaste]+"\n"+actionStatusTips[actionEditPaste];
    toolButtonTips[toolButtonUndo]=actionMainWindowText[actionEditUndo]+"\n"+actionStatusTips[actionEditUndo];
    toolButtonTips[toolButtonRedo]=actionMainWindowText[actionEditRedo]+"\n"+actionStatusTips[actionEditRedo];
    toolButtonTips[toolButtonSearch]=actionMainWindowText[actionSearchFind]+"\n"+actionStatusTips[actionSearchFind];
    toolButtonTips[toolButtonCompileAndRun]=actionMainWindowText[actionExecuteCompileAndRun]+"\n"+actionStatusTips[actionExecuteCompileAndRun];

    setWindowTitle(tr(trWindowTitle.toLatin1()));
    for(int i=menuFile; i<menuMainItemsCount; i++)
    {
        menuMainWindowItem[i]->setTitle(menuMainWindowText[i]);
    }

    for(int i=actionFileNewFile; i<actionMainWindowCount; i++)
    {
        actionMainWindowItem[i]->setText(actionMainWindowText[i]);
        actionMainWindowItem[i]->setStatusTip(actionStatusTips[i]);
    }
    for(int i=toolButtonNewFile; i<mainToolbarButtonCount; i++)
    {
        buttonMainToolbarItem[i]->setToolTip(toolButtonTips[i]);
    }
}

void MainWindow::showPreference()
{
    KCPreference *newPreference=new KCPreference(this);
    newPreference->exec();
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
    KCCodeEditor *currEditor=tabManager->getCurrentEditor();
    if(currEditor==NULL)
    {
        return ;
    }

    KCLanguageMode *currLangMode=currEditor->langMode();
    KCCompileOutputReceiver *compilerReceiver=currLangMode->getCompilerReceiver();
    if(compilerReceiver!=NULL)
    {
        compileDock->setCompileOutputReceiver(compilerReceiver);
    }

    connectDebugDockWithCurrEditor();
}

void MainWindow::startDebug()
{
    KCCodeEditor *currEditor=tabManager->getCurrentEditor();
    KCLanguageMode *currLangMode=currEditor->langMode();
    currLangMode->startDebug();

    connectDebugDockWithCurrEditor();
    showDebugDocks();
}

void MainWindow::connectDebugDockWithCurrEditor()
{
    KCLanguageMode *currLangMode=tabManager->getCurrentEditor()->langMode();

    GdbController *gdbControllerInstance=currLangMode->getGdbController();

    if(gdbControllerInstance!=NULL)
    {
        debugCommandIO->setGdbInstance(gdbControllerInstance);
        debugControl->setGdbController(gdbControllerInstance);
    }
}

#ifdef Q_OS_MACX
void MainWindow::setFullScreen()
{
    if(this->isFullScreen())
    {
        //TODO: The title of the menu can be replaced by a QString.
        actionMainWindowItem[actionViewFullscreen]->setText(tr("Enter Full Screen"));
        this->showNormal();
    }
    else
    {
        actionMainWindowItem[actionViewFullscreen]->setText(tr("Exit Full Screen"));
        this->showFullScreen();
    }
}
#endif
