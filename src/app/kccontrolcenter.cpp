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

#include "kcsearchlinetext.h"
#include "Controls/SettingItems/kcsettinglistitemcombo.h"
#include "Controls/SettingItems/kcsettinglistitemboolean.h"
#include "Controls/SettingItems/kcsettinglistitemlinetext.h"
#include "Controls/SettingItems/kcsettinglistitembrowsetext.h"
#include "Controls/SettingItems/kcsettinglistitemnuminput.h"
#include "Controls/SettingItems/kcsettinglistitemlanguageitem.h"
#include "Controls/SettingItems/kcsettinglistitembutton.h"
#include "kclistbutton.h"

#include "kcgeneralconfigure.h"
#include "kceditorconfigure.h"
#include "kccompilerconfigure.h"
#include "kclanguageconfigure.h"
#include "kcclipboard.h"
#include "kchistoryconfigure.h"
#include "kccolorconfigure.h"

#include "kccontrolcenter.h"

/**************************************/
/*    Based Widget - KCScrollArea    */
/**************************************/
KCScrollArea::KCScrollArea(QWidget *parent):
    QScrollArea(parent)
{
    ;
}

void KCScrollArea::resizeEvent(QResizeEvent *event)
{
    event->accept();
    QScrollArea::resizeEvent(event);
    emit sizeChanged();
}

//-------------Banner--------------
KCControlCenterBanner::KCControlCenterBanner(QWidget *parent):
    QWidget(parent)
{
    setObjectName("KCControlCenterBanner");
    setFixedHeight(44);
    setContentsMargins(0,0,0,0);
    setAutoFillBackground(true);

    //Set Palette
    QPalette pal=this->palette();
    KCColorConfigure::getInstance()->getPalette(pal,objectName());
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
    lblBannerTitle->setObjectName("lblBannerTitle");
    pal=lblBannerTitle->palette();
    KCColorConfigure::getInstance()->getPalette(pal,objectName());
    lblBannerTitle->setPalette(pal);
    TitleLayout->addWidget(lblBannerTitle);
    //Set Stretch
    TitleLayout->addStretch(0);
    //Set Search Bar
    /*CCSearch=new KCSearchLineText();
    CCSearch->setFixedWidth(250);
    TitleLayout->addWidget(CCSearch);
    TitleLayout->addSpacing(7);*/
}

//----------------Left Bar-------------------
KCControlCenterLeftBar::KCControlCenterLeftBar(QWidget *parent) :
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
    for(int i=cclstGerneral; i<cclist_count; i++)
    {
        lsbLeftButtons[i]=new KCListButton(this);
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

void KCControlCenterLeftBar::connectLeftAndRight(const int &lstButtonID, QWidget *userInterface)
{
    lsbLeftButtons[lstButtonID]->setUserInterfaceWidget(userInterface);
}

void KCControlCenterLeftBar::lstClick(int Index)
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
KCAbstractCCTabContent::KCAbstractCCTabContent(QWidget *parent):
    QWidget(parent)
{
    setObjectName("KCAbstractCCTabContent");
    QPalette pal=palette();
    KCColorConfigure::getInstance()->registerColorInfo(QPalette::Window, QColor(255,255,255),objectName());
    KCColorConfigure::getInstance()->getPalette(pal,objectName());
    setPalette(pal);
}
//---------------Gerneral------------------------
KCCCTabGerneralContent::KCCCTabGerneralContent(QWidget *parent) :
    KCAbstractCCTabContent(parent)
{
    setObjectName("KCCCTabGerneralContent");
    setAutoFillBackground(true);
    setContentsMargins(0, 0, 0, 0);

    QFont TitleFont=this->font();
    TitleFont.setPixelSize(20);

    //Set Layout.
    MainLayout=new QVBoxLayout(this);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);
    setLayout(MainLayout);

    QLabel *tblEnvironment=new QLabel(this);
    tblEnvironment->setText(" " + tr("Envronment"));
    tblEnvironment->setFont(TitleFont);
    tblEnvironment->setFixedHeight(30);
    MainLayout->addSpacing(5);
    MainLayout->addWidget(tblEnvironment);

    sboDefaultLanguage=new KCSettingListItemCombo(this);
    sboDefaultLanguage->captionText->setText(tr("Default Programming Language:"));
    sboDefaultLanguage->addListItem(tr("Plain Text"));
    sboDefaultLanguage->addListItem(tr("C"));
    sboDefaultLanguage->addListItem(tr("C++"));
    sboDefaultLanguage->addListItem(tr("Pascal"));
    sboDefaultLanguage->setValue(KCGeneralConfigure::getInstance()->getDefaultLanguageMode());
    MainLayout->addWidget(sboDefaultLanguage);

    sboUseDefaultLanguageOnOpen=new KCSettingListItemBoolean(this);
    sboUseDefaultLanguageOnOpen->setEnabledText(tr("Auto select default language file suffix when opening files."));
    sboUseDefaultLanguageOnOpen->setDisabledText(tr("Don't select default language file suffix when opening files."));
    sboUseDefaultLanguageOnOpen->setTheValue(KCGeneralConfigure::getInstance()->getUseDefaultLanguageWhenOpen());
    MainLayout->addWidget(sboUseDefaultLanguageOnOpen);

    sboUseDefaultLanguageOnSave=new KCSettingListItemBoolean(this);
    sboUseDefaultLanguageOnSave->setEnabledText(tr("Auto select default language file suffix when saving files."));
    sboUseDefaultLanguageOnSave->setDisabledText(tr("Don't select default language file suffix when saving files."));
    sboUseDefaultLanguageOnSave->setTheValue(KCGeneralConfigure::getInstance()->getUseDefaultLanguageWhenSave());
    MainLayout->addWidget(sboUseDefaultLanguageOnSave);

    QLabel *tblRemember=new QLabel(this);
    tblRemember->setText(" " + tr("Automatic Remember"));
    tblRemember->setFont(TitleFont);
    tblRemember->setFixedHeight(30);
    MainLayout->addSpacing(5);
    MainLayout->addWidget(tblRemember);

    sbnAutoOpenUnclosed=new KCSettingListItemBoolean(this);
    sbnAutoOpenUnclosed->setEnabledText(tr("Restore files when quitting and re-opening files."));
    sbnAutoOpenUnclosed->setDisabledText(tr("Don't restore files when quitting and re-opening files."));
    sbnAutoOpenUnclosed->setTheValue(KCGeneralConfigure::getInstance()->getRememberUnclosedFile());
    MainLayout->addWidget(sbnAutoOpenUnclosed);

    QLabel *tblHistoryLabel=new QLabel(this);
    tblHistoryLabel->setText(" " + tr("History"));
    tblHistoryLabel->setFont(TitleFont);
    tblHistoryLabel->setFixedHeight(30);
    MainLayout->addSpacing(5);
    MainLayout->addWidget(tblHistoryLabel);

    slnHistoryMax=new KCSettingListItemNumInput(this);
    slnHistoryMax->captionText->setText(tr("Maximum History Tracking Items:"));
    slnHistoryMax->setMinValue(4);
    slnHistoryMax->setMaxValue(100);
    slnHistoryMax->setValue(KCHistoryConfigure::getInstance()->getMaxRecentFilesSize());
    MainLayout->addWidget(slnHistoryMax);

    sbtClearHistory=new KCSettingListItemButton(this);
    sbtClearHistory->setButtonText(tr("Clear History Record"));
    connect(sbtClearHistory, &KCSettingListItemButton::buttonPressed,
            this, &KCCCTabGerneralContent::clearHistoryFilesRecord);
    MainLayout->addWidget(sbtClearHistory);

    QLabel *tblSearch=new QLabel(this);
    tblSearch->setText(" " + tr("Search Options"));
    tblSearch->setFont(TitleFont);
    tblSearch->setFixedHeight(30);
    MainLayout->addSpacing(5);
    MainLayout->addWidget(tblSearch);

    sboSearchEngine=new KCSettingListItemCombo(this);
    sboSearchEngine->captionText->setText(tr("Online Search Engine:"));
    QList<searchEngine> searchEngines=KCGeneralConfigure::getInstance()->getSearchEngineList();
    for(int i=0; i<searchEngines.count(); i++)
    {
        sboSearchEngine->addListItem(searchEngines[i].name);
    }
    sboSearchEngine->setValue(KCGeneralConfigure::getInstance()->getSearchEngineIndex());
    MainLayout->addWidget(sboSearchEngine);
}

void KCCCTabGerneralContent::apply()
{
    //Remember Unclosed Set.
    KCGeneralConfigure::getInstance()->setRememberUnclosedFile(sbnAutoOpenUnclosed->getValue());
    //Default Language Mode Sets.
    KCGeneralConfigure::getInstance()->setDefaultLanguageMode(sboDefaultLanguage->getValue());
    //Save and Open States using language mode.
    KCGeneralConfigure::getInstance()->setUseDefaultLanguageWhenOpen(sboUseDefaultLanguageOnOpen->getValue());
    KCGeneralConfigure::getInstance()->setUseDefaultLanguageWhenSave(sboUseDefaultLanguageOnSave->getValue());
    //History Settings.
    KCHistoryConfigure::getInstance()->setMaxRecentFilesSize(slnHistoryMax->getValue());
    //Search
    KCGeneralConfigure::getInstance()->setSearchEngineIndex(sboSearchEngine->getValue());
}

void KCCCTabGerneralContent::clearHistoryFilesRecord()
{
    KCHistoryConfigure::getInstance()->clearAllRecentFilesRecord();
}

//--------------------Editor------------------
KCCCTabEditorContent::KCCCTabEditorContent(QWidget *parent) :
    KCAbstractCCTabContent(parent)
{
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);

    QFont TitleFont=this->font();
    TitleFont.setPixelSize(20);

    //Set Layout.
    MainLayout=new QVBoxLayout(this);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);
    setLayout(MainLayout);

    //Title Label.
    QLabel *tblViewOption=new QLabel(this);
    tblViewOption->setText(" " + tr("View Option"));
    tblViewOption->setFont(TitleFont);
    tblViewOption->setFixedHeight(30);
    MainLayout->addSpacing(5);
    MainLayout->addWidget(tblViewOption);

    tabSpaceEnabled=new KCSettingListItemBoolean(this);
    tabSpaceEnabled->setEnabledText(tr("Use space instead of tab."));
    tabSpaceEnabled->setDisabledText(tr("Enable tab."));
    tabSpaceEnabled->setTheValue(KCEditorConfigure::getInstance()->usingBlankInsteadTab());
    MainLayout->addWidget(tabSpaceEnabled);

    lineNumberVisible=new KCSettingListItemBoolean(this);
    lineNumberVisible->setEnabledText(tr("Show line number panel."));
    lineNumberVisible->setDisabledText(tr("Hide line number panel."));
    lineNumberVisible->setTheValue(KCEditorConfigure::getInstance()->getLineNumVisible());
    MainLayout->addWidget(lineNumberVisible);

    tabSpaceNum=new KCSettingListItemNumInput(this);
    tabSpaceNum->captionText->setText(tr("Tab Spacing:"));
    tabSpaceNum->setValue(KCEditorConfigure::getInstance()->getTabWidth());
    MainLayout->addWidget(tabSpaceNum);

    wrapMode=new KCSettingListItemCombo(this);
    wrapMode->captionText->setText(tr("Word Wrap Mode:"));
    wrapMode->addListItem(tr("No word wrapped"));
    wrapMode->addListItem(tr("Wrapped at word boundaries"));
    wrapMode->addListItem(tr("Wrapped at any point"));
    wrapMode->addListItem(tr("Wrapping at word boundary or anywhere"));
    switch(KCEditorConfigure::getInstance()->getWrapMode())
    {
    case QTextOption::NoWrap:
        wrapMode->setValue(0);
        break;
    case QTextOption::WordWrap:
        wrapMode->setValue(1);
        break;
    case QTextOption::WrapAnywhere:
        wrapMode->setValue(2);
        break;
    case QTextOption::WrapAtWordBoundaryOrAnywhere:
        wrapMode->setValue(3);
        break;
    default:
        //This should be no way to execute.

        wrapMode->setValue(0);
    }

    wrapMode->setValue(KCEditorConfigure::getInstance()->getWrapMode());
    MainLayout->addWidget(wrapMode);

    cursorWidth=new KCSettingListItemNumInput(this);
    cursorWidth->captionText->setText(tr("Cursor Width:"));
    cursorWidth->setMinValue(1);
    cursorWidth->setMaxValue(10);
    cursorWidth->setValue(KCEditorConfigure::getInstance()->getCursorWidth());
    MainLayout->addWidget(cursorWidth);

    //Multi-Tab Editing.
    QLabel *tblMultiTab=new QLabel(this);
    tblMultiTab->setText(" " + tr("Multi-Tab Option"));
    tblMultiTab->setFont(TitleFont);
    tblMultiTab->setFixedHeight(30);
    MainLayout->addSpacing(5);
    MainLayout->addWidget(tblMultiTab);

    //Tab Movealbe.
    slnTabMoveable=new KCSettingListItemBoolean(this);
    slnTabMoveable->setEnabledText(tr("Enable tab moving."));
    slnTabMoveable->setDisabledText(tr("Disable tab moving."));
    slnTabMoveable->setTheValue(KCEditorConfigure::getInstance()->getTabMoveable());
    MainLayout->addWidget(slnTabMoveable);

    //Tab Closable.
    slnTabCloseable=new KCSettingListItemBoolean(this);
    slnTabCloseable->setEnabledText(tr("Enable tab closable."));
    slnTabCloseable->setDisabledText(tr("Disable tab closable."));
    slnTabCloseable->setTheValue(KCEditorConfigure::getInstance()->getTabCloseable());
    MainLayout->addWidget(slnTabCloseable);

    //Title Label.
    QLabel *tblClipboard=new QLabel(this);
    tblClipboard->setText(" " + tr("Clipboard"));
    tblClipboard->setFont(TitleFont);
    tblClipboard->setFixedHeight(30);
    MainLayout->addSpacing(5);
    MainLayout->addWidget(tblClipboard);

    //Clipboard Max
    clipboardMax=new KCSettingListItemNumInput(this);
    clipboardMax->captionText->setText(tr("Maximum Clipboard Tracking Items: "));
    clipboardMax->setMinValue(5);
    clipboardMax->setMaxValue(100);
    clipboardMax->setValue(KCClipboard::getInstance()->getMaxDataCount());
    MainLayout->addWidget(clipboardMax);
}

void KCCCTabEditorContent::apply()
{
    KCEditorConfigure *instance=KCEditorConfigure::getInstance();
    instance->setTabWidth(tabSpaceNum->getValue());
    instance->setCursorWidth(cursorWidth->getValue());
    switch(wrapMode->getValue())
    {
    case 0:
        instance->setWrapMode(QTextOption::NoWrap);
        break;
    case 1:
        instance->setWrapMode(QTextOption::WordWrap);
        break;
    case 2:
        instance->setWrapMode(QTextOption::WrapAnywhere);
        break;
    case 3:
        instance->setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        break;
    }
    instance->setTabMoveable(slnTabMoveable->getValue());
    instance->setTabCloseable(slnTabCloseable->getValue());
    instance->setLineNumVisible(lineNumberVisible->getValue());
    instance->setUsingBlankInsteadTab(tabSpaceEnabled->getValue());
    KCClipboard::getInstance()->setMaxDataCount(clipboardMax->getValue());
}

//-----------------Compiler----------------
KCCCTabCompilerContent::KCCCTabCompilerContent(QWidget *parent) :
    KCAbstractCCTabContent(parent)
{
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);

    QFont TitleFont=this->font();
    TitleFont.setPixelSize(20);

    //Set Layout.
    MainLayout=new QVBoxLayout(this);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);
    setLayout(MainLayout);

    //Title Label.
    QLabel *tblCompilerPath=new QLabel(this);
    tblCompilerPath->setText(" " + tr("Compiler Path"));
    tblCompilerPath->setFont(TitleFont);
    tblCompilerPath->setFixedHeight(30);
    MainLayout->addSpacing(5);
    MainLayout->addWidget(tblCompilerPath);

    KCCompilerConfigure *instance=KCCompilerConfigure::getInstance();

    txeGppCompilerPath=new KCSettingListItemBrowseText(this);
    txeGppCompilerPath->captionText->setText(tr("G++ Compiler Path:"));
    txeGppCompilerPath->setValue(instance->getGppPath());
    MainLayout->addWidget(txeGppCompilerPath);

    txeGccCompilerPath=new KCSettingListItemBrowseText(this);
    txeGccCompilerPath->captionText->setText(tr("GCC Compiler Path:"));
    txeGccCompilerPath->setValue(instance->getGccPath());
    MainLayout->addWidget(txeGccCompilerPath);

    txeFpcCompilerPath=new KCSettingListItemBrowseText(this);
    txeFpcCompilerPath->captionText->setText(tr("FPC Compiler Path:"));
    txeFpcCompilerPath->setValue(instance->getFpcPath());
    MainLayout->addWidget(txeFpcCompilerPath);
}

void KCCCTabCompilerContent::apply()
{
    KCCompilerConfigure *instance=KCCompilerConfigure::getInstance();
    instance->setGccPath(txeGccCompilerPath->getValue());
    instance->setGppPath(txeGppCompilerPath->getValue());
    instance->setFpcPath(txeFpcCompilerPath->getValue());
}

//-----------------Debugger-----------------
KCCCTabDebuggerContent::KCCCTabDebuggerContent(QWidget *parent) :
    KCAbstractCCTabContent(parent)
{
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);

    QFont TitleFont=this->font();
    TitleFont.setPixelSize(20);

    //Set Layout.
    MainLayout=new QVBoxLayout(this);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);
    setLayout(MainLayout);

    //Title Label.
    QLabel *tblGDBSettings=new QLabel(this);
    tblGDBSettings->setText(" " + tr("GDB Settings"));
    tblGDBSettings->setFont(TitleFont);
    tblGDBSettings->setFixedHeight(30);
    MainLayout->addSpacing(5);
    MainLayout->addWidget(tblGDBSettings);

    txeGDBDebuggerPath=new KCSettingListItemBrowseText(this);
    txeGDBDebuggerPath->captionText->setText(tr("GDB Path:"));
    MainLayout->addWidget(txeGDBDebuggerPath);

}

//-----------------File Association-----------
KCCCTabFileAssociationContent::KCCCTabFileAssociationContent(QWidget *parent) :
    KCAbstractCCTabContent(parent)
{
    ;
}

//-----------------Language-------------------
KCCCTabLanguageContent::KCCCTabLanguageContent(QWidget *parent) :
    KCAbstractCCTabContent(parent)
{
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);

    //Set Layout.
    mainLayout=new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    //Set Signal Mapper;
    languageSet=new QSignalMapper(this);

    KCLanguageConfigure *instance=KCLanguageConfigure::getInstance();
    int languageNum=instance->getLanguageList().count(),i;
    for(i=0; i<languageNum; i++)
    {
        KCSettingListItemLanguageItem *lanItem=new KCSettingListItemLanguageItem(this);
        lanItem->setLanguageName(instance->getLanguageNameList().at(i));
        if(i==instance->getCurrLanguageIndex())
        {
            lanItem->setCheck(true);
        }
        connect(lanItem, SIGNAL(languageSelect()), languageSet, SLOT(map()));
        languageSet->setMapping(lanItem, i);
        languageItem.append(lanItem);
        mainLayout->addWidget(languageItem.at(i));
    }
    connect(languageSet, SIGNAL(mapped(int)), this, SLOT(applyLanguageSettings(int)));
}

void KCCCTabLanguageContent::applyLanguageSettings(int newLangaugeIndex)
{
    languageItem.at(KCLanguageConfigure::getInstance()->getCurrLanguageIndex())->setCheck(false);
    languageItem.at(newLangaugeIndex)->setCheck(true);
    KCLanguageConfigure::getInstance()->setLanguageIndex(newLangaugeIndex);
}

//------------------Container----------------------
KCControlCenterTab::KCControlCenterTab(QWidget *contentWidget, QWidget *parent) :
    KCAbstractCCTabContent(parent)
{
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);

    //Set FakeLayout.
    FakeLayout=new QVBoxLayout(this);
    FakeLayout->setContentsMargins(0,0,0,0);
    FakeLayout->setSpacing(0);
    setLayout(FakeLayout);

    //Set Content.
    contentWidget->setParent(this);
    contentMWidget=contentWidget;

    //Set Main Widget.
    mainScrollArea=new KCScrollArea(this);
    mainScrollArea->setAutoFillBackground(true);
    mainScrollArea->setFrameShape(QFrame::NoFrame);
    mainScrollArea->setContentsMargins(0,0,0,0);
    mainScrollArea->setWidget(contentWidget);
    FakeLayout->addWidget(mainScrollArea);

    connect(mainScrollArea, SIGNAL(sizeChanged()),
            this, SLOT(sizeChangeResize()));
}

void KCControlCenterTab::sizeChangeResize()
{
    contentMWidget->setFixedWidth(mainScrollArea->viewport()->width());
}

/*************************************/
/*      Control Center Contents      */
/*************************************/
KCControlCenterContents::KCControlCenterContents(QWidget *parent) :
    QWidget(parent)
{
    contentWidgets[cclstGerneral]=new KCCCTabGerneralContent(this);
    contentWidgets[cclstEditor]=new KCCCTabEditorContent(this);
    contentWidgets[cclstCompiler]=new KCCCTabCompilerContent(this);
    contentWidgets[cclstDebugger]=new KCCCTabDebuggerContent(this);
    contentWidgets[cclstFileAssociation]=new KCCCTabFileAssociationContent(this);
    contentWidgets[cclstLanguage]=new KCCCTabLanguageContent(this);

    ccTab[cclstGerneral]=new KCControlCenterTab(contentWidgets[cclstGerneral], this);
    ccTab[cclstEditor]=new KCControlCenterTab(contentWidgets[cclstEditor], this);
    ccTab[cclstCompiler]=new KCControlCenterTab(contentWidgets[cclstCompiler], this);
    ccTab[cclstDebugger]=new KCControlCenterTab(contentWidgets[cclstDebugger], this);
    ccTab[cclstFileAssociation]=new KCControlCenterTab(contentWidgets[cclstFileAssociation], this);
    ccTab[cclstLanguage]=new KCControlCenterTab(contentWidgets[cclstLanguage], this);

    contentIndex=ccTab[cclstGerneral];
}

QWidget *KCControlCenterContents::getCCTab(const int &index)
{
    return ccTab[index];
}

KCAbstractCCTabContent *KCControlCenterContents::getContentWidgets(const int &index)
{
    return contentWidgets[index];
}

void KCControlCenterContents::animeToIndex(QWidget *Index)
{
    Index->setGeometry(0,0,width(),height());
    contentIndex->setGeometry(this->width(),0,this->width(),this->height());
    contentIndex=Index;
}

void KCControlCenterContents::resizeEvent(QResizeEvent *e)
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

KCControlCenter::KCControlCenter(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Cuties Control Center"));
    setMinimumSize(640, 400);

    //Set Whole Layout
    WholeTitleBarSplit=new QVBoxLayout(this);
    WholeTitleBarSplit->setContentsMargins(0,0,0,0);
    WholeTitleBarSplit->setSpacing(0);
    setLayout(WholeTitleBarSplit);

    //Set Banner
    ccBanner=new KCControlCenterBanner(this);
    WholeTitleBarSplit->addWidget(ccBanner);
    //Set Content Layout.
    ContentLayout=new QHBoxLayout();
    ContentLayout->setContentsMargins(0,0,0,0);
    ContentLayout->setSpacing(0);
    WholeTitleBarSplit->addLayout(ContentLayout);

    //Set List.
    ccLeftBar=new KCControlCenterLeftBar(this);
    ContentLayout->addWidget(ccLeftBar);

    //Set Main Contents.
    //This widget ONLY use to get size, no use.
    CCMainContents=new KCControlCenterContents(this);
    ContentLayout->addWidget(CCMainContents);
    connect(ccLeftBar,SIGNAL(NowSelectChanged(QWidget *)),
            CCMainContents,SLOT(animeToIndex(QWidget *)));

    for(int i=cclstGerneral; i<cclist_count; i++)
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
    connect(btApply,SIGNAL(clicked()),
            this,SLOT(onApply()));
    connect(btYes,SIGNAL(clicked()),
            this,SLOT(onYes()));

    BottomButton->addStretch();
    BottomButton->addWidget(btYes);
    BottomButton->addSpacing(3);
    BottomButton->addWidget(btCancel);
    BottomButton->addSpacing(3);
    BottomButton->addWidget(btApply);

    int maxButtonWidth=btYes->sizeHint().width();
    if(btCancel->sizeHint().width()>maxButtonWidth)
    {
        maxButtonWidth=btCancel->sizeHint().width();
    }
    if(btApply->sizeHint().width()>maxButtonWidth)
    {
        maxButtonWidth=btApply->sizeHint().width();
    }

    btYes->setFixedWidth(maxButtonWidth);
    btCancel->setFixedWidth(maxButtonWidth);
    btApply->setFixedWidth(maxButtonWidth);

    WholeTitleBarSplit->addLayout(BottomButton);
    setFocus();
}

void KCControlCenter::onApply()
{
    for(int i=cclstGerneral; i<cclist_count; i++)
    {
        CCMainContents->getContentWidgets(i)->apply();
    }
    KCGlobal::getInstance()->writeSettings();
}

void KCControlCenter::onYes()
{
    onApply();
    close();
}
