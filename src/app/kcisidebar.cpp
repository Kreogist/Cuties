#include "kcisidebar.h"

kciClipboardHistoryStack::kciClipboardHistoryStack(QWidget *parent) :
    QListView(parent)
{
    setModel(kciClipboard::getInstance()->getClipboardTextsModel());
    connect(this, &kciClipboardHistoryStack::activated,
            this, &kciClipboardHistoryStack::dblClickClipboardItems);
}

void kciClipboardHistoryStack::dblClickClipboardItems(QModelIndex ItemID)
{
    emit requiredInsertText(kciClipboard::getInstance()->getHistoryClipboardText(ItemID.row()));
}

kciHistoryStack::kciHistoryStack(QWidget *parent) :
    QListView(parent)
{
    setModel(kciHistoryConfigure::getInstance()->getRecentOpenedFileModel());
    connect(this, &kciHistoryStack::activated,
            this, &kciHistoryStack::dblClickHistoryItems);
}

void kciHistoryStack::dblClickHistoryItems(QModelIndex ItemID)
{
    emit requiredOpenFiles(kciHistoryConfigure::getInstance()->getRecentOpenedFileModel()->item(ItemID.row())->toolTip());
}

kciSidebarButton::kciSidebarButton(QWidget *parent) :
    QToolButton(parent)
{
    //Set Properties.
    setAutoRaise(true);
    setFixedSize(30, 35);
    setCheckable(true);

    pal=this->palette();
    buttonColor=QColor(0x35,0x35,0x35,0);
    pal.setColor(QPalette::Button,buttonColor);
    setPalette(pal);

    connect(this, SIGNAL(clicked()),
            this, SLOT(sidebarButtonClick()));
}

void kciSidebarButton::sidebarButtonClick()
{
    if(this->isChecked())
    {
        this->setChecked(false);
        emit buttonUpByClick();
    }
    else
    {
        buttonColor.setAlpha(255);
        pal.setColor(QPalette::Button, buttonColor);
        setPalette(pal);
    }
}

kciSideBarContent::kciSideBarContent(QWidget *parent) :
    QWidget(parent)
{
    setMinimumWidth(0);
    switcherGroup=new QButtonGroup(this);
    buttonGroupLayout=new QVBoxLayout();
    buttonGroupLayout->setContentsMargins(0,0,0,0);
    buttonGroupLayout->setSpacing(0);

    mainLayout=new QHBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    //Add History Button.
    buttonRecent=new kciSidebarButton(this);
    buttonRecent->setToolTip(tr("History"));
    buttonRecent->setIcon(QIcon(":/Sidebar/image/Sidebar/History.png"));
    switcherGroup->addButton(buttonRecent, 0);
    buttonGroupLayout->addWidget(buttonRecent);

    //Add Clipboard History Button.
    buttonClipboard=new kciSidebarButton(this);
    buttonClipboard->setToolTip(tr("Clipboard"));
    buttonClipboard->setIcon(QIcon(":/Sidebar/image/Sidebar/Clipboard.png"));
    switcherGroup->addButton(buttonClipboard, 1);
    buttonGroupLayout->addWidget(buttonClipboard);

    buttonGroupLayout->addStretch();
    //Add Layout.
    mainLayout->addLayout(buttonGroupLayout);

    //Ready Stacked Widget.
    contents=new QStackedWidget(this);
    contents->setContentsMargins(0,0,0,0);
    contents->setMinimumWidth(0);
    contents->hide();
    mainLayout->addWidget(contents,1);
    mainLayout->addStretch();

    //Add Widgets
    historyStack=new kciHistoryStack(this);
    contents->addWidget(historyStack);
    connect(historyStack, SIGNAL(requiredOpenFiles(QString)),
            this, SIGNAL(historyRequiredOpenFiles(QString)));

    clipboardStack=new kciClipboardHistoryStack(this);
    contents->addWidget(clipboardStack);
    connect(clipboardStack, SIGNAL(requiredInsertText(QString)),
            this, SIGNAL(clipRequiredInsertText(QString)));

    connect(switcherGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(listButtonClicked(int)));
}

kciSideBarContent::~kciSideBarContent()
{
    buttonGroupLayout->deleteLater();
}

void kciSideBarContent::setContentFixedWidth(int newContentWidth)
{
    contents->setFixedWidth(newContentWidth);
}

void kciSideBarContent::showContent()
{
    contents->show();
}

void kciSideBarContent::hideContent()
{
    contents->hide();
}

void kciSideBarContent::listButtonClicked(int Index)
{
    emit expandRequest();
    contents->setCurrentIndex(Index);
}

kciSideBar::kciSideBar(QWidget *parent) :
    QDockWidget(parent)
{
    //Set ObjectName
    setObjectName("Sidebar");
    //Claer Title bar.
    QWidget *clearTitleBar=new QWidget(this);
    setTitleBarWidget(clearTitleBar);
    //Set Features.
    setFeatures(QDockWidget::NoDockWidgetFeatures);
    //Set Fixed Size.
    setMinimumWidth(0);
    setFixedWidth(30);
    //Set Style
    setContentsMargins(0,0,0,0);
    QPalette pal=this->palette();
    pal.setBrush(QPalette::Window, QBrush(QColor(83,83,83)));
    pal.setColor(QPalette::Base,QColor(0x35,0x35,0x35));
    pal.setColor(QPalette::WindowText,QColor(255,255,255));
    pal.setColor(QPalette::Button,QColor(83,83,83));
    pal.setColor(QPalette::Text,QColor(255,255,255));
    pal.setColor(QPalette::ButtonText,QColor(255,255,255));
    setPalette(pal);
    setWindowTitle(" " + tr("Sidebar") + " ");

    //New Central Widget
    CentralWidget=new kciSideBarContent(this);
    CentralWidget->setMinimumWidth(0);
    setWidget(CentralWidget);

    connect(CentralWidget, SIGNAL(historyRequiredOpenFiles(QString)),
            this, SIGNAL(historyRequiredOpenFiles(QString)));
    connect(CentralWidget, SIGNAL(clipRequiredInsertText(QString)),
            this, SIGNAL(clipboardRequiredInsertText(QString)));
    connect(CentralWidget, SIGNAL(expandRequest()),
            this, SLOT(showAnime()));

    showAnimation=new QTimeLine(250, this);

    connect(showAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(resizeDock(int)));
    hideAnimation=new QTimeLine(250, this);
    connect(hideAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(resizeDock(int)));
    connect(hideAnimation, SIGNAL(finished()),
            CentralWidget, SLOT(hideContent()));
    expandState=true;
}

void kciSideBar::showAnime()
{
    if(showAnimation->state()!=QTimeLine::Running)
    {
        hideAnimation->stop();
        showAnimation->setEasingCurve(QEasingCurve::OutCubic);
        showAnimation->setStartFrame(this->width());
        showAnimation->setEndFrame(230);
        resizeDock(this->width());
        CentralWidget->showContent();
        expandState=true;
        showAnimation->start();
    }
}

void kciSideBar::resizeDock(int newWidth)
{
    CentralWidget->setContentFixedWidth(newWidth - 30);
    setFixedWidth(newWidth);
}

void kciSideBar::hideAnime()
{
    if(hideAnimation->state()!=QTimeLine::Running)
    {
        showAnimation->stop();
        hideAnimation->setEasingCurve(QEasingCurve::OutCubic);
        hideAnimation->setStartFrame(230);
        hideAnimation->setEndFrame(30);
        expandState=false;
        hideAnimation->start();
    }
}

bool kciSideBar::getExpandState() const
{
    return expandState;
}

void kciSideBar::setExpandState(bool value)
{
    expandState = value;
}
