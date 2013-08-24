#include "kcisettinglistitembrowsetext.h"

kciSettingListItemBrowseText::kciSettingListItemBrowseText(QWidget *parent) :
    kciSettingListItemBase(parent)
{
    //New Layout Sets.
    MainLayout=new QHBoxLayout(this);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);
    setLayout(MainLayout);

    //Clear Item Value;
    ItemValue="";

    //Set Caption.
    MainLayout->addSpacing(5);
    MainLayout->addWidget(Caption);
    MainLayout->addSpacing(3);

    //Set Value Displayer.
    ValueDisplayer=new QLabel(this);
    MainLayout->addWidget(ValueDisplayer);

    //Set Text Editor.
    ValueEditor=new QLineEdit(this);
    ValueEditor->setEnabled(false);
    ValueEditor->hide();
    MainLayout->addWidget(ValueEditor,1);
    MainLayout->addSpacing(2);

    //Set Browse Folder.
    browseFolder=new QToolButton(this);
    browseFolder->setText(tr("Browse"));
    browseFolder->setEnabled(false);
    browseFolder->hide();
    MainLayout->addWidget(browseFolder);
    MainLayout->addSpacing(3);
    MainLayout->addStretch();

    folderMode=false;

    connect(browseFolder,SIGNAL(clicked()),
            this,SLOT(getFolderPath()));
}

bool kciSettingListItemBrowseText::getFolderMode() const
{
    return folderMode;
}

void kciSettingListItemBrowseText::setFolderMode(bool value)
{
    folderMode = value;
}

void kciSettingListItemBrowseText::setValue(const QString &NewTextValue)
{
    ItemValue=NewTextValue;
    ValueEditor->setText(ItemValue);
    ValueDisplayer->setText(ItemValue);
}

QString kciSettingListItemBrowseText::getValue()
{
    return ItemValue;
}

void kciSettingListItemBrowseText::mousePressEvent(QMouseEvent *e)
{
    ValueDisplayer->hide();
    ValueEditor->setEnabled(true);
    ValueEditor->show();
    browseFolder->setEnabled(true);
    browseFolder->show();
    e->accept();
}

void kciSettingListItemBrowseText::getFolderPath()
{
    QString newPath;
    if(folderMode)
    {
        newPath=QFileDialog::getExistingDirectory(this,
                                                  tr("Browse"),
                                                  ".");
    }
    else
    {
        newPath=QFileDialog::getOpenFileName(this,
                                             tr("Browse"),
                                             ".");
    }
    if(!newPath.isEmpty())
    {
        setValue(newPath);
    }
}
