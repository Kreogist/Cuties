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

#ifndef KCCOMPILEDOCK_H
#define KCCOMPILEDOCK_H

#include <QTreeView>
#include <QPalette>
#include <QWidget>
#include <QSplitter>
#include <QList>
#include <QVector>
#include <QPropertyAnimation>
#include <QDockWidget>
#include <QModelIndex>
#include <QDebug>
#include <QTimeLine>

#include "kcplaintextbrowser.h"
#include "kccompileoutputreceiver.h"
#include "kcconnectionhandler.h"

class KCCompiledock : public QDockWidget
{
    Q_OBJECT
public:
    explicit KCCompiledock(QWidget *parent = 0);

    //Compile File Path
    void setCompileFilePath(QString FilePath);
    QString CompileFilePath();

    void setReceiver(const KCCompileOutputReceiver *currReceiver);

private:
    QWidget *objCombine;
    QSplitter *splCombine;
    QTreeView *trevwCompileInfo;
    KCPlainTextBrowser *compileOutput;
    QModelIndex lastSelIndex;
    QTimeLine *animeShowTimeLine, *animeHideTimeLine;
    const QVector<ErrInfo> *erifList;
    KCConnectionHandler receiverConnectionHandles;

signals:
    void requireOpenErrFile(QString filePath);
    void requireGotoLine(int nLineNum, int nColNum);
    void requireSetFocus();

public slots:
    //Show & Hide Error Animation.
    void animeShowError();
    void animeHideError();

private slots:
    void changeDockCompileWidth(int dockCompileWidth);
    void selectAnError(QModelIndex ItemIndex);
    void jumpToError(QModelIndex ItemID);
};

#endif // KCCOMPILEDOCK_H
