#include "kcreplacewindow.h"

static int replaceWidgetsHeight=25;

KCReplaceWindow::KCReplaceWindow(QWidget *parent) :
    KCSearchWidget(parent)
{
    setObjectName("KCReplaceWindow");
    setContentsMargins(3,2,3,1);
    setMinimumHeight(0);
    setAutoFillBackground(true);

    QPalette pal=palette();
    KCColorConfigure::getInstance()->getPalette(pal,objectName());
    setPalette(pal);

    mapper=new QSignalMapper(this);

    mainLayout=(QGridLayout *)layout();
    mainLayout->setVerticalSpacing(2);

    replaceText=new QLineEdit(this);
    replaceText->setPlaceholderText(tr("Replace with"));
    replaceText->setFrame(false);
    replaceText->setFixedHeight(replaceWidgetsHeight);
    mainLayout->addWidget(replaceText,1,0,1,KCSearchWidget::searchTextPartWidth);

    replaceButtons[replace]=new QToolButton(this);
    replaceButtons[replace]->setText(tr("Replace"));
    replaceButtons[replace]->setAutoRaise(true);
    replaceButtons[replace]->setFixedHeight(replaceWidgetsHeight);
    mainLayout->addWidget(replaceButtons[replace],1,KCSearchWidget::searchTextPartWidth,1,2);

    replaceButtons[findAndReplace]=new QToolButton(this);
    replaceButtons[findAndReplace]->setText(tr("Find And Replace"));
    replaceButtons[findAndReplace]->setAutoRaise(true);
    replaceButtons[findAndReplace]->setFixedHeight(replaceWidgetsHeight);
    mainLayout->addWidget(replaceButtons[findAndReplace],1,KCSearchWidget::searchTextPartWidth+2,1,2);

    replaceButtons[replaceAll]=new QToolButton(this);
    replaceButtons[replaceAll]->setText(tr("Replace All"));
    replaceButtons[replaceAll]->setAutoRaise(true);
    replaceButtons[replaceAll]->setFixedHeight(replaceWidgetsHeight);
    mainLayout->addWidget(replaceButtons[replaceAll],1,KCSearchWidget::searchTextPartWidth+4,1,2);

    for(int i=0; i<typeCount; i++)
    {
        mapper->setMapping(replaceButtons[i],i);
        connect(replaceButtons[i],SIGNAL(clicked()),mapper,SLOT(map()));
    }
    connect(mapper,SIGNAL(mapped(int)),
            this,SLOT(onOneOfReplaceButtonsClicked(int)));

    //Set Close Button
    closeButton=new QToolButton(this);
    closeButton->setIcon(QIcon(":/toolbutton/image/Close.png"));
    closeButton->setAutoRaise(true);
    closeButton->setFixedSize(16,26);
    mainLayout->addWidget(closeButton,0,mainLayout->columnCount());

    //Set Button Palette
    pal=closeButton->palette();
    closeButton->setObjectName("KCReplaceWindowCloseButton");
    KCColorConfigure::getInstance()->getPalette(pal,closeButton->objectName());
    closeButton->setPalette(pal);
    //Set Button Action
    connect(closeButton, &QToolButton::clicked,
            this, &KCReplaceWindow::hideAnime);
    connect(this, &KCReplaceWindow::requireHide,
            this, &KCReplaceWindow::hideAnime);

    //Set Original Height.
    setFixedHeight(0);
}

void KCReplaceWindow::showAnime()
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

void KCReplaceWindow::resizeDock(int newHeight)
{
    setFixedHeight(newHeight);
}

void KCReplaceWindow::hideAnime()
{
    QTimeLine *hideAnimation=new QTimeLine(250, this);
    hideAnimation->setEasingCurve(QEasingCurve::OutCubic);
    hideAnimation->setStartFrame(61);
    hideAnimation->setEndFrame(0);
    connect(hideAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(resizeDock(int)));
    connect(hideAnimation, &QTimeLine::finished,
            this, &KCReplaceWindow::hide);
    hideAnimation->start();
}

void KCReplaceWindow::onOneOfReplaceButtonsClicked(int type)
{
    QString newText=replaceText->text(),
            oldText=text();
    switch(type)
    {
    case replace:
        emit requireReplace(oldText,newText);
        break;
    case findAndReplace:
        emit requireReplaceAndFind(oldText,newText);
        break;
    case replaceAll:
        emit requireReplaceAll(oldText,newText);
        break;
    default:
        qDebug()<<"unknow replace button type!";
    }
}
