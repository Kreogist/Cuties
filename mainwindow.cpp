/*
 *  Copyright 2013 Wang Luming
 *
 *  main.cpp is part of Kreogist-Cute-IDE.
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

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    editor = new QTextEdit(this);
    setCentralWidget(editor);

    createActions();
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

    //quit
    act[quit]=new QAction(tr("quit"),this);

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

void MainWindow::createMenu()
{
    int i;
    QMenuBar *_menubar=menuBar();

    //file menu
    menu[file] = _menubar->addMenu(tr("file"));
    //from new_file to quit add into file menu
    for(i=new_file;i<=quit;i++)
        menu[file]->addAction(act[i]);

    //edit menu
    menu[edit]= _menubar->addMenu(tr("edit"));
    //from redo to paste add into edit menu
    for(i=redo;i<=paste;i++)
        menu[edit]->addAction(act[i]);

    //help menu
    menu[help]= _menubar->addMenu(tr("help"));
    //from about to about_qt add into help menu
    for(i=about;i<=about_qt;i++)
        menu[help]->addAction(act[i]);

}

void MainWindow::createStatusbar()
{
    QStatusBar *statusbar=statusBar();

    //...
}
