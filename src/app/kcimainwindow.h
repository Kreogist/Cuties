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


#ifndef KCIMAINWINDOW_H
#define KCIMAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QMouseEvent>
#include <QCursor>
#include <QPoint>
#include <QDebug>
#include <QGraphicsDropShadowEffect>

#include "kcititlebar.h"
#include "kreogistcutestyle.h"
#include "kcidragproxy.h"

class kciMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit kciMainWindow(QWidget *parent = 0);
    
    kciTitleBar *titleBar() const;
    void setTitleBar(kciTitleBar *titleBar);
#ifndef Q_OS_MACX
    void setMenu(QMenu *menu);
    void setMainButtonIcon(const QString& mainIcon);
#endif

signals:
    
public slots:

private:

    kciTitleBar *m_titleBar;
    QPoint startPos;
};

#endif // KCIMAINWINDOW_H
