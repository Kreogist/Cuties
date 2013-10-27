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

#include "kccolorconfigure.h"

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
