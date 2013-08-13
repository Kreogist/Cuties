/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *      Wang Luming <wlm199558@126.com>
 *      Miyanaga Saki <tomguts@126.com>
 *      Zhang Jiayi <bf109g2@126.com>
 *
 *  This file is part of Kreogist-Cute-IDE.
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

#ifndef KCIMAINWINDOW_H
#define KCIMAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QMouseEvent>
#include <QCursor>
#include <QPoint>
#include <QDebug>

#include "kcititlebar.h"
#include "kreogistcutestyle.h"

class kciMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit kciMainWindow(QWidget *parent = 0);
    
    kciTitleBar *titleBar() const;
    void setTitleBar(kciTitleBar *titleBar);
    void setWindowTitle(const QString &title);
#ifndef Q_OS_MACX
    void setMenu(QMenu *menu);
    void setMainButtonIcon(const QString& mainIcon);
#endif

signals:
    
public slots:

protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    //bool eventFilter(QObject *obj, QEvent *e);

private:
    enum pressType
    {
        none,
        left_frame,
        right_frame,
        bottom_frame
    };

    kciTitleBar *m_titleBar;
    static int range;
    int pressed;
    QPoint startPos;
};

#endif // KCIMAINWINDOW_H
