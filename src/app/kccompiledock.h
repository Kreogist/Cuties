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
#include <QSplitter>
#include <QList>
#include <QDockWidget>
#include <QModelIndex>
#include <QTimeLine>

#include <QDebug>

#include "kcplaintextbrowser.h"
#include "kccompileoutputreceiver.h"
#include "kcconnectionhandler.h"

/*
 * KCCompileDock is used to display the compiler information.
 */

class KCCompileDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit KCCompileDock(QWidget *parent = 0);
    //Set output info receiver.
    void setCompileOutputReceiver(KCCompileOutputReceiver *newReceiver);

signals:
    void requireOpenErrFile(QString filePath);
    void requireGotoLine(int nLineNum, int nColNum);
    void requireSetFocus();

public slots:
    //Show & Hide Error Animation.
    void animeShowCompileError();
    void animeHideCompileError();

private slots:
    //Change the splitter value to show/hide the treeview widget
    void changeCompileSplitterWidthValue(int newCompileTreeWidth);
    //Send request to show details
    void displayErrorDetails(QModelIndex errorItemIndex);
    //Send request to jump to position of error occur
    void jumpToError(QModelIndex currentErrorItemIndex);

private:
    //Define the widget splitter.
    QSplitter *compileOutputInfoSplitter;

    //Define the info display widget.
    QTreeView *compileOutputErrorInfoTree;
    KCPlainTextBrowser *compileOutputTextInfo;

    //Define error display variables.
    int lastSelectionIndex;
    const QList<compileErrorInfo> *compileErrorInfoList;
    KCConnectionHandler receiverConnectionHandles;

    //Define the animation variables.
    QTimeLine *animeShowErrorInfoTree;
    QTimeLine *animeHideErrorInfoTree;

    //Define the current KCCompileOutputReceiver variable.
    KCCompileOutputReceiver *currentReceiver;
};

#endif // KCCOMPILEDOCK_H
