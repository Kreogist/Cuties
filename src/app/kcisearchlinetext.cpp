#include "kcisearchlinetext.h"

kciSearchLineText::kciSearchLineText(QWidget *parent) :
    QWidget(parent)
{
    //Set Main Layout.
    MainLayout=new QHBoxLayout(this);
    setLayout(MainLayout);
    //Set Line Edit.
    searchTextBox=new QLineEdit(this);
    MainLayout->addWidget(searchTextBox);
}
