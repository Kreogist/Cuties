/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist Cuties.
 *
 *    Kreogist Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "dbgoutputreceiver.h"
#include "kclanguageconfigure.h"

dbgOutputReceiver::dbgOutputReceiver(QObject *parent) :
    QObject(parent)
{
    retranslate();
    textStreamOutput=new QTextDocument(this);
    textStreamOutput->setDocumentLayout(
        new QPlainTextDocumentLayout(textStreamOutput));

    stackInfoModel=new QStandardItemModel(this);

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

    watchExps.clear();
    resetExprValue();

    connect(KCLanguageConfigure::getInstance(), &KCLanguageConfigure::newLanguageSet,
            this, &dbgOutputReceiver::retranslateAndSet);
}

void dbgOutputReceiver::addErrorText(QString text)
{
    insertText(text,errorFormat);
}

void dbgOutputReceiver::addConsoleOutput(QString text)
{
    insertText(text,normalFormat);
}

void dbgOutputReceiver::addTargetOutput(QString text)
{
    insertText(text,targetFormat);
}

void dbgOutputReceiver::addLogOutput(QString text)
{
    insertText(text,logFormat);
}

void dbgOutputReceiver::addLocals(GdbMiValue localVars)
{
    localVarModel->clear();

    localVarModel->setColumnCount(2);
    localVarModel->setHorizontalHeaderLabels(labels);
    for(int i=0; i<localVars.size(); i++)
    {
        QString name=localVars.at(i).at(0).getValue();  //name
        QString value=localVars.at(i).at(1).getValue(); //value
        QStandardItem *varName=new QStandardItem(name);
        QStandardItem *varValue=new QStandardItem(value);
        QList<QStandardItem *> localVar;
        localVar<<varName<<varValue;
        localVarModel->appendRow(localVar);
        watchIndex=0;
    }
}

void dbgOutputReceiver::addExprValue(QString value)
{
    QString name=watchExps.at(watchIndex);  //name
    QStandardItem *varName=new QStandardItem(name);
    QStandardItem *varValue=new QStandardItem(value);
    QList<QStandardItem *> watchVar;
    watchVar<<varName<<varValue;
    watchModel->appendRow(watchVar);
    watchIndex++;
}

void dbgOutputReceiver::resetExprValue()
{
    watchModel->clear();
    watchModel->setColumnCount(2);
    watchModel->setHorizontalHeaderLabels(labels);
    if(watchExps.isEmpty())
    {
        watchIndex=-1;
    }
    else
    {
        watchIndex=0;
    }
}

void dbgOutputReceiver::addText(const QString &text)
{
    insertText(text,normalFormat);
}

void dbgOutputReceiver::removeExpr(int expIndex)
{
    watchModel->removeRow(expIndex);
    watchExps.removeAt(expIndex);
    if(watchExps.isEmpty())
    {
        watchIndex=-1;
    }
    else
    {
        watchIndex=0;
    }
}

void dbgOutputReceiver::insertText(const QString &text,
                                   const QTextCharFormat &charFormat)
{
    QTextCursor text_cursor=QTextCursor(textStreamOutput);
    text_cursor.movePosition(QTextCursor::End);
    text_cursor.insertText(text,charFormat);
}

QStringList dbgOutputReceiver::getWatchExpList() const
{
    return watchExps;
}

QString dbgOutputReceiver::getWatchExp(const int &index) const
{
    if(index>-1 && index<watchExps.count())
    {
        return watchExps.at(index);
    }
    return QString("");
}

void dbgOutputReceiver::setWatchExps(const QStringList &value)
{
    watchExps = value;
}

QTextDocument *dbgOutputReceiver::getTextStreamOutput() const
{
    return textStreamOutput;
}

void dbgOutputReceiver::retranslate()
{
    labels<<tr("Name")<<tr("Value");
}

void dbgOutputReceiver::retranslateAndSet()
{
    retranslate();
    localVarModel->setHorizontalHeaderLabels(labels);
    watchModel->setHorizontalHeaderLabels(labels);
}

void dbgOutputReceiver::clearTextStream()
{
    textStreamOutput->clear();
    textStreamOutput->setDocumentLayout(
        new QPlainTextDocumentLayout(textStreamOutput));
}

void dbgOutputReceiver::clearOutput()
{
    clearTextStream();
    stackInfoModel->clear();
    localVarModel->clear();
    watchModel->clear();
}

void dbgOutputReceiver::appendExpr(const QString &value)
{
    watchExps.append(value);
    QString name=value;  //name
    QString empty=QString(""); //value
    QStandardItem *varName=new QStandardItem(name);
    QStandardItem *varValue=new QStandardItem(empty);
    QList<QStandardItem *> watchVar;
    watchVar<<varName<<varValue;
    watchModel->appendRow(watchVar);
}

void dbgOutputReceiver::insertExpr(int expIndex, const QString &value)
{
    watchExps.insert(expIndex, value);
    QString name=value;  //name
    QString empty=QString(""); //value
    QStandardItem *varName=new QStandardItem(name);
    QStandardItem *varValue=new QStandardItem(empty);
    QList<QStandardItem *> watchVar;
    watchVar<<varName<<varValue;
    watchModel->insertRow(expIndex, watchVar);
}

void dbgOutputReceiver::modifyExpr(int expIndex, const QString &value)
{
    insertExpr(expIndex, value);
    removeExpr(expIndex+1);
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
