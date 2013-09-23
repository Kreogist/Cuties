#include "kcisidebar.h"

kciClipboardHistoryStack::kciClipboardHistoryStack(QWidget *parent) :
    QListView(parent)
{
    setModel(kciClipboard::getInstance()->getClipboardTextsModel());
    connect(this, &kciClipboardHistoryStack::doubleClicked,
            this, &kciClipboardHistoryStack::dblClickClipboardItems);
}

void kciClipboardHistoryStack::dblClickClipboardItems(QModelIndex ItemID)
{
    emit requiredInsertText(kciClipboard::getInstance()->getClipboardTextsModel()->item(ItemID.row())->text());
}

kciHistoryStack::kciHistoryStack(QWidget *parent) :
    QListView(parent)
{
    setModel(kciHistoryConfigure::getInstance()->getRecentOpenedFileModel());
    connect(this, &kciHistoryStack::doubleClicked,
            this, &kciHistoryStack::dblClickHistoryItems);
    connect(this, &kciHistoryStack::activated,
            this, &kciHistoryStack::dblClickHistoryItems);
}

void kciHistoryStack::dblClickHistoryItems(QModelIndex ItemID)
{
    emit requiredOpenFiles(kciHistoryConfigure::getInstance()->getRecentOpenedFileModel()->item(ItemID.row())->toolTip());
}

kciSideBarContent::kciSideBarContent(QWidget *parent) :
    QWidget(parent)
{
    QButtonGroup *switcherGroup=new QButtonGroup(this);
    buttonGroupLayout=new QHBoxLayout();
    buttonGroupLayout->setContentsMargins(4,4,4,4);
    buttonGroupLayout->setSpacing(0);

    mainLayout=new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    //Add History Button.
    buttonRecent=new QToolButton(this);
    buttonRecent->setAutoRaise(true);
    buttonRecent->setCheckable(true);
    buttonRecent->setChecked(true);
    buttonRecent->setFixedSize(35,20);
    buttonRecent->setToolTip(tr("History"));
    buttonRecent->setIcon(QIcon(":/Sidebar/image/Sidebar/History.png"));
    switcherGroup->addButton(buttonRecent, 0);
    buttonGroupLayout->addWidget(buttonRecent);

    //Add Clipboard History Button.
    buttonClipboard=new QToolButton(this);
    buttonClipboard->setAutoRaise(true);
    buttonClipboard->setCheckable(true);
    buttonClipboard->setFixedSize(35,20);
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
    mainLayout->addWidget(contents);

    //Add Widgets
    historyStack=new kciHistoryStack(this);
    contents->addWidget(historyStack);
    connect(historyStack, SIGNAL(requiredOpenFiles(QString)),
            this, SIGNAL(historyRequiredOpenFiles(QString)));

    clipboardStack=new kciClipboardHistoryStack(this);
    contents->addWidget(clipboardStack);
    connect(clipboardStack, SIGNAL(requiredInsertText(QString)),
            this, SIGNAL(clipRequiredInsertText(QString)));

    connect(switcherGroup, SIGNAL(buttonPressed(int)),
            contents, SLOT(setCurrentIndex(int)));
}

kciSideBarContent::~kciSideBarContent()
{
    buttonGroupLayout->deleteLater();
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
    setFixedWidth(0);
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
    setWidget(CentralWidget);

    connect(CentralWidget, SIGNAL(historyRequiredOpenFiles(QString)),
            this, SIGNAL(historyRequiredOpenFiles(QString)));
    connect(CentralWidget, SIGNAL(clipRequiredInsertText(QString)),
            this, SIGNAL(clipboardRequiredInsertText(QString)));
}

void kciSideBar::showAnime()
{
    QTimeLine *showAnimation=new QTimeLine(250, this);
    showAnimation->setEasingCurve(QEasingCurve::OutCubic);
    showAnimation->setStartFrame(0);
    showAnimation->setEndFrame(230);
    connect(showAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(resizeDock(int)));
    this->show();
    showAnimation->start();
}

void kciSideBar::resizeDock(int newWidth)
{
    setFixedWidth(newWidth);
}

void kciSideBar::hideAnime()
{
    QTimeLine *hideAnimation=new QTimeLine(250, this);
    hideAnimation->setEasingCurve(QEasingCurve::OutCubic);
    hideAnimation->setStartFrame(230);
    hideAnimation->setEndFrame(0);
    connect(hideAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(resizeDock(int)));
    connect(hideAnimation, SIGNAL(finished()),
            this, SLOT(hide()));
    hideAnimation->start();
}
