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

#include "kcsearchwidget.h"

const int KCSearchWidget::searchTextPartWidth=3;


KCSearchTextBox::KCSearchTextBox(QWidget *parent) :
    QLineEdit(parent)
{
    ;
}

void KCSearchTextBox::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        emit requireSearchNext();
        return;
    case Qt::Key_Escape:
        emit requireLostFocus();
        return;
    }
    QLineEdit::keyPressEvent(e);
}

KCSearchWidget::KCSearchWidget(QWidget *parent) :
    QWidget(parent)
{
    //Set properties.
    setObjectName("KCSearchWidget");
    setAutoFillBackground(true);
    setContentsMargins(7,7,7,7);
    lastSearchText="";

    //Combined search textbox.
    searchTextWidget=new QWidget(this);
    //Set Background Fill.
    searchTextWidget->setAutoFillBackground(true);
    //Palette Set.
    QPalette pal=searchTextWidget->palette();
    KCColorConfigure::getInstance()->getPalette(pal,objectName());
    searchTextWidget->setPalette(pal);
    //Set New Layout
    mainLayout=new QHBoxLayout(searchTextWidget);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    searchTextWidget->setLayout(mainLayout);
    //Set Icon PushButton
    searchIcon=new QPushButton(searchTextWidget);
    searchIcon->setIcon(QIcon(QString(":/img/image/SearchIcon.png")));
    searchIcon->setFixedSize(24,24);
    searchIcon->setContentsMargins(0,0,0,0);
    searchIcon->setFlat(true);
    mainLayout->addWidget(searchIcon);
    //Set Text Input box
    searchText=new KCSearchTextBox(searchTextWidget);
    searchText->setFrame(false);
    searchText->setPlaceholderText(QString(tr("Search")));
    connect(searchText, &KCSearchTextBox::textChanged,
            this, &KCSearchWidget::onTextChanged);
    //Init search option menu
    menu=new QMenu(searchTextWidget);
    menuAction[menuRegularExpress]=menu->addAction(tr("Regular Expression"));
    menuAction[menuMatchCase]=menu->addAction(tr("Match Case"));
    menuAction[menuWholeWord]=menu->addAction(tr("Match whole word"));
    //Set Actions
    for(int i=0; i<menuItemCount; i++)
    {
        menuAction[i]->setCheckable(true);
        connect(menuAction[i],SIGNAL(triggered()),
                this,SLOT(onMenuClicked()));
    }
    searchIcon->setMenu(menu);
    mainLayout->addWidget(searchText);

    //Set New Layout
    searchLayout=new QGridLayout(this);
    searchLayout->setContentsMargins(0,0,0,0);
    searchLayout->setSpacing(0);
    setLayout(searchLayout);
    searchLayout->addWidget(searchTextWidget,0,0,1,searchTextPartWidth);
    searchLayout->setHorizontalSpacing(3);

    //Set Up Button
    prevResult=new QToolButton(this);
    prevResult->setObjectName("KCSearchWidgetUpButton");
    prevResult->setIcon(QIcon(":/img/image/leftSearchButton.png"));
    prevResult->setAutoRaise(true);
    prevResult->setFixedSize(26,26);
    KCColorConfigure::getInstance()->getPalette(pal,prevResult->objectName());
    prevResult->setPalette(pal);
    searchLayout->addWidget(prevResult,0,3);
    connect(prevResult,SIGNAL(clicked()),
            this,SIGNAL(requireShowPreviousResult()));
    //Set Down Button
    nextResult=new QToolButton(this);
    nextResult->setObjectName("KCSearchWidgetDownButton");
    nextResult->setIcon(QIcon(":/img/image/rightSearchButton.png"));
    nextResult->setAutoRaise(true);
    nextResult->setFixedSize(26,26);
    KCColorConfigure::getInstance()->getPalette(pal,nextResult->objectName());
    nextResult->setPalette(pal);
    searchLayout->addWidget(nextResult,0,4);
    connect(searchText, &KCSearchTextBox::requireSearchNext,
            this, &KCSearchWidget::requireShowNextResult);
    connect(nextResult, &QToolButton::clicked,
            this, &KCSearchWidget::requireShowNextResult);
    connect(searchText, &KCSearchTextBox::requireLostFocus,
            this, &KCSearchWidget::requireLostFocus);
}

QString KCSearchWidget::text() const
{
    return searchText->text();
}

void KCSearchWidget::restoreLastSearchText()
{
    searchText->setText(lastSearchText);
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
    onTextChanged(searchText->text());
}

void KCSearchWidget::setResultMatchStyle()
{
    ;
}

void KCSearchWidget::setResultUnmatchStyle()
{
    ;
}

void KCSearchWidget::setText(const QString &text)
{
    searchText->setText(text);
}

void KCSearchWidget::setTextFocus()
{
    searchText->setFocus();
}

void KCSearchWidget::resizeEvent(QResizeEvent *event)
{
    searchText->setFixedWidth(event->size().width());
}
bool KCSearchWidget::getConnected() const
{
    return connected;
}

void KCSearchWidget::setConnected(bool value)
{
    connected = value;
}

