
#include <QSignalMapper>

#include "kclanguageconfigure.h"
#include "kccolorconfigure.h"

#include "kcpreference.h"

KCPreferenceBannerWidget::KCPreferenceBannerWidget(QWidget *parent) :
    QWidget(parent)
{
    //Set Languages.
    retranslate();

    //Set Properties.
    setObjectName("KCControlCenterBanner");
    setFixedHeight(50);
    setContentsMargins(15,0,15,0);
    setAutoFillBackground(true);

    //Set Palette
    QPalette pal=this->palette();
    KCColorConfigure::getInstance()->getPalette(pal,objectName());
    setPalette(pal);

    //Set Layout.
    QHBoxLayout *titleLayout=new QHBoxLayout(this);
    titleLayout->setContentsMargins(0,0,0,0);
    setLayout(titleLayout);

    titleCaption=new QLabel(this);
    QFont titleCaptionFont=titleCaption->font();
    titleCaptionFont.setPixelSize(15);
    titleCaptionFont.setBold(true);
    titleCaption->setFont(titleCaptionFont);
    titleCaption->setObjectName("lblBannerTitle");
    pal=titleCaption->palette();
    KCColorConfigure::getInstance()->getPalette(pal,objectName());
    titleCaption->setPalette(pal);
    titleCaption->setText(titleCaptionText);
    titleLayout->addWidget(titleCaption);

    localeIcon=new QLabel(this);
    //
    titleLayout->addWidget(localeIcon);

    titleLayout->addStretch();
}

void KCPreferenceBannerWidget::retranslate()
{
    titleCaptionText=tr("Preference");
}

void KCPreferenceBannerWidget::retranslateAndSet()
{
    retranslate();
    titleCaption->setText(titleCaptionText);
}

KCPreferenceListButton::KCPreferenceListButton(QWidget *parent) :
    QWidget(parent)
{
    //Set Properties
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);
    categoryChanged=false;
    categoryPressed=false;
    setFixedHeight(40);

    //Set all status alpha
    normalAlpha=0;
    changedAlpha=30;
    hoverAlpha=80;
    pushAlpha=255;

    //Set background color
    backgroundColor=QColor(0xf7,0xcf,0x3d, normalAlpha);

    //Get Palette and Colors
    pal=this->palette();
    pal.setColor(QPalette::Window, backgroundColor);
    setPalette(pal);

    //Set Layout.
    QHBoxLayout *listButtonLayout=new QHBoxLayout(this);
    listButtonLayout->setContentsMargins(5,5,5,5);
    listButtonLayout->setSpacing(0);
    categoryIcon=new QLabel(this);
    listButtonLayout->addWidget(categoryIcon);
    listButtonLayout->addSpacing(5);
    categoryCaption=new QLabel(this);
    listButtonLayout->addWidget(categoryCaption);
    listButtonLayout->addStretch();

    //Init Fade Out Animation
    fadeOutAnimation=new QTimeLine(128, this);
    fadeOutAnimation->setEasingCurve(QEasingCurve::OutCubic);
    fadeOutAnimation->setEndFrame(0);
    connect(fadeOutAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(changeBackAlpha(int)));
}

void KCPreferenceListButton::setCategoryIcon(const QString &fileName)
{
    categoryIcon->setPixmap(QPixmap(fileName));
}

void KCPreferenceListButton::setCategoryTitle(const QString &text)
{
    categoryCaption->setText(text);
}

void KCPreferenceListButton::enterEvent(QEvent *e)
{
    if(!categoryPressed)
    {
        changeBackAlpha(hoverAlpha);
        QWidget::enterEvent(e);
    }
}

void KCPreferenceListButton::leaveEvent(QEvent *e)
{
    if(!categoryPressed)
    {
        fadeMeOut();
    }
    QWidget::leaveEvent(e);
}

void KCPreferenceListButton::mouseReleaseEvent(QMouseEvent *e)
{
    setCategoryPressed(true);
    emit categorySelected();
    QWidget::mouseReleaseEvent(e);
}

bool KCPreferenceListButton::getCategoryPressed() const
{
    return categoryPressed;
}

void KCPreferenceListButton::changeBackAlpha(int newAlpha)
{
    backgroundColor.setAlpha(newAlpha);
    pal.setColor(QPalette::Window, backgroundColor);
    setPalette(pal);
}

void KCPreferenceListButton::setCategoryPressed(bool value)
{
    categoryPressed = value;
    if(categoryPressed)
    {
        changeBackAlpha(pushAlpha);
    }
    else
    {
        fadeMeOut();
    }
}

void KCPreferenceListButton::fadeMeOut()
{
    if(fadeOutAnimation->state()!=QTimeLine::Running)
    {
        backgroundColor=pal.color(QPalette::Window);
        fadeOutAnimation->stop();
        fadeOutAnimation->setStartFrame(pal.color(QPalette::Window).alpha());
        fadeOutAnimation->start();
    }
}

KCPreferenceCategoryList::KCPreferenceCategoryList(QWidget *parent) :
    QWidget(parent)
{
    //Set Language String
    retranslate();
    QString categoryIcons[KCCategoryCount];
    categoryIcons[KCPreferenceGeneral]=":/controlcenter/image/Control Center/cciGeneral.png";
    categoryIcons[KCPreferenceEditor]=":/controlcenter/image/Control Center/cciEditor.png";
    categoryIcons[KCPreferenceCompiler]=":/controlcenter/image/Control Center/cciCompiler.png";
    categoryIcons[KCPreferenceDebugger]=":/controlcenter/image/Control Center/cciDebugger.png";
    categoryIcons[KCPreferenceFileAssociation]=":/controlcenter/image/Control Center/cciFileAssociation.png";

    //Set Properties
    setContentsMargins(0,0,0,0);
    setFixedWidth(215);

    //Set Layout and Add Widgets;
    QVBoxLayout *categoryListLayout=new QVBoxLayout(this);
    categoryListLayout->setContentsMargins(0,0,0,0);
    categoryListLayout->setSpacing(0);
    setLayout(categoryListLayout);

    //Signal mapper sets
    QSignalMapper *listSelectSignals=new QSignalMapper(this);

    for(int i=KCPreferenceGeneral; i<KCCategoryCount; i++)
    {
        categoryButton[i]=new KCPreferenceListButton(this);
        categoryButton[i]->setCategoryTitle(categoryCaptions[i]);
        categoryButton[i]->setCategoryIcon(categoryIcons[i]);
        connect(categoryButton[i], SIGNAL(categorySelected()),
                listSelectSignals, SLOT(map()));
        listSelectSignals->setMapping(categoryButton[i], i);
        categoryListLayout->addWidget(categoryButton[i]);
    }
    categoryListLayout->addStretch();
    connect(listSelectSignals, SIGNAL(mapped(int)),
            this, SLOT(listSelectChangedEvent(int)));

    //Current Index
    /*
     * Fixed Here!
     *
     * Change this to a previous settings.
     * This should be saved.
     *
     */
    currentCategory=KCPreferenceGeneral;
    categoryButton[currentCategory]->setCategoryPressed(true);
}

void KCPreferenceCategoryList::listSelectChangedEvent(int listIndex)
{
    if(currentCategory==listIndex)
    {
        return;
    }
    categoryButton[currentCategory]->setCategoryPressed(false);
    currentCategory=listIndex;
    emit categoryChanged(currentCategory);
    categoryButton[currentCategory]->setCategoryPressed(true);
}

void KCPreferenceCategoryList::retranslate()
{
    categoryCaptions[KCPreferenceGeneral]=tr("Gerneral");
    categoryCaptions[KCPreferenceEditor]=tr("Editor");
    categoryCaptions[KCPreferenceCompiler]=tr("Compiler");
    categoryCaptions[KCPreferenceDebugger]=tr("Debugger");
    categoryCaptions[KCPreferenceFileAssociation]=tr("File Association");
}

void KCPreferenceCategoryList::retranslateAndSet()
{
    retranslate();
}

KCPreferenceContents::KCPreferenceContents(QWidget *parent) :
    KCPreferencePager(parent)
{
    embeddedSuperList[KCPreferenceGeneral]=new KCPreferenceEmbeddedGeneral(this);
    embeddedSuperList[KCPreferenceEditor]=new KCPreferenceEmbeddedEditor(this);
    embeddedSuperList[KCPreferenceCompiler]=new KCPreferenceEmbeddedCompiler(this);
    embeddedSuperList[KCPreferenceDebugger]=new KCPreferenceEmbeddedDebugger(this);
    embeddedSuperList[KCPreferenceFileAssociation]=new KCPreferenceEmbeddedFileAssociation(this);

    for(int i=KCPreferenceGeneral; i<KCCategoryCount; i++)
    {
        addSuperList(embeddedSuperList[i]);
    }
    initPager();
}

void KCPreferenceContents::applyAllSettings()
{
    for(int i=KCPreferenceGeneral; i<KCCategoryCount; i++)
    {
        embeddedSuperList[i]->applyPreference();
    }
    KCGlobal::getInstance()->writeSettings();
}

KCPreferenceCommander::KCPreferenceCommander(QWidget *parent) :
    QWidget(parent)
{
    retranslate();
    setContentsMargins(8,8,8,8);
    setAutoFillBackground(true);

    commanderLayout=new QHBoxLayout(this);
    commanderLayout->setContentsMargins(0,0,0,0);
    commanderLayout->setSpacing(0);
    setLayout(commanderLayout);

    int maxButtonWidth=0;
    for(int i=commanderYes; i<commanderCount; i++)
    {
        commanderControls[i]=new QToolButton(this);
        commanderControls[i]->setText(commanderTitle[i]);
        if(commanderControls[i]->sizeHint().width()>maxButtonWidth)
        {
            maxButtonWidth=commanderControls[i]->sizeHint().width();
        }
    }
    commanderLayout->addStretch();
    for(int i=commanderYes; i<=commanderApply; i++)
    {
        commanderControls[i]->setFixedWidth(maxButtonWidth);
        commanderLayout->addWidget(commanderControls[i]);
        commanderLayout->addSpacing(3);
    }

    connect(commanderControls[commanderYes], SIGNAL(clicked()),
            this, SIGNAL(requireYes()));
    connect(commanderControls[commanderCancel], SIGNAL(clicked()),
            this, SIGNAL(requireCancel()));
    connect(commanderControls[commanderApply], SIGNAL(clicked()),
            this, SIGNAL(requireApply()));
}

void KCPreferenceCommander::retranslate()
{
    commanderTitle[commanderYes]=tr("Yes");
    commanderTitle[commanderCancel]=tr("Cancel");
    commanderTitle[commanderApply]=tr("Apply");
}

void KCPreferenceCommander::retranslateAndSet()
{
    retranslate();
}

KCPreference::KCPreference(QWidget *parent) :
    QDialog(parent)
{
    //Set Language String
    retranslate();

    //Set Dialog Properties
    setWindowTitle(titleText);
    setMinimumSize(800, 400);

    //Banner Layout
    QVBoxLayout *bannerLayout=new QVBoxLayout(this);
    bannerLayout->setContentsMargins(0,0,0,0);
    bannerLayout->setSpacing(0);
    setLayout(bannerLayout);

    //Set Title Bar
    bannerWidget=new KCPreferenceBannerWidget(this);
    bannerLayout->addWidget(bannerWidget);

    //Content Layout
    contentLayout=new QHBoxLayout();
    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->setSpacing(0);
    bannerLayout->addLayout(contentLayout, 1);

    //Set Category List
    categoryList=new KCPreferenceCategoryList(this);
    contentLayout->addWidget(categoryList);

    //Set Contents
    contents=new KCPreferenceContents(this);
    contentLayout->addWidget(contents, 1);

    //Connect category list and contents
    connect(categoryList, SIGNAL(categoryChanged(int)),
            contents, SLOT(switchToPage(int)));

    //Set Commander
    commander=new KCPreferenceCommander(this);
    bannerLayout->addWidget(commander);

    connect(commander, &KCPreferenceCommander::requireYes,
            this, &KCPreference::yesAction);
    connect(commander, &KCPreferenceCommander::requireCancel,
            this, &KCPreference::cancelAction);
    connect(commander, &KCPreferenceCommander::requireApply,
            this, &KCPreference::applyAction);

    connect(KCLanguageConfigure::getInstance(), &KCLanguageConfigure::newLanguageSet,
            this, &KCPreference::retranslateAndSet);
}

KCPreference::~KCPreference()
{
    contentLayout->deleteLater();
}

void KCPreference::retranslate()
{
    titleText=tr("Preference");
}

void KCPreference::retranslateAndSet()
{
    //Retranslate All Widget
    bannerWidget->retranslateAndSet();
    retranslate();
    setWindowTitle(titleText);
}

void KCPreference::yesAction()
{
    applyAction();
    close();
}

void KCPreference::cancelAction()
{
    close();
}

void KCPreference::applyAction()
{
    contents->applyAllSettings();
}

