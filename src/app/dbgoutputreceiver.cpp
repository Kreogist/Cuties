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

    normalFormat.setForeground(QBrush(QColor(255,255,255)));
    errorFormat.setForeground(QBrush(QColor(255,0,0)));
    targetFormat.setForeground(QBrush(QColor(0,0x8f,0xff)));
    logFormat.setForeground(QBrush(Qt::yellow));
}

void dbgOutputReceiver::connectGDB(gdb *gdbInstance)
{
    if(this->gdbInstance!=NULL)
    {
        connectionHandles.disConnectAll();
    }

    connectionHandles+=connect(gdbInstance,&gdb::errorOccured,
                                           this,&dbgOutputReceiver::receiveError);
    connectionHandles+=connect(gdbInstance,&gdb::consoleOutputStream,
                                           this,&dbgOutputReceiver::receiveconsoleOutput);
    connectionHandles+=connect(gdbInstance,&gdb::targetOutputStream,
                                           this,&dbgOutputReceiver::receivetargetOutput);
    connectionHandles+=connect(gdbInstance,&gdb::logOutputStream,
                                           this,&dbgOutputReceiver::receivelogOutput);
}

void dbgOutputReceiver::receiveError(QString text)
{
    insertText(text,errorFormat);
}

void dbgOutputReceiver::receiveconsoleOutput(QString text)
{
    insertText(text,normalFormat);
}

void dbgOutputReceiver::receivetargetOutput(QString text)
{
    insertText(text,targetFormat);
}

void dbgOutputReceiver::receivelogOutput(QString text)
{
    insertText(text,logFormat);
}

void dbgOutputReceiver::addText(const QString& text)
{
    insertText(text,normalFormat);
}

void dbgOutputReceiver::insertText(const QString &text,
                                   const QTextCharFormat& charFormat)
{
    QTextCursor text_cursor=QTextCursor(textStreamOutput);
    text_cursor.movePosition(QTextCursor::End);
    text_cursor.insertText(text,charFormat);
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
