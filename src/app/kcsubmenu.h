/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Project Nerve.
 *
 *    Kreogist Nerve is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by the
 *  Free Software Foundation, either version 3 of the License, or (at your
 *  option) any later version.
 *
 *    Kreogist Nerve is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along with
 *  Kreogist Nerve. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KCSUBMAINMENU_H
#define KCSUBMAINMENU_H

#include <QPropertyAnimation>
#include <QShowEvent>
#include <QMenu>

class KCSubMenu : public QMenu
{
    Q_OBJECT
public:
    explicit KCSubMenu(QWidget *parent = 0);

signals:

public slots:

protected:
    void showEvent(QShowEvent *e);

private:
    QPropertyAnimation *showAnimation;
};

#endif // KCSUBMAINMENU_H
