
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
    setContentsMargins(0,0,0,0);
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

    //Set All Color
    normalColor=QColor(255,255,255,0);
    changedColor=QColor(255,255,255,70);
    hoverColor=QColor(255,255,255,200);
    pushColor=QColor(255,255,255,255);

    //Get Palette and Colors
    pal=this->palette();
    pal.setColor(QPalette::Window, normalColor);
    setPalette(pal);

    //Set Layout.
    QHBoxLayout *listButtonLayout=new QHBoxLayout(this);
    listButtonLayout->setContentsMargins(0,0,0,0);
    listButtonLayout->setSpacing(0);
    categoryIcon=new QLabel(this);
    listButtonLayout->addWidget(categoryIcon);
    categoryCaption=new QLabel(this);
    listButtonLayout->addWidget(categoryCaption);
    listButtonLayout->addStretch();
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
        pal.setColor(QPalette::Window, hoverColor);
        setPalette(pal);
        QWidget::enterEvent(e);
    }
}

void KCPreferenceListButton::leaveEvent(QEvent *e)
{
    if(!categoryPressed)
    {
        if(!categoryChanged)
        {
            pal.setColor(QPalette::Window, normalColor);
            setPalette(pal);
            QWidget::enterEvent(e);
        }

    }
    QWidget::leaveEvent(e);
}

void KCPreferenceListButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(!categoryPressed)
    {
        //Change state, emit signal
        categoryPressed=!categoryPressed;
        pal.setColor(QPalette::Window, pushColor);
        setPalette(pal);
        emit categorySelected();
        QWidget::enterEvent(e);
    }
    QWidget::mouseReleaseEvent(e);
}

bool KCPreferenceListButton::getCategoryPressed() const
{
    return categoryPressed;
}

void KCPreferenceListButton::setCategoryPressed(bool value)
{
    categoryPressed = value;
}

void KCPreferenceListButton::fadeMeOut()
{

}

KCPreferenceCategoryList::KCPreferenceCategoryList(QWidget *parent) :
    QWidget(parent)
{
    //Set Language String
    retranslate();
    QString categoryIcons[KCCategoryCount];
    categoryIcons[KCPreferenceGerneral]=":/controlcenter/image/Control Center/cciGeneral.png";
    categoryIcons[KCPreferenceEditor]=":/controlcenter/image/Control Center/cciEditor.png";
    categoryIcons[KCPreferenceCompiler]=":/controlcenter/image/Control Center/cciCompiler.png";
    categoryIcons[KCPreferenceDebugger]=":/controlcenter/image/Control Center/cciDebugger.png";
    categoryIcons[KCPreferenceFileAssociation]=":/controlcenter/image/Control Center/cciFileAssociation.png";
    categoryIcons[KCPreferenceLanguage]=":/controlcenter/image/Control Center/cciLanguage.png";

    //Set Properties
    setContentsMargins(0,0,0,0);
    setFixedWidth(215);

    //Current Index
    /*
     * Fixed Here!
     *
     * Change this to a previous settings.
     * This should be saved.
     *
     */
    currentCategory=KCPreferenceGerneral;

    //Set Layout and Add Widgets;
    QVBoxLayout *categoryListLayout=new QVBoxLayout(this);
    categoryListLayout->setContentsMargins(0,0,0,0);
    categoryListLayout->setSpacing(0);
    setLayout(categoryListLayout);

    //Signal mapper sets
    QSignalMapper *listSelectSignals=new QSignalMapper(this);

    for(int i=KCPreferenceGerneral; i<KCCategoryCount; i++)
    {
        categoryButton[i]=new KCPreferenceListButton(this);
        categoryButton[i]->setCategoryTitle(categoryCaptions[i]);
        categoryButton[i]->setCategoryIcon(categoryIcons[i]);
        listSelectSignals->setMapping(categoryButton[i],i);
        categoryListLayout->addWidget(categoryButton[i]);
    }
    categoryListLayout->addStretch();
}

void KCPreferenceCategoryList::listSelectChangedEvent(int listIndex)
{
    categoryButton[listIndex]->setCategoryPressed(true);
    categoryButton[currentCategory]->setCategoryPressed(false);
    currentCategory=listIndex;
}

void KCPreferenceCategoryList::retranslate()
{
    categoryCaptions[KCPreferenceGerneral]=tr("Gerneral");
    categoryCaptions[KCPreferenceEditor]=tr("Editor");
    categoryCaptions[KCPreferenceCompiler]=tr("Compiler");
    categoryCaptions[KCPreferenceDebugger]=tr("Debugger");
    categoryCaptions[KCPreferenceFileAssociation]=tr("File Association");
    categoryCaptions[KCPreferenceLanguage]="";
}

void KCPreferenceCategoryList::retranslateAndSet()
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
    setMinimumSize(640, 400);

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
    bannerLayout->addLayout(contentLayout);

    //Set Category List
    categoryList=new KCPreferenceCategoryList(this);
    contentLayout->addWidget(categoryList);

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
