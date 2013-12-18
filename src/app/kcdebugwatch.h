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

#ifndef KCDEBUGWATCH_H
#define KCDEBUGWATCH_H

#include <QDockWidget>

class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class QSplitter;
class QTreeView;
class QToolBar;
class QToolButton;
class QStandardItemModel;


class KCDebugWatch : public QDockWidget
{
    Q_OBJECT
public:
    explicit KCDebugWatch(QWidget *parent = 0);
    ~KCDebugWatch();
    void clearLocalWatchModel();
    void clearCustomWatchModel();
    void setLocalWatchModel(QStandardItemModel* model);
    void setCustomWatchModel(QStandardItemModel* model);

signals:

public slots:
    void retranslate();
    void retranslateAndSet();

private:
    QSplitter *watchDockContainer;
    QTreeView *localWatch;
    QTreeView *customWatch;
    QLabel *localWatchCaption, *customWatchCaption;
    QToolBar *customWatchControl;

    enum CustomWatchCommand
    {
        customWatchAdd,
        customWatchEdit,
        customWatchRemove,
        CustomWatchCommandCount
    };
    QToolButton *customWatchCommands[CustomWatchCommandCount];
    QString customWatchCommandTitle[CustomWatchCommandCount];

    QHBoxLayout *customWatchControlLayout;

    QString windowTitleString,
            localWatchTitle,
            customWatchTitle;
};

#endif // KCDEBUGWATCH_H
