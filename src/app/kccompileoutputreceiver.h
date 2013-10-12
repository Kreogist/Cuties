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

#ifndef KCCOMPILEOUTPUTRECEIVER_H
#define KCCOMPILEOUTPUTRECEIVER_H

#include <QStandardItemModel>
#include <QTime>
#include <QDebug>

#include "kccompilerbase.h"

/*
 * KCCompilerOutputReceiver is used to process the
 * information sent from compiler.
 */

class KCCompileOutputReceiver : public QObject
{
    Q_OBJECT
public:
    explicit KCCompileOutputReceiver(QObject *parent = 0);
    //Model Controllers
    void addErrorInfoItem(const compileErrorInfo &newError);
    void clearErrorInfoItem();
    //Text Controllers
    void addBeginCompileText();
    void addCompilerOutputText(QString newOutputText);
    void clearCompilerOutputText();
    //Receiver Controllers
    QStandardItemModel *getCompilerOutputModel() const;
    const QString &getCompilerOutputText() const;
    const QList<compileErrorInfo> *getCompileErrorInfoList() const;
    void resetCompilerOutputReceiver();
    //Return whether there is an error occured.
    bool isCompileErrorOccur();

    //Save compiler version to a QString
    void setCompilerVersionString(const QString &compilerVersionString);

    //Show/Hide one model item details
    void foldItem(QStandardItem *itemModelIndex);
    void expandItem(QStandardItem *itemModelIndex);

signals:
    //Show error signal
    void requireShowError();
    //Output text changed
    void compilerOutputTextChanged(QString text);

public slots:
    void onCompileMessageReceived(compileErrorInfo error);
    void onCompileFinished(bool errorOccured);

private:
    //Define an output mark.
    bool hasOutputHeader;
    //Define compiler error info model and text output.
    QStandardItemModel *compilerOutputModel;
    QString compilerOutputText;
    //Define error list.
    QList<compileErrorInfo> compileErrorInfoList;
    //Define compiler info
    QString compilerVersion;
};

#endif // KCCOMPILEOUTPUTRECEIVER_H
