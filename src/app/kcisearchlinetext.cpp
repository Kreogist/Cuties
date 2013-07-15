#include "kcisearchlinetext.h"

kciSearchLineText::kciSearchLineText(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);
    setFixedHeight(26);

    //Palette Set.
    QPalette pal=this->palette();
    pal.setColor(QPalette::Window,QColor(255,255,255));
    pal.setColor(QPalette::Base,QColor(255,255,255));
    pal.setColor(QPalette::Text,QColor(0,0,0));
    pal.setColor(QPalette::WindowText,QColor(50,50,50));
    setPalette(pal);

    //Set Main Layout.
    MainLayout=new QHBoxLayout(this);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);
    setLayout(MainLayout);
    //Set Icon.
    lblImage=new QLabel(this);
    lblImage->setPixmap(QPixmap(":/img/image/SearchIcon.png"));
    MainLayout->addSpacing(2);
    MainLayout->addWidget(lblImage);
    //Set Line Edit.
    searchTextBox=new QLineEdit(this);
    searchTextBox->setFrame(false);
    searchTextBox->setPlaceholderText(tr("Search"));
    MainLayout->addWidget(searchTextBox);
}
