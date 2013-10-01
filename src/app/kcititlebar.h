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


#ifndef KCITITLEBAR_H
#define KCITITLEBAR_H

#include <QPoint>
#include <QMouseEvent>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPropertyAnimation>
#include <QRect>
#include <QIcon>
#include <QString>
#include <QToolBar>
#include <QWidget>
#include <QPalette>
#include <QDebug>

#ifndef Q_OS_MACX
class kciTitleBarAutoFill : public QWidget
{
    Q_OBJECT
public:
    explicit kciTitleBarAutoFill(QWidget *parent = 0);

signals:
    void dblClickEmit();

protected:
    void mouseDoubleClickEvent(QMouseEvent *e);

private:
};
#endif

class kciTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit kciTitleBar(QWidget *parent = 0);
    void addToolButton(QToolButton *tblMainButton);
    void addToolSeparator();
    void setWindowMax();
    void setWindowNormal();
    void setWindowMin();
#ifndef Q_OS_MACX
    void setMenu(QMenu *menu);
    void setMainButtonIcon(const QString &mainIcon);
#endif

signals:

public slots:
    void showToolBar();
    void hideToolBar();

private slots:
    void _exchange_button_state();
#ifndef Q_OS_MACX
    void spacingDblClick();
#endif

protected:
#ifndef Q_OS_MACX
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
#endif

private:
    bool hasPressed;
    bool isShowingNormalButton;   //false when show minimizeButton, true when show normalButton
    bool toolbarShown;
    QPoint mousePosStart;
    QWidget *mainWindow;

    QToolButton *maximizeButton,*minimizeButton;
    QToolButton *closeButton;

    QVBoxLayout *vMinLayout, *vMaxLayout, *vCloseLayout;
    QHBoxLayout *hLayout;
    QString windowTitle;

#ifndef Q_OS_MACX
    kciTitleBarAutoFill *autoFill;
    QToolButton *mainButton;
#endif

    QIcon mainButtonIcon,normalButtonIcon,maximizeButtonIcon,minimizeButtonIcon,closeButtonIcon;
    QToolBar *mainToolBar;
    QPropertyAnimation *tlbHideAnime, *tlbShowAnime;

    QSpacerItem *NoUseSpacing;
};

#endif // KCITITLEBAR_H
