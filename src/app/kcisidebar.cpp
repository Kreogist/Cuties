#include "kcisidebar.h"

kciSideBarContent::kciSideBarContent(QWidget *parent) :
    QWidget(parent)
{
    ;
}

kciSideBarTitle::kciSideBarTitle(QWidget *parent) :
    QWidget(parent)
{
    setFixedHeight(16);

    titleMainLayout=new QHBoxLayout(this);
    titleMainLayout->setContentsMargins(0,0,0,0);
    titleMainLayout->setSpacing(0);
    setLayout(titleMainLayout);

    titleMainLayout->addSpacing(3);
    sidebarTitle=new QLabel(this);
    sidebarTitle->setText(tr("Siderbar"));
    titleMainLayout->addWidget(sidebarTitle);

    titleMainLayout->addStretch();

    sidebarLock=new QToolButton(this);
    sidebarLock->setFixedSize(13,15 );
    titleMainLayout->addWidget(sidebarLock);
}

void kciSideBarTitle::setSidebarTitle(const QString title)
{
    sidebarTitle->setText(title);
}

kciSideBar::kciSideBar(QWidget *parent) :
    QDockWidget(parent)
{
    //Set ObjectName
    setObjectName("Sidebar");
    //Claer Title bar.
    sidebarTitleBar=new kciSideBarTitle(this);
    setTitleBarWidget(sidebarTitleBar);
    //Set Features.
    setFeatures(QDockWidget::NoDockWidgetFeatures);
    //Set Fixed Size.
    setFixedWidth(250);
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
