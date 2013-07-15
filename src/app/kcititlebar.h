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

#ifndef KCITITLEBAR_H
#define KCITITLEBAR_H

#include <QPoint>
#include <QMouseEvent>
#include <QToolButton>
#include <QStyle>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QString>
#include <QToolBar>
#include <QWidget>
#include <QPalette>

class kciTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit kciTitleBar(QWidget *parent = 0);
    void addToolButton(QToolButton *tblMainButton);
    void setMenu(QMenu *menu);
    void setMainButtonIcon(const QString& mainIcon);
    void setTitle(const QString &title);
    void setWindowMax();
    void setWindowNormal();
    void setWindowMin();

signals:
    
public slots:

private slots:
    void _exchange_button_state();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    bool hasPressed;
    bool isShowingNormalButton;   //false when show minimizeButton, true when show normalButton
    QPoint mousePosStart;
    QWidget *mainWindow;

    QToolButton *maximizeButton,*minimizeButton;
    QToolButton *closeButton;

    QVBoxLayout *vMinLayout, *vMaxLayout, *vCloseLayout;
    QHBoxLayout *hLayout;
    QLabel *titleLabel;
    QString windowTitle;

    QToolButton *mainButton;
    QIcon mainButtonIcon,normalButtonIcon,maximizeButtonIcon,minimizeButtonIcon,closeButtonIcon;
    QToolBar *mainToolBar;
};

#endif // KCITITLEBAR_H
