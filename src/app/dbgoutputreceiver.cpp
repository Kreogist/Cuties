#include "dbgoutputreceiver.h"

dbgOutputReceiver::dbgOutputReceiver(QObject *parent) :
    QObject(parent)
{
    gdbInstance=NULL;

    textStreamOutput=new QTextDocument(this);
    textStreamOutput->setDocumentLayout(
                new QPlainTextDocumentLayout(textStreamOutput));

    stackInfoModel=new QStandardItemModel(this);
    watchModel=new QStandardItemModel(this);
    localVarModel=new QStandardItemModel(this);
}

void dbgOutputReceiver::connectGDB(gdb *gdbInstance)
{
    if(this->gdbInstance!=NULL)
    {
        for(int i=0;i<connectionCount;i++)
        {
            if(connectionHandle[i])
                disconnect(connectionHandle[i]);
        }
    }

    connectionHandle[errorOccured]=connect(gdbInstance,&gdb::errorOccured,
                                           this,&dbgOutputReceiver::addText);
    connectionHandle[consoleOutputStream]=connect(gdbInstance,&gdb::consoleOutputStream,
                                           this,&dbgOutputReceiver::addText);
    connectionHandle[targetOutputStream]=connect(gdbInstance,&gdb::targetOutputStream,
                                           this,&dbgOutputReceiver::addText);
    connectionHandle[logOutputStream]=connect(gdbInstance,&gdb::logOutputStream,
                                           this,&dbgOutputReceiver::addText);
}

void dbgOutputReceiver::addText(QString text)
{
    QTextCursor text_cursor=QTextCursor(textStreamOutput);
    text_cursor.movePosition(QTextCursor::End);
    text_cursor.insertText(text);
}

QTextDocument *dbgOutputReceiver::getTextStreamOutput() const
{
    return textStreamOutput;
}

QStandardItemModel *dbgOutputReceiver::getWatchModel() const
{
    return watchModel;
}

QStandardItemModel *dbgOutputReceiver::getLocalVarModel() const
{
    return localVarModel;
}

QStandardItemModel *dbgOutputReceiver::getStackInfoModel() const
{
    return stackInfoModel;
}
