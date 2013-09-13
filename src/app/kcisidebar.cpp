#include "kcisidebar.h"

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
    buttonRecent->setFixedSize(35,20);
    buttonRecent->setToolTip(tr("History"));
    buttonRecent->setIcon(QIcon(":/Sidebar/image/Sidebar/History.png"));
    switcherGroup->addButton(buttonRecent, 0);
    buttonGroupLayout->addWidget(buttonRecent);

    buttonGroupLayout->addStretch();
    //Add Layout.
    mainLayout->addLayout(buttonGroupLayout);

    //Ready Stacked Widget.
    contents=new QStackedWidget(this);
    contents->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(contents);

    //Add Widgets
    historyStack=new QListView(this);
    contents->addWidget(historyStack);

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
