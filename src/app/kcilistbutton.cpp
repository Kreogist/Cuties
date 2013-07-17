#include "kcilistbutton.h"

kciListButton::kciListButton(QWidget *parent) :
    QWidget(parent)
{
    lblButtonText=new QLabel(this);
    mLayout=new QHBoxLayout();
    setLayout(mLayout);

    mLayout->addWidget(lblButtonText);
}
