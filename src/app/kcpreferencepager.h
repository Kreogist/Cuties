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

#ifndef KCPREFERENCEPAGER_H
#define KCPREFERENCEPAGER_H

#include <QList>
#include <QWidget>
#include <QResizeEvent>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

#include "kcpreferencesuperlist.h"

class KCPreferencePager : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferencePager(QWidget *parent = 0);
    void addSuperList(KCPreferenceSuperList *newSuperList);
    void initPager();
    void setPageVisible(int pageIndex, bool visible);

signals:

public slots:
    void switchToPage(int pageIndex);

private slots:
    void hideBackupPage();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QList<KCPreferenceSuperList *> preferenceSuperLists;
    int currentPageIndex;
    int backupPage;
    QParallelAnimationGroup *moveAnimationGroup;
};

#endif // KCPREFERENCEPAGER_H
