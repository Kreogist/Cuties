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

class KCCompileOutputReceiver : public QObject
{
    Q_OBJECT
public:
    explicit KCCompileOutputReceiver(QObject *parent = 0);
    //Tree View Controls:
    void addRootItem(const ErrInfo &error);
    void clearAllItem();

    //Text Controls:
    void clearText();
    void addText(const QString &NewText);
    void addForwardText();

    void reset();

    QStandardItemModel *getCompilerOutputModel() const;
    const QString &getCompilerOutputText() const;
    const QVector<ErrInfo> *getCompileErrorInfoList() const;

    bool hasCompileError();

    QString getCompilerVersionString() const;
    void setCompilerVersionString(const QString &strVersion);

signals:
    void requireShowError();
    void compilerOutputTextChanged(QString text);

public slots:
    void onCompileMsgReceived(ErrInfo error);
    void onCompileFinished(bool hasError);

private:
    bool hasOutput;
    QStandardItemModel *compilerOutputModel;
    QString compilerOutputText;
    QModelIndex lastSelectedIndex;
    QVector<ErrInfo> compileErrorInfoList;
    QString compilerVersion;
};

#endif // KCCOMPILEOUTPUTRECEIVER_H
