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

#include "kcjudgedock.h"

KCJudgeFileEdit::KCJudgeFileEdit(QWidget *parent) :
    QWidget(parent)
{
    lblInput=new QLabel(tr("Input File:"),this);
    lblOutput=new QLabel(tr("Output File:"),this);
    lblUserOutput=new QLabel(tr("Execute Output:"),this);
    InputFileEdit=new QPlainTextEdit(this);
    connect(InputFileEdit,SIGNAL(textChanged()),this,SIGNAL(textChange()));
    OutputFileEdit=new QPlainTextEdit(this);
    connect(OutputFileEdit,SIGNAL(textChanged()),this,SIGNAL(textChange()));
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

QString KCJudgeFileEdit::inputFile()
{
    return InputFileEdit->toPlainText();
}

QString KCJudgeFileEdit::outputFile()
{
    return OutputFileEdit->toPlainText();
}

KCIJudgeEditWidget::KCIJudgeEditWidget(QWidget *parent) :
    QWidget(parent)
{
    MainLayout=new QVBoxLayout(this);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);
    setLayout(MainLayout);

    //Set Judge Files Tab.
    tabJudgeFiles=new QTabWidget(this);

    QPalette pal=tabJudgeFiles->palette();
    pal.setColor(QPalette::HighlightedText, QColor(255,255,255));
    tabJudgeFiles->setPalette(pal);

    tabJudgeFiles->setContentsMargins(0,0,0,0);
    tabJudgeFiles->setDocumentMode(true);
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
    connect(tlbacRemove,SIGNAL(clicked()),this,SLOT(removeCurrentTab()));
    tlbacStartAll=new QToolButton(this);
    tlbacStartAll->setText(tr("Start All Test."));
    tlbacStartAll->setFixedSize(23,23);
    tlbacStartAll->setIcon(QIcon(":/JudgeToolBar/image/Judge Dock/ToolBarStartAll.png"));
    tlbacStop=new QToolButton(this);
    tlbacStop->setText(tr("Stop the test."));
    tlbacStop->setFixedSize(23,23);
    tlbacStop->setIcon(QIcon(":/JudgeToolBar/image/Judge Dock/ToolBarStop.png"));
    tlbacBackup=new QToolButton(this);
    tlbacBackup->setText(tr("Save the test data."));
    tlbacBackup->setFixedSize(23,23);
    tlbacBackup->setIcon(QIcon(":/JudgeToolBar/image/Judge Dock/ToolBarBackup.png"));
    tlbacImport=new QToolButton(this);
    tlbacImport->setText(tr("Import a test data backup file."));
    tlbacImport->setFixedSize(23,23);
    tlbacImport->setIcon(QIcon(":/JudgeToolBar/image/Judge Dock/ToolBarImport.png"));

    //Set Judge Tool Bar
    tlbJudge=new QToolBar("judgetbl",this);
    tlbJudge->setContentsMargins(0,0,0,0);

    tlbJudge->addWidget(tlbacAdd);
    tlbJudge->addWidget(tlbacRemove);
    tlbJudge->addSeparator();
    tlbJudge->addWidget(tlbacStartAll);
    tlbJudge->addWidget(tlbacStop);
    tlbJudge->addSeparator();
    tlbJudge->addWidget(tlbacBackup);
    tlbJudge->addWidget(tlbacImport);
    MainLayout->addWidget(tlbJudge);

    resetJudgetEditWidget();
}

void KCIJudgeEditWidget::backupTestData()
{

}

void KCIJudgeEditWidget::importTestData()
{

}

void KCIJudgeEditWidget::documentChanged()
{
    KCJudgeFileEdit *Editor=qobject_cast<KCJudgeFileEdit *>(sender());
    if(Editor!=NULL)
    {
        int nFilesIndex=tabJudgeFiles->indexOf(Editor);
        strInputFiles.replace(nFilesIndex, Editor->inputFile());
        strOutputFiles.replace(nFilesIndex, Editor->outputFile());
    }
}

void KCIJudgeEditWidget::resetJudgetEditWidget()
{
    //Remove all tabs.
    int i=tabJudgeFiles->count();
    while(i--)
    {
        removeTabIndex(i);
    }
    //Clear Cache.
    strInputFiles.clear();
    strOutputFiles.clear();
}

void KCIJudgeEditWidget::removeTabIndex(int TabIndex)
{
    //Remove Tab.
    KCJudgeFileEdit *JudgeEditor=qobject_cast<KCJudgeFileEdit *>(tabJudgeFiles->widget(TabIndex));
    if(Q_LIKELY(JudgeEditor!=NULL))
    {
        tabJudgeFiles->removeTab(TabIndex);
    }
    //Remove Memory.
    strInputFiles.removeAt(TabIndex);
    strOutputFiles.removeAt(TabIndex);
    //Reset Tab Num.
    int tabMax=tabJudgeFiles->count();
    for(int i=TabIndex; i<tabMax; i++)
    {
        tabJudgeFiles->setTabText(i,QString::number(i+1));
    }
}

void KCIJudgeEditWidget::removeCurrentTab()
{
    removeTabIndex(tabJudgeFiles->currentIndex());
}

void KCIJudgeEditWidget::addNewTab()
{
    //Set New Tab Content.
    KCJudgeFileEdit *newJudgeEdit = new KCJudgeFileEdit(this);
    tabJudgeFiles->addTab(newJudgeEdit,QString::number(tabJudgeFiles->count()+1));
    connect(newJudgeEdit,SIGNAL(textChange()),this,SLOT(documentChanged()));
    //Set List Memory.
    strInputFiles.append(QString(""));
    strOutputFiles.append(QString(""));

}

KCIJudgeDock::KCIJudgeDock(QWidget *parent) :
    QDockWidget(parent)
{
    //Set Object Name.
    setObjectName(QString("Judge Dock"));

    //Set Dock Style.
    setContentsMargins(0,0,0,0);
    QPalette pal=this->palette();
    pal.setBrush(QPalette::Window, QBrush(QColor(83,83,83)));
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
    kjwEditWidget=new KCIJudgeEditWidget(this);
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
