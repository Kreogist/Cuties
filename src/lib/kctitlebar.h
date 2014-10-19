/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist Cuties.
 *
 *    Kreogist Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef KCTITLEBAR_H
#define KCTITLEBAR_H

#include <QPoint>
#include <QMouseEvent>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPropertyAnimation>
#include <QRect>
#include <QFont>
#include <QIcon>
#include <QString>
#include <QToolBar>
#include <QWidget>
#include <QPalette>
#include <QPushButton>
#include <QDebug>

#include "kclib_global.h"
#include "kccolorconfigure.h"

class KCLIB_EXPORT KCTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit KCTitleBar(QWidget *parent = 0);
    void addToolButton(QToolButton *tblMainButton);
    void addToolSeparator();
#ifndef Q_OS_MACX
    void setMenu(QMenu *menu);
    void setMainButtonIcon(const QString &mainIcon);
#endif

signals:

public slots:
    void showToolBar();
    void hideToolBar();

private:
    bool hasPressed;
    bool toolbarShown;
    QPoint mousePosStart;
    QWidget *mainWindow;

    QVBoxLayout *vMinLayout, *vMaxLayout, *vCloseLayout;
    QHBoxLayout *hLayout;
    QString windowTitle;

#ifndef Q_OS_MACX
    QToolButton *mainButton;
#endif

    QIcon mainButtonIcon,normalButtonIcon,maximizeButtonIcon,minimizeButtonIcon,closeButtonIcon;
    QToolBar *mainToolBar;
    QPropertyAnimation *tlbHideAnime, *tlbShowAnime;
};

#endif // KCTITLEBAR_H
