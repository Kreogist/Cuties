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

#include "kchistoryconfigure.h"
#include "kclanguageconfigure.h"

KCHistoryConfigure *KCHistoryConfigure::instance = nullptr;
QString KCHistoryConfigure::historyFileName;

KCHistoryConfigure::KCHistoryConfigure()
{
    setHistoryFileName(QString("Settings/History.db"));
    retranslate();

    //Load Default Value.
    cleanMark=false;
    trackUserHistory=true;
    maxRecentFilesSize=10;
    recentOpenedFileModel=new QStandardItemModel(this);

    //Load File Icon.
    recentFileIcon[cSourceFile]=QIcon(":/Sidebar/image/Sidebar/source_c.png");
    recentFileIcon[cppSourceFile]=QIcon(":/Sidebar/image/Sidebar/source_cpp.png");
    recentFileIcon[pasSourceFile]=QIcon(":/Sidebar/image/Sidebar/source_pas.png");
    recentFileIcon[otherSourceFile]=QIcon(":/Sidebar/image/Sidebar/source_others.png");

    connect(KCLanguageConfigure::getInstance(), &KCLanguageConfigure::newLanguageSet,
            this, &KCHistoryConfigure::retranslateAndSet);
}

KCHistoryConfigure *KCHistoryConfigure::getInstance()
{
    return instance==nullptr?
           instance=new KCHistoryConfigure:
    instance;
}

void KCHistoryConfigure::readConfigure()
{
    QSettings settings(getHistoryFileName(),
                       QSettings::IniFormat);

    settings.beginGroup("Environments");
    historyDirPath=settings.value("HistoryDir").toString();
    settings.endGroup();

    QString filePath;
    settings.beginGroup("History");
    maxRecentFilesSize=settings.value("maxRecentFilesSize", 10).toInt();
    int recentOpenedFilesSize=settings.beginReadArray("recentOpenedFiles");
    if(recentOpenedFilesSize > maxRecentFilesSize)
    {
        recentOpenedFilesSize=maxRecentFilesSize;
    }
    recentFileList.clear();
    for(int i=0; i<recentOpenedFilesSize; i++)
    {
        settings.setArrayIndex(i);
        filePath=settings.value("filePath").toString();

        //check whether the file is exist first
        QFile *historyFileItem=new QFile(filePath);
        if(historyFileItem->exists())
        {
            appendRecentFileInfo(filePath);
        }
    }
    refreshHistoryModel();
    settings.endArray();

    settings.endGroup();
}

void KCHistoryConfigure::writeConfigure()
{
    QSettings settings(getHistoryFileName(),
                       QSettings::IniFormat);

    if(Q_UNLIKELY(cleanMark || !trackUserHistory))
    {
        settings.remove("");
    }
    else
    {
        settings.beginGroup("Environments");
        settings.setValue("HistoryDir",historyDirPath);
        settings.endGroup();

        settings.beginGroup("History");
        settings.setValue("maxRecentFilesSize", maxRecentFilesSize);
        settings.beginWriteArray("recentOpenedFiles");
        for(int i=0; i<recentFileList.count(); i++)
        {
            settings.setArrayIndex(i);
            settings.setValue("filePath", recentFileList.at(i).fileFullPath);
        }
        settings.endArray();
        settings.endGroup();
    }
}

void KCHistoryConfigure::setHistoryDir(const QString &dirPath)
{
    historyDirPath=dirPath;
}

QString KCHistoryConfigure::getHistoryDir() const
{
    return historyDirPath;
}

void KCHistoryConfigure::cleanAllHistorys()
{
    cleanMark=true;
}

void KCHistoryConfigure::setTrackUserHistoryEnabled(bool enabled)
{
    trackUserHistory=enabled;
}

bool KCHistoryConfigure::isTrackUserHistoryEnabled() const
{
    return trackUserHistory;
}

int KCHistoryConfigure::getMaxRecentFilesSize() const
{
    return maxRecentFilesSize;
}

void KCHistoryConfigure::setMaxRecentFilesSize(int value)
{
    maxRecentFilesSize = value;
}

void KCHistoryConfigure::clearAllRecentFilesRecord()
{
    recentOpenedFileModel->clear();
}

void KCHistoryConfigure::appendRecentFileInfo(const QString &path)
{
    recentFileList.append(createRecentFileInfo(path));
}

void KCHistoryConfigure::prependRecentFileInfo(const QString &path)
{
    recentFileList.prepend(createRecentFileInfo(path));
}

recentFileInfo KCHistoryConfigure::createRecentFileInfo(const QString &path)
{
    recentFileInfo historyFileItem;
    historyFileItem.fileFullPath=path;
    QFileInfo historyFileInfo(path);
    historyFileItem.fileName=historyFileInfo.fileName();
    historyFileItem.fileLastReadDate=historyFileInfo.lastRead().toString();
    historyFileItem.fileDir=historyFileInfo.absolutePath();
    QString fileExtName=historyFileInfo.suffix().toLower();
    if(fileExtName==QString("c"))
    {
        historyFileItem.fileType=cSourceFile;
    }
    else if(fileExtName==QString("cpp"))
    {
        historyFileItem.fileType=cppSourceFile;
    }
    else if(fileExtName==QString("pas"))
    {
        historyFileItem.fileType=pasSourceFile;
    }
    else
    {
        historyFileItem.fileType=otherSourceFile;
    }
    return historyFileItem;
}

QStandardItem *KCHistoryConfigure::createRecentFileItem(const int &recentFileItemIndex)
{
    recentFileInfo historyFileItem=recentFileList.at(recentFileItemIndex);
    QStandardItem *recentFileItem=new QStandardItem(historyFileItem.fileName);
    recentFileItem->setEditable(false);
    recentFileItem->setIcon(recentFileIcon[historyFileItem.fileType]);

    QString toolTipDetailsInfo = historyFileItem.fileName + "\n" +
                                 fileTypes[historyFileItem.fileType] + "\n" +
                                 filePathCaption + historyFileItem.fileFullPath + "\n" +
                                 lastReadCaption + historyFileItem.fileLastReadDate;
    recentFileItem->setToolTip(toolTipDetailsInfo);
    return recentFileItem;
}

QList<recentFileInfo> KCHistoryConfigure::getRecentFileList() const
{
    return recentFileList;
}

void KCHistoryConfigure::addRecentFileRecord(const QString &path)
{
    QFileInfo historyFileInfo(path);
    QList<QStandardItem *> results=recentOpenedFileModel->findItems(historyFileInfo.fileName());
    if(!results.isEmpty())
    {
        for(auto i=results.begin(); i!=results.end(); i++)
        {
            recentFileList.removeAt((*i)->row());
            recentOpenedFileModel->removeRow((*i)->row());
        }
    }
    prependRecentFileInfo(path);
    recentOpenedFileModel->insertRow(0, createRecentFileItem(0));
    while(recentFileList.count() > maxRecentFilesSize)
    {
        recentOpenedFileModel->removeRow(recentFileList.count()-1);
        recentFileList.removeAt(recentFileList.count()-1);
    }
}

QStandardItemModel *KCHistoryConfigure::getRecentOpenedFileModel() const
{
    return recentOpenedFileModel;
}

void KCHistoryConfigure::setRecentOpenedFileModel(QStandardItemModel *value)
{
    recentOpenedFileModel = value;
}

QString KCHistoryConfigure::getHistoryFileName()
{
    return historyFileName;
}

void KCHistoryConfigure::setHistoryFileName(const QString &value)
{
    historyFileName = value;
}

void KCHistoryConfigure::refreshHistoryModel()
{
    recentOpenedFileModel->clear();
    for(int i=0; i<recentFileList.count(); i++)
    {
        recentOpenedFileModel->appendRow(createRecentFileItem(i));
    }
}

void KCHistoryConfigure::retranslate()
{
    fileTypes[cSourceFile]=tr("C Source File");
    fileTypes[cppSourceFile]=tr("C++ Source File");
    fileTypes[pasSourceFile]=tr("Pascal Source File");
    fileTypes[otherSourceFile]=tr("Plain Text File");
    filePathCaption=tr("File Path: ");
    lastReadCaption=tr("Last Read: ");
}

void KCHistoryConfigure::retranslateAndSet()
{
    retranslate();
    refreshHistoryModel();
}
