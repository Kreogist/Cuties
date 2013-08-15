#include "dbgoutputreceiver.h"

dbgOutputReceiver::dbgOutputReceiver(QObject *parent) :
    QObject(parent)
{
    textStreamOutput=new QTextDocument(this);
    textStreamOutput->setDocumentLayout(
                new QPlainTextDocumentLayout(textStreamOutput));

    stackInfoModel=new QStandardItemModel(this);

    QStringList labels;
    labels<<tr("name")<<tr("value");

    watchModel=new QStandardItemModel(this);
    watchModel->setColumnCount(2);
    watchModel->setHorizontalHeaderLabels(labels);

    localVarModel=new QStandardItemModel(this);
    localVarModel->setColumnCount(2);
    localVarModel->setHorizontalHeaderLabels(labels);

    normalFormat.setForeground(QBrush(QColor(255,255,255)));
    errorFormat.setForeground(QBrush(QColor(255,0,0)));
    targetFormat.setForeground(QBrush(QColor(0,0x8f,0xff)));
    logFormat.setForeground(QBrush(Qt::yellow));
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

void dbgOutputReceiver::receiveLocals(GdbMiValue localVars)
{
    localVarModel->clear();

    for(QList<GdbMiValue>::iterator i=localVars.begin(),e=localVars.end();
        i<e;
        i++)
    {
        QString name=i->at(0).getValue();  //name
        QString value=i->at(1).getValue(); //value

        QStandardItem* varName=new QStandardItem(name);
        QStandardItem* varValue=new QStandardItem(value);
        QList<QStandardItem*> localVar;
        localVar<<varName<<varValue;
        localVarModel->appendRow(localVar);
    }
}

void dbgOutputReceiver::receiveExprValue(QString value)
{

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
