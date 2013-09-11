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

    mainLayout->addWidget(searchText);

    replaceText=new QLineEdit(this);
    replaceText->setPlaceholderText(tr("Replace with"));
    replaceText->setFrame(false);
    replaceText->setFixedHeight(25);
    mainLayout->addWidget(replaceText);
}
