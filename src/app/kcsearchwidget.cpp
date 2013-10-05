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

#include "kcsearchwidget.h"

const int KCSearchWidget::searchTextPartWidth=3;

KCSearchWidget::KCSearchWidget(QWidget *parent) :
    QWidget(parent)
{
    setObjectName("KCSearchWidget");
    setAutoFillBackground(true);
    setContentsMargins(7,7,7,7);
    lastSearchText="";

    searchText=new QWidget(this);
    //Set Background Fill.
    searchText->setAutoFillBackground(true);

    //Palette Set.
    QPalette pal=searchText->palette();
    KCColorConfigure::getInstance()->getPalette(pal,objectName());
    searchText->setPalette(pal);

    //Set New Layout
    mainLayout=new QHBoxLayout(searchText);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    searchText->setLayout(mainLayout);

    //Set Icon PushButton
    searchIcon=new QPushButton(searchText);
    searchIcon->setIcon(QIcon(QString(":/img/image/SearchIcon.png")));
    searchIcon->setFixedSize(24,24);
    searchIcon->setContentsMargins(0,0,0,0);
    searchIcon->setFlat(true);
    mainLayout->addWidget(searchIcon);

    searchTexts=new QLineEdit(searchText);
    searchTexts->setFrame(false);
    searchTexts->setPlaceholderText(QString(tr("Search")));
    connect(searchTexts, &QLineEdit::textChanged,
            this, &KCSearchWidget::onTextChanged);

    //Init menu
    menu=new QMenu(searchText);
    menuAction[menuRegularExpress]=menu->addAction(tr("Regular Expression"));
    menuAction[menuMatchCase]=menu->addAction(tr("Match Case"));
    menuAction[menuWholeWord]=menu->addAction(tr("Match whole word"));

    for(int i=0; i<menuItemCount; i++)
    {
        menuAction[i]->setCheckable(true);
        connect(menuAction[i],SIGNAL(triggered()),
                this,SLOT(onMenuClicked()));
    }
    searchIcon->setMenu(menu);

    mainLayout->addWidget(searchTexts);

    //Set New Layout
    searchLayout=new QGridLayout(this);
    searchLayout->setContentsMargins(0,0,0,0);
    searchLayout->setSpacing(0);
    setLayout(searchLayout);

    searchLayout->addWidget(searchText,0,0,1,searchTextPartWidth);
    searchLayout->setHorizontalSpacing(3);

    //Set Up Button
    upButton=new QToolButton(this);
    upButton->setObjectName("KCSearchWidgetUpButton");
    pal=upButton->palette();
    KCColorConfigure::getInstance()->getPalette(pal,upButton->objectName());
    upButton->setPalette(pal);
    upButton->setIcon(QIcon(":/img/image/leftSearchButton.png"));
    upButton->setAutoRaise(true);
    upButton->setFixedSize(26,26);
    searchLayout->addWidget(upButton,0,3);
    connect(upButton,SIGNAL(clicked()),this,SIGNAL(requireShowPreviousResult()));
    //Set Down Button
    downButton=new QToolButton(this);
    downButton->setObjectName("KCSearchWidgetDownButton");
    downButton->setIcon(QIcon(":/img/image/rightSearchButton.png"));
    downButton->setAutoRaise(true);
    downButton->setFixedSize(26,26);
    KCColorConfigure::getInstance()->getPalette(pal,downButton->objectName());
    downButton->setPalette(pal);
    searchLayout->addWidget(downButton,0,4);
    connect(downButton, &QToolButton::clicked,
            this, &KCSearchWidget::requireShowNextResult);
}

QString KCSearchWidget::text() const
{
    return searchTexts->text();
}

void KCSearchWidget::restoreLastSearchText()
{
    searchTexts->setText(lastSearchText);
}

void KCSearchWidget::onTextChanged(const QString &text)
{
    emit requireSearch(text,
                       menuAction[menuRegularExpress]->isChecked(),
                       menuAction[menuMatchCase]->isChecked(),
                       menuAction[menuWholeWord]->isChecked());
}

void KCSearchWidget::onMenuClicked()
{
    onTextChanged(searchTexts->text());
}

void KCSearchWidget::setText(const QString &text)
{
    searchTexts->setText(text);
}

void KCSearchWidget::setTextFocus()
{
    searchTexts->setFocus();
}

void KCSearchWidget::resizeEvent(QResizeEvent *event)
{
    searchTexts->setFixedWidth(event->size().width());
}

void KCSearchWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        lastSearchText=searchTexts->text();
        searchTexts->setText("");
        emit requireHide();
    default:
        QWidget::keyPressEvent(event);
    }
}
