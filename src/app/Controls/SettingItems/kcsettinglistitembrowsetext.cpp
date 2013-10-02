#include "kcsettinglistitembrowsetext.h"

KCSettingListItemBrowseText::KCSettingListItemBrowseText(QWidget *parent) :
    KCSettingListItemBase(parent)
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
    blnEditMode=false;

    connect(browseFolder,SIGNAL(clicked()),
            this, SLOT(setEditModeEnabled()));
    connect(ValueEditor,SIGNAL(textChanged(QString)),
            this, SLOT(setEditModeEnabled()));
    connect(browseFolder,SIGNAL(clicked()),
            this,SLOT(getFolderPath()));
}

bool KCSettingListItemBrowseText::getFolderMode() const
{
    return folderMode;
}

void KCSettingListItemBrowseText::setFolderMode(bool value)
{
    folderMode = value;
}

void KCSettingListItemBrowseText::setValue(const QString &NewTextValue)
{
    ItemValue=NewTextValue;
    ValueEditor->setText(ItemValue);
    ValueDisplayer->setText(ItemValue);
}

QString KCSettingListItemBrowseText::getValue()
{
    return ItemValue;
}

void KCSettingListItemBrowseText::enterEvent(QEvent *e)
{
    if(!blnEditMode)
    {
        ValueDisplayer->hide();
        ValueEditor->setEnabled(true);
        ValueEditor->show();
        browseFolder->setEnabled(true);
        browseFolder->show();
    }
    KCSettingListItemBase::enterEvent(e);
}

void KCSettingListItemBrowseText::leaveEvent(QEvent *e)
{
    if(!blnEditMode)
    {
        ValueEditor->setEnabled(false);
        ValueEditor->hide();
        browseFolder->setEnabled(false);
        browseFolder->hide();
        ValueDisplayer->show();
    }
    KCSettingListItemBase::leaveEvent(e);
}

void KCSettingListItemBrowseText::setEditModeEnabled()
{
    blnEditMode=true;
}

void KCSettingListItemBrowseText::mousePressEvent(QMouseEvent *e)
{
    setEditModeEnabled();
    KCSettingListItemBase::mousePressEvent(e);
}

void KCSettingListItemBrowseText::getFolderPath()
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
