#include "kcfiletype.h"

KCFileType::KCFileType(QWidget *parent) :
    QWidget(parent)
{
    //Set Widget Margins.
    setContentsMargins(0,0,0,0);

    //Set Palette
    QPalette pal = palette();
    pal.setColor(QPalette::Base,QColor(0x38,0x38,0x38));
    pal.setColor(QPalette::Text,QColor(255,255,255));
    pal.setColor(QPalette::Button,QColor(83,83,83));
    setPalette(pal);

    //Set Main Layout.
    mainLayout=new QHBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    //Add File Type.
    fileType=new QComboBox(this);
    pal=fileType->palette();
    pal.setColor(QPalette::ButtonText,QColor(255,255,255));
    fileType->setPalette(pal);
    fileType->setAttribute(Qt::WA_NoBackground,true);
    fileType->addItem(tr("Plain Text"));
    fileType->addItem(tr("C/C++"));
    fileType->addItem(tr("Pascal"));

    //Add ComboBox to layout.
    mainLayout->addWidget(fileType);
}
