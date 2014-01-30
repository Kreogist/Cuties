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

#include "kccompileoutputreceiver.h"

KCCompileOutputReceiver::KCCompileOutputReceiver(QObject *parent) :
    QObject(parent)
{
    //Build the compiler model and reset variables.
    compilerOutputModel=new QStandardItemModel(this);
    resetCompilerOutputReceiver();
}

//Return the error list model
QStandardItemModel *KCCompileOutputReceiver::getCompilerOutputModel() const
{
    return compilerOutputModel;
}

//Return the compile output text
const QString &KCCompileOutputReceiver::getCompilerOutputText() const
{
    return compilerOutputText;
}

//Clear the compile output text
void KCCompileOutputReceiver::clearCompilerOutputText()
{
    compilerOutputText.clear();
}

//Add new text to the output text, and emit a change signal
void KCCompileOutputReceiver::addCompilerOutputText(QString newOutputText)
{
    compilerOutputText.append(newOutputText);
    emit compilerOutputTextChanged(compilerOutputText);
}

//Add the compiler info text, and the begin caption
void KCCompileOutputReceiver::addBeginCompileText()
{
    //Prepare Compiler
    addCompilerOutputText(QTime::currentTime().toString("hh:mm:ss") +
                          " " +
                          tr("Preparing Compiler.")+
                          "\n");
    //Get Compiler Info.
    addCompilerOutputText(QTime::currentTime().toString("hh:mm:ss") +
                          " " +
                          tr("Current Compiler Details:") + "\n" +
                          compilerVersion);

    //Output Compile Info:
    addCompilerOutputText(QTime::currentTime().toString("hh:mm:ss") +
                          " " +
                          tr("Compile Command:") +
                          "\n");
    //Compile command will be output when compiler emit signal compileinfo
    //so we will not emit it here.
}

//When there is an error occur, use this procedure to add it to error list
void KCCompileOutputReceiver::addErrorInfoItem(const compileErrorInfo &newError)
{
    QStandardItem *itemAdd=new QStandardItem(newError.errorDescription);
    compilerOutputModel->appendRow(itemAdd);
}

//Clean the error list
void KCCompileOutputReceiver::clearErrorInfoItem()
{
    compilerOutputModel->clear();
}

//Reset the compiler output receiver.
void KCCompileOutputReceiver::resetCompilerOutputReceiver()
{
    //Reset the output mark
    hasOutputHeader=false;
    //Reset the model/text/list
    clearErrorInfoItem();
    clearCompilerOutputText();
    errorCounter=0;
    compileErrorInfoList.clear();
}

//When there's something compiler output to command-line, this slot will
//capture the text and display it on the text panel.
void KCCompileOutputReceiver::onCompileMessageReceived(compileErrorInfo error)
{
    //Check if has output the header.
    if(!hasOutputHeader)
    {
        addCompilerOutputText(QTime::currentTime().toString("hh:mm:ss") +
                              " " +
                              tr("Compile Output:") +
                              "\n");
        emit requireShowError();
        hasOutputHeader=true;
    }
    errorCounter++;
    //Add the new error to the list
    compileErrorInfoList.append(error);
    //Expand the model
    addErrorInfoItem(error);
    //Emit a signal for code editor to show mark.
    emit occurErrorAtLine(error.errorLine);
}

//Return the compile error info list
const QList<compileErrorInfo> *KCCompileOutputReceiver::getCompileErrorInfoList() const
{
    return &compileErrorInfoList;
}

//When compile finishes, check if there is any error occured.
//Output the compile state
void KCCompileOutputReceiver::onCompileFinished(bool errorOccured)
{
    if(errorOccured)
    {
        //Output the count of errors
        addCompilerOutputText(QTime::currentTime().toString("hh:mm:ss") +
                              " " + QString::number(errorCounter) +
                              tr(" Errors Occur."));
        emit errorOccurs(errorCounter);
    }
    else
    {
        //Output compile success info
        addCompilerOutputText(QTime::currentTime().toString("hh:mm:ss") +
                              " " + tr("Compile Successful."));
    }

}

//Use this function can check whether there's error output
bool KCCompileOutputReceiver::getHasOutputHeader() const
{
    return hasOutputHeader;
}

//Fold the expanded error item, actually we just rewrite the contents of
//the item to the description of the error.
void KCCompileOutputReceiver::foldItem(QStandardItem *itemModelIndex)
{
    itemModelIndex->setText(compileErrorInfoList[itemModelIndex->row()].errorDescription);
}

/* Expand a fold error item, like folding an item, we just rewrite the contents.
 * There are three lines of an expaned item:
 *   Error description.
 *   Line number. If possible, column number will be displayed as well.
 *   File location.
 */
void KCCompileOutputReceiver::expandItem(QStandardItem *itemModelIndex)
{
    //Get the index of the error
    int itemErrorIndex=itemModelIndex->row();
    QString expandItemInfo;
    expandItemInfo=compileErrorInfoList[itemErrorIndex].errorDescription;
    //If line number is avaliable, display it.
    if(compileErrorInfoList[itemErrorIndex].errorLine > -1)
    {
        //If column number is abaliable, display it.
        if(compileErrorInfoList[itemErrorIndex].errorColumn != -1)
        {
            expandItemInfo+= QString("\n" +
                             tr("Line ") + QString::number(compileErrorInfoList[itemErrorIndex].errorLine) +
                             tr(", ") +
                             tr("Column ") + QString::number(compileErrorInfoList[itemErrorIndex].errorColumn) +
                             tr("."));
        }
        else
        {
            expandItemInfo+= "\n" +
                             tr("Line ") + QString::number(compileErrorInfoList[itemErrorIndex].errorLine) +
                             tr(".");
        }
    }
    //If the file path is avalibable, display it! :)
    if(!compileErrorInfoList[itemErrorIndex].errorFilePath.isEmpty())
    {
        expandItemInfo+= + "\n" + tr("At file: ") + compileErrorInfoList[itemErrorIndex].errorFilePath;
    }
    //Set the new info text
    itemModelIndex->setText(expandItemInfo);
}

//Return the version info of the compiler.
void KCCompileOutputReceiver::setCompilerVersionString(const QString &compilerVersionString)
{
    compilerVersion=compilerVersionString;
}
