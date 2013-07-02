#include "kcisearchtextbox.h"

kciSearchTextBox::kciSearchTextBox(QWidget *parent) :
    QWidget(parent)
{
    //Set Background Fill.
    setAutoFillBackground(true);

    //Palette Set.
    QPalette pal=this->palette();
    pal.setColor(QPalette::Window,QColor(255,255,255));
    setPalette(pal);

    //Set New Layout
    Layout=new QHBoxLayout(this);
    Layout->setContentsMargins(0,0,0,0);
    Layout->setSpacing(0);
    setLayout(Layout);

    //Set Icon PushButton
    SearchIcon=new QPushButton(this);
    SearchIcon->setIcon(QIcon(QString(":/img/image/SearchIcon.png")));
    SearchIcon->setFixedSize(24,24);
    SearchIcon->setContentsMargins(0,0,0,0);
    SearchIcon->setFlat(true);
    Layout->addWidget(SearchIcon);

    SearchTexts=new QLineEdit(this);
    SearchTexts->setFrame(false);
    SearchTexts->setPlaceholderText(QString(tr("Search")));

    Layout->addWidget(SearchTexts);
}

void kciSearchTextBox::setTheFocus()
{
    SearchTexts->setFocus();
}
