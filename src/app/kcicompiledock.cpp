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

    //Set Dock Widget and Layout.
    splCombine=new QSplitter(Qt::Horizontal, this);
    splCombine->setContentsMargins(0,0,0,0);

    //Set Text Output.
    compileOutput=new QPlainTextEdit(this);
    compileOutput->setContentsMargins(0,0,0,0);
    compileOutput->setWordWrapMode(QTextOption::NoWrap);
    splCombine->addWidget(compileOutput);

    //Set TreeView Controls.
    trevwCompileInfo=new QTreeView(this);
    trevwCompileInfo->setContentsMargins(0,0,0,0);
    pal=trevwCompileInfo->palette();
    pal.setColor(QPalette::WindowText,QColor(255,255,255));
    trevwCompileInfo->setPalette(pal);
    trevwCompileInfo->setHeaderHidden(true);
    trevwCompileInfo->setGeometry(0,0,0,0);
    compileInfo=new QStandardItemModel();
    trevwCompileInfo->setModel(compileInfo);
    trevwCompileInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    splCombine->addWidget(trevwCompileInfo);
    QList<int> l_sizes;
    l_sizes << width() << 0;
    splCombine->setSizes(l_sizes);

    //Set Default Value
    resetCompileDock();
    setWidget(splCombine);

    connect(trevwCompileInfo,SIGNAL(clicked(QModelIndex)),
            this,SLOT(selectAnError(QModelIndex)));
    connect(trevwCompileInfo,SIGNAL(activated(QModelIndex)),
            this,SLOT(selectAnError(QModelIndex)));
    connect(trevwCompileInfo,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(jumpToError(QModelIndex)));

}

void kcicompiledock::jumpToError(QModelIndex ItemID)
{
    int ErrID=ItemID.row();
    if(erifList[ErrID].nColumnNum>-1)
    {
        //Open the file;
        emit requireOpenErrFile(erifList[ErrID].strFilePath);
        //Jump to the line;
        emit requireGotoLine(erifList[ErrID].nLineNum - 1, erifList[ErrID].nColumnNum);
        //Set Focus;
        emit requireSetFocus();
    }
}

void kcicompiledock::selectAnError(QModelIndex ItemID)
{
    if(lastSelID>-1)
    {
        compileInfo->item(lastSelID)->setText(erifList[lastSelID].strErrDescription);
    }
    lastSelID=ItemID.row();
    if(erifList[lastSelID].nLineNum>-1)
    {
        QString strSelErrText;
        strSelErrText=erifList[lastSelID].strErrDescription + "\n" +
                tr("Line ") + QString::number(erifList[lastSelID].nLineNum) + tr(", ") +
                tr("Column ") + QString::number(erifList[lastSelID].nColumnNum) + tr(". ") + "\n" +
                tr("At file: ") + erifList[lastSelID].strFilePath;
        compileInfo->itemFromIndex(ItemID)->setText(strSelErrText);
    }
}

void kcicompiledock::animeShowError()
{
    QList<int> l_sizes_finish;
    int dockCompileWidth=this->width();
    dockCompileWidth/=5;
    l_sizes_finish << dockCompileWidth << this->width()-dockCompileWidth;
    splCombine->setSizes(l_sizes_finish);
}

void kcicompiledock::animeHideError()
{
    QList<int> l_sizes_finish;
    l_sizes_finish << width() << 0;
    splCombine->setSizes(l_sizes_finish);
}

void kcicompiledock::clearText()
{
    compileOutput->clear();
}

void kcicompiledock::addText(QString NewText)
{
    QTextDocument *document=compileOutput->document();
    QTextCursor text_cursor=QTextCursor(document);
    text_cursor.movePosition(QTextCursor::End);
    text_cursor.insertText(NewText);
}

void kcicompiledock::addRootItem(QString ItemText)
{
    QStandardItem *itemAdd=new QStandardItem(ItemText);
    compileInfo->appendRow(itemAdd);
}

void kcicompiledock::clearAllItem()
{
    compileInfo->clear();
}

void kcicompiledock::outputCompileInfo(QString msg)
{
    addText(msg);
}

void kcicompiledock::onCompileMsgReceived(ErrInfo error)
{
    if(!hasError)
    {
        animeShowError();
        addText(QTime::currentTime().toString("hh:mm:ss") +
                " " +
                tr("Compile Output:") +
                "\n");
        hasError=true;
    }

    erifList.append(error);
    addRootItem(error.strErrDescription);
}

void kcicompiledock::compileFinish(int ExitNum)
{
    qDebug()<<ExitNum;
    if(hasError)
    {
        //Output Error Num
        addText(QTime::currentTime().toString("hh:mm:ss") +
                " " + compileInfo->rowCount() +
                tr(" Errors Occur."));
    }
    else
    {
        //Output Compile Success.
        addText(QTime::currentTime().toString("hh:mm:ss") +
                " " + tr("Compile Successful."));
    }
}

void kcicompiledock::resetCompileDock()
{
    clearAllItem();
    clearText();
    strCompileFilePath="";
    hasError=false;
    ErrorOccur=false;
    WarningOccur=false;
    lastSelID=-1;
    erifList.clear();
}

void kcicompiledock::setCompileFilePath(QString FilePath)
{
    strCompileFilePath=FilePath;
}

QString kcicompiledock::CompileFilePath()
{
    return strCompileFilePath;
}
