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
    maxRecentFilesSize=10;
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

    unClosedCurrent=settings.value("CurrIndex", -1).toInt();
    int unClosedFilePathsSize=settings.beginReadArray("unClosedFilePaths");

    for(int i=0;i<unClosedFilePathsSize;i++)
    {
        settings.setArrayIndex(i);
        unClosedFilePaths.append(settings.value("filePath").toString());
        unClosedFileH.append(settings.value("hPosition").toInt());
        unClosedFileV.append(settings.value("vPosition").toInt());
    }
    settings.endArray();

    int recentOpenedFilesSize=settings.beginReadArray("recentOpenedFiles");
    for(int i=0;i<recentOpenedFilesSize;i++)
    {
        settings.setArrayIndex(i);
        RecentOpenedFiles.append(settings.value("filePath").toString());
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
        settings.setValue("CurrIndex", unClosedCurrent);
        settings.beginWriteArray("unClosedFilePaths");

        int unCloseCount=unClosedFilePaths.size()-1;
        int itemCount;
        for(int i=0;i<=unCloseCount;i++)
        {
           itemCount=unCloseCount - i;
           settings.setArrayIndex(i);
           settings.setValue("filePath",unClosedFilePaths.at(itemCount));
           settings.setValue("hPosition", unClosedFileH.at(itemCount));
           settings.setValue("vPosition", unClosedFileV.at(itemCount));
        }
        settings.endArray();

        settings.beginWriteArray("recentOpenedFiles");
        for(int i=0;i<RecentOpenedFiles.size();i++)
        {
            settings.setArrayIndex(i);
            settings.setValue("filePath",RecentOpenedFiles.at(i));
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
    unClosedFileH.clear();
    unClosedFileV.clear();
}

QStringList kciHistoryConfigure::getAllUnClosedFilePaths() const
{
    return unClosedFilePaths;
}

void kciHistoryConfigure::addUnClosedFilePath(const QString &path, const int &HValue, const int &VValue)
{
    unClosedFilePaths.append(path);
    unClosedFileH.append(HValue);
    unClosedFileV.append(VValue);
}

QList<int> kciHistoryConfigure::getAllUnClosedFileHs() const
{
    return unClosedFileH;
}

QList<int> kciHistoryConfigure::getAllUnClosedFileVs() const
{
    return unClosedFileV;
}

int kciHistoryConfigure::getUnClosedCurrent() const
{
    return unClosedCurrent;
}

void kciHistoryConfigure::setUnClosedCurrent(int value)
{
    unClosedCurrent = value;
}

int kciHistoryConfigure::getMaxRecentFilesSize() const
{
    return maxRecentFilesSize;
}

void kciHistoryConfigure::setMaxRecentFilesSize(int value)
{
    maxRecentFilesSize = value;
}

void kciHistoryConfigure::clearAllRecentFilesRecord()
{
    RecentOpenedFiles.clear();

    emit recentFilesRecordsChanged();
}

void kciHistoryConfigure::addRecentFileRecord(const QString &path)
{
    int index=RecentOpenedFiles.indexOf(path);
    if(index!=-1)
    {
        RecentOpenedFiles.removeAt(index);
    }
    RecentOpenedFiles.prepend(path);

    while(RecentOpenedFiles.size()>maxRecentFilesSize)
    {
        RecentOpenedFiles.removeLast();
    }

    emit recentFilesRecordsChanged();
}

QStringList kciHistoryConfigure::getAllRecentOpenedFilesRecord() const
{
    return RecentOpenedFiles;
}
