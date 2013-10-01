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

#include "compileoutputreceiver.h"

compileOutputReceiver::compileOutputReceiver(QObject *parent) :
    QObject(parent)
{
    compilerOutputModel=new QStandardItemModel(this);

    reset();
}

const QString &compileOutputReceiver::getCompilerOutputText() const
{
    return compilerOutputText;
}

QStandardItemModel *compileOutputReceiver::getCompilerOutputModel() const
{
    return compilerOutputModel;
}

void compileOutputReceiver::clearText()
{
    compilerOutputText.clear();
}

void compileOutputReceiver::addText(const QString &NewText)
{
    compilerOutputText.append(NewText);
    emit compilerOutputTextChanged(compilerOutputText);
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
        QList<QStandardItem *> column;
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
