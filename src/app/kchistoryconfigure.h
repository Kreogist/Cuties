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

#ifndef KCHISTORYCONFIGURE_H
#define KCHISTORYCONFIGURE_H

#include <QString>
#include <QStringList>
#include <QStandardItemModel>
#include <QList>
#include <QFile>
#include <QIcon>
#include <QFileInfo>
#include <QDebug>

#include "kcconfigure.h"

class KCHistoryConfigure : public KCConfigure
{
    Q_OBJECT

public:
    static KCHistoryConfigure *getInstance();

    void readConfigure();
    void writeConfigure();

    void writeLastSessionConfigure();

    void cleanAllHistorys();

    void setTrackUserHistoryEnabled(bool enabled);
    bool isTrackUserHistoryEnabled() const;

    void setHistoryDir(const QString &dirPath);
    QString getHistoryDir() const;

    void clearAllUnClosedFilePaths();
    QStringList getAllUnClosedFilePaths() const;
    void addUnClosedFilePath(const QString &path, const int &HValue, const int &VValue);

    int getMaxRecentFilesSize() const;
    void setMaxRecentFilesSize(int value);
    void clearAllRecentFilesRecord();
    void addRecentFileRecord(const QString &path);
    QStringList getAllRecentOpenedFilesRecord() const;

    QList<int> getAllUnClosedFileVs() const;
    QList<int> getAllUnClosedFileHs() const;
    int getUnClosedCurrent() const;
    void setUnClosedCurrent(int value);

    QStandardItemModel *getRecentOpenedFileModel() const;
    void setRecentOpenedFileModel(QStandardItemModel *value);

    static QString getHistoryFileName();
    static void setHistoryFileName(const QString &value);

private:
    KCHistoryConfigure();
    static QString historyFileName;
    QString historyDirPath;

    QIcon getFileIcon(QString fileExtName);

    QStandardItemModel *recentOpenedFileModel;
    QStandardItem *recentRootItem;

    int maxRecentFilesSize;
    bool trackUserHistory;
    bool cleanMark;
    QStringList unClosedFilePaths;
    static KCHistoryConfigure *instance;

    QList<int> unClosedFileV;
    QList<int> unClosedFileH;
    int unClosedCurrent;

    QIcon cFileIcon, cppFileIcon, pasFileIcon, otherFileIcon;
};

#endif // KCHISTORYCONFIGURE_H
