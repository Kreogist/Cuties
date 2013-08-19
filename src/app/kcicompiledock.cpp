/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *      Wang Luming <wlm199558@126.com>
 *      Miyanaga Saki <tomguts@126.com>
 *      Zhang Jiayi <bf109g2@126.com>
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

#include "kcicompiledock.h"

kcicompiledock::kcicompiledock(QWidget *parent):
    QDockWidget(parent)
{
    //Set Object Name.
    setObjectName(QString("Compile Dock"));

    //Set Dock Style.
    setContentsMargins(0,0,0,0);
    QPalette pal=this->palette();
    pal.setColor(QPalette::Base,QColor(0x35,0x35,0x35));
    pal.setColor(QPalette::WindowText,QColor(255,255,255));
    pal.setColor(QPalette::Button,QColor(83,83,83));
    pal.setColor(QPalette::Text,QColor(255,255,255));
    pal.setColor(QPalette::ButtonText,QColor(255,255,255));
    this->setPalette(pal);
    setWindowTitle(QString(tr("Compiler")));
    setAllowedAreas(Qt::BottomDockWidgetArea);

    //Set Time Lines:
    animeShowTimeLine=new QTimeLine(400,this);
    animeShowTimeLine->setEasingCurve(QEasingCurve::OutCubic);
    connect(animeShowTimeLine, SIGNAL(frameChanged(int)),
            this, SLOT(changeDockCompileWidth(int)));

    animeHideTimeLine=new QTimeLine(400,this);
    animeHideTimeLine->setEasingCurve(QEasingCurve::OutCubic);
    connect(animeHideTimeLine, SIGNAL(frameChanged(int)),
            this, SLOT(changeDockCompileWidth(int)));

    //Set Dock Widget and Layout.
    splCombine=new QSplitter(Qt::Horizontal, this);
    splCombine->setContentsMargins(0,0,0,0);

    //Set Text Output.
    compileOutput=new kciPlainTextBrowser(this);
    compileOutput->setContentsMargins(0,0,0,0);
    compileOutput->setWordWrapMode(QTextOption::NoWrap);
    compileOutput->setMinimumWidth(1);
    splCombine->addWidget(compileOutput);

    //Set TreeView Controls.
    trevwCompileInfo=new QTreeView(this);
    trevwCompileInfo->setRootIsDecorated(false);
    trevwCompileInfo->setContentsMargins(0,0,0,0);
    pal=trevwCompileInfo->palette();
    pal.setColor(QPalette::WindowText,QColor(255,255,255));
    trevwCompileInfo->setPalette(pal);
    trevwCompileInfo->setHeaderHidden(true);
    trevwCompileInfo->setGeometry(0,0,0,0);
    trevwCompileInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    trevwCompileInfo->setMinimumWidth(1);
    splCombine->addWidget(trevwCompileInfo);
    QList<int> l_sizes;
    l_sizes << width() << 0;
    splCombine->setSizes(l_sizes);

    //Set Default Value
    setWidget(splCombine);

    connect(trevwCompileInfo,SIGNAL(clicked(QModelIndex)),
            this,SLOT(selectAnError(QModelIndex)));
    connect(trevwCompileInfo,SIGNAL(activated(QModelIndex)),
            this,SLOT(selectAnError(QModelIndex)));
    connect(trevwCompileInfo,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(jumpToError(QModelIndex)));

}

static inline QModelIndex getRootItem(QModelIndex item)
{
    while(item.parent().isValid())
    {
        item=item.parent();
    }
    return item;
}

void kcicompiledock::jumpToError(QModelIndex ItemID)
{
    ItemID=getRootItem(ItemID);

    int ErrID=ItemID.row();

    if(erifList->at(ErrID).nColumnNum>-1)
    {
        //Open the file;
        emit requireOpenErrFile(erifList->at(ErrID).strFilePath);
        //Jump to the line;
        emit requireGotoLine(erifList->at(ErrID).nLineNum - 1,
                             erifList->at(ErrID).nColumnNum);
        //Set Focus;
        emit requireSetFocus();
    }
}

void kcicompiledock::selectAnError(QModelIndex ItemIndex)
{
    ItemIndex=getRootItem(ItemIndex);

    if(ItemIndex!=lastSelIndex)
    {
        trevwCompileInfo->collapse(lastSelIndex);
        trevwCompileInfo->expand(ItemIndex);
    }

    lastSelIndex=ItemIndex;
}

void kcicompiledock::animeShowError()
{
    animeHideTimeLine->stop();
    if(animeShowTimeLine->state()!=QTimeLine::Running)
    {
        animeShowTimeLine->setFrameRange(compileOutput->width(), int(width()/5));
        animeShowTimeLine->start();
    }
}

void kcicompiledock::animeHideError()
{
    animeShowTimeLine->stop();
    if(animeHideTimeLine->state()!=QTimeLine::Running)
    {
        animeHideTimeLine->setFrameRange(compileOutput->width(), width());
        animeHideTimeLine->start();
    }
}

void kcicompiledock::changeDockCompileWidth(int dockCompileWidth)
{
    QList<int> l_sizes_finish;
    l_sizes_finish << dockCompileWidth << width() - dockCompileWidth;
    splCombine->setSizes(l_sizes_finish);
}

void kcicompiledock::setReceiver(const compileOutputReceiver *currReceiver)
{
    Q_ASSERT(currReceiver!=NULL);

    receiverConnectionHandles.disConnectAll();

    erifList=currReceiver->getErifList();
    compileOutput->setPlainText(currReceiver->getCompilerOutputText());
    trevwCompileInfo->setModel(currReceiver->getCompilerOutputModel());
    receiverConnectionHandles+=connect(currReceiver, SIGNAL(requireShowError()),
                                       this, SLOT(animeShowError()));
    receiverConnectionHandles+=connect(currReceiver,SIGNAL(compilerOutputTextChanged(QString)),
                                       compileOutput,SLOT(setPlainText(QString)));
}
