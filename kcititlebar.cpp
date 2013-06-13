#include "kcititlebar.h"

kciTitleBar::kciTitleBar(QWidget *parent) :
    QWidget(parent),
    mainWindow(parent)
{
    setMouseTracking(true);
    setAutoFillBackground(true);

    windowTitle=parent->windowTitle();

    closeButton = new QToolButton(this);
    closeButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    closeButton->setAutoFillBackground(true);

    minimizeButton = new QToolButton(this);
    minimizeButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMinButton));

    maximizeButton = new QToolButton(this);
    maximizeButtonIcon=style()->standardIcon(QStyle::SP_TitleBarMaxButton);
    maximizeButton->setIcon(maximizeButtonIcon);
    isShowingNormalButton = false;

    normalButtonIcon=style()->standardIcon(QStyle::SP_TitleBarNormalButton);

    connect(closeButton,SIGNAL(clicked()),this->parent(),SLOT(close()));
    connect(minimizeButton,SIGNAL(clicked()),
                            this->parent(),SLOT(showMinimized()));
    connect(maximizeButton,SIGNAL(clicked()),
            this,SLOT(_exchange_button_state()));

    titleLabel=new QLabel(windowTitle,this);
    QPalette pal=titleLabel->palette();
    pal.setColor(QPalette::WindowText,QColor(208,208,208));
    titleLabel->setPalette(pal);

    mainButton=new QToolButton(this);
    connect(mainButton,SIGNAL(clicked()),mainButton,SLOT(showMenu()));

    hLayout = new QHBoxLayout(this);
    setLayout(hLayout);
    hLayout->setContentsMargins(0,0,0,0);
    hLayout->setSpacing(0);
    hLayout->addWidget(mainButton);
    hLayout->addStretch();
    hLayout->addWidget(titleLabel);
    hLayout->addSpacing(3);
    hLayout->addWidget(minimizeButton);
    hLayout->addWidget(maximizeButton);
    hLayout->addWidget(closeButton);

    /*
    setMinimumWidth(mainButton->width() + titleLabel->width() + 3 +
                    minimizeButton->width() + maximizeButton->width() +
                    closeButton->width());
    */
}

void kciTitleBar::_exchange_button_state()
{
    if(isShowingNormalButton)
    {
        mainWindow->showNormal();
        maximizeButton->setIcon(maximizeButtonIcon);
    }
    else
    {
        mainWindow->showMaximized();
        maximizeButton->setIcon(normalButtonIcon);
    }

    isShowingNormalButton^=1;   //change the state
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

void kciTitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        _exchange_button_state();
    }
}
