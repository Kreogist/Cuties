/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *      Wang Luming <wlm199558@126.com>
 *      Miyanaga Saki <tomguts@126.com>
 *      Zhang Jiayi <bf109g2@126.com>
 *
 *  This file is part of Kreogist-Cute-IDE.
 *
 *    Kreogist-Cute-IDE is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cute-IDE is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cute-IDE.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "kcijudgedock.h"

kciJudgeFileEdit::kciJudgeFileEdit(QWidget *parent) :
    QWidget(parent)
{
    lblInput=new QLabel(tr("Input File:"),this);
    lblOutput=new QLabel(tr("Output File:"),this);
    lblUserOutput=new QLabel(tr("Execute Output:"),this);
    InputFileEdit=new QPlainTextEdit(this);
    OutputFileEdit=new QPlainTextEdit(this);
    UserOutput=new QPlainTextEdit(this);

    EditLayout=new QVBoxLayout(this);
    EditLayout->setContentsMargins(0,0,0,0);
    EditLayout->addWidget(lblInput);
    EditLayout->addWidget(InputFileEdit);
    EditLayout->addWidget(lblOutput);
    EditLayout->addWidget(OutputFileEdit);
    EditLayout->addWidget(lblUserOutput);
    EditLayout->addWidget(UserOutput);
}

kciJudgeEditWidget::kciJudgeEditWidget(QWidget *parent) :
    QWidget(parent)
{
    MainLayout=new QVBoxLayout(this);
    setLayout(MainLayout);

    //Set Judge Files Tab.
    tabJudgeFiles=new QTabWidget(this);

    QPalette pal=tabJudgeFiles->palette();
    pal.setColor(QPalette::HighlightedText, QColor(255,255,255));
    tabJudgeFiles->setPalette(pal);

    tabJudgeFiles->setDocumentMode(true);
    tabJudgeFiles->setMovable(true);
    tabJudgeFiles->setTabsClosable(true);
    tabJudgeFiles->setTabPosition(QTabWidget::South);

    MainLayout->addWidget(tabJudgeFiles);

    //Set ToolBar Action
    tlbacAdd=new QToolButton(this);
    tlbacAdd->setText(tr("Add Test Data."));
    tlbacAdd->setFixedSize(23,23);
    tlbacAdd->setIcon(QIcon(":/JudgeToolBar/image/Judge Dock/ToolBarAdd.png"));
    connect(tlbacAdd,SIGNAL(clicked()),this,SLOT(addNewTab()));
    tlbacRemove=new QToolButton(this);
    tlbacRemove->setText(tr("Remove Test Data."));
    tlbacRemove->setFixedSize(23,23);
    tlbacRemove->setIcon(QIcon(":/JudgeToolBar/image/Judge Dock/ToolBarRemove.png"));
    tlbacStartAll=new QToolButton(this);
    tlbacStartAll->setText(tr("Start All Test."));
    tlbacStartAll->setFixedSize(23,23);
    tlbacStartAll->setIcon(QIcon(":/JudgeToolBar/image/Judge Dock/ToolBarStartAll.png"));
    tlbacStop=new QToolButton(this);
    tlbacStop->setText(tr("Stop the test."));
    tlbacStop->setFixedSize(23,23);
    tlbacStop->setIcon(QIcon(":/JudgeToolBar/image/Judge Dock/ToolBarStop.png"));

    //Set Judge Tool Bar
    tlbJudge=new QToolBar("judgetbl",this);
    tlbJudge->setContentsMargins(0,0,0,0);

    tlbJudge->addWidget(tlbacAdd);
    tlbJudge->addWidget(tlbacRemove);
    tlbJudge->addWidget(tlbacStartAll);
    tlbJudge->addWidget(tlbacStop);
    MainLayout->addWidget(tlbJudge);

}

void kciJudgeEditWidget::addNewTab()
{
    //Set new content.
    kciJudgeFileEdit *newJudgeEdit = new kciJudgeFileEdit(this);
    tabJudgeFiles->addTab(newJudgeEdit,"Test");
}

kciJudgeDock::kciJudgeDock(QWidget *parent) :
    QDockWidget(parent)
{
    //Set Object Name.
    setObjectName(QString("Judge Dock"));

    //Set Dock Style.
    setContentsMargins(0,0,0,0);
    QPalette pal=this->palette();
    pal.setColor(QPalette::Base,QColor(0x35,0x35,0x35));
    pal.setColor(QPalette::WindowText,QColor(255,255,255));
    pal.setColor(QPalette::Button,QColor(83,83,83));
    pal.setColor(QPalette::Text,QColor(255,255,255));
    pal.setColor(QPalette::ButtonText,QColor(255,255,255));
    this->setPalette(pal);
    setWindowTitle(QString(tr("Judge")));
    setAllowedAreas(Qt::RightDockWidgetArea);

    //Set Main Split.
    splCombine=new QSplitter(Qt::Vertical,this);
    splCombine->setContentsMargins(0,0,0,0);

    //Set Judge Edit Widget
    kjwEditWidget=new kciJudgeEditWidget(this);
    splCombine->addWidget(kjwEditWidget);

    //Set Judge List
    trevwJudgeList=new QTreeView(this);
    trevwJudgeList->setContentsMargins(0,0,0,0);
    pal=trevwJudgeList->palette();
    pal.setColor(QPalette::WindowText,QColor(255,255,255));
    trevwJudgeList->setPalette(pal);
    splCombine->addWidget(trevwJudgeList);

    //Init Widget Height.
    l_sizes << height() << 0;
    splCombine->setSizes(l_sizes);

    //Set Widget
    setWidget(splCombine);
}
