/*
 *  Copyright 2013 Wang Luming <wlm199558@126.com>
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    enum MainWindowActions
    {
        new_file,
        open,
        save,
        save_as,
        save_all,
        close,
        close_all,
        quit,
        redo,
        undo,
        cut,
        copy,
        paste,
        about,
        about_qt,
        act_count   //the number of actions.
    };

    enum MainWindowMenu
    {
        file,
        edit,
        help,
        menu_count  //the number of menus
    };

    QTextEdit *editor;
    QAction *act[act_count];
    QMenu *menu[menu_count];

    void createActions();
    void createMenu();
    void createStatusbar();
};

#endif // MAINWINDOW_H
