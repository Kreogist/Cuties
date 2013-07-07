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
    pal.setColor(QPalette::Foreground,QColor(255,255,255));
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
                tr("Line ") + QString::number(erifList[lastSelID].nLineNum) + ", " +
                tr("Column ") + QString::number(erifList[lastSelID].nColumnNum) + "\n" +
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

void kcicompiledock::parseMessage(QString msg)
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
    //Add Original Text To TextBox.
    addText(msg);

    //Process Msg:
    QString strJudgedStr=msg.left(2).toLower();
    if(strJudgedStr=="in" || strJudgedStr=="  ")
    {
        ErrInfo ThisErr;
        ThisErr.nColumnNum=-1;
        ThisErr.nLineNum=-1;
        ThisErr.strErrDescription=msg;
        ThisErr.strErrDescription=ThisErr.strErrDescription.remove(
                    ThisErr.strErrDescription.length()-1,1);
        ThisErr.strFilePath="";
        erifList.append(ThisErr);
        addRootItem(ThisErr.strErrDescription);
    }
    else
    {
        expressMsg=new QRegularExpression("(<command[ -]line>|([A-Za-z]:)?[^:]+):");
        QRegularExpressionMatch match=expressMsg->match(msg);
        if(match.hasMatch()){
            QString FileName=match.captured();
            int NewHead=FileName.length();
            FileName=FileName.remove(NewHead-1,1);
            QString ErrorDetailInfo=msg.mid(NewHead);
            ErrorDetailInfo.remove(ErrorDetailInfo.length()-1,1);
            expressMsg->setPattern("\\d+:\\d+");
            match=expressMsg->match(ErrorDetailInfo);
            if(match.hasMatch())
            {
                QString strErrPosition=match.captured();
                QStringList sltErrPos=strErrPosition.split(":");

                ErrInfo ThisErr;
                ThisErr.nLineNum=sltErrPos.at(0).toInt();
                ThisErr.nColumnNum=sltErrPos.at(1).toInt();
                ThisErr.strFilePath=FileName;
                ThisErr.strErrDescription=ErrorDetailInfo;
                erifList.append(ThisErr);
                addRootItem(ErrorDetailInfo);
            }

        }
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
