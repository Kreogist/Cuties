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

#include "kcirecentlyfilesmenu.h"

kciRecentlyFilesMenu::kciRecentlyFilesMenu(QWidget *parent) :
    QMenu(parent)
{
    setTitle(tr("recently opened files"));

    mapper=new QSignalMapper(this);

    generateMenuItems();

    connect(kciHistoryConfigure::getInstance(),
            SIGNAL(recentFilesRecordsChanged()),
            this,
            SLOT(onRecordsChanged()));
}

void kciRecentlyFilesMenu::onRecordsChanged()
{
    clear();
    connections.disConnectAll();
    generateMenuItems();
}

void kciRecentlyFilesMenu::generateMenuItems()
{
    QStringList records=kciHistoryConfigure::getInstance()->getAllRecentOpenedFilesRecord();

    int size=records.size();
    for(int i=0;i<size;i++)
    {
        QFileInfo _fileInfo(records.at(i));
        QAction *action=addAction(_fileInfo.fileName());
        mapper->setMapping(action,records.at(i));
        connections+=connect(action,SIGNAL(triggered()),mapper,SLOT(map()));
    }

    connections+=connect(mapper,SIGNAL(mapped(QString)),SIGNAL(requireOpenFile(QString)));
}
