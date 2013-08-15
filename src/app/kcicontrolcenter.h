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

#include <QDialog>

#include "kcisearchlinetext.h"
#include "Controls/SettingItems/kcisettinglistitemcombo.h"
#include "Controls/SettingItems/kcisettinglistitemboolean.h"
#include "Controls/SettingItems/kcisettinglistitemlinetext.h"
#include "kcilistbutton.h"

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

signals:
    void NowSelectChanged(int newIndex);

private slots:
    void lstClick(int Index);

private:
    enum kciCCLists
    {
        cclstGerneral,
        cclstEditor,
        cclstCompiler,
        cclstDebugger,
        cclstFileAssociation,
        cclist_count
    };

    QSequentialAnimationGroup *WholeAnimeGroup;
    kciListButton *lsbLeftButtons[cclist_count];
    QSignalMapper *lstMapper;
    int lstSelect;

};

//----------------------------Contents Widget-----------------------

//-------------Gerneral-----------------
class kciCCTabGerneralContent : public QWidget
{
    Q_OBJECT
public:
    explicit kciCCTabGerneralContent(QWidget *parent = 0);

private:
    QVBoxLayout *MainLayout;
    kciSettingListItemCombo *sboDefaultLanguage;
    kciSettingListItemCombo *sboDefaultEncode;
    kciSettingListItemBoolean *slnEnableAnime;
};
//------------------Editor---------------
class kciCCTabEditorContent : public QWidget
{
    Q_OBJECT
public:
    explicit kciCCTabEditorContent(QWidget *parent = 0);

private:
    QVBoxLayout *MainLayout;
    kciSettingListItemBoolean *slnEnableLineNum;
    kciSettingListItemLineText *txeCCompilerPath;
};
//-------------------Container--------------------
class kciControlCenterTab : public QWidget
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

public slots:
    void animeToIndex(int Index);

protected:
    void resizeEvent(QResizeEvent *e);

private:
    QParallelAnimationGroup *tabModeAnime;

    kciControlCenterTab *tabGerneral;
    kciControlCenterTab *tabEditor;

    kciCCTabGerneralContent *contentWidgetGerneral;
    kciCCTabEditorContent   *contentWidgetEditor;

    int contentIndex;
};
class kciControlCenter : public QDialog
{
    Q_OBJECT
public:
    explicit kciControlCenter(QWidget *parent = 0);
    
signals:
    
public slots:

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
