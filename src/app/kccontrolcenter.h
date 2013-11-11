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

#ifndef KCCONTROLCENTER_H
#define KCCONTROLCENTER_H

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

class KCSearchLineText;
class KCListButton;
class KCSettingListItemCombo;
class KCSettingListItemBoolean;
class KCSettingListItemNumInput;
class KCSettingListItemButton;
class KCSettingListItemBrowseText;
class KCSettingListItemLanguageItem;

#include "kcglobal.h"

enum KCCCLists
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
class KCScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit KCScrollArea(QWidget *parent = 0);

signals:
    void sizeChanged();

protected:
    void resizeEvent(QResizeEvent *event);
};

//------------------------------Display Widget------------------------------
//Banner Widget.
class KCControlCenterBanner : public QWidget
{
    Q_OBJECT
public:
    explicit KCControlCenterBanner(QWidget *parent = 0);

private:
    QHBoxLayout *TitleLayout;
    QLabel *lblBannerTitle;
    KCSearchLineText *CCSearch;
};

//Left Bar List Widget
class KCControlCenterLeftBar : public QWidget
{
    Q_OBJECT
public:
    explicit KCControlCenterLeftBar(QWidget *parent = 0);
    void connectLeftAndRight(const int &lstButtonID, QWidget *userInterface);

signals:
    void NowSelectChanged(QWidget *newIndex);

private slots:
    void lstClick(int Index);

private:
    KCListButton *lsbLeftButtons[cclist_count];

    QSequentialAnimationGroup *WholeAnimeGroup;
    QSignalMapper *lstMapper;
    int lstSelect;

};

//----------------------------Contents Widget-----------------------

class KCAbstractCCTabContent : public QWidget
{
public:
    explicit KCAbstractCCTabContent(QWidget *parent = 0);
    virtual void apply() {}
};

//-------------Gerneral-----------------
class KCCCTabGerneralContent : public KCAbstractCCTabContent
{
    Q_OBJECT
public:
    explicit KCCCTabGerneralContent(QWidget *parent = 0);
    void apply();

private slots:
    void clearHistoryFilesRecord();

private:
    QVBoxLayout *MainLayout;
    KCSettingListItemCombo *sboDefaultLanguage;
    KCSettingListItemBoolean *sbnAutoOpenUnclosed;
    KCSettingListItemBoolean *sboUseDefaultLanguageOnOpen, *sboUseDefaultLanguageOnSave;
    KCSettingListItemNumInput *slnHistoryMax;
    KCSettingListItemButton *sbtClearHistory;
    KCSettingListItemCombo *sboSearchEngine;
};
//------------------Editor---------------
class KCCCTabEditorContent : public KCAbstractCCTabContent
{
    Q_OBJECT
public:
    explicit KCCCTabEditorContent(QWidget *parent = 0);
    void apply();

private:
    QVBoxLayout *MainLayout;
    KCSettingListItemBoolean *slnTabMoveable, *slnTabCloseable;
    KCSettingListItemBoolean *tabSpaceEnabled;
    KCSettingListItemBoolean *lineNumberVisible;
    KCSettingListItemNumInput *tabSpaceNum;
    KCSettingListItemCombo *wrapMode;
    KCSettingListItemNumInput *cursorWidth;
    KCSettingListItemNumInput *clipboardMax;
};
//------------------Compiler--------------
class KCCCTabCompilerContent : public KCAbstractCCTabContent
{
    Q_OBJECT
public:
    explicit KCCCTabCompilerContent(QWidget *parent = 0);
    void apply();

private:
    QVBoxLayout *MainLayout;
    KCSettingListItemBrowseText *txeGppCompilerPath;
    KCSettingListItemBrowseText *txeGccCompilerPath;
    KCSettingListItemBrowseText *txeFpcCompilerPath;
};
//-----------------Debugger-----------------
class KCCCTabDebuggerContent : public KCAbstractCCTabContent
{
    Q_OBJECT
public:
    explicit KCCCTabDebuggerContent(QWidget *parent = 0);

private:
    QVBoxLayout *MainLayout;
    KCSettingListItemBrowseText *txeGDBDebuggerPath;
};
//---------------File Association-------------
class KCCCTabFileAssociationContent : public KCAbstractCCTabContent
{
    Q_OBJECT
public:
    explicit KCCCTabFileAssociationContent(QWidget *parent = 0);

private:
    QVBoxLayout *MainLayout;
};
//--------------Language-------------------
class KCCCTabLanguageContent : public KCAbstractCCTabContent
{
    Q_OBJECT
public:
    explicit KCCCTabLanguageContent(QWidget *parent = 0);

private slots:
    void applyLanguageSettings(int newLangaugeIndex);

private:
    QSignalMapper *languageSet;
    QVBoxLayout *mainLayout;
    QList<KCSettingListItemLanguageItem *> languageItem;
};

//-------------------Container--------------------
class KCControlCenterTab : public KCAbstractCCTabContent
{
    Q_OBJECT
public:
    explicit KCControlCenterTab(QWidget *contentWidget, QWidget *parent = 0);

private slots:
    void sizeChangeResize();

private:
    QVBoxLayout *FakeLayout;
    KCScrollArea *mainScrollArea;
    QWidget *contentMWidget;
};

/********************************************************/
/*                  Main Control Center                 */
/********************************************************/

class KCControlCenterContents : public QWidget
{
    Q_OBJECT
public:
    explicit KCControlCenterContents(QWidget *parent = 0);
    QWidget *getCCTab(const int &index);
    KCAbstractCCTabContent *getContentWidgets(const int &index);

public slots:
    void animeToIndex(QWidget *Index);

protected:
    void resizeEvent(QResizeEvent *e);

private:
    QParallelAnimationGroup *tabModeAnime;

    KCControlCenterTab *ccTab[cclist_count];
    KCAbstractCCTabContent *contentWidgets[cclist_count];

    QWidget *contentIndex;
};

class KCControlCenter : public QDialog
{
    Q_OBJECT
public:
    explicit KCControlCenter(QWidget *parent = 0);

signals:

public slots:
    void onApply();
    void onYes();

private slots:

private:
    QVBoxLayout *WholeTitleBarSplit;
    QHBoxLayout *ContentLayout;
    KCControlCenterContents *CCMainContents;
    KCControlCenterBanner *ccBanner;
    KCControlCenterLeftBar *ccLeftBar;
    QToolButton *btYes, *btCancel, *btApply;
};

#endif // KCCONTROLCENTER_H
