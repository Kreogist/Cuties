/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist-Cuties.
 *
 *    Kreogist-Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "kcpreferenceitempath.h"

KCPreferenceItemPath::KCPreferenceItemPath(QWidget *parent) :
    KCPreferenceItemBase(parent)
{
    //Set properties
    setFixedHeight(45);
    foldAnimation->setEndFrame(45);
    showAnimation->setEndFrame(45);

    //Set language
    retranslate();

    //Set Edit Mode Layout
    editLayout=new QVBoxLayout(this);
    editLayout->setContentsMargins(5,5,5,5);
    editLayout->setSpacing(3);
    setLayout(editLayout);

    pathCaption=new QLabel(this);
    editLayout->addWidget(pathCaption);
    editLayout->addWidget(valueDisplayer);
    editLayout->addWidget(originalValueDisplayer);

    pathLayout=new QHBoxLayout();
    pathLayout->setContentsMargins(0,0,0,0);
    pathLayout->setSpacing(0);

    filePathData=new QLineEdit(this);
    browseFileAction=new QPushButton(this);
    browseFileAction->setText(browseText);
    setEditWidgetStatus(false);
    pathLayout->addWidget(filePathData, 1);
    pathLayout->addWidget(browseFileAction);

    editLayout->addLayout(pathLayout);
    editLayout->addStretch();

    guaranteeFileExsist=false;

    connect(browseFileAction, SIGNAL(clicked()),
            this, SLOT(getFilePath()));

    setExpandFinishedHeight(70);

    connect(KCLanguageConfigure::getInstance(), &KCLanguageConfigure::newLanguageSet,
            this, &KCPreferenceItemPath::retranslateAndSet);
}

KCPreferenceItemPath::~KCPreferenceItemPath()
{
    pathLayout->deleteLater();
}

void KCPreferenceItemPath::setOriginalValue(const QVariant &value)
{
    filePathData->setText(value.toString());
    KCPreferenceItemBase::setOriginalValue(value);
    valueDisplayer->setText(value.toString());
    setOriginalDisplayVisible(false);
    connect(filePathData, SIGNAL(textChanged(QString)),
            this, SLOT(valueChangedEvent()));
}

void KCPreferenceItemPath::setPathText(const QString &value)
{
    pathText = value;
}

void KCPreferenceItemPath::setPathCaptionText(const QString &value)
{
    pathCaption->setText(value);
}

void KCPreferenceItemPath::setDialogTitle(const QString &newDialogTitle)
{
    dialogTitleText=newDialogTitle;
}

void KCPreferenceItemPath::retranslate()
{
    browseText=tr("Browse");
}

void KCPreferenceItemPath::retranslateAndSet()
{
    retranslate();
}

void KCPreferenceItemPath::heightState(bool newState)
{
    if(newState)
    {
        setFixedHeight(45);
        show();
    }
    else
    {
        setFixedHeight(0);
        hide();
    }
}

void KCPreferenceItemPath::setEditWidgetStatus(bool states)
{
    filePathData->setVisible(states);
    filePathData->setEnabled(states);
    browseFileAction->setVisible(states);
    browseFileAction->setEnabled(states);
}

void KCPreferenceItemPath::setWidgetValue(QVariant newWidgeValue)
{
    filePathData->setText(newWidgeValue.toString());
}

void KCPreferenceItemPath::getFilePath()
{
    QString newItemPath,
            defaultBrowsePath;
    QFileInfo currentfileInfo;
    currentfileInfo.setFile(getCurrentValue().toString());
    defaultBrowsePath=currentfileInfo.exists()?
                      currentfileInfo.absoluteDir().absolutePath():
                      ".";

    QFileDialog getItemPath(this);
    if(guaranteeFileExsist)
    {
        getItemPath.setFileMode(QFileDialog::ExistingFile);
    }
    newItemPath=getItemPath.getOpenFileName(this,
                                            dialogTitleText,
                                            defaultBrowsePath);
    if(!newItemPath.isEmpty())
    {
        setWidgetValue(newItemPath);
    }
}

bool KCPreferenceItemPath::getGuaranteeFileExsist() const
{
    return guaranteeFileExsist;
}

void KCPreferenceItemPath::setGuaranteeFileExsist(bool value)
{
    guaranteeFileExsist = value;
}


QVariant KCPreferenceItemPath::getUserNewValue()
{
    return filePathData->text();
}

void KCPreferenceItemPath::refreshValueDisplay()
{
    valueDisplayer->setText(filePathData->text());
    if(valueDisplayer->text() == originalValue.toString())
    {
        setOriginalDisplayVisible(false);
        //Here, we have to set some values
        setExpandFinishedHeight(70);
        setFixedHeight(70);
        foldAnimation->setEndFrame(45);
        showAnimation->setEndFrame(45);
        return;
    }
    originalValueDisplayer->setText(originalValueIs +
                                    originalValue.toString());
    //Some value:
    setExpandFinishedHeight(90);
    setFixedHeight(90);
    foldAnimation->setEndFrame(63);
    showAnimation->setEndFrame(63);
    setOriginalDisplayVisible(true);
}
