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

#include "kcihistoryconfigure.h"

kciHistoryConfigure* kciHistoryConfigure::instance = nullptr;

kciHistoryConfigure::kciHistoryConfigure()
{
    cleanMark=false;
    trackUserHistory=true;
}

kciHistoryConfigure* kciHistoryConfigure::getInstance()
{
    return instance==nullptr?
                instance=new kciHistoryConfigure:
                instance;
}

void kciHistoryConfigure::readConfigure()
{
    QSettings settings(getCfgFileName(),
                       QSettings::IniFormat);

    settings.beginGroup("History");
    historyDirPath=settings.value("historyDir").toString();

    int size=settings.beginReadArray("unClosedFilePaths");
    for(int i=0;i<size;i++)
    {
        settings.setArrayIndex(i);
        unClosedFilePaths.append(settings.value("filePath").toString());
    }
    settings.endArray();

    settings.endGroup();
}

void kciHistoryConfigure::writeConfigure()
{
    QSettings settings(getCfgFileName(),
                       QSettings::IniFormat);

    settings.beginGroup("History");
    if(Q_UNLIKELY(cleanMark || !trackUserHistory))
        settings.remove("");
    else
    {
        settings.setValue("historyDir",historyDirPath);

        settings.beginWriteArray("unClosedFilePaths");
        for(int i=0;i<unClosedFilePaths.size();i++)
        {
           settings.setArrayIndex(i);
           settings.setValue("filePath",unClosedFilePaths.at(i));
        }
        settings.endArray();
    }
    settings.endGroup();
}

void kciHistoryConfigure::setHistoryDir(const QString &dirPath)
{
    historyDirPath=dirPath;
}

QString kciHistoryConfigure::getHistoryDir() const
{
    return historyDirPath;
}

void kciHistoryConfigure::cleanAllHistorys()
{
    cleanMark=true;
}

void kciHistoryConfigure::setTrackUserHistoryEnabled(bool enabled)
{
    trackUserHistory=enabled;
}

bool kciHistoryConfigure::isTrackUserHistoryEnabled() const
{
    return trackUserHistory;
}

void kciHistoryConfigure::clearAllUnClosedFilePaths()
{
    unClosedFilePaths.clear();
}

QList<QString> kciHistoryConfigure::getAllUnClosedFilePaths() const
{
    return unClosedFilePaths;
}

void kciHistoryConfigure::addUnClosedFilePath(const QString &path)
{
    unClosedFilePaths.append(path);
}
