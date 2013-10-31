#include <QHBoxLayout>
#include <QDebug>

#include "kcmessagebox.h"

KCMessageBoxTitle::KCMessageBoxTitle(QWidget *parent) :
    QWidget(parent)
{
    //Set properties
    setAutoFillBackground(true);
    setFixedHeight(60);
    //For debug
    QPalette pal=this->palette();
    pal.setColor(QPalette::Window, QColor(255,0,0));
    setPalette(pal);

    /*QLabel *background=new QLabel(this);
    background->setPixmap(QPixmap(":/MsgBox/image/MessageBox/Title.png"));
    setFixedHeight(background->sizeHint().height());*/

    //Set layout for title caption display
    QHBoxLayout *titleLayout=new QHBoxLayout(this);
    titleLayout->setContentsMargins(0,0,0,0);
    titleLayout->setSpacing(0);
    setLayout(titleLayout);

    QFont titleFont;
    titleFont.setFamily("sao");
    titleFont.setPixelSize(20);

    //Add title caption
    titleCaption=new QLabel(this);
    titleCaption->setFont(titleFont);
    titleCaption->setAlignment(Qt::AlignCenter);
    titleLayout->addWidget(titleCaption);
}

void KCMessageBoxTitle::setTitleText(QString newTitleText)
{
    titleCaption->setText(newTitleText);
}

KCMessageBoxPanel::KCMessageBoxPanel(QWidget *parent) :
    QWidget(parent)
{
    //Set properties
    setAutoFillBackground(true);
    setFixedHeight(67);

    //Debug use
    QPalette pal=this->palette();
    pal.setColor(QPalette::Window, QColor(0,255,0));
    setPalette(pal);
}

KCMessageBoxContent::KCMessageBoxContent(QWidget *parent) :
    QWidget(parent)
{
    //Set properties
    setAutoFillBackground(true);
    setMinimumWidth(0);
    setMinimumHeight(18);

    //Debug use
    QPalette pal=this->palette();
    pal.setColor(QPalette::Window, QColor(0xdd, 0xdd, 0xdd));
    setPalette(pal);

    //Set MainLayout
    mainLayout=new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    //Add up bound image
    QLabel *upBoundImage=new QLabel(this);
    upBoundImage->setPixmap(QPixmap(":/MsgBox/image/MessageBox/UpBound.png"));
    mainLayout->addWidget(upBoundImage);

    //Add content layout, all the widget will be add to this layout
    contentLayout=new QVBoxLayout();
    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->setSpacing(0);
    mainLayout->addLayout(contentLayout, 1);

    //Add down bound image
    QLabel *downBoundImage=new QLabel(this);
    downBoundImage->setPixmap(QPixmap(":/MsgBox/image/MessageBox/DownBound.png"));
    mainLayout->addWidget(downBoundImage);
}

KCMessageBoxContent::~KCMessageBoxContent()
{
    contentLayout->deleteLater();
}

void KCMessageBoxContent::addText(QString displayText)
{
    QLabel *newLabelText=new QLabel(this);
    newLabelText->setText(displayText);
    contentLayout->addWidget(newLabelText);
}

//Message Box Title
KCMessageBox::KCMessageBox(QWidget *parent) :
    QWidget(parent)
{
    //Set properties
    setWindowFlags(Qt::Window |
                   Qt::FramelessWindowHint);
    setMinimumWidth(0);
    setMinimumHeight(0);

    //Set main layout
    mainLayout=new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    //Set title widget
    titleWidget=new KCMessageBoxTitle(this);
    mainLayout->addWidget(titleWidget);

    //Set content widget
    contentWidget=new KCMessageBoxContent(this);
    contentWidget->setVisible(false);
    mainLayout->addWidget(contentWidget, 1);

    //Set panel widget
    panelWidget=new KCMessageBoxPanel(this);
    mainLayout->addWidget(panelWidget);

    //Set animation variable
    widthExpand=new QPropertyAnimation(this, "geometry", this);
    widthExpand->setDuration(300);
}

void KCMessageBox::show()
{
    //Start width expand animation
    int originalX=parentWidget()->x()+parentWidget()->width()/2-width()/2;
    QRect startRect=QRect(originalX,
                          parentWidget()->y()+parentWidget()->height()/2-63,
                          width(),
                          127);
    QRect endRect=startRect;
    endRect.setX(originalX - 150);
    endRect.setWidth(300);
    widthExpand->setStartValue(startRect);
    widthExpand->setEndValue(endRect);
    QWidget::show();
    widthExpand->start();
    qDebug()<<endRect.left()<<startRect.left();
}

void KCMessageBox::addText(QString displayText)
{
    contentWidget->addText(displayText);
}

void KCMessageBox::setTitle(QString messageBoxTitle)
{
    titleWidget->setTitleText(messageBoxTitle);
}

