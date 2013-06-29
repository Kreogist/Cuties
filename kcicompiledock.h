/*
 *  Copyright 2013 Wang Luming<wlm199558@126.com>
 *  Copyright 2013 Ye Haolei(Miyanaga Saki) <tomguts@126.com>
 *
 *  kcicompiledock.h is part of Kreogist-Cute-IDE.
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
#include <QSignalMapper>
#include <QPropertyAnimation>
#include <QPlainTextEdit>
#include <QDockWidget>
#include <QStandardItemModel>

class kcicompiledock : public QDockWidget
{
    Q_OBJECT
public:
    explicit kcicompiledock(QWidget *parent = 0);

    //Tree View Controls:
    void addRootItem(QString ItemText);
    void addLastSubItem(QString ItemText);
    void clearAllItem();

    //Text Controls:
    void clearText();
    void addText(QString NewText);

    //Show/Hide Error Animation.
    void animeShowError();
    void animeHideError();

private:
    QWidget *objCombine;
    QSplitter *splCombine;
    QTreeView *trevwCompileInfo;
    QStandardItemModel *compileInfo;
    QPlainTextEdit *compileOutput;

signals:
    
public slots:
    void parseMessage(QString msg);
    
};

#endif // KCICOMPILEDOCK_H
