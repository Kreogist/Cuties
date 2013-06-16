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

    editor = new kciTextEditor(this);
    setCentralWidget(editor);
    setContentsMargins(0,0,0,0);

    QPalette QPpal = palette();
    QPpal.setBrush(QPalette::Window, QBrush(QColor(83,83,83)));
    setPalette(QPpal);

    setWindowFlags(Qt::FramelessWindowHint);

    restoreSettings();

    createActions();
    createTitlebar();
    createMenu();
    createStatusbar();
}

void MainWindow::createActions()
{
    //new file
    act[new_file]=new QAction(tr("new file"),this);

    //open
    act[open]=new QAction(tr("open"),this);
    connect(act[open],SIGNAL(triggered()),editor,SLOT(open()));

    //save
    act[save]=new QAction(tr("save"),this);
    connect(act[save],SIGNAL(triggered()),editor,SLOT(save()));

    //save_as
    act[save_as]=new QAction(tr("save as"),this);
    connect(act[save_as],SIGNAL(triggered()),editor,SLOT(saveAs()));

    //save_all
    act[save_all]=new QAction(tr("save all"),this);

    //close
    act[close]=new QAction(tr("close"),this);

    //closs_all
    act[close_all]=new QAction(tr("close all"),this);

    //close_allother
    act[close_allother]=new QAction(tr("close all other file"),this);

    //quit
    act[quit]=new QAction(tr("quit"),this);
    connect(act[quit],SIGNAL(triggered()),this,SLOT(close()));

    //redo
    act[redo]=new QAction(tr("redo"),this);

    //undo
    act[undo]=new QAction(tr("undo"),this);

    //cut
    act[cut]=new QAction(tr("cut"),this);

    //copy
    act[copy]=new QAction(tr("copy"),this);

    //paste
    act[paste]=new QAction(tr("paste"),this);

    //select all
    act[select_all]=new QAction(tr("select all"),this);

    //set_break_point
    act[set_break_point]=new QAction(tr("set break point"),this);

    //preference
    act[preference]=new QAction(tr("preference"),this);

    //search in file
    act[searchinfile]=new QAction(tr("searchinfile"),this);

    //search all file
    act[searchallfile]=new QAction(tr("searchallfile"),this);

    //replace in file
    act[replaceinfile]=new QAction(tr("replaceinfile"),this);

    //replace all file
    act[replaceallfile]=new QAction(tr("replaceallfile"),this);

    //search online
    act[searchonline]=new QAction(tr("searchonline"),this);

    //go to line
    act[gotoline]=new QAction(tr("gotoline"),this);

    //compile and run
    act[compileandrun]=new QAction(tr("Compile & Run"),this);

    //compile
    act[compile]=new QAction(tr("compile"),this);

    //compile all file
    act[compileallfile]=new QAction(tr("Complie all file"),this);

    //run
    act[runexe]=new QAction(tr("Runexe"),this);

    //Parameters
    act[parameters]=new QAction(tr("Parameters"),this);

    //Set Input file
    act[setinputfile]=new QAction(tr("Set Input File"),this);

    //Show Output file
    act[showoutputfile]=new QAction(tr("Show Output file"),this);

    //Run And show
    act[runshowoutputfile]=new QAction(tr("Run And Show Output File"),this);

    //Set Input, Run and Show Output
    act[setinputrunshowoutput]=new QAction(
                tr("Set Input, Run and show Output"), this);

    //debug start
    act[debugstart]=new QAction(tr("Start Debug"),this);

    //debug pause
    act[debugcontinue]=new QAction(tr("Pause Debug"),this);

    //Stop Execute
    act[stopexecute]=new QAction(tr("Stop execute"),this);

    //next line
    act[nextline]=new QAction(tr("Next Line"),this);

    //Go Into line
    act[intoline]=new QAction(tr("Into Line"),this);

    //Go Next Instruction
    act[nextinstruction]=new QAction(tr("Next Instruction"),this);

    //Go Into Instruction
    act[mnuDebugIntoInstruction]=new QAction(tr("Into Instruction"),this);

    //Skip Function
    act[skipfunction]=new QAction(tr("skip function"),this);

    //Add Watch
    act[addwatch]=new QAction(tr("Add Watch"),this);

    //Modify Watch
    act[modifywatch]=new QAction(tr("Modify Watch"),this);

    //Remove Watch
    act[removewatch]=new QAction(tr("Remove Watch"),this);

    //about
    act[about]=new QAction(tr("about"),this);
    connect(act[about],SIGNAL(triggered()),this,SLOT(aboutKCI()));

    //about_qt
    act[about_qt]=new QAction(tr("about Qt"),this);
    connect(act[about_qt],SIGNAL(triggered()),this,SLOT(aboutQt()));
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

void MainWindow::createMenu()
{
    int i;

    QMenu *_mainMenu=new QMenu;
    _mainMenu->setWindowOpacity(50);
    QIcon *MenuIconAddor=new QIcon;
    QSize *MenuIconSize=new QSize;
    MenuIconSize->setHeight(50);
    MenuIconSize->setWidth(50);
    //file menu
    MenuIconAddor->addFile(QString(":/img/image/FileMenuIcon.png"),*MenuIconSize);
    menu[file] = _mainMenu->addMenu(tr("file"));
    //menu[file]->setStyle(cuteStyle);
    menu[file]->setIcon(*MenuIconAddor);
    //from new_file to quit add into file menu
    for(i=new_file;i<=quit;i++)
    {
        menu[file]->addAction(act[i]);
        act[i]->setIcon(*MenuIconAddor);
    }

    //edit menu
    menu[edit] = _mainMenu->addMenu(tr("edit"));
    //from redo to paste add into edit menu
    for(i=redo;i<=preference;i++)
    {
        menu[edit]->addAction(act[i]);
    }

    //view menu
    menu[view] = _mainMenu->addMenu(tr("view"));

    //search menu
    menu[search] = _mainMenu->addMenu(tr("search"));
    for(i=searchinfile;i<=gotoline;i++)
    {
        menu[search]->addAction(act[i]);
    }

    //insert menu
    menu[insert] = _mainMenu->addMenu(tr("insert"));

    //run menu
    menu[run] = _mainMenu->addMenu(tr("run"));
    for(i=compileandrun;i<=setinputrunshowoutput;i++)
    {
        menu[run]->addAction(act[i]);
    }

    //debug menu
    menu[debug] = _mainMenu->addMenu(tr("debug"));
    for(i=debugstart;i<=removewatch;i++)
    {
        menu[debug]->addAction(act[i]);
    }

    //plugins menu
    menu[plugins] = _mainMenu->addMenu(tr("plugins"));

    //help menu
    menu[help] = _mainMenu->addMenu(tr("help"));
    //from about to about_qt add into help menu
    for(i=about;i<=about_qt;i++)
    {
        menu[help]->addAction(act[i]);
    }

    titlebar->setMenu(_mainMenu);
}

void MainWindow::createStatusbar()
{
    QStatusBar *statusbar=statusBar();

    QPalette pal=statusbar->palette();
    pal.setColor(QPalette::Window,QColor(0x89,0x89,0x89));
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
    if(editor->close())
    {
        saveSettings();
        e->accept();
    }
    else
    {
        e->ignore();
    }
}
