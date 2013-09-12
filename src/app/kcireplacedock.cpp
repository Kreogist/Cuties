#include "kcireplacedock.h"

kciReplaceDock::kciReplaceDock(QWidget *parent) :
    QWidget(parent)
{
    setMinimumHeight(0);

    QPalette pal=this->palette();
    pal.setColor(QPalette::Base,QColor(255,255,255));
    pal.setColor(QPalette::WindowText,QColor(0,0,0));
    pal.setColor(QPalette::Button,QColor(83,83,83));
    pal.setColor(QPalette::Text,QColor(0,0,0));
    pal.setColor(QPalette::ButtonText,QColor(255,255,255));
    this->setPalette(pal);

    mainLayout=new QVBoxLayout(this);
    mainLayout->setContentsMargins(4,4,4,4);
    mainLayout->setSpacing(2);
    setLayout(mainLayout);

    searchLayout=new QHBoxLayout();
    searchLayout->setContentsMargins(0,0,0,0);
    searchLayout->setSpacing(0);

    //--------TextBox Init-----------------
    searchText=new QWidget(this);
    //Set Background Fill.
    searchText->setAutoFillBackground(true);

    //Palette Set.
    pal=searchText->palette();
    pal.setColor(QPalette::Window,QColor(255,255,255));
    pal.setColor(QPalette::Base,QColor(255,255,255));
    pal.setColor(QPalette::Text,QColor(0,0,0));
    pal.setColor(QPalette::WindowText,QColor(50,50,50));
    pal.setColor(QPalette::Button, QColor(255,255,255));
    searchText->setPalette(pal);

    //Set New Layout
    Layout=new QHBoxLayout(searchText);
    Layout->setContentsMargins(0,0,0,0);
    Layout->setSpacing(0);
    searchText->setLayout(Layout);

    //Set Icon PushButton
    SearchIcon=new QPushButton(searchText);
    SearchIcon->setIcon(QIcon(QString(":/img/image/SearchIcon.png")));
    SearchIcon->setFixedSize(24,24);
    SearchIcon->setContentsMargins(0,0,0,0);
    SearchIcon->setFlat(true);

    Layout->addWidget(SearchIcon);

    SearchTexts=new QLineEdit(searchText);
    SearchTexts->setFrame(false);
    SearchTexts->setPlaceholderText(QString(tr("Search")));
    //connect(SearchTexts,SIGNAL(textChanged(QString)),this,SLOT(onTextChanged(QString)));

    //Init menu
    menu=new QMenu(searchText);
    menuAction[menuRegularExpress]=menu->addAction(tr("Regular Expression"));
    menuAction[menuMatchCase]=menu->addAction(tr("Match Case"));
    menuAction[menuWholeWord]=menu->addAction(tr("Match whole word"));

    for(int i=0;i<menuItemCount;i++)
    {
        menuAction[i]->setCheckable(true);
        //connect(menuAction[i],SIGNAL(triggered()),this,SLOT(onMenuClicked()));
    }

    SearchIcon->setMenu(menu);

    Layout->addWidget(SearchTexts);
    searchLayout->addWidget(searchText);

    //Set Up Button
    upButton=new QToolButton(this);
    pal=upButton->palette();
    pal.setColor(QPalette::Button,QColor(0,0,190));
    upButton->setPalette(pal);
    upButton->setIcon(QIcon(":/img/image/leftSearchButton.png"));
    upButton->setAutoRaise(true);
    upButton->setFixedSize(26,26);
    searchLayout->addWidget(upButton);
    //connect(upButton,SIGNAL(clicked()),this,SIGNAL(requireShowPreviousResult()));
    //Set Down Button
    downButton=new QToolButton(this);
    downButton->setIcon(QIcon(":/img/image/rightSearchButton.png"));
    downButton->setAutoRaise(true);
    downButton->setFixedSize(26,26);
    downButton->setPalette(pal);
    searchLayout->addWidget(downButton);
    //connect(downButton,SIGNAL(clicked()),this,SIGNAL(requireShowNextResult()));
    searchLayout->addStretch();

    //Set Close Button
    closeButton=new QToolButton(this);
    closeButton->setIcon(QIcon(":/toolbutton/image/Close.png"));
    closeButton->setAutoRaise(true);
    closeButton->setFixedSize(16,26);
    //Set Button Palette
    pal=closeButton->palette();
    pal.setColor(QPalette::Button, QColor(190,0,0));
    closeButton->setPalette(pal);
    connect(closeButton, &QToolButton::clicked,
            this, &kciReplaceDock::hideAnime);
    searchLayout->addWidget(closeButton);

    mainLayout->addLayout(searchLayout);

    replaceLayout=new QHBoxLayout();
    replaceLayout->setContentsMargins(0,0,0,0);
    replaceLayout->setSpacing(0);

    replaceText=new QLineEdit(this);
    replaceText->setPlaceholderText(tr("Replace with"));
    replaceText->setFrame(false);
    replaceText->setFixedHeight(25);
    replaceLayout->addWidget(replaceText, 1);

    replaceButton=new QToolButton(this);
    replaceButton->setText(tr("Replace"));
    replaceButton->setAutoRaise(true);
    replaceButton->setFixedHeight(25);
    replaceLayout->addWidget(replaceButton);

    findAndReplaceButton=new QToolButton(this);
    findAndReplaceButton->setText(tr("Find And Replace"));
    findAndReplaceButton->setAutoRaise(true);
    findAndReplaceButton->setFixedHeight(25);
    replaceLayout->addWidget(findAndReplaceButton);

    replaceAllButton=new QToolButton(this);
    replaceAllButton->setText(tr("Replace All"));
    replaceAllButton->setAutoRaise(true);
    replaceAllButton->setFixedHeight(25);
    replaceLayout->addWidget(replaceAllButton);
    replaceLayout->addStretch();

    mainLayout->addLayout(replaceLayout);

    //Set Original Height.
    setFixedHeight(0);
}

kciReplaceDock::~kciReplaceDock()
{
    searchLayout->deleteLater();
    replaceLayout->deleteLater();
}

void kciReplaceDock::resizeEvent(QResizeEvent *event)
{
    int newWidth=event->size().width() / 2;
    searchText->setFixedWidth(newWidth);
    replaceText->setFixedWidth(newWidth);
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
