#include "kcititlebar.h"

kciTitleBar::kciTitleBar(QWidget *parent) :
    QWidget(parent),
    mainWindow(parent)
{
    setMouseTracking(true);

    windowTitle=parent->windowTitle();

    closeButton = new QToolButton;
    closeButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    closeButton->setAutoFillBackground(true);

    maximizeButton = new QToolButton;
    maximizeButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));

    minimizeButton = new QToolButton;
    minimizeButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMinButton));

    connect(closeButton,SIGNAL(clicked()),this->parent(),SLOT(close()));
    connect(maximizeButton,SIGNAL(clicked()),this->parent(),SLOT(showMaximized()));
    connect(minimizeButton,SIGNAL(clicked()),this->parent(),SLOT(showMinimized()));

    titleLabel=new QLabel(windowTitle,this);

    mainButton=new QToolButton(this);
    connect(mainButton,SIGNAL(clicked()),mainButton,SLOT(showMenu()));

    hLayout = new QHBoxLayout(this);
    setLayout(hLayout);

    hLayout->addWidget(mainButton);
    hLayout->addStretch();
    hLayout->addWidget(minimizeButton);
    hLayout->addWidget(maximizeButton);
    hLayout->addWidget(closeButton);
}

void kciTitleBar::setMenu(QMenu *menu)
{
    mainButton->setMenu(menu);
}

void kciTitleBar::setMainButtonIcon(const QString &mainIcon)
{
    mainButtonIcon.addFile(mainIcon);
    mainButton->setIcon(mainButtonIcon);
}

void kciTitleBar::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton &&
       event->pos().x()>=this->pos().x() &&
       event->pos().y()>=this->pos().y() &&
       event->pos().x()<=this->pos().x()+this->width()&&
       event->pos().y()<=this->pos().y()+this->height())
    {
        hasPressed=true;
        mousePosStart=event->pos();
        event->accept();
    }
    else
        event->ignore();
}

void kciTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(hasPressed && event->buttons() == Qt::LeftButton)
    {
        mainWindow->move(mainWindow->pos() + event->pos() - mousePosStart);
    }
}

void kciTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if(hasPressed)
    {
        hasPressed=false;
        event->accept();
    }
    else
        event->ignore();
}
