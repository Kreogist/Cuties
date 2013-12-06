#include <QApplication>
#include <QSettings>
#include <QDir>
#include <QDebug>

#include "kcdocumentrecorder.h"

KCDocumentRecorder *KCDocumentRecorder::instance=nullptr;
QString KCDocumentRecorder::unclosedUntitledFileDir;
QString KCDocumentRecorder::unclosedSettingFile;

KCDocumentRecorder *KCDocumentRecorder::getInstance()
{
    return instance==nullptr?instance=new KCDocumentRecorder:instance;
}

void KCDocumentRecorder::appendRecord(const QString &fileName,
                                      QTextCursor cursor)
{
    UnclosedFileStatus currentStatus;
    currentStatus.filePath=fileName;
    currentStatus.untitled=false;
    currentStatus.horizontalCursorPosition=cursor.blockNumber();
    currentStatus.verticalCursorPosition=cursor.columnNumber();
    unclosedFileInfos.prepend(currentStatus);
}

void KCDocumentRecorder::appendRecord(KCCodeEditor *textEditor)
{
    //This will treat as a untitled file.
    QString cacheFilePath=QString(unclosedUntitledFileDir +
                                  QString::number(cacheCount++) +
                                  ".txt");

    //Save the file as a cache file
    textEditor->writeCacheFile(cacheFilePath);
    QTextCursor cursor=textEditor->getTextCursor();
    //This is a unsaved untitled file
    UnclosedFileStatus currentStatus;
    currentStatus.filePath=cacheFilePath;
    currentStatus.untitled=true;
    currentStatus.horizontalCursorPosition=cursor.blockNumber();
    currentStatus.verticalCursorPosition=cursor.columnNumber();
    unclosedFileInfos.prepend(currentStatus);
}

UnclosedFileStatus KCDocumentRecorder::getUnclosedFileStatus(int index)
{
    return unclosedFileInfos.at(index);
}

int KCDocumentRecorder::getUnclosedFileCount()
{
    return unclosedFileInfos.count();
}

void KCDocumentRecorder::setUnclosedSettingFile(const QString &filePath)
{
    unclosedSettingFile=filePath;
}

void KCDocumentRecorder::clear()
{
    unclosedFileInfos.clear();
    cacheCount=0;
}

void KCDocumentRecorder::readSettings()
{
    QSettings settings(unclosedSettingFile,
                       QSettings::IniFormat);

    //Clear cache first
    clear();

    settings.beginGroup("UnclosedFile");
    int unclosedFileCounts=settings.value("UnclosedFileNum", 0).toInt();
    unclosedCurrentIndex=settings.value("UnclosedCurrentIndex", -1).toInt();
    settings.beginReadArray("UnclosedFiles");
    for(int i=0; i<unclosedFileCounts; i++)
    {
        settings.setArrayIndex(i);
        UnclosedFileStatus currentStatus;
        currentStatus.untitled=settings.value("Untitled", false).toBool();
        currentStatus.filePath=settings.value("FilePath", QString("")).toString();
        qDebug()<<currentStatus.filePath;
        currentStatus.horizontalCursorPosition=settings.value("HorizontalPosition", 0).toInt();
        currentStatus.verticalCursorPosition=settings.value("VerticalPosition", 0).toInt();
        unclosedFileInfos.append(currentStatus);
    }
    settings.endArray();
    settings.endGroup();
}

void KCDocumentRecorder::writeSettings()
{
    QSettings settings(unclosedSettingFile,
                       QSettings::IniFormat);
    settings.beginGroup("UnclosedFile");
    settings.setValue("UnclosedFileNum", unclosedFileInfos.count());
    settings.setValue("UnclosedCurrentIndex", unclosedCurrentIndex);
    settings.beginWriteArray("UnclosedFiles");
    for(int i=0; i<unclosedFileInfos.count(); i++)
    {
        settings.setArrayIndex(i);
        UnclosedFileStatus currentStatus=unclosedFileInfos.at(i);
        settings.setValue("Untitled", currentStatus.untitled);
        settings.setValue("FilePath", currentStatus.filePath);
        settings.setValue("HorizontalPosition", currentStatus.horizontalCursorPosition);
        settings.setValue("VerticalPosition", currentStatus.verticalCursorPosition);
    }
    settings.endArray();
    settings.endGroup();
}

bool KCDocumentRecorder::setUnclosedUntitledFileDir(const QString &dirPath)
{
    unclosedUntitledFileDir=dirPath;
    QDir unclosedCacheDir;
    unclosedCacheDir.setPath(dirPath);
    if(!unclosedCacheDir.exists())
    {
        return unclosedCacheDir.mkdir(dirPath);
    }
    return true;
}

KCDocumentRecorder::KCDocumentRecorder()
{
    setUnclosedUntitledFileDir(qApp->applicationDirPath() + "/AutoRemember/");
    setUnclosedSettingFile("Settings/Unclosed.ini");

}
int KCDocumentRecorder::getUnclosedCurrentIndex() const
{
    return unclosedCurrentIndex;
}

void KCDocumentRecorder::setUnclosedCurrentIndex(int value)
{
    unclosedCurrentIndex = value;
}

