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

#ifndef KCSIDEBAR_H
#define KCSIDEBAR_H

#include <QDockWidget>
#include <QLabel>
#include <QTimeLine>
#include <QIcon>
#include <QToolButton>
#include <QPushButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QMouseEvent>
#include <QSignalMapper>

#include <QStackedWidget>
#include <QListView>

#include "kchistoryconfigure.h"
#include "kcclipboard.h"

class KCIClipboardHistoryStack : public QListView
{
    Q_OBJECT
public:
    explicit KCIClipboardHistoryStack(QWidget *parent = 0);

signals:
    void requiredInsertText(QString insertText);

private slots:
    void dblClickClipboardItems(QModelIndex ItemID);

private:

};

class KCIHistoryStack : public QListView
{
    Q_OBJECT
public:
    explicit KCIHistoryStack(QWidget *parent = 0);

signals:
    void requiredOpenFiles(QString filePath);

private slots:
    void dblClickHistoryItems(QModelIndex ItemID);

private:

};

class KCISidebarButton : public QWidget
{
    Q_OBJECT
public:
    explicit KCISidebarButton(QWidget *parent = 0);
    void setIcon(QString IconPath);
    void setPressed(bool newValue, bool force);
    void setBackgroundColor();

signals:
    void mouseEnter();
    void mouseExit();
    void mousePressed();

protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);

private:
    QPalette pal;
    QColor buttonBackcolor;
    QVBoxLayout *mainLayout;
    QLabel *iconDisplayer;

    bool buttonPressed;
    bool buttonLocked;
};

class KCISideBarContent : public QWidget
{
    Q_OBJECT
public:
    explicit KCISideBarContent(QWidget *parent = 0);
    ~KCISideBarContent();
    void setContentFixedWidth(int newContentWidth);
    void forceClearButtonState();
    void forceShowButtonState();

signals:
    void historyRequiredOpenFiles(QString filePath);
    void clipRequiredInsertText(QString insertText);
    void expandRequest();
    void foldRequest();

public slots:
    void showContent();
    void hideContent();
    void listButtonClicked(int Index);

private:
    QHBoxLayout *mainLayout;
    QVBoxLayout *buttonGroupLayout;
    enum sidebarButtons
    {
        sideButtonHistory,
        sideButtonClipboard,
        sidebarButtonCount
    };

    KCISidebarButton *sidebarButton[sidebarButtonCount];
    QSignalMapper *sidebarButtonMapper;

    QStackedWidget *contents;
    KCIHistoryStack *historyStack;
    KCIClipboardHistoryStack *clipboardStack;

    int sidebarButtonIndex;
    QToolButton *sidebarLock;
};

class KCISideBar : public QDockWidget
{
    Q_OBJECT
public:
    explicit KCISideBar(QWidget *parent = 0);
    void forceClearButtonState();
    void forceShowButtonState();

    bool getExpandState() const;
    void setExpandState(bool value);

signals:
    void historyRequiredOpenFiles(QString filePath);
    void clipboardRequiredInsertText(QString insertText);

public slots:
    void showAnime();
    void hideAnime();


private slots:
    void resizeDock(int newWidth);

private:
    bool expandState;
    QTimeLine *showAnimation, *hideAnimation;
    KCISideBarContent *CentralWidget;
};

#endif // KCSIDEBAR_H
