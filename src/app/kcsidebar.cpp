#include "kcsidebar.h"
#include "kclanguageconfigure.h"

KCClipboardHistoryStack::KCClipboardHistoryStack(QWidget *parent) :
    QListView(parent)
{
    QPalette pal=this->palette();
    pal.setColor(QPalette::Window, QColor(69,69,69));
    setPalette(pal);

    setModel(KCClipboard::getInstance()->getClipboardTextsModel());
    connect(this, &KCClipboardHistoryStack::activated,
            this, &KCClipboardHistoryStack::dblClickClipboardItems);
}

void KCClipboardHistoryStack::dblClickClipboardItems(QModelIndex ItemID)
{
    emit requiredInsertText(KCClipboard::getInstance()->getHistoryClipboardText(ItemID.row()));
}

KCHistoryStack::KCHistoryStack(QWidget *parent) :
    QListView(parent)
{
    QPalette pal=this->palette();
    pal.setColor(QPalette::Window, QColor(69,69,69));
    setPalette(pal);

    setModel(KCHistoryConfigure::getInstance()->getRecentOpenedFileModel());
    connect(this, &KCHistoryStack::activated,
            this, &KCHistoryStack::dblClickHistoryItems);
}

void KCHistoryStack::dblClickHistoryItems(QModelIndex itemIndex)
{
    emit requiredOpenFiles(KCHistoryConfigure::getInstance()->getRecentFileList().at(itemIndex.row()).fileFullPath);
}

KCSidebarButton::KCSidebarButton(QWidget *parent) :
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
    pal=this->palette();
    buttonBackcolor=QColor(0x35,0x35,0x35,0);
    setBackgroundColor();

    //Set Displayer.
    iconDisplayer=new QLabel(this);
    iconDisplayer->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(iconDisplayer,1);

    buttonPressed=false;
    buttonLocked=false;
}

void KCSidebarButton::setIcon(QString IconPath)
{
    iconDisplayer->setPixmap(QPixmap(IconPath));
}

void KCSidebarButton::setPressed(bool newValue, bool force)
{
    buttonPressed=newValue;
    if(buttonPressed)
    {
        buttonBackcolor.setAlpha(255);
        setBackgroundColor();
    }
    else
    {
        buttonBackcolor.setAlpha(force?0:100);
        setBackgroundColor();
    }
}

void KCSidebarButton::setBackgroundColor()
{
    pal.setColor(QPalette::Window, buttonBackcolor);
    setPalette(pal);
}

void KCSidebarButton::enterEvent(QEvent *e)
{
    if(!buttonPressed)
    {
        buttonBackcolor.setAlpha(100);
        setBackgroundColor();
        emit mouseEnter();
    }
    QWidget::enterEvent(e);
}

void KCSidebarButton::leaveEvent(QEvent *e)
{
    if(!buttonPressed)
    {
        buttonBackcolor.setAlpha(0);
        setBackgroundColor();
        emit mouseExit();
    }
    QWidget::leaveEvent(e);
}

void KCSidebarButton::mousePressEvent(QMouseEvent *e)
{
    setPressed(!buttonPressed, false);
    QWidget::mousePressEvent(e);
    emit mousePressed();
}

KCSideBarContent::KCSideBarContent(QWidget *parent) :
    QWidget(parent)
{
    //Set language
    retranslate();

    //Set Properties.
    setMinimumWidth(0);
    sidebarButtonIndex=-1;

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

    //Set Sidebar Buttons.
    sidebarButton[sideButtonHistory]=new KCSidebarButton(this);
    sidebarButton[sideButtonHistory]->setIcon(":/Sidebar/image/Sidebar/History.png");
    sidebarButton[sideButtonHistory]->setToolTip(historyButtonTips);

    sidebarButton[sideButtonClipboard]=new KCSidebarButton(this);
    sidebarButton[sideButtonClipboard]->setIcon(":/Sidebar/image/Sidebar/Clipboard.png");
    sidebarButton[sideButtonClipboard]->setToolTip(clipboardButtonTips);

    for(int i=sideButtonHistory; i<sidebarButtonCount; i++)
    {
        buttonGroupLayout->addWidget(sidebarButton[i]);
        connect(sidebarButton[i], SIGNAL(mousePressed()),
                sidebarButtonMapper, SLOT(map()));
        sidebarButtonMapper->setMapping(sidebarButton[i], i);
    }
    connect(sidebarButtonMapper, SIGNAL(mapped(int)),
            this, SLOT(listButtonClicked(int)));

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
    historyStack=new KCHistoryStack(this);
    contents->addWidget(historyStack);
    connect(historyStack, SIGNAL(requiredOpenFiles(QString)),
            this, SIGNAL(historyRequiredOpenFiles(QString)));

    clipboardStack=new KCClipboardHistoryStack(this);
    contents->addWidget(clipboardStack);
    connect(clipboardStack, SIGNAL(requiredInsertText(QString)),
            this, SIGNAL(clipRequiredInsertText(QString)));
}

KCSideBarContent::~KCSideBarContent()
{
    buttonGroupLayout->deleteLater();
}

void KCSideBarContent::setContentFixedWidth(int newContentWidth)
{
    contents->setFixedWidth(newContentWidth);
}

void KCSideBarContent::forceClearButtonState()
{
    if(sidebarButtonIndex!=-1)
    {
        sidebarButton[sidebarButtonIndex]->setPressed(false, true);
        sidebarButtonIndex=-1;
    }
}

void KCSideBarContent::forceShowButtonState()
{
    if(sidebarButtonIndex!=-1)
    {
        sidebarButton[sidebarButtonIndex]->setPressed(true, true);
    }
    sidebarButtonIndex=contents->currentIndex();
    sidebarButton[sidebarButtonIndex]->setPressed(true, true);
}

void KCSideBarContent::showContent()
{
    contents->show();
}

void KCSideBarContent::hideContent()
{
    contents->hide();
}

void KCSideBarContent::retranslate()
{
    historyButtonTips=tr("History");
    clipboardButtonTips=tr("Clipboard");
}

void KCSideBarContent::retranslateAndSet()
{
    retranslate();
    sidebarButton[sideButtonHistory]->setToolTip(historyButtonTips);
    sidebarButton[sideButtonClipboard]->setToolTip(clipboardButtonTips);
}

void KCSideBarContent::listButtonClicked(int Index)
{
    if(sidebarButtonIndex==Index)
    {
        forceClearButtonState();
        emit foldRequest();
    }
    else
    {
        if(sidebarButtonIndex==-1)
        {
            emit expandRequest();
        }
        else
        {
            sidebarButton[sidebarButtonIndex]->setPressed(false, true);
        }
        contents->setCurrentIndex(Index);
        sidebarButtonIndex=Index;
    }
}

KCSideBar::KCSideBar(QWidget *parent) :
    QDockWidget(parent)
{
    //Set translate langauge
    retranslate();
    //Set ObjectName
    setObjectName("Sidebar");
    //Claer Title bar.
    QWidget *clearTitleBar=new QWidget(this);
    setTitleBarWidget(clearTitleBar);
    //Set Features.
    setFeatures(QDockWidget::NoDockWidgetFeatures);
    //Set Fixed Size.
    setMinimumWidth(0);
    setFixedWidth(5);
    //Set Style
    setContentsMargins(0,0,0,0);
    setAutoFillBackground(true);
    pal=palette();
    pal.setBrush(QPalette::Window, QBrush(QColor(100,100,100)));
    pal.setColor(QPalette::Base,QColor(0x35,0x35,0x35));
    pal.setColor(QPalette::WindowText,QColor(255,255,255));
    pal.setColor(QPalette::Button,QColor(83,83,83));
    pal.setColor(QPalette::Text,QColor(255,255,255));
    pal.setColor(QPalette::ButtonText,QColor(255,255,255));
    setPalette(pal);
    setWindowTitle(" " + windowTitleString + " ");

    //New Central Widget
    centralWidget=new KCSideBarContent(this);
    centralWidget->setMinimumWidth(0);
    setWidget(centralWidget);

    connect(centralWidget, SIGNAL(historyRequiredOpenFiles(QString)),
            this, SIGNAL(historyRequiredOpenFiles(QString)));
    connect(centralWidget, SIGNAL(clipRequiredInsertText(QString)),
            this, SIGNAL(clipboardRequiredInsertText(QString)));
    connect(centralWidget, SIGNAL(expandRequest()),
            this, SLOT(expandAnime()));
    connect(centralWidget, SIGNAL(foldRequest()),
            this, SLOT(foldAnime()));

    showDockAnimation=new QTimeLine(100, this);
    showDockAnimation->setEasingCurve(QEasingCurve::OutCubic);
    showDockAnimation->setEndFrame(30);
    connect(showDockAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(resizeDock(int)));

    hideDockAnimation=new QTimeLine(100, this);
    hideDockAnimation->setEasingCurve(QEasingCurve::OutCubic);
    hideDockAnimation->setEndFrame(6);
    connect(hideDockAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(resizeDock(int)));

    expandAnimation=new QTimeLine(250, this);
    expandAnimation->setEasingCurve(QEasingCurve::OutCubic);
    expandAnimation->setEndFrame(230);
    connect(expandAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(resizeDock(int)));

    foldAnimation=new QTimeLine(250, this);
    foldAnimation->setEasingCurve(QEasingCurve::OutCubic);
    foldAnimation->setEndFrame(30);
    connect(foldAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(resizeDock(int)));
    connect(foldAnimation, SIGNAL(finished()),
            centralWidget, SLOT(hideContent()));

    expandState=false;
    unlockState=true;

    connect(KCLanguageConfigure::getInstance(), &KCLanguageConfigure::newLanguageSet,
            this, &KCSideBar::retranslateAndSet);
}

void KCSideBar::forceClearButtonState()
{
    centralWidget->forceClearButtonState();
}

void KCSideBar::forceShowButtonState()
{
    centralWidget->forceShowButtonState();
}

void KCSideBar::expandAnime()
{
    if(expandAnimation->state()!=QTimeLine::Running)
    {

        foldAnimation->stop();
        expandAnimation->setStartFrame(this->width());
        resizeDock(this->width());
        expandState=true;
        centralWidget->showContent();
        expandAnimation->start();
    }
}

void KCSideBar::resizeDock(int newWidth)
{
    centralWidget->setContentFixedWidth(newWidth-30>0?newWidth-30:0);
    setFixedWidth(newWidth);
}

void KCSideBar::foldAnime()
{
    if(foldAnimation->state()!=QTimeLine::Running)
    {
        disconnect(animationHide);
        expandAnimation->stop();
        foldAnimation->setStartFrame(this->width());
        expandState=false;
        foldAnimation->start();
    }
}

bool KCSideBar::getExpandState() const
{
    return expandState;
}

void KCSideBar::setExpandState(bool value)
{
    expandState = value;
}

void KCSideBar::showDock()
{
    hideDockAnimation->stop();
    showDockAnimation->stop();
    showDockAnimation->setStartFrame(this->width());
    showDockAnimation->start();
}

void KCSideBar::hideDock()
{
    showDockAnimation->stop();
    hideDockAnimation->stop();
    hideDockAnimation->setStartFrame(this->width());
    hideDockAnimation->start();
}

bool KCSideBar::getUnlockState() const
{
    return unlockState;
}

void KCSideBar::setUnlockState(bool value)
{
    unlockState = value;
    if(unlockState)
    {
        pal.setBrush(QPalette::Window, QBrush(QColor(100,100,100)));
        setPalette(pal);
        if(expandAnimation->state()==QTimeLine::Running ||
                foldAnimation->state()==QTimeLine::Running)
        {
            animationHide=connect(foldAnimation, SIGNAL(finished()),
                                  this, SLOT(hideDock()));
        }
        else
        {
            hideDock();
        }
    }
    else
    {
        pal.setBrush(QPalette::Window, QBrush(QColor(150,150,150)));
        setPalette(pal);
        showDock();
    }
}

void KCSideBar::retranslate()
{
    windowTitleString=tr("Sidebar");
}

void KCSideBar::retranslateAndSet()
{
    retranslate();
    setWindowTitle(windowTitleString);
    centralWidget->retranslateAndSet();
}

void KCSideBar::enterEvent(QEvent *e)
{
    QDockWidget::enterEvent(e);
    if(unlockState)
    {
        if(!expandState &&
                expandAnimation->state()!=QTimeLine::Running &&
                foldAnimation->state()!=QTimeLine::Running)
        {
            pal.setBrush(QPalette::Window, QBrush(QColor(150,150,150)));
            setPalette(pal);
            showDock();
        }
    }
}

void KCSideBar::leaveEvent(QEvent *e)
{
    QDockWidget::leaveEvent(e);
    if(unlockState)
    {
        if(!expandState)
        {
            pal.setBrush(QPalette::Window, QBrush(QColor(100,100,100)));
            setPalette(pal);
            if(expandAnimation->state()==QTimeLine::Running ||
                    foldAnimation->state()==QTimeLine::Running)
            {
                animationHide=connect(foldAnimation, SIGNAL(finished()),
                                      this, SLOT(hideDock()));
            }
            else
            {
                hideDock();
            }
        }
    }
}
