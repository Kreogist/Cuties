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

/**************************************/
/*    Based Widget - kciScrollArea    */
/**************************************/
kciScrollArea::kciScrollArea(QWidget *parent):
    QScrollArea(parent)
{
    ;
}

void kciScrollArea::resizeEvent(QResizeEvent *event)
{
    event->accept();
    QScrollArea::resizeEvent(event);
    emit sizeChanged();
}

//-------------Banner--------------
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

//----------------Left Bar-------------------
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
    strLabelTexts[cclstLanguage]="";

    strLabelIcons[cclstGerneral]=":/controlcenter/image/Control Center/cciGeneral.png";
    strLabelIcons[cclstEditor]=":/controlcenter/image/Control Center/cciEditor.png";
    strLabelIcons[cclstCompiler]=":/controlcenter/image/Control Center/cciCompiler.png";
    strLabelIcons[cclstDebugger]=":/controlcenter/image/Control Center/cciDebugger.png";
    strLabelIcons[cclstFileAssociation]=":/controlcenter/image/Control Center/cciFileAssociation.png";
    strLabelIcons[cclstLanguage]=":/controlcenter/image/Control Center/cciLanguage.png";

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

void kciControlCenterLeftBar::connectLeftAndRight(const int& lstButtonID, QWidget *userInterface)
{
    lsbLeftButtons[lstButtonID]->setUserInterfaceWidget(userInterface);
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
        QPropertyAnimation *moveListButton=new QPropertyAnimation(lsbLeftButtons[Index],"geometry",this);
        QRect animeStartPos=lsbLeftButtons[Index]->geometry();
        QRect animeEndPos=lsbLeftButtons[lstSelect]->geometry();
        moveListButton->setStartValue(animeStartPos);
        moveListButton->setEndValue(animeEndPos);
        moveListButton->setEasingCurve(QEasingCurve::OutCubic);
        MainAnimeGroup->addAnimation(moveListButton);
        //Hide Anime
        QPropertyAnimation *hideListButton=new QPropertyAnimation(lsbLeftButtons[lstSelect],"geometry",this);
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
        QPropertyAnimation *showListButton=new QPropertyAnimation(lsbLeftButtons[lstSelect],"geometry",this);
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

        //Emit Signal.
        emit NowSelectChanged(lsbLeftButtons[Index]->getUserInterfaceWidget());
    }
}

/********************************************/
/*          Contorl Center Contents         */
/********************************************/
//---------------Gerneral------------------------
kciCCTabGerneralContent::kciCCTabGerneralContent(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);

    QPalette pal=this->palette();
    pal.setColor(QPalette::Window, QColor(255,255,255));
    setPalette(pal);

    QFont TitleFont=this->font();
    TitleFont.setPixelSize(20);

    //Set Layout.
    MainLayout=new QVBoxLayout(this);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);
    setLayout(MainLayout);

    //Title Label.
    QLabel *tblLanguage=new QLabel(this);
    tblLanguage->setText(" " + tr("Language Settings"));
    tblLanguage->setFont(TitleFont);
    tblLanguage->setFixedHeight(30);
    MainLayout->addSpacing(5);
    MainLayout->addWidget(tblLanguage);

    sboDefaultLanguage=new kciSettingListItemCombo(this);
    sboDefaultLanguage->Caption->setText(tr("Default Language:"));
    sboDefaultLanguage->addListItem(tr("Plain Text"));
    sboDefaultLanguage->addListItem(tr("C/C++"));
    sboDefaultLanguage->addListItem(tr("Pascal"));
    sboDefaultLanguage->setCurrentItemIndex(2);
    MainLayout->addWidget(sboDefaultLanguage);

    sboDefaultEncode=new kciSettingListItemCombo(this);
    sboDefaultEncode->Caption->setText(tr("Default Encoder:"));
    sboDefaultEncode->addListItem(tr("Unicode"));
    sboDefaultEncode->addListItem(tr("ANSI"));
    sboDefaultEncode->addListItem(tr("UTF-8"));
    MainLayout->addWidget(sboDefaultEncode);

    slnEnableAnime=new kciSettingListItemBoolean(this);
    slnEnableAnime->setEnabledText(tr("Enabled Animation Effect."));
    slnEnableAnime->setDisabledText(tr("Disabled Animation Effect."));
    MainLayout->addWidget(slnEnableAnime);
}

//--------------------Editor------------------
kciCCTabEditorContent::kciCCTabEditorContent(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);

    QPalette pal=this->palette();
    pal.setColor(QPalette::Window, QColor(255,255,255));
    setPalette(pal);

    QFont TitleFont=this->font();
    TitleFont.setPixelSize(20);

    //Set Layout.
    MainLayout=new QVBoxLayout(this);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);
    setLayout(MainLayout);

    //Title Label.
    QLabel *tblLanguage=new QLabel(this);
    tblLanguage->setText(" " + tr("Editor Component"));
    tblLanguage->setFont(TitleFont);
    tblLanguage->setFixedHeight(30);
    MainLayout->addSpacing(5);
    MainLayout->addWidget(tblLanguage);

    //Set Line Text.
    slnEnableLineNum=new kciSettingListItemBoolean(this);
    slnEnableLineNum->setEnabledText(tr("Enabled Line Number Panel."));
    slnEnableLineNum->setDisabledText(tr("Disabled Line Number Panel."));
    MainLayout->addWidget(slnEnableLineNum);

    //Text Edit Test.
    txeCCompilerPath=new kciSettingListItemLineText(this);
    txeCCompilerPath->Caption->setText(tr("g++/gcc Path:"));
    txeCCompilerPath->setTextValue("C:/MinGW/bin/g++.exe");
    MainLayout->addWidget(txeCCompilerPath);
}

//------------------Container----------------------
kciControlCenterTab::kciControlCenterTab(QWidget *contentWidget, QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);

    QPalette pal=this->palette();
    pal.setColor(QPalette::Window, QColor(255,255,255));
    setPalette(pal);

    //Set FakeLayout.
    FakeLayout=new QVBoxLayout(this);
    FakeLayout->setContentsMargins(0,0,0,0);
    FakeLayout->setSpacing(0);
    setLayout(FakeLayout);

    //Set Content.
    contentWidget->setParent(this);
    contentMWidget=contentWidget;

    //Set Main Widget.
    mainScrollArea=new kciScrollArea(this);
    mainScrollArea->setAutoFillBackground(true);
    mainScrollArea->setFrameShape(QFrame::NoFrame);
    mainScrollArea->setContentsMargins(0,0,0,0);
    mainScrollArea->setWidget(contentWidget);
    FakeLayout->addWidget(mainScrollArea);

    connect(mainScrollArea, SIGNAL(sizeChanged()),
            this, SLOT(sizeChangeResize()));
}

void kciControlCenterTab::sizeChangeResize()
{
    contentMWidget->setFixedWidth(mainScrollArea->viewport()->width());
}

/*************************************/
/*      Control Center Contents      */
/*************************************/
kciControlCenterContents::kciControlCenterContents(QWidget *parent) :
    QWidget(parent)
{
    contentWidgets[cclstGerneral]=new kciCCTabGerneralContent(this);
    contentWidgets[cclstEditor]=new kciCCTabEditorContent(this);
    contentWidgets[cclstCompiler]=new QWidget(this);
    contentWidgets[cclstDebugger]=new QWidget(this);
    contentWidgets[cclstFileAssociation]=new QWidget(this);
    contentWidgets[cclstLanguage]=new QWidget(this);

    ccTab[cclstGerneral]=new kciControlCenterTab(contentWidgets[cclstGerneral], this);
    ccTab[cclstEditor]=new kciControlCenterTab(contentWidgets[cclstEditor], this);
    ccTab[cclstCompiler]=new kciControlCenterTab(contentWidgets[cclstCompiler], this);
    ccTab[cclstDebugger]=new kciControlCenterTab(contentWidgets[cclstDebugger], this);
    ccTab[cclstFileAssociation]=new kciControlCenterTab(contentWidgets[cclstFileAssociation], this);
    ccTab[cclstLanguage]=new kciControlCenterTab(contentWidgets[cclstLanguage], this);

    contentIndex=ccTab[cclstGerneral];
}

QWidget *kciControlCenterContents::getCCTab(const int &Index)
{
    return ccTab[Index];
}

void kciControlCenterContents::animeToIndex(QWidget *Index)
{
    Index->setGeometry(0,0,width(),height());
    contentIndex->setGeometry(this->width(),0,this->width(),this->height());
    contentIndex=Index;
}

void kciControlCenterContents::resizeEvent(QResizeEvent *e)
{
    for(int i=cclstGerneral; i<cclist_count; i++)
    {
        if(contentIndex==ccTab[i])
        {
            contentIndex->setGeometry(0,0,width(),height());
        }
        else
        {
            ccTab[i]->setGeometry(width(),0,width(),height());
        }
    }
    e->accept();
}

kciControlCenter::kciControlCenter(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Cuties Control Center"));

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
    connect(ccLeftBar,SIGNAL(NowSelectChanged(QWidget*)),
            CCMainContents,SLOT(animeToIndex(QWidget*)));

    for(int i=cclstGerneral; i<cclist_count;i++)
    {
        ccLeftBar->connectLeftAndRight(i, CCMainContents->getCCTab(i));
    }

    //Main Buttom
    QHBoxLayout *BottomButton=new QHBoxLayout();
    BottomButton->setContentsMargins(8,8,8,8);
    btYes=new QToolButton(this);
    btCancel=new QToolButton(this);
    btApply=new QToolButton(this);

    btYes->setText(tr("Ok"));
    btCancel->setText(tr("Cancel"));
    connect(btCancel, SIGNAL(clicked()),
            this, SLOT(close()));
    btApply->setText(tr("Apply"));

    BottomButton->addStretch();
    BottomButton->addWidget(btYes);
    BottomButton->addSpacing(3);
    BottomButton->addWidget(btCancel);
    BottomButton->addSpacing(3);
    BottomButton->addWidget(btApply);
    WholeTitleBarSplit->addLayout(BottomButton);
}
