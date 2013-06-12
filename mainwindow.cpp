/*
 *  Copyright 2013 Wang Luming
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
    editor = new kciTextEditor(this);
    setCentralWidget(editor);

    setWindowFlags(Qt::FramelessWindowHint);

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

    //save
    act[save]=new QAction(tr("save"),this);

    //save_as
    act[save_as]=new QAction(tr("save as"),this);

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

    //about
    act[about]=new QAction(tr("about"),this);

    //about_qt
    act[about_qt]=new QAction(tr("about Qt"),this);
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
    QIcon *MenuIconAddor=new QIcon;
    QSize *MenuIconSizeor=new QSize;

    //file menu
    MenuIconSizeor->setHeight(100);
    MenuIconSizeor->setWidth(100);
    MenuIconAddor->addFile(QString(":/img/image/FileMenuIcon.png"),*MenuIconSizeor);
    menu[file] = _mainMenu->addMenu(tr("file"));
    menu[file]->setIcon(*MenuIconAddor);
    //from new_file to quit add into file menu
    for(i=new_file;i<=quit;i++)
        menu[file]->addAction(act[i]);

    //edit menu
    menu[edit] = _mainMenu->addMenu(tr("edit"));
    //from redo to paste add into edit menu
    for(i=redo;i<=paste;i++)
        menu[edit]->addAction(act[i]);

    //view menu
    menu[view] = _mainMenu->addMenu(tr("view"));

    //search menu
    menu[search] = _mainMenu->addMenu(tr("search"));

    //insert menu
    menu[insert] = _mainMenu->addMenu(tr("insert"));

    //debug menu
    menu[debug] = _mainMenu->addMenu(tr("debug"));

    //run menu
    menu[run] = _mainMenu->addMenu(tr("run"));

    //plugins menu
    menu[plugins] = _mainMenu->addMenu(tr("plugins"));

    //help menu
    menu[help] = _mainMenu->addMenu(tr("help"));
    //from about to about_qt add into help menu
    for(i=about;i<=about_qt;i++)
        menu[help]->addAction(act[i]);

    titlebar->setMenu(_mainMenu);
}

void MainWindow::createStatusbar()
{
    QStatusBar *statusbar=statusBar();

    QPalette pal=statusbar->palette();
    pal.setColor(QPalette::Window,QColor(0x89,0x89,0x89));
    statusbar->setPalette(pal);
}
