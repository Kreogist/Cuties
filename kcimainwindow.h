/*
 *  Copyright 2013 Wang Luming <wlm199558@126.com>
 *
 *  kcimainwindow.cpp is part of Kreogist-Cute-IDE.
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

class kciMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit kciMainWindow(QWidget *parent = 0);
    
    kciTitleBar *titleBar() const;
    void setTitleBar(kciTitleBar *titleBar);
    void setMenu(QMenu *menu);
    void setMainButtonIcon(const QString& mainIcon);
    void setWindowTitle(const QString &title);

signals:
    
public slots:

protected:
    bool eventFilter(QObject *obj, QEvent *e);

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
