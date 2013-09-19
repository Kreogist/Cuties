#include "kcireplacedock.h"

static int replaceWidgetsHeight=25;

kciReplaceDock::kciReplaceDock(QWidget *parent) :
    kciSearchWidget(parent)
{
    setMinimumHeight(0);
    setAutoFillBackground(true);

    QPalette pal=palette();
    pal.setColor(QPalette::Window,QColor(128,128,128));
    pal.setColor(QPalette::Base,QColor(255,255,255));
    pal.setColor(QPalette::WindowText,QColor(0,0,0));
    pal.setColor(QPalette::Button,QColor(83,83,83));
    pal.setColor(QPalette::Text,QColor(0,0,0));
    pal.setColor(QPalette::ButtonText,QColor(255,255,255));
    setPalette(pal);

    mainLayout=(QGridLayout*)layout();

    replaceText=new QLineEdit(this);
    replaceText->setPlaceholderText(tr("Replace with"));
    replaceText->setFrame(false);
    replaceText->setFixedHeight(replaceWidgetsHeight);
    mainLayout->addWidget(replaceText,1,0,1,kciSearchWidget::searchTextPartWidth);

    replaceButton=new QToolButton(this);
    replaceButton->setText(tr("Replace"));
    replaceButton->setAutoRaise(true);
    replaceButton->setFixedHeight(replaceWidgetsHeight);
    mainLayout->addWidget(replaceButton,1,kciSearchWidget::searchTextPartWidth,1,2);

    findAndReplaceButton=new QToolButton(this);
    findAndReplaceButton->setText(tr("Find And Replace"));
    findAndReplaceButton->setAutoRaise(true);
    findAndReplaceButton->setFixedHeight(replaceWidgetsHeight);
    mainLayout->addWidget(findAndReplaceButton,1,kciSearchWidget::searchTextPartWidth+2,1,2);

    replaceAllButton=new QToolButton(this);
    replaceAllButton->setText(tr("Replace All"));
    replaceAllButton->setAutoRaise(true);
    replaceAllButton->setFixedHeight(replaceWidgetsHeight);
    mainLayout->addWidget(replaceAllButton,1,kciSearchWidget::searchTextPartWidth+4,1,2);

    //Set Close Button
    closeButton=new QToolButton(this);
    closeButton->setIcon(QIcon(":/toolbutton/image/Close.png"));
    closeButton->setAutoRaise(true);
    closeButton->setFixedSize(16,26);
    mainLayout->addWidget(closeButton,0,mainLayout->columnCount());

    //Set Button Palette
    pal=closeButton->palette();
    pal.setColor(QPalette::Button, QColor(190,0,0));
    closeButton->setPalette(pal);
    //Set Button Action
    connect(closeButton, SIGNAL(clicked()),
            this, SLOT(hideAnime()));

    //Set Original Height.
    setFixedHeight(0);
}

void kciReplaceDock::showAnime()
{
    QTimeLine *showAnimation=new QTimeLine(250, this);
    showAnimation->setEasingCurve(QEasingCurve::OutCubic);
    showAnimation->setStartFrame(0);
    showAnimation->setEndFrame(61);
    connect(showAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(resizeDock(int)));
    this->show();
    showAnimation->start();
}

void kciReplaceDock::resizeDock(int newHeight)
{
    setFixedHeight(newHeight);
}

void kciReplaceDock::hideAnime()
{
    QTimeLine *hideAnimation=new QTimeLine(250, this);
    hideAnimation->setEasingCurve(QEasingCurve::OutCubic);
    hideAnimation->setStartFrame(61);
    hideAnimation->setEndFrame(0);
    connect(hideAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(resizeDock(int)));
    connect(hideAnimation, SIGNAL(finished()),
            this, SLOT(hide()));
    hideAnimation->start();
}
