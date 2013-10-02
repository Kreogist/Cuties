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

#include "kccompiledock.h"

KCCompiledock::KCCompiledock(QWidget *parent):
    QDockWidget(parent)
{
    //Set compile dock properties
    setObjectName(QString("Compile Dock"));
    setWindowTitle(QString(tr("Compiler")));
    setContentsMargins(0,0,0,0);
    setAllowedAreas(Qt::BottomDockWidgetArea);

    //Set compile dock palette
    QPalette pal=this->palette();
    pal.setColor(QPalette::Base,QColor(0x35,0x35,0x35));
    pal.setColor(QPalette::WindowText,QColor(255,255,255));
    pal.setColor(QPalette::Button,QColor(83,83,83));
    pal.setColor(QPalette::Text,QColor(255,255,255));
    pal.setColor(QPalette::ButtonText,QColor(255,255,255));
    this->setPalette(pal);

    //Set compile info splitter widget
    compileOutputInfoSplitter=new QSplitter(Qt::Horizontal, this);
    compileOutputInfoSplitter->setContentsMargins(0,0,0,0);
    //Set text output widget
    compileOutputTextInfo=new KCPlainTextBrowser(this);
    compileOutputTextInfo->setContentsMargins(0,0,0,0);
    compileOutputTextInfo->setMinimumWidth(0);
    compileOutputTextInfo->setWordWrapMode(QTextOption::NoWrap);
    compileOutputInfoSplitter->addWidget(compileOutputTextInfo);
    //Set treeview output widget
    compileOutputErrorInfoTree=new QTreeView(this);
    compileOutputErrorInfoTree->setContentsMargins(0,0,0,0);
    compileOutputErrorInfoTree->setMinimumWidth(0);
    compileOutputErrorInfoTree->setRootIsDecorated(false);
    compileOutputErrorInfoTree->setHeaderHidden(true);
    compileOutputErrorInfoTree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    pal=compileOutputErrorInfoTree->palette();
    pal.setColor(QPalette::WindowText,QColor(255,255,255));
    compileOutputErrorInfoTree->setPalette(pal);
    compileOutputInfoSplitter->addWidget(compileOutputErrorInfoTree);
    //Set splitter width
    QList<int> splitterWidgetSize;
    splitterWidgetSize << width() << 0;
    compileOutputInfoSplitter->setSizes(splitterWidgetSize);
    //Set splitter widget
    setWidget(compileOutputInfoSplitter);

    //Set error info treeview widget show/hide animation timeline
    animeShowErrorInfoTree=new QTimeLine(400,this);
    animeShowErrorInfoTree->setEasingCurve(QEasingCurve::OutCubic);
    connect(animeShowErrorInfoTree, SIGNAL(frameChanged(int)),
            this, SLOT(changeCompileSplitterWidthValue(int)));
    animeHideErrorInfoTree=new QTimeLine(400,this);
    animeHideErrorInfoTree->setEasingCurve(QEasingCurve::OutCubic);
    connect(animeHideErrorInfoTree, SIGNAL(frameChanged(int)),
            this, SLOT(changeCompileSplitterWidthValue(int)));

    //Connect signals and slots.
    connect(compileOutputErrorInfoTree,SIGNAL(clicked(QModelIndex)),
            this,SLOT(selectAnError(QModelIndex)));
    connect(compileOutputErrorInfoTree,SIGNAL(activated(QModelIndex)),
            this,SLOT(selectAnError(QModelIndex)));
    connect(compileOutputErrorInfoTree,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(jumpToError(QModelIndex)));

}

//Get the root item of model.
static inline QModelIndex getRootItem(QModelIndex item)
{
    while(item.parent().isValid())
    {
        item=item.parent();
    }
    return item;
}

//When user select an error, this slot function will get the info of the
//error. If the file has been closed, we will emit a signal to open the file.
//Then jump to line where the error occur.
void KCCompiledock::jumpToError(QModelIndex ItemID)
{
    ItemID=getRootItem(ItemID);

    int ErrID=ItemID.row();

    if(compileErrorInfoList->at(ErrID).nColumnNum>-1)
    {
        //Open the file;
        emit requireOpenErrFile(compileErrorInfoList->at(ErrID).strFilePath);
        //Jump to the line;
        emit requireGotoLine(compileErrorInfoList->at(ErrID).nLineNum - 1,
                             compileErrorInfoList->at(ErrID).nColumnNum);
        //Set Focus;
        emit requireSetFocus();
    }
}

void KCCompiledock::selectAnError(QModelIndex ItemIndex)
{
    ItemIndex=getRootItem(ItemIndex);

    if(ItemIndex!=lastSelIndex)
    {
        compileOutputErrorInfoTree->collapse(lastSelIndex);
        compileOutputErrorInfoTree->expand(ItemIndex);
    }

    lastSelIndex=ItemIndex;
}

//Animation of showing compile error info tree
void KCCompiledock::animeShowCompileError()
{
    animeHideErrorInfoTree->stop();
    if(animeShowErrorInfoTree->state()!=QTimeLine::Running)
    {
        compileOutputTextInfo->setFocus();
        animeShowErrorInfoTree->setFrameRange(compileOutputErrorInfoTree->width(), (width()/5)*4);
        animeShowErrorInfoTree->start();
    }
}

//Animation of hiding compile error info tree
void KCCompiledock::animeHideCompileError()
{
    animeShowErrorInfoTree->stop();
    if(animeHideErrorInfoTree->state()!=QTimeLine::Running)
    {
        animeHideErrorInfoTree->setFrameRange(compileOutputErrorInfoTree->width(), 0);
        animeHideErrorInfoTree->start();
    }
}

//This slot is used to change the value of splitter,
//QPropertyAnimation can't do this for me, so I use QTimeLine to show up the QTreeView.
//Calculate the width for each required, save the value into a QList, and set it to the QSplitter.
void KCCompiledock::changeCompileSplitterWidthValue(int newCompileTreeWidth)
{
    QList<int> splitterWidgetSize;
    splitterWidgetSize << width() - newCompileTreeWidth << newCompileTreeWidth;
    compileOutputInfoSplitter->setSizes(splitterWidgetSize);
}

//Set receiver.
void KCCompiledock::setCompileOutputReceiver(const KCCompileOutputReceiver *currReceiver)
{
    Q_ASSERT(currReceiver!=NULL);

    receiverConnectionHandles.disConnectAll();

    compileErrorInfoList=currReceiver->getCompileErrorInfoList();
    compileOutputTextInfo->setPlainText(currReceiver->getCompilerOutputText());
    compileOutputErrorInfoTree->setModel(currReceiver->getCompilerOutputModel());
    receiverConnectionHandles+=connect(currReceiver, SIGNAL(requireShowError()),
                                       this, SLOT(animeShowCompileError()));
    receiverConnectionHandles+=connect(currReceiver,SIGNAL(compilerOutputTextChanged(QString)),
                                       compileOutputTextInfo,SLOT(setPlainText(QString)));
}
