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

#ifndef KCICONTROLCENTER_H
#define KCICONTROLCENTER_H

#include <QWidget>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPalette>
#include <QFrame>
#include <QLabel>
#include <QIcon>
#include <QSize>
#include <QFont>
#include <QScrollArea>
#include <QScrollBar>
#include <QRect>
#include <QFrame>
#include <QSignalMapper>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QComboBox>
#include <QDebug>
#include <QStringList>

#include <QDialog>

#include "kcisearchlinetext.h"
#include "Controls/SettingItems/kcisettinglistitemcombo.h"
#include "Controls/SettingItems/kcisettinglistitemboolean.h"
#include "Controls/SettingItems/kcisettinglistitemlinetext.h"
#include "Controls/SettingItems/kcisettinglistitembrowsetext.h"
#include "Controls/SettingItems/kcisettinglistitemnuminput.h"
#include "Controls/SettingItems/kcisettinglistitemlanguageitem.h"
#include "Controls/SettingItems/kcisettinglistitembutton.h"
#include "kcilistbutton.h"

#include "kciglobal.h"
#include "kcigeneralconfigure.h"
#include "kcieditorconfigure.h"
#include "kcicompilerconfigure.h"
#include "kcilanguageconfigure.h"
#include "kciclipboard.h"
#include "kcihistoryconfigure.h"

enum kciCCLists
{
    cclstGerneral,
    cclstEditor,
    cclstCompiler,
    cclstDebugger,
    cclstFileAssociation,
    cclstLanguage,
    cclist_count
};

//------------------------------Based Widget-------------------------------
//Our Scroll Area, Can emit resize signal.
class kciScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit kciScrollArea(QWidget *parent = 0);

signals:
    void sizeChanged();

protected:
    void resizeEvent(QResizeEvent *event);
};

//------------------------------Display Widget------------------------------
//Banner Widget.
class kciControlCenterBanner : public QWidget
{
    Q_OBJECT
public:
    explicit kciControlCenterBanner(QWidget *parent = 0);

private:
    QHBoxLayout *TitleLayout;
    QLabel *lblBannerTitle;
    kciSearchLineText *CCSearch;
};

//Left Bar List Widget
class kciControlCenterLeftBar : public QWidget
{
    Q_OBJECT
public:
    explicit kciControlCenterLeftBar(QWidget *parent = 0);
    void connectLeftAndRight(const int &lstButtonID, QWidget *userInterface);

signals:
    void NowSelectChanged(QWidget *newIndex);

private slots:
    void lstClick(int Index);

private:
    kciListButton *lsbLeftButtons[cclist_count];

    QSequentialAnimationGroup *WholeAnimeGroup;
    QSignalMapper *lstMapper;
    int lstSelect;

};

//----------------------------Contents Widget-----------------------

class kciAbstractCCTabContent : public QWidget
{
public:
    explicit kciAbstractCCTabContent(QWidget *parent = 0);
    virtual void apply() {}
};

//-------------Gerneral-----------------
class kciCCTabGerneralContent : public kciAbstractCCTabContent
{
    Q_OBJECT
public:
    explicit kciCCTabGerneralContent(QWidget *parent = 0);
    void apply();

private slots:
    void clearHistoryFilesRecord();

private:
    QVBoxLayout *MainLayout;
    kciSettingListItemCombo *sboDefaultLanguage;
    kciSettingListItemBoolean *sbnAutoOpenUnclosed;
    kciSettingListItemBoolean *sboUseDefaultLanguageOnOpen, *sboUseDefaultLanguageOnSave;
    kciSettingListItemNumInput *slnHistoryMax;
    kciSettingListItemButton *sbtClearHistory;
};
//------------------Editor---------------
class kciCCTabEditorContent : public kciAbstractCCTabContent
{
    Q_OBJECT
public:
    explicit kciCCTabEditorContent(QWidget *parent = 0);
    void apply();

private:
    QVBoxLayout *MainLayout;
    kciSettingListItemBoolean *slnTabMoveable, *slnTabCloseable;
    kciSettingListItemNumInput *tabSpaceNum;
    kciSettingListItemCombo *wrapMode;
    kciSettingListItemNumInput *cursorWidth;
    kciSettingListItemNumInput *clipboardMax;
};
//------------------Compiler--------------
class kciCCTabCompilerContent : public kciAbstractCCTabContent
{
    Q_OBJECT
public:
    explicit kciCCTabCompilerContent(QWidget *parent = 0);
    void apply();

private:
    QVBoxLayout *MainLayout;
    kciSettingListItemBrowseText *txeGppCompilerPath;
    kciSettingListItemBrowseText *txeGccCompilerPath;
    kciSettingListItemBrowseText *txeFpcCompilerPath;
};
//-----------------Debugger-----------------
class kciCCTabDebuggerContent : public kciAbstractCCTabContent
{
    Q_OBJECT
public:
    explicit kciCCTabDebuggerContent(QWidget *parent = 0);

private:
    QVBoxLayout *MainLayout;
    kciSettingListItemBrowseText *txeGDBDebuggerPath;
};
//---------------File Association-------------
class kciCCTabFileAssociationContent : public kciAbstractCCTabContent
{
    Q_OBJECT
public:
    explicit kciCCTabFileAssociationContent(QWidget *parent = 0);

private:
    QVBoxLayout *MainLayout;
};
//--------------Language-------------------
class kciCCTabLanguageContent : public kciAbstractCCTabContent
{
    Q_OBJECT
public:
    explicit kciCCTabLanguageContent(QWidget *parent = 0);

private:
    QVBoxLayout *MainLayout;
    QList<kciSettingListItemLanguageItem*> languageItem;
};

//-------------------Container--------------------
class kciControlCenterTab : public kciAbstractCCTabContent
{
    Q_OBJECT
public:
    explicit kciControlCenterTab(QWidget *contentWidget, QWidget *parent = 0);

private slots:
    void sizeChangeResize();

private:
    QVBoxLayout *FakeLayout;
    kciScrollArea *mainScrollArea;
    QWidget *contentMWidget;
};

/********************************************************/
/*                  Main Control Center                 */
/********************************************************/

class kciControlCenterContents : public QWidget
{
    Q_OBJECT
public:
    explicit kciControlCenterContents(QWidget *parent = 0);
    QWidget *getCCTab(const int& index);
    kciAbstractCCTabContent* getContentWidgets(const int& index);

public slots:
    void animeToIndex(QWidget *Index);

protected:
    void resizeEvent(QResizeEvent *e);

private:
    QParallelAnimationGroup *tabModeAnime;

    kciControlCenterTab *ccTab[cclist_count];
    kciAbstractCCTabContent *contentWidgets[cclist_count];

    QWidget *contentIndex;
};
class kciControlCenter : public QDialog
{
    Q_OBJECT
public:
    explicit kciControlCenter(QWidget *parent = 0);
    
signals:
    
public slots:
    void onApply();
    void onYes();

private slots:

private:
    QVBoxLayout *WholeTitleBarSplit;
    QHBoxLayout *ContentLayout;
    kciControlCenterContents *CCMainContents;
    kciControlCenterBanner *ccBanner;
    kciControlCenterLeftBar *ccLeftBar;
    QToolButton *btYes, *btCancel, *btApply;
};

#endif // KCICONTROLCENTER_H
