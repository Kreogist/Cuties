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

#ifndef KCIRECENTLYFILESMENU_H
#define KCIRECENTLYFILESMENU_H

#include <QMenu>
#include <QFileInfo>
#include <QSignalMapper>

#include "kcihistoryconfigure.h"
#include "connectionhandler.h"

class kciRecentlyFilesMenu : public QMenu
{
    Q_OBJECT
public:
    explicit kciRecentlyFilesMenu(QWidget *parent = 0);
    
signals:
    void requireOpenFile(QString filePath);

public slots:
    void onRecordsChanged();
    
private:
    void generateMenuItems();

    QSignalMapper *mapper;
    connectionHandler connections;
};

#endif // KCIRECENTLYFILESMENU_H
