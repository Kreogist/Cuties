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


#include "kcisearchwindow.h"

static const int nFixedWidth=290;

kciSearchWindow::kciSearchWindow(QWidget *parent) :
    QWidget(parent)
{
    //--------TextBox Init-----------------
    searchText=new QWidget(this);
    //Set Background Fill.
    searchText->setAutoFillBackground(true);

    //Palette Set.
    QPalette pal=searchText->palette();
    pal.setColor(QPalette::Window,QColor(255,255,255));
    pal.setColor(QPalette::Base,QColor(255,255,255));
    pal.setColor(QPalette::Text,QColor(0,0,0));
    pal.setColor(QPalette::WindowText,QColor(50,50,50));
    searchText->setPalette(pal);

    //Set New Layout
    Layout=new QHBoxLayout(searchText);
    Layout->setContentsMargins(0,0,0,0);
    Layout->setSpacing(0);
    searchText->setLayout(Layout);

    //Set Icon PushButton
    SearchIcon=new QPushButton(searchText);
    SearchIcon->setIcon(QIcon(QString(":/img/image/SearchIcon.png")));
    SearchIcon->setFixedSize(24,24);
    SearchIcon->setContentsMargins(0,0,0,0);
    SearchIcon->setFlat(true);
    Layout->addWidget(SearchIcon);

    SearchTexts=new QLineEdit(searchText);
    SearchTexts->setFrame(false);
    SearchTexts->setPlaceholderText(QString(tr("Search")));
    connect(SearchTexts,SIGNAL(textChanged(QString)),
            this,SLOT(onTextChanged(QString)));

    //Init menu
    menu=new QMenu(searchText);
    menuAction[menuRegularExpress]=menu->addAction(tr("Regular Expression"));
    menuAction[menuMatchCase]=menu->addAction(tr("Match Case"));
    menuAction[menuWholeWord]=menu->addAction(tr("Match whole word"));

    for(int i=0;i<menuItemCount;i++)
    {
        menuAction[i]->setCheckable(true);
        connect(menuAction[i],SIGNAL(triggered()),
                this,SLOT(onMenuClicked()));
    }

    SearchIcon->setMenu(menu);

    Layout->addWidget(SearchTexts);

    //--------Search Window Init-------------
    setAutoFillBackground(true);
    setContentsMargins(7,7,7,7);

    QPalette kswPal=this->palette();
    kswPal.setColor(QPalette::Window,QColor(0,0,0));
    setPalette(kswPal);

    //Set New Layout
    searchLayout=new QHBoxLayout(this);
    searchLayout->setContentsMargins(0,0,0,0);
    searchLayout->setSpacing(0);
    setLayout(searchLayout);

    searchLayout->addWidget(searchText);
    searchLayout->addSpacing(3);

    //Set Search Details.
    setFixedSize(nFixedWidth,38);

    //Set Up Button
    upButton=new QToolButton(this);
    pal=upButton->palette();
    pal.setColor(QPalette::Button,QColor(0,0,190));
    upButton->setPalette(pal);
    upButton->setIcon(QIcon(":/img/image/leftSearchButton.png"));
    upButton->setAutoRaise(true);
    upButton->setFixedSize(26,26);
    searchLayout->addWidget(upButton);
    connect(upButton,SIGNAL(clicked()),this,SIGNAL(requireShowPreviousResult()));
    //Set Down Button
    downButton=new QToolButton(this);
    downButton->setIcon(QIcon(":/img/image/rightSearchButton.png"));
    downButton->setAutoRaise(true);
    downButton->setFixedSize(26,26);
    downButton->setPalette(pal);
    searchLayout->addWidget(downButton);
    connect(downButton,SIGNAL(clicked()),this,SIGNAL(requireShowNextResult()));

    searchLayout->addSpacing(3);

    //Set Close Button
    closeButton=new QToolButton(this);
    closeButton->setIcon(QIcon(":/toolbutton/image/Close.png"));
    closeButton->setAutoRaise(true);
    closeButton->setFixedSize(16,26);
    //Set Button Palette
    pal=closeButton->palette();
    pal.setColor(QPalette::Button, QColor(190,0,0));
    closeButton->setPalette(pal);
    //Set Button Action
    connect(closeButton, SIGNAL(clicked()),
            this, SIGNAL(hideButtonPressed()));

    searchLayout->addWidget(closeButton);

    QGraphicsDropShadowEffect *wndShadow = new QGraphicsDropShadowEffect(this);
    wndShadow->setBlurRadius(15.0);
    wndShadow->setColor(QColor(0, 0, 0, 200));
    wndShadow->setOffset(0);
    this->setGraphicsEffect(wndShadow);
}

void kciSearchWindow::setText(const QString &text)
{
    SearchTexts->setText(text);
}

void kciSearchWindow::onTextChanged(const QString &text)
{
    bool Regexp=menuAction[menuRegularExpress]->isChecked();
    bool MatchCase=menuAction[menuMatchCase]->isChecked();
    bool WholeWord=menuAction[menuWholeWord]->isChecked();

    emit requireSearch(text,Regexp,MatchCase,WholeWord);
}

void kciSearchWindow::onMenuClicked()
{
    onTextChanged(SearchTexts->text());
}

void kciSearchWindow::setTextFocus()
{
    SearchTexts->setFocus();
}

void kciSearchWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Escape:
        emit hideButtonPressed();
    default:
        QWidget::keyPressEvent(event);
    }
}
