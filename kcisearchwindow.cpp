#include "kcisearchwindow.h"

kciSearchWindow::kciSearchWindow(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);
    setContentsMargins(7,7,7,7);
    setFixedSize(300,38);

    QPalette pal=this->palette();
    pal.setColor(QPalette::Background,QColor(0,0,0));
    setPalette(pal);

    //Set New Layout
    searchLayout=new QHBoxLayout(this);
    searchLayout->setContentsMargins(0,0,0,0);
    searchLayout->setSpacing(0);
    setLayout(searchLayout);

    searchText=new kciSearchTextBox(this);
    searchLayout->addWidget(searchText);
    searchLayout->addSpacing(3);

    //Set Up Button
    upButton=new QToolButton(this);
    pal=upButton->palette();
    pal.setColor(QPalette::Button,QColor(0,0,190));
    upButton->setPalette(pal);
    upButton->setIcon(QIcon(":/img/image/leftSearchButton.png"));
    upButton->setAutoRaise(true);
    upButton->setFixedSize(26,26);
    searchLayout->addWidget(upButton);
    //Set Down Button
    downButton=new QToolButton(this);
    downButton->setIcon(QIcon(":/img/image/rightSearchButton.png"));
    downButton->setAutoRaise(true);
    downButton->setFixedSize(26,26);
    downButton->setPalette(pal);
    searchLayout->addWidget(downButton);

    searchLayout->addSpacing(3);

    //Set Close Button
    closeButton=new QToolButton(this);
    closeButton->setIcon(QIcon(":/toolbutton/image/Close.png"));
    closeButton->setAutoRaise(true);
    closeButton->setFixedSize(16,26);
    //Set Button Palette
    pal=closeButton->palette();
    pal.setColor(QPalette::Button, QColor(190,0,0));
    closeButton->setPalette(pal);
    //Set Button Action
    connect(closeButton,SIGNAL(clicked()),
            this,SLOT(hide()));

    searchLayout->addWidget(closeButton);

    QGraphicsDropShadowEffect *wndShadow = new QGraphicsDropShadowEffect(this);
    wndShadow->setBlurRadius(15.0);
    wndShadow->setColor(QColor(0, 0, 0, 200));
    wndShadow->setOffset(0);
    this->setGraphicsEffect(wndShadow);

}

void kciSearchWindow::setDocument(QTextDocument *doc)
{
    searchText->setDocument(doc);
}

void kciSearchWindow::setTextFocus()
{
    searchText->setTheFocus();
}

void kciSearchWindow::hideEvent(QHideEvent *e)
{
    QWidget::hideEvent(e);
    emit hideButtonPressed();
}
