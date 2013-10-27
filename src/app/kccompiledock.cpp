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

#include <QTreeView>
#include <QPalette>
#include <QSplitter>
#include <QList>
#include <QTimeLine>

#include <QDebug>

#include "kcplaintextbrowser.h"
#include "kccompileoutputreceiver.h"
#include "kccolorconfigure.h"

#include "kccompiledock.h"

KCCompileDock::KCCompileDock(QWidget *parent):
    QDockWidget(parent)
{

    //Set compile dock properties
    setAutoFillBackground(true);
    setObjectName(QString("Compile Dock"));
    setWindowTitle(QString(tr("Compiler")));
    setContentsMargins(0,0,0,0);
    setAllowedAreas(Qt::BottomDockWidgetArea);

    //Set compile dock palette
    QPalette pal=palette();
    KCColorConfigure::getInstance()->getPalette(pal,objectName());
    pal.setColor(QPalette::Window, QColor(0x53, 0x53, 0x53));
    setPalette(pal);

    //Set compile info splitter widget
    compileOutputInfoSplitter=new QSplitter(Qt::Horizontal, this);
    compileOutputInfoSplitter->setContentsMargins(0,0,0,0);
    compileOutputInfoSplitter->setAutoFillBackground(true);
    pal=compileOutputInfoSplitter->palette();
    pal.setColor(QPalette::Base, QColor(0x35, 0x35, 0x35));
    pal.setColor(QPalette::Button, QColor(0x53, 0x53, 0x53));
    pal.setColor(QPalette::ButtonText, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::Text, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::WindowText, QColor(0xff, 0xff, 0xff));
    compileOutputInfoSplitter->setPalette(pal);
    //Set text output widget
    compileOutputTextInfo=new KCPlainTextBrowser(this);
    compileOutputTextInfo->setContentsMargins(0,0,0,0);
    compileOutputTextInfo->setMinimumWidth(0);
    compileOutputTextInfo->setWordWrapMode(QTextOption::NoWrap);
    compileOutputInfoSplitter->addWidget(compileOutputTextInfo);
    //Set treeview output widget
    compileOutputErrorInfoTree=new QTreeView(this);
    compileOutputErrorInfoTree->setObjectName("compileOutputErrorInfoTree");
    compileOutputErrorInfoTree->setContentsMargins(0,0,0,0);
    compileOutputErrorInfoTree->setMinimumWidth(0);
    compileOutputErrorInfoTree->setRootIsDecorated(false);
    compileOutputErrorInfoTree->setHeaderHidden(true);
    compileOutputErrorInfoTree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    pal=compileOutputErrorInfoTree->palette();
    KCColorConfigure::getInstance()->registerColorInfo(QPalette::WindowText,QColor(255,255,255),compileOutputErrorInfoTree->objectName());
    KCColorConfigure::getInstance()->getPalette(pal,compileOutputErrorInfoTree->objectName());
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
    connect(compileOutputErrorInfoTree, &QTreeView::clicked,
            this, &KCCompileDock::displayErrorDetails);
    connect(compileOutputErrorInfoTree, &QTreeView::activated,
            this, &KCCompileDock::jumpToError);
}

//When user select an error, this slot function will get the info of the
//error. If the file has been closed, we will emit a signal to open the file.
//Then jump to line where the error occur.
void KCCompileDock::jumpToError(QModelIndex currentErrorItemIndex)
{
    int indexCurrentError=currentErrorItemIndex.row();
    if(compileErrorInfoList->at(indexCurrentError).errorLine>-1)
    {
        //Open the file;
        emit requireOpenErrFile(compileErrorInfoList->at(indexCurrentError).errorFilePath);
        //Jump to the line;
        if(compileErrorInfoList->at(indexCurrentError).errorColumn > -1)
        {
            emit requireGotoLine(compileErrorInfoList->at(indexCurrentError).errorLine - 1,
                                 compileErrorInfoList->at(indexCurrentError).errorColumn);
        }
        else
        {
            emit requireGotoLine(compileErrorInfoList->at(indexCurrentError).errorLine - 1,
                                 0);
        }
        //Set focus to the current documents;
        emit requireSetFocus();
    }
}

//When user select an error, the treeview widget will display the details
//of the compiler error from the model.
void KCCompileDock::displayErrorDetails(QModelIndex errorItemIndex)
{
    //If there is an item has been expanded, just fold it.
    //Please notice to check whether the last selection is valid. (not -1)
    if(lastSelectionIndex != -1 && errorItemIndex.row()!=lastSelectionIndex)
    {
        currentReceiver->foldItem(currentReceiver->getCompilerOutputModel()->item(lastSelectionIndex));
    }
    //Set the last selection index to the current selection.
    lastSelectionIndex=errorItemIndex.row();
    //Expand the current selection
    currentReceiver->expandItem(currentReceiver->getCompilerOutputModel()->item(lastSelectionIndex));
}

//Animation of showing compile error info tree
void KCCompileDock::animeShowCompileError()
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
void KCCompileDock::animeHideCompileError()
{
    animeShowErrorInfoTree->stop();
    if(animeHideErrorInfoTree->state()!=QTimeLine::Running)
    {
        animeHideErrorInfoTree->setFrameRange(compileOutputErrorInfoTree->width(), 0);
        animeHideErrorInfoTree->start();
    }
}

void KCCompileDock::hideCompileDock()
{
    setVisible(false);
}

void KCCompileDock::setFloat()
{
    setFloating(true);
}

//This slot is used to change the value of splitter,
//QPropertyAnimation can't do this for me, so I use QTimeLine to show up the QTreeView.
//Calculate the width for each required, save the value into a QList, and set it to the QSplitter.
void KCCompileDock::changeCompileSplitterWidthValue(int newCompileTreeWidth)
{
    QList<int> splitterWidgetSize;
    splitterWidgetSize << width() - newCompileTreeWidth << newCompileTreeWidth;
    compileOutputInfoSplitter->setSizes(splitterWidgetSize);
}

//Set receiver.
void KCCompileDock::setCompileOutputReceiver(KCCompileOutputReceiver *newReceiver)
{
    Q_ASSERT(newReceiver!=NULL);
    //Disconnect the old connections.
    receiverConnectionHandles.disConnectAll();

    //Set the receiver pointer to the new receiver.
    currentReceiver=newReceiver;
    //Reset
    lastSelectionIndex=-1;
    //Set models.
    compileErrorInfoList=currentReceiver->getCompileErrorInfoList();
    compileOutputTextInfo->setPlainText(currentReceiver->getCompilerOutputText());
    compileOutputErrorInfoTree->setModel(currentReceiver->getCompilerOutputModel());
    //Connet signals and slots
    receiverConnectionHandles+=connect(currentReceiver, &KCCompileOutputReceiver::requireShowError,
                                       this, &KCCompileDock::animeShowCompileError);
    receiverConnectionHandles+=connect(currentReceiver, &KCCompileOutputReceiver::compilerOutputTextChanged,
                                       compileOutputTextInfo, &KCPlainTextBrowser::setPlainText);
}
