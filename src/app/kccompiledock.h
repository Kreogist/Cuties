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
    void setCompileOutputReceiver(const KCCompileOutputReceiver *currReceiver);

signals:
    void requireOpenErrFile(QString filePath);
    void requireGotoLine(int nLineNum, int nColNum);
    void requireSetFocus();

public slots:
    //Show & Hide Error Animation.
    void animeShowCompileError();
    void animeHideCompileError();

private slots:
    void changeCompileSplitterWidthValue(int newCompileTreeWidth);
    void selectAnError(QModelIndex ItemIndex);
    void jumpToError(QModelIndex ItemID);

private:
    //Define the widget splitter.
    QSplitter *compileOutputInfoSplitter;

    //Define the info display widget.
    QTreeView *compileOutputErrorInfoTree;
    KCPlainTextBrowser *compileOutputTextInfo;

    //Define error display variables.
    QModelIndex lastSelIndex;
    const QVector<ErrInfo> *compileErrorInfoList;
    KCConnectionHandler receiverConnectionHandles;

    //Define the animation variables.
    QTimeLine *animeShowErrorInfoTree;
    QTimeLine *animeHideErrorInfoTree;

};

#endif // KCCOMPILEDOCK_H
