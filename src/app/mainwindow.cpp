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
#include "kchistoryconfigure.h"
#include "kcstatusrecorder.h"
#include "kcmailreports.h"

MainWindow::MainWindow(QWidget *parent) :
    KCMainWindow(parent)
{
    //Set MainWindow properties.
    setObjectName("MainWindow");
    //Set MainWindow title.
    setWindowTitle(tr(trWindowTitle.toLatin1()));

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
    createDocks();
    createTitlebar();
    createToolBar();
    createStatusbar();
    createMenu();
    createActions();

    connect(tabManager,SIGNAL(tabAdded()),
            this,SLOT(setDocOpenMenuEnabled()));
    connect(tabManager,SIGNAL(tabAdded()),
            titlebar,SLOT(showToolBar()));
    connect(tabManager,SIGNAL(tabClear()),
            this,SLOT(setNoDocOpenMenuEnabled()));
    connect(tabManager,SIGNAL(tabClear()),
            titlebar,SLOT(hideToolBar()));

    //Restore the last time running states
    retranslateAndSet();
    connect(KCLanguageConfigure::getInstance(), &KCLanguageConfigure::newLanguageSet,
            this, &MainWindow::retranslateAndSet);

    welcomeWindow=new KCWelcomeWindow(this);

    showWelcomeWindow=new QPropertyAnimation(welcomeWindow, "geometry", this);
    showWelcomeWindow->setEasingCurve(QEasingCurve::OutCubic);

    hideWelcomeWindow=new QPropertyAnimation(welcomeWindow, "geometry", this);
    hideWelcomeWindow->setEasingCurve(QEasingCurve::OutCubic);

    connect(hideWelcomeWindow, &QPropertyAnimation::finished, welcomeWindow, &KCWelcomeWindow::hide);
    connect(tabManager, &KCTabManager::tabNonClear, this, &MainWindow::animateHideWelcomeWindow);
    connect(tabManager, &KCTabManager::tabClear, this, &MainWindow::animateShowWelcomeWindow);
    connect(welcomeWindow, &KCWelcomeWindow::requiredNewFile,
            tabManager, &KCTabManager::newFileWithHighlight);
    connect(welcomeWindow, SIGNAL(requiredOpenFile()),
            tabManager, SLOT(open()));
    connect(welcomeWindow, SIGNAL(requiredOpenRecentFile(QString)),
            tabManager, SLOT(openAndJumpTo(QString)));
    connect(tabManager, SIGNAL(requiredHideDocks()),
            this, SLOT(hideAllDocks()));
    connect(tabManager, SIGNAL(requireDisconnectDebug()),
            this, SLOT(disconnectDebugDock()));

    restoreSettings();
}

void MainWindow::showEvent(QShowEvent *e)
{
    KCMainWindow::showEvent(e);
    welcomeWindow->setGeometry(width()/8,
                               height()/8,
                               width()/4*3,
                               height()/4*3);
}


void MainWindow::animateShowWelcomeWindow()
{
    hideWelcomeWindow->stop();
    welcomeWindow->show();
    QRect endValue=QRect(width()/8,
                         height()/8,
                         width()/4*3,
                         height()/4*3);
    showWelcomeWindow->setStartValue(welcomeWindow->geometry());
    showWelcomeWindow->setEndValue(endValue);
    showWelcomeWindow->start();
}

void MainWindow::animateHideWelcomeWindow()
{
    showWelcomeWindow->stop();
    QRect endValue=QRect(width()/8,
                         -height(),
                         width()/4*3,
                         height()/4*3);
    hideWelcomeWindow->setStartValue(welcomeWindow->geometry());
    hideWelcomeWindow->setEndValue(endValue);
    hideWelcomeWindow->start();
}

void MainWindow::createActions()
{
    //Set Icon first
    stringActionIconPath[actionFileNewFile]=QString(":/menuicon/image/MenuIcons/mnuFileNew.png");
    stringActionIconPath[actionFileOpen]=QString(":/menuicon/image/MenuIcons/mnuFileOpen.png");
    stringActionIconPath[actionFileSave]=QString(":/menuicon/image/MenuIcons/mnuFileSave.png");
    stringActionIconPath[actionFileSaveAs]=QString(":/menuicon/image/MenuIcons/mnuFileSaveAs.png");
    stringActionIconPath[actionFileClose]=QString(":/menuicon/image/MenuIcons/mnuFileClose.png");
    stringActionIconPath[actionFileExit]=QString(":/menuicon/image/MenuIcons/mnuFileExit.png");
    stringActionIconPath[actionEditUndo]=QString(":/menuicon/image/MenuIcons/mnuEditUndo.png");
    stringActionIconPath[actionEditRedo]=QString(":/menuicon/image/MenuIcons/mnuEditRedo.png");
    stringActionIconPath[actionEditCut]=QString(":/menuicon/image/MenuIcons/mnuEditCut.png");
    stringActionIconPath[actionEditCopy]=QString(":/menuicon/image/MenuIcons/mnuEditCopy.png");
    stringActionIconPath[actionEditPaste]=QString(":/menuicon/image/MenuIcons/mnuEditPaste.png");
    stringActionIconPath[actionEditSelectAll]=QString(":/menuicon/image/MenuIcons/mnuEditSelectAll.png");
    stringActionIconPath[actionToolsPreferences]=QString(":/menuicon/image/MenuIcons/mnuEditPerformance.png");

    int i;
    QIcon *MenuIconAddor=new QIcon;
    QFont menuFont=KCFontConfigure::getInstance()->getMenuFont();
    //Create File Menu
#ifndef Q_OS_MACX
    MenuIconAddor->addFile(QString(":/img/image/FileMenuIcon.png"));
    menuMainWindowItem[menuFile]->setIcon(*MenuIconAddor);
    //KCSubMenu *subMenuFile=new KCSubMenu(this);
#endif
    for(i=actionFileNewFile; i<=actionFileExit; i++)
    {
#ifndef Q_OS_MACX
        actionMainWindowItem[i]=new QAction(tr(actionMainWindowText[i].toLatin1()),
                                            menuMainWindowItem[menuFile]);
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
        actionMainWindowItem[i]=new QAction(tr(actionMainWindowText[i].toLatin1()),
                                            menuMainWindowItem[menuEdit]);
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
    for(i=actionViewSidebar; i<=actionViewFullscreen; i++)
    {
        actionMainWindowItem[i]=new QAction(tr(actionMainWindowText[i].toLatin1()),
                                            menuMainWindowItem[menuView]);
#ifndef Q_OS_MACX
        MenuIconAddor->addFile(stringActionIconPath[i]);
        actionMainWindowItem[i]->setIcon(*MenuIconAddor);
        actionMainWindowItem[i]->setFont(menuFont);
#endif
        menuMainWindowItem[menuView]->addAction(actionMainWindowItem[i]);
#ifdef Q_OS_MACX
        switch(i)
        {
        case actionViewDebugWatch:
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
        actionMainWindowItem[i]=new QAction(tr(actionMainWindowText[i].toLatin1()),
                                            menuMainWindowItem[menuSearch]);
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
        actionMainWindowItem[i]=new QAction(tr(actionMainWindowText[i].toLatin1()),
                                            menuMainWindowItem[menuExecute]);
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
        actionMainWindowItem[i]=new QAction(tr(actionMainWindowText[i].toLatin1()),
                                            menuMainWindowItem[menuDebug]);
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
        actionMainWindowItem[i]=new QAction(tr(actionMainWindowText[i].toLatin1()),
                                            menuMainWindowItem[menuTools]);
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
        actionMainWindowItem[i]=new QAction(tr(actionMainWindowText[i].toLatin1()),
                                            menuMainWindowItem[menuWindow]);
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
    for(i=actionHelpAbout; i<=actionHelpSendFeedbacks; i++)
    {
        actionMainWindowItem[i]=new QAction(tr(actionMainWindowText[i].toLatin1()),
                                            menuMainWindowItem[menuHelp]);
#ifndef Q_OS_MACX
        MenuIconAddor->addFile(stringActionIconPath[i]);
        actionMainWindowItem[i]->setIcon(*MenuIconAddor);
        actionMainWindowItem[i]->setFont(menuFont);
#endif
        menuMainWindowItem[menuHelp]->addAction(actionMainWindowItem[i]);
    }

    setNoDocOpenMenuEnabled();

    //File -> New
    actionMainWindowItem[actionFileNewFile]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_N));
    connect(actionMainWindowItem[actionFileNewFile],SIGNAL(triggered()),tabManager,SLOT(newFile()));

    //File -> Open
    actionMainWindowItem[actionFileOpen]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_O));
    connect(actionMainWindowItem[actionFileOpen],SIGNAL(triggered()),tabManager,SLOT(open()));

    //File -> Save
    actionMainWindowItem[actionFileSave]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_S));
    connect(actionMainWindowItem[actionFileSave],SIGNAL(triggered()),tabManager,SLOT(save()));

    //File -> Save As
    actionMainWindowItem[actionFileSaveAs]->setShortcut(QKeySequence(Qt::CTRL+Qt::ALT+Qt::Key_S));
    connect(actionMainWindowItem[actionFileSaveAs],SIGNAL(triggered()),tabManager,SLOT(saveAs()));

    //File -> Save All
    actionMainWindowItem[actionFileSaveAll]->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_S));
    connect(actionMainWindowItem[actionFileSaveAll],SIGNAL(triggered()),tabManager,SLOT(saveAll()));

    //File -> Close
    actionMainWindowItem[actionFileClose]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_W));
    connect(actionMainWindowItem[actionFileClose],SIGNAL(triggered()),tabManager,SLOT(closeCurrentTab()));

    //File -> Close All
    actionMainWindowItem[actionFileCloseAll]->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_W));
    connect(actionMainWindowItem[actionFileCloseAll],SIGNAL(triggered()),tabManager,SLOT(closeAllTab()));

    //File -> Close All Except This
    actionMainWindowItem[actionFileCloseAllExceptThis]->setShortcut(QKeySequence(Qt::CTRL+Qt::ALT+Qt::Key_W));
    connect(actionMainWindowItem[actionFileCloseAllExceptThis],SIGNAL(triggered()),tabManager,SLOT(closeAllOtherTab()));

    //File -> Exit
    actionMainWindowItem[actionFileExit]->setMenuRole(QAction::QuitRole);
    connect(actionMainWindowItem[actionFileExit],SIGNAL(triggered()),this,SLOT(close()));

    //Edit -> Undo
    connect(actionMainWindowItem[actionEditUndo],SIGNAL(triggered()),tabManager,SLOT(undo()));

    //Edit -> Redo
    actionMainWindowItem[actionEditRedo]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Y));
    connect(actionMainWindowItem[actionEditRedo],SIGNAL(triggered()),tabManager,SLOT(redo()));

    //Edit -> Cut
    connect(actionMainWindowItem[actionEditCut],SIGNAL(triggered()),tabManager,SLOT(cut()));

    //Edit -> Copy
    connect(actionMainWindowItem[actionEditCopy],SIGNAL(triggered()),tabManager,SLOT(copy()));

    //Edit -> Paste
    connect(actionMainWindowItem[actionEditPaste],SIGNAL(triggered()),tabManager,SLOT(paste()));

    //Edit -> Select All
    connect(actionMainWindowItem[actionEditSelectAll],SIGNAL(triggered()),tabManager,SLOT(selectAll()));

    //View -> Sidebar
    connect(actionMainWindowItem[actionViewSidebar], &QAction::triggered,
            this, &MainWindow::changeSidebarVisibleState);

    //View -> Compile Dock
    connect(actionMainWindowItem[actionViewCompileDock],SIGNAL(triggered()),this,SLOT(changeCompileDockVisibleState()));

    //View -> Debug Controls
    connect(actionMainWindowItem[actionViewDebugControls], &QAction::triggered,
            this, &MainWindow::changeDebugControlVisibleState);

    //View -> Debug Command IO
    connect(actionMainWindowItem[actionViewDebugCommandIO], &QAction::triggered,
            this, &MainWindow::changeDebugCommandIOVisibleState);

    //View -> Debug Watch
    connect(actionMainWindowItem[actionViewDebugWatch], &QAction::triggered,
            this, &MainWindow::changeDebugWatchVisibleState);

    //View -> Judge Dock
    /*act[mnuViewJudgeDock]=new QAction(tr("Judge Dock"),this);
    actStatusTips[mnuViewJudgeDock]=QString(tr("Show Judge Dock."));
    connect(act[mnuViewJudgeDock],SIGNAL(triggered()),this,SLOT(diffVisibleJudgeDock()));*/

    //View -> Fullscreen
    actionMainWindowItem[actionViewFullscreen]->setShortcut(Qt::CTRL+Qt::META+Qt::Key_F);
    connect(actionMainWindowItem[actionViewFullscreen], SIGNAL(triggered()),
            this, SLOT(setFullScreen()));

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

    //Debug -> Start Debug
    connect(actionMainWindowItem[actionDebugStart], SIGNAL(triggered()),
            debugControl, SLOT(onDebugStartClicked()));

    //Debug -> Stop Debug
    connect(actionMainWindowItem[actionDebugStop], SIGNAL(triggered()),
            debugControl, SLOT(onDebugStopClicked()));

    //Debug -> Run to Cursor
    connect(actionMainWindowItem[actionDebugRunToCursor], SIGNAL(triggered()),
            debugControl, SLOT(onRunToCursorClicked()));

    //Debug
    connect(actionMainWindowItem[actionDebugNext], SIGNAL(triggered()),
            debugControl, SLOT(onDebugNextClicked()));

    connect(actionMainWindowItem[actionDebugContinue], SIGNAL(triggered()),
            debugControl, SLOT(onDebugContinueClicked()));

    connect(actionMainWindowItem[actionDebugStep], SIGNAL(triggered()),
            debugControl, SLOT(onDebugStepClicked()));

    connect(actionMainWindowItem[actionDebugNexti], SIGNAL(triggered()),
            debugControl, SLOT(onDebugNextiClicked()));

    connect(actionMainWindowItem[actionDebugStepi], SIGNAL(triggered()),
            debugControl, SLOT(onDebugStepiClicked()));

    connect(actionMainWindowItem[actionDebugReturn], SIGNAL(triggered()),
            debugControl, SLOT(onDebugReturnClicked()));

    //Tools -> Preferences
    actionMainWindowItem[actionToolsPreferences]->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Period));
    actionMainWindowItem[actionToolsPreferences]->setMenuRole(QAction::PreferencesRole);
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

    //Help -> Report a bug
    connect(actionMainWindowItem[actionHelpBugReport],SIGNAL(triggered()),this,SLOT(onActionBugReport()));

    //Help -> Send feedbacks
    connect(actionMainWindowItem[actionHelpSendFeedbacks],SIGNAL(triggered()),this,SLOT(onActionSendFeedbacks()));
}

void MainWindow::aboutCuties()
{
    QMessageBox::about(this, tr("About Cuties"),
                       tr("Kreogist Cuties is an light IDE which is designed for ACMer/OIer"));
    /*KCMessageBox *test=new KCMessageBox(this);
    test->setTitle("About");
    test->addText(tr("Kreogist Cute IDE is an light IDE which is designed for ACMer/OIer"));
    test->show();*/
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
    sideBar->hide();
    addDockWidget(Qt::LeftDockWidgetArea,sideBar);
    connect(sideBar, SIGNAL(historyRequiredOpenFiles(QString)),
            tabManager, SLOT(openAndJumpTo(QString)));
    connect(sideBar, SIGNAL(clipboardRequiredInsertText(QString)),
            tabManager, SLOT(insertToCurrentEditor(QString)));
    connect(tabManager, &KCTabManager::tabNonClear,
            sideBar, &KCSideBar::show);
    connect(tabManager, &KCTabManager::tabClear,
            sideBar, &KCSideBar::hide);

    //Debug Panel
    debugControl=new KCDebugControlPanel(this);
    addDockWidget(Qt::BottomDockWidgetArea, debugControl, Qt::Horizontal);
    connect(debugControl, &KCDebugControlPanel::debugStarted,
            this, &MainWindow::startDebug);
    connect(debugControl, &KCDebugControlPanel::debugStopped,
            this, &MainWindow::stopDebug);
    debugControl->hide();

    //Debug Command IO
    debugCommandIO=new KCDebugCommandIO(this);
    addDockWidget(Qt::BottomDockWidgetArea, debugCommandIO, Qt::Horizontal);
    debugCommandIO->hide();

    //Debug Watch
    debugWatch=new KCDebugWatch(this);
    addDockWidget(Qt::RightDockWidgetArea, debugWatch, Qt::Vertical);
    debugWatch->hide();
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
    KCMainMenu *_mainMenu=new KCMainMenu(this);

    QIcon *MenuIconAddor=new QIcon;

    QFont menuFont=KCFontConfigure::getInstance()->getMenuFont();
    _mainMenu->setFont(menuFont);
#endif
    for(i=menuFile; i<menuMainItemsCount; i++)
    {
        menuMainWindowItem[i]=new KCSubMenu(_mainMenu);
        menuMainWindowItem[i]->setTitle(menuMainWindowText[i]);
        _mainMenu->addMenu(menuMainWindowItem[i]);
    }

#ifndef Q_OS_MACX
    delete MenuIconAddor;
    titlebar->setMenu(_mainMenu);
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
    menuMainWindowItem[menuEdit]->menuAction()->setEnabled(state);
    menuMainWindowItem[menuEdit]->menuAction()->setVisible(state);

    //View Menu
    for(i=actionViewSidebar;i<=actionViewDebugWatch;i++)
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
    setGeometry(KCStatusRecorder::getInstance()->getWidgetRect(objectName()));
    Qt::WindowStates mainWindowState=KCStatusRecorder::getInstance()->getWidgetState(objectName());
    if(mainWindowState==Qt::WindowFullScreen)
    {
        setFullScreen();
    }
    else
    {
        setWindowState(mainWindowState);
    }
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    KCMainWindow::resizeEvent(e);

    //Recording window state
    KCStatusRecorder::getInstance()->setWidgetGeometry(objectName(),
                                                       geometry(),
                                                       windowState());

    //Welcome window state sets.
    if(showWelcomeWindow->state()==QPropertyAnimation::Running)
    {
        welcomeWindow->setGeometry(width()/8,
                                   welcomeWindow->y(),
                                   width()/4*3,
                                   height()/4*3);
        showWelcomeWindow->stop();
        animateShowWelcomeWindow();
        return;
    }
    if(hideWelcomeWindow->state()==QPropertyAnimation::Running)
    {
        welcomeWindow->setGeometry(width()/8,
                                   welcomeWindow->y(),
                                   width()/4*3,
                                   height()/4*3);
        hideWelcomeWindow->stop();
        animateHideWelcomeWindow();
        return;
    }
    if(welcomeWindow->isVisible())
    {
        welcomeWindow->setGeometry(width()/8,
                                   height()/8,
                                   width()/4*3,
                                   height()/4*3);
    }
    else
    {
        welcomeWindow->setGeometry(width()/8,
                                   -height(),
                                   width()/4*3,
                                   height()/4*3);
    }
}

void MainWindow::saveSettings()
{
    KCStatusRecorder::getInstance()->setWidgetGeometry(objectName(),
                                                       geometry(),
                                                       windowState());
    KCStatusRecorder::getInstance()->writeRecord();
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
        if(tabManager->count()>0)
        {
            welcomeWindow->hide();
        }
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
    currentEditor->showCompileBar();
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
    actionMainWindowItem[actionViewSidebar]->setText(sideBar->getUnlockState()?sidebarStateString[sidebarLock]:sidebarStateString[sidebarUnlock]);
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

void MainWindow::changeDebugWatchVisibleState()
{
    debugWatch->setVisible(!debugWatch->isVisible());
}

void MainWindow::changeJudgeDockVisibleState()
{
    judgeDock->setVisible(!judgeDock->isVisible());
}

void MainWindow::onActionBugReport()
{
    KCMailReports *bugReport=new KCMailReports(this);
    bugReport->setMode(KCMailReports::BugReportMode);
    bugReport->exec();
}

void MainWindow::onActionSendFeedbacks()
{
    KCMailReports *feedbackReport=new KCMailReports(this);
    feedbackReport->setMode(KCMailReports::FeedbackReportMode);
    feedbackReport->exec();
}

void MainWindow::hideAllDocks()
{
    compileDock->setVisible(false);
    debugControl->setVisible(false);
    debugCommandIO->setVisible(false);
    debugWatch->setVisible(false);
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
    sidebarStateString[sidebarLock]=tr("Lock Sidebar");
    sidebarStateString[sidebarUnlock]=tr("Unlock sidebar");
    fullScreenStateString[fullScreen]=tr("Enter Full Screen");
    fullScreenStateString[normalScreen]=tr("Exit Full Screen");

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
    actionStatusTips[actionViewSidebar]=tr("Lock or unlock the sidebar.");
    actionStatusTips[actionViewCompileDock]=tr("Show or hide the Compile Dock.");
    actionStatusTips[actionViewDebugControls]=tr("Show or hide the Debug Controls.");
    actionStatusTips[actionViewDebugCommandIO]=tr("Show or hide the Debug Command Input/Output Dock.");
    actionStatusTips[actionViewDebugWatch]=tr("Show or hide the Debug Watch dock.");
    actionStatusTips[actionViewFullscreen]=tr("Show or exit full screen mode.");
    actionStatusTips[actionSearchFind]=tr("Search for text in the active document.");
    actionStatusTips[actionSearchReplace]=tr("Replace occurrences of search string.");
    actionStatusTips[actionSearchSearchOnline]=tr("Search the text via online search engine.");
    actionStatusTips[actionSearchGoto]=tr("Go to specified line.");
    actionStatusTips[actionExecuteCompileAndRun]=tr("Compile the active file and run.");
    actionStatusTips[actionExecuteCompile]=tr("Compile the active file.");
    actionStatusTips[actionExecuteRun]=tr("Run the compiled execution.");
    actionStatusTips[actionDebugStart]=tr("Start GNU Debugger to debug your program.");
    actionStatusTips[actionDebugStop]=tr("Stop debugging.");
    actionStatusTips[actionDebugRunToCursor]=tr("Run to the current cursor line.");
    actionStatusTips[actionDebugNext]=tr("Continue to the next source line in the current (innermost) stack frame.");
    actionStatusTips[actionDebugContinue]=tr("Resume program execution, at the address where your program last stopped; any breakpoints set at that address are bypassed. ");
    actionStatusTips[actionDebugStep]=tr("Continue running your program until control reaches a different source line, then stop it and return control to GDB.");
    actionStatusTips[actionDebugNexti]=tr("Execute one machine instruction, but if it is a function call, proceed until the function returns.");
    actionStatusTips[actionDebugStepi]=tr("Execute one machine instruction, then stop and return to the debugger.");
    actionStatusTips[actionDebugReturn]=tr("Cancel execution of a function call.");
    actionStatusTips[actionDebugAddWatch]=tr("Add a new variable or expression to watch.");
    actionStatusTips[actionDebugModifiedWatch]=tr("Modified a variable or expression in watching.");
    actionStatusTips[actionDebugRemoveWatch]=tr("Remove a variable or expression from watching.");
    actionStatusTips[actionToolsPreferences]=tr("Customize your Cuties.");
    actionStatusTips[actionWindowNext]=tr("Switch to the next tab.");
    actionStatusTips[actionWindowPrev]=tr("Switch to the previous tab.");
    actionStatusTips[actionHelpAbout]=tr("Display the Kreogist Cuties information.");
    actionStatusTips[actionHelpAboutQt]=tr("Display the Qt information, version number and copyright.");
    actionStatusTips[actionHelpBugReport]=tr("Report a bug of Cuties to Kreogist Dev Team.");
    actionStatusTips[actionHelpSendFeedbacks]=tr("Send a feedback to Kreogist Dev Team. Thanks a lot!");

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
    actionMainWindowText[actionViewSidebar]=sideBar->getUnlockState()?
                                            sidebarStateString[sidebarLock]:
                                            sidebarStateString[sidebarUnlock];
    actionMainWindowText[actionViewCompileDock]=tr("Compiler Dock");
    actionMainWindowText[actionViewDebugControls]=tr("Debug Controls");
    actionMainWindowText[actionViewDebugCommandIO]=tr("Debug Command Dock");
    actionMainWindowText[actionViewDebugWatch]=tr("Debug Watch Dock");
    actionMainWindowText[actionViewFullscreen]=isFullScreen()?
                                               fullScreenStateString[normalScreen]:
                                               fullScreenStateString[fullScreen];
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
    actionMainWindowText[actionHelpBugReport]=tr("Report a bug");
    actionMainWindowText[actionHelpSendFeedbacks]=tr("Send a feedback");

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
    if(currEditor->getDebugging())
    {
        //Current File is debugging
        return;
    }
    KCLanguageMode *currLangMode=currEditor->langMode();
    currEditor->setDebugging(true);
    currLangMode->startDebug();

    connectDebugDockWithCurrEditor();
    showDebugDocks();
}

void MainWindow::stopDebug()
{
    KCCodeEditor *currEditor=tabManager->getCurrentEditor();
    if(currEditor==NULL)
    {
        return;
    }
    if(!currEditor->getDebugging())
    {
        return;
    }
    KCLanguageMode *currLangMode=currEditor->langMode();
    if(currLangMode!=NULL)
    {
        currLangMode->stopDebug();
        currEditor->setDebugging(false);
    }
    disconnectDebugDock();
}

void MainWindow::connectDebugDockWithCurrEditor()
{
    KCLanguageMode *currLangMode=tabManager->getCurrentEditor()->langMode();
    GdbController *gdbControllerInstance=currLangMode->getGdbController();

    if(gdbControllerInstance!=NULL)
    {
        debugControl->setGdbController(gdbControllerInstance);
        debugCommandIO->setGdbInstance(gdbControllerInstance);
        debugWatch->setLocalWatchModel(gdbControllerInstance->getDbgOutputs()->getLocalVarModel());
        debugWatch->setCustomWatchModel(gdbControllerInstance->getDbgOutputs()->getWatchModel());
    }
    else
    {
        disconnectDebugDock();
    }
}

void MainWindow::disconnectDebugDock()
{
    debugCommandIO->clearInstance();
    debugControl->clearGdbController();
    debugWatch->clearLocalWatchModel();
    debugWatch->clearCustomWatchModel();
}

void MainWindow::setFullScreen()
{
    if(isFullScreen())
    {
        actionMainWindowItem[actionViewFullscreen]->setText(fullScreenStateString[fullScreen]);
        showNormal();
    }
    else
    {
        actionMainWindowItem[actionViewFullscreen]->setText(fullScreenStateString[normalScreen]);
        showFullScreen();
    }
}
