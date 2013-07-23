/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *      Wang Luming <wlm199558@126.com>
 *      Miyanaga Saki <tomguts@126.com>
 *      Zhang Jiayi <bf109g2@126.com>
 *
 *  This file is part of Kreogist-Cute-IDE.
 *
 *    Kreogist-Cute-IDE is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cute-IDE is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cute-IDE.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KCICOMPILEDOCK_H
#define KCICOMPILEDOCK_H

#include <QTreeView>
#include <QPalette>
#include <QWidget>
#include <QSplitter>
#include <QDebug>
#include <QList>
#include <QVector>
#include <QTime>
#include <QSignalMapper>
#include <QRegularExpression>
#include <QPropertyAnimation>
#include <QPlainTextEdit>
#include <QDockWidget>
#include <QModelIndex>
#include <QStandardItemModel>

#include "compilerbase.h"
#include "compileoutputreceiver.h"

class kcicompiledock : public QDockWidget
{
    Q_OBJECT
public:
    explicit kcicompiledock(QWidget *parent = 0);

    //Compile File Path
    void setCompileFilePath(QString FilePath);
    QString CompileFilePath();

    void setReceiver(const compileOutputReceiver* currReceiver);

private:
    QWidget *objCombine;
    QSplitter *splCombine;
    QTreeView *trevwCompileInfo;
    QPlainTextEdit *compileOutput;
    QModelIndex lastSelIndex;
    const compileOutputReceiver *receiver;
    QMetaObject::Connection receiverConnectionHandle;

signals:
    void requireOpenErrFile(QString filePath);
    void requireGotoLine(int nLineNum, int nColNum);
    void requireSetFocus();
    
public slots:
    //Show/Hide Error Animation.
    void animeShowError();
    void animeHideError();

private slots:
    void selectAnError(QModelIndex ItemIndex);
    void jumpToError(QModelIndex ItemID);
    
};

#endif // KCICOMPILEDOCK_H
