#include "kcsettinglistitembrowsetext.h"

KCSettingListItemBrowseText::KCSettingListItemBrowseText(QWidget *parent) :
    KCSettingListItemBase(parent)
{
    //New Layout Sets.
    mainLayout=new QHBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    //Clear Item Value;
    itemValue="";

    //Set Caption.
    mainLayout->addSpacing(5);
    mainLayout->addWidget(captionText);
    mainLayout->addSpacing(3);

    //Set Value Displayer.
    valueDisplayer=new QLabel(this);
    mainLayout->addWidget(valueDisplayer);

    //Set Text Editor.
    valueEditor=new KCSettingControlLineEdit(this);
    valueEditor->setEnabled(false);
    valueEditor->hide();
    mainLayout->addWidget(valueEditor,1);
    mainLayout->addSpacing(2);

    //Set Browse Folder.
    browseFolder=new QToolButton(this);
    browseFolder->setText(tr("Browse"));
    browseFolder->setEnabled(false);
    browseFolder->hide();
    mainLayout->addWidget(browseFolder);
    mainLayout->addSpacing(3);
    mainLayout->addStretch();

    folderMode=false;
    editMode=false;

    connect(browseFolder,SIGNAL(clicked()),
            this, SLOT(setEditModeEnabled()));
    connect(valueEditor,SIGNAL(clicked()),
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
    itemValue=NewTextValue;
    valueEditor->setText(itemValue);
    valueDisplayer->setText(itemValue);
}

QString KCSettingListItemBrowseText::getValue()
{
    return itemValue;
}

void KCSettingListItemBrowseText::enterEvent(QEvent *e)
{
    if(!editMode)
    {
        valueDisplayer->hide();
        valueEditor->setEnabled(true);
        valueEditor->show();
        browseFolder->setEnabled(true);
        browseFolder->show();
    }
    KCSettingListItemBase::enterEvent(e);
}

void KCSettingListItemBrowseText::leaveEvent(QEvent *e)
{
    if(!editMode)
    {
        valueEditor->setEnabled(false);
        valueEditor->hide();
        browseFolder->setEnabled(false);
        browseFolder->hide();
        valueDisplayer->show();
    }
    KCSettingListItemBase::leaveEvent(e);
}

void KCSettingListItemBrowseText::setEditModeEnabled()
{
    editMode=true;
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
