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

#include "kcicontrolcenter.h"

kciControlCenterBanner::kciControlCenterBanner(QWidget *parent):
    QWidget(parent)
{
    setFixedHeight(44);
    setContentsMargins(0,0,0,0);
    setAutoFillBackground(true);

    //Set Palette
    QPalette pal=this->palette();
    pal.setColor(QPalette::Window, QColor(83,83,83));
    setPalette(pal);

    //Set Title Layout
    TitleLayout=new QHBoxLayout(this);
    TitleLayout->setContentsMargins(0,0,0,0);
    setLayout(TitleLayout);
    //Add some spacing
    TitleLayout->addSpacing(15);
    //Set Title Text
    lblBannerTitle=new QLabel(this);
    lblBannerTitle->setText(tr("Cuties Control Center"));
    QFont TitleFont=lblBannerTitle->font();
    TitleFont.setPointSize(11);
    TitleFont.setBold(true);
    lblBannerTitle->setFont(TitleFont);
    pal=lblBannerTitle->palette();
    pal.setColor(QPalette::WindowText, QColor(255,255,255));
    lblBannerTitle->setPalette(pal);
    TitleLayout->addWidget(lblBannerTitle);
    //Set Stretch
    TitleLayout->addStretch(0);
    //Set Search Bar
    CCSearch=new kciSearchLineText();
    CCSearch->setFixedWidth(250);
    TitleLayout->addWidget(CCSearch);
    TitleLayout->addSpacing(7);
}

kciControlCenterLeftBar::kciControlCenterLeftBar(QWidget *parent) :
    QWidget(parent)
{
    //Set Content Margin.
    setContentsMargins(0,0,0,0);
    setFixedWidth(215);
    //Set Label Strings.
    QString strLabelTexts[cclist_count], strLabelIcons[cclist_count];
    strLabelTexts[cclstGerneral]=tr("Gerneral");
    strLabelTexts[cclstEditor]=tr("Editor");
    strLabelTexts[cclstCompiler]=tr("Compiler");
    strLabelTexts[cclstDebugger]=tr("Debugger");
    strLabelTexts[cclstFileAssociation]=tr("File Association");

    strLabelIcons[cclstGerneral]=":/controlcenter/image/Control Center/cciGeneral.png";
    strLabelIcons[cclstEditor]=":/controlcenter/image/Control Center/cciEditor.png";
    strLabelIcons[cclstCompiler]=":/controlcenter/image/Control Center/cciCompiler.png";
    strLabelIcons[cclstDebugger]=":/controlcenter/image/Control Center/cciDebugger.png";
    strLabelIcons[cclstFileAssociation]=":/controlcenter/image/Control Center/cciFileAssociation.png";

    //Set Now Index.
    lstSelect=cclstGerneral;

    lstMapper=new QSignalMapper(this);
    for(int i=cclstGerneral;i<cclist_count;i++)
    {
        lsbLeftButtons[i]=new kciListButton(this);
        lsbLeftButtons[i]->setLabelText(strLabelTexts[i]);
        lsbLeftButtons[i]->setLabelIcon(strLabelIcons[i]);
        lsbLeftButtons[i]->setGeometry(0,
                                       i*40,
                                       215,
                                       40);
        connect(lsbLeftButtons[i],SIGNAL(click()),lstMapper,SLOT(map()));
        lstMapper->setMapping(lsbLeftButtons[i],i);

    }
    connect(lstMapper,SIGNAL(mapped(int)),this,SLOT(lstClick(int)));

    //Set First To Be Pushed.
    lsbLeftButtons[lstSelect]->setPushed(true);

    //Set Min Height
    setMinimumHeight((cclist_count)*40);

    //Set Anime.
    WholeAnimeGroup=new QSequentialAnimationGroup(this);
}

void kciControlCenterLeftBar::lstClick(int Index)
{
    if(Index == lstSelect)
    {
        return;
    }

    if(WholeAnimeGroup->state()!=QAbstractAnimation::Running)
    {
        //Clear Anime.
        WholeAnimeGroup->clear();
        QParallelAnimationGroup *MainAnimeGroup=new QParallelAnimationGroup(this);
        //Move Anime
        QPropertyAnimation *moveListButton=new QPropertyAnimation(lsbLeftButtons[Index],"geometry");
        QRect animeStartPos=lsbLeftButtons[Index]->geometry();
        QRect animeEndPos=lsbLeftButtons[lstSelect]->geometry();
        moveListButton->setStartValue(animeStartPos);
        moveListButton->setEndValue(animeEndPos);
        moveListButton->setEasingCurve(QEasingCurve::OutCubic);
        MainAnimeGroup->addAnimation(moveListButton);
        //Hide Anime
        QPropertyAnimation *hideListButton=new QPropertyAnimation(lsbLeftButtons[lstSelect],"geometry");
        animeStartPos=lsbLeftButtons[lstSelect]->geometry();
        animeEndPos=animeStartPos;
        animeEndPos.setX(-animeEndPos.width());
        hideListButton->setStartValue(animeStartPos);
        hideListButton->setEndValue(animeEndPos);
        hideListButton->setEasingCurve(QEasingCurve::OutCubic);
        MainAnimeGroup->addAnimation(hideListButton);
        //Add to Whole Anime.
        WholeAnimeGroup->addAnimation(MainAnimeGroup);

        //Show Anime
        QPropertyAnimation *showListButton=new QPropertyAnimation(lsbLeftButtons[lstSelect],"geometry");
        animeEndPos=lsbLeftButtons[Index]->geometry();
        animeStartPos=animeEndPos;
        animeStartPos.setX(-animeStartPos.width());
        showListButton->setStartValue(animeStartPos);
        showListButton->setEndValue(animeEndPos);
        showListButton->setEasingCurve(QEasingCurve::OutQuad);
        WholeAnimeGroup->addAnimation(showListButton);
        WholeAnimeGroup->start();

        //Set Pushed.
        lsbLeftButtons[lstSelect]->setPushed(false);
        lsbLeftButtons[Index]->setPushed(true);
        //Set Index.
        lstSelect=Index;
    }
}

kciCCTabGerneralContent::kciCCTabGerneralContent(QWidget *parent) :
    QWidget(parent)
{
    MainLayout=new QVBoxLayout(this);
    setLayout(MainLayout);

    /*sboDefaultLanguage=new kciSettingListItemCombo(this);
    sboDefaultLanguage->Caption->setText("test!!");
    sboDefaultLanguage->addListItem("C/C++");
    sboDefaultLanguage->addListItem("Pascal");
    MainLayout->addWidget(sboDefaultLanguage);*/
}

kciControlCenterTabGerneral::kciControlCenterTabGerneral(QWidget *parent) :
    QWidget(parent)
{
    //Set FakeLayout.
    FakeLayout=new QVBoxLayout(this);
    FakeLayout->setContentsMargins(0,0,0,0);
    FakeLayout->setSpacing(0);
    setLayout(FakeLayout);

    //Set Main Widget.
    mainScrollArea=new QScrollArea(this);
    mainScrollArea->setAutoFillBackground(true);
    mainScrollArea->setFrameShape(QFrame::NoFrame);
    QPalette pal=mainScrollArea->palette();
    pal.setColor(QPalette::Window, QColor(255,255,255));
    mainScrollArea->setPalette(pal);
    FakeLayout->addWidget(mainScrollArea);

    //Set Contents.
    contentWidget=new kciCCTabGerneralContent(this);
    mainScrollArea->setContentsMargins(0,0,0,0);
    mainScrollArea->setWidget(contentWidget);
}

kciControlCenterContents::kciControlCenterContents(QWidget *parent) :
    QWidget(parent)
{
    contentIndex=0;
    tabGerneral=new kciControlCenterTabGerneral(this);
}

void kciControlCenterContents::resizeEvent(QResizeEvent *e)
{
    switch(contentIndex)
    {
    case 0:
        tabGerneral->setGeometry(0,0,this->width(),this->height());
    }

    QWidget::resizeEvent(e);
}

kciControlCenter::kciControlCenter(QWidget *parent) :
    QWidget(parent)
{
    //Set Whole Layout
    WholeTitleBarSplit=new QVBoxLayout(this);
    WholeTitleBarSplit->setContentsMargins(0,0,0,0);
    WholeTitleBarSplit->setSpacing(0);
    setLayout(WholeTitleBarSplit);

    //Set Banner
    ccBanner=new kciControlCenterBanner(this);
    WholeTitleBarSplit->addWidget(ccBanner);
    //Set Content Layout.
    ContentLayout=new QHBoxLayout();
    ContentLayout->setContentsMargins(0,0,0,0);
    ContentLayout->setSpacing(0);
    WholeTitleBarSplit->addLayout(ContentLayout);

    //Set List.
    ccLeftBar=new kciControlCenterLeftBar(this);
    ContentLayout->addWidget(ccLeftBar);

    //Set Main Contents.
    //This widget ONLY use to get size, no use.
    CCMainContents=new kciControlCenterContents(this);
    ContentLayout->addWidget(CCMainContents);
}
