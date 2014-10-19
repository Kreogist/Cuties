/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist Cuties.
 *
 *    Kreogist Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "kccolorconfigure.h"
#include "kclanguageconfigure.h"

#include "kcsearchlinetext.h"

KCSearchLineText::KCSearchLineText(QWidget *parent) :
    QWidget(parent)
{
    retranslate();
    setObjectName("KCSearchLineText");
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);
    setFixedHeight(26);

    //Palette Set.
    QPalette pal=this->palette();
    KCColorConfigure::getInstance()->getPalette(pal,objectName());
    setPalette(pal);

    //Set Main Layout.
    searchLayout=new QHBoxLayout(this);
    searchLayout->setContentsMargins(0,0,0,0);
    searchLayout->setSpacing(0);
    setLayout(searchLayout);
    //Set Icon.
    searchIconImage=new QLabel(this);
    searchIconImage->setPixmap(QPixmap(":/img/image/SearchIcon.png"));
    searchLayout->addSpacing(2);
    searchLayout->addWidget(searchIconImage);
    //Set Line Edit.
    searchTextBox=new QLineEdit(this);
    searchTextBox->setFrame(false);
    searchTextBox->setPlaceholderText(placeHolderText);
    searchLayout->addWidget(searchTextBox);

    connect(KCLanguageConfigure::getInstance(), &KCLanguageConfigure::newLanguageSet,
            this, &KCSearchLineText::retranslateAndSet);
}

void KCSearchLineText::retranslate()
{
    placeHolderText=tr("Search");
}

void KCSearchLineText::retranslateAndSet()
{
    retranslate();
    searchTextBox->setPlaceholderText(placeHolderText);
}
