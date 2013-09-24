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

#ifndef KCISIDEBAR_H
#define KCISIDEBAR_H

#include <QDockWidget>
#include <QLabel>
#include <QTimeLine>
#include <QIcon>
#include <QToolButton>
#include <QPushButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QStackedWidget>
#include <QListView>

#include "kcihistoryconfigure.h"
#include "kciclipboard.h"

class kciClipboardHistoryStack : public QListView
{
    Q_OBJECT
public:
    explicit kciClipboardHistoryStack(QWidget *parent = 0);

signals:
    void requiredInsertText(QString insertText);

private slots:
    void dblClickClipboardItems(QModelIndex ItemID);

private:

};

class kciHistoryStack : public QListView
{
    Q_OBJECT
public:
    explicit kciHistoryStack(QWidget *parent = 0);

signals:
    void requiredOpenFiles(QString filePath);

private slots:
    void dblClickHistoryItems(QModelIndex ItemID);

private:

};

class kciSideBarContent : public QWidget
{
    Q_OBJECT
public:
    explicit kciSideBarContent(QWidget *parent = 0);
    ~kciSideBarContent();

signals:
    void historyRequiredOpenFiles(QString filePath);
    void clipRequiredInsertText(QString insertText);
    void expandRequest();

public slots:
    void showContent();
    void hideContent();

private:
    QHBoxLayout *mainLayout;
    QVBoxLayout *buttonGroupLayout;
    QToolButton *buttonRecent, *buttonClipboard;

    QStackedWidget *contents;
    kciHistoryStack *historyStack;
    kciClipboardHistoryStack *clipboardStack;
};

class kciSideBar : public QDockWidget
{
    Q_OBJECT
public:
    explicit kciSideBar(QWidget *parent = 0);
    
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
    kciSideBarContent *CentralWidget;
};

#endif // KCISIDEBAR_H
