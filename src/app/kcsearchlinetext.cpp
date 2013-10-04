#include "kcsearchlinetext.h"

KCSearchLineText::KCSearchLineText(QWidget *parent) :
    QWidget(parent)
{
    setObjectName("KCSearchLineText");
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);
    setFixedHeight(26);

    //Palette Set.
    QPalette pal=this->palette();
    KCColorConfigure::getInstance()->getPalette(pal,objectName());
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
