#include "compileoutputreceiver.h"

compileOutputReceiver::compileOutputReceiver(QObject *parent) :
    QObject(parent)
{
    compilerOutputModel=new QStandardItemModel(this);
    compilerOutputText=new QTextDocument(this);

    plainTextLayout=new QPlainTextDocumentLayout(compilerOutputText);
    compilerOutputText->setDocumentLayout(plainTextLayout);
}

QTextDocument *compileOutputReceiver::getCompilerOutputText() const
{
    return compilerOutputText;
}

QStandardItemModel *compileOutputReceiver::getCompilerOutputModel() const
{
    return compilerOutputModel;
}

void compileOutputReceiver::clearText()
{
   compilerOutputText->clear();
}

void compileOutputReceiver::addText(QString NewText)
{
    QTextCursor text_cursor=QTextCursor(compilerOutputText);
    text_cursor.movePosition(QTextCursor::End);
    text_cursor.insertText(NewText);
}

void compileOutputReceiver::addForwardText()
{
    //Prepare Compiler
    addText(QTime::currentTime().toString("hh:mm:ss") +
                      " " +
                      tr("Preparing Compiler.")+
                      "\n");
    //Get Compiler Info.
    addText(QTime::currentTime().toString("hh:mm:ss") +
                      " " +
                      tr("Current Compiler Details:\n") +
                      compilerVersion
                       +
                      "\n");

    //Output Compile Info:
    addText(QTime::currentTime().toString("hh:mm:ss") +
                      " " +
                      tr("Compile Command:") +
                      "\n");
    //compile command will be output when compiler emit signal compileinfo
}

void compileOutputReceiver::addRootItem(const ErrInfo &error)
{
    QStandardItem *itemAdd=new QStandardItem(error.strErrDescription);

    if(error.nLineNum>-1)
    {
        QList<QStandardItem*> column;
        column<<new QStandardItem(tr("Line ") +
                                  QString::number(error.nLineNum) +
                                  tr(", ") + tr("Column ") +
                                  QString::number(error.nColumnNum)
                                  + tr(". "))
             <<new QStandardItem(tr("At file: ") + error.strFilePath);

        itemAdd->appendColumn(column);
    }

    compilerOutputModel->appendRow(itemAdd);
}

void compileOutputReceiver::clearAllItem()
{
    compilerOutputModel->clear();
}

void compileOutputReceiver::reset()
{
    clearAllItem();
    clearText();
    erifList.clear();
    hasOutput=false;
}

void compileOutputReceiver::onCompileMsgReceived(ErrInfo error)
{
    if(!hasOutput)
    {
        emit requireShowError();
        addText(QTime::currentTime().toString("hh:mm:ss") +
                " " +
                tr("Compile Output:") +
                "\n");
        hasOutput=true;
    }

    erifList.append(error);

    addRootItem(error);
}

const QVector<ErrInfo> *compileOutputReceiver::getErifList() const
{
    return &erifList;
}

void compileOutputReceiver::onCompileFinished(bool hasError)
{
    if(hasError)
    {
        //Output Error Count
        addText(QTime::currentTime().toString("hh:mm:ss") +
                " " + QString::number(compilerOutputModel->rowCount()) +
                tr(" Errors Occur."));
    }
    else
    {
        //Output Compile Success.
        addText(QTime::currentTime().toString("hh:mm:ss") +
                " " + tr("Compile Successful."));
    }

}

void compileOutputReceiver::setCompilerVersionString(const QString &strVersion)
{
    compilerVersion=strVersion;
}
