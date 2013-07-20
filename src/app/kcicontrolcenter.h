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
#include <QRect>
#include <QFrame>
#include <QScrollArea>
#include <QSignalMapper>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QComboBox>

#include "kcisearchlinetext.h"
#include "kcilistbutton.h"

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

class kciControlCenterLeftBar : public QWidget
{
    Q_OBJECT
public:
    explicit kciControlCenterLeftBar(QWidget *parent = 0);

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

class kciControlCenterTabGerneral : public QWidget
{
public:
    explicit kciControlCenterTabGerneral(QWidget *parent = 0);
private:
    QVBoxLayout *FakeLayout, *RealLayout;
    QScrollArea *mainScrollArea;
};

class kciControlCenterContents : public QWidget
{
public:
    explicit kciControlCenterContents(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *e);

private:
    kciControlCenterTabGerneral *tabGerneral;
    int contentIndex;
};

class kciControlCenter : public QWidget
{
    Q_OBJECT
public:
    explicit kciControlCenter(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    QVBoxLayout *WholeTitleBarSplit;
    QHBoxLayout *ContentLayout;
    kciControlCenterContents *CCMainContents;
    kciControlCenterBanner *ccBanner;
    kciControlCenterLeftBar *ccLeftBar;
};

#endif // KCICONTROLCENTER_H
