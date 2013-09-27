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
    QWidget(parent)
{
    //Set Properties.
    setAutoFillBackground(true);
    setContentsMargins(6,4,4,4);
    setFixedSize(30,35);

    //Set Layout;
    mainLayout=new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    //Set Background Color.
    buttonBackcolor=QColor(0x35,0x35,0x35,0);
    pal.setColor(QPalette::Window, buttonBackcolor);
    setPalette(pal);

    //Set Displayer.
    iconDisplayer=new QLabel(this);
    iconDisplayer->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(iconDisplayer,1);

    buttonPressed=false;
}

void kciSidebarButton::setIcon(QString IconPath)
{
    iconDisplayer->setPixmap(QPixmap(IconPath));
}

void kciSidebarButton::enterEvent(QEvent *e)
{
    if(!buttonPressed)
    {
        buttonBackcolor.setAlpha(100);
        pal.setColor(QPalette::Window, buttonBackcolor);
        setPalette(pal);
        emit mouseEnter();
    }
    QWidget::enterEvent(e);
}

void kciSidebarButton::leaveEvent(QEvent *e)
{
    if(!buttonPressed)
    {
        buttonBackcolor.setAlpha(0);
        pal.setColor(QPalette::Window, buttonBackcolor);
        setPalette(pal);
        emit mouseExit();
    }
    QWidget::leaveEvent(e);
}

void kciSidebarButton::mousePressEvent(QMouseEvent *e)
{
    if(!buttonLocked)
    {
        if(!buttonPressed)
        {
            buttonPressed=true;
            buttonBackcolor.setAlpha(255);
            pal.setColor(QPalette::Window, buttonBackcolor);
            setPalette(pal);
            emit mousePressed(buttonPressed);
        }
        else
        {
            buttonPressed=false;
            buttonBackcolor.setAlpha(100);
            pal.setColor(QPalette::Window, buttonBackcolor);
            setPalette(pal);
            emit mousePressed(buttonPressed);
        }
        QWidget::mousePressEvent(e);
    }
}

kciSideBarContent::kciSideBarContent(QWidget *parent) :
    QWidget(parent)
{
    //Set Properties.
    setMinimumWidth(0);

    //Set Main Layout.
    mainLayout=new QHBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    //Set Button Group Layout.
    buttonGroupLayout=new QVBoxLayout();
    buttonGroupLayout->setContentsMargins(0,0,0,0);
    buttonGroupLayout->setSpacing(0);

    //Set Sidebar Button Mapper.
    sidebarButtonMapper=new QSignalMapper(this);

    sidebarButton[sideButtonHistory]=new kciSidebarButton(this);
    sidebarButton[sideButtonHistory]->setIcon(":/Sidebar/image/Sidebar/History.png");
    sidebarButton[sideButtonHistory]->setToolTip(tr("History"));
    connect(sidebarButton[sideButtonHistory],SIGNAL(mousePressed(bool)),
            sidebarButtonMapper, SLOT(map()));
    buttonGroupLayout->addWidget(sidebarButton[sideButtonHistory]);

    sidebarButton[sideButtonClipboard]=new kciSidebarButton(this);
    sidebarButton[sideButtonClipboard]->setToolTip(tr("Clipboard"));
    sidebarButton[sideButtonClipboard]->setIcon(":/Sidebar/image/Sidebar/Clipboard.png");
    buttonGroupLayout->addWidget(sidebarButton[sideButtonClipboard]);

    buttonGroupLayout->addStretch();
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

    sidebarButtonIndex=-1;
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
