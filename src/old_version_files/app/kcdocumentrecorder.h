#ifndef KCDOCUMENTRECORDER_H
#define KCDOCUMENTRECORDER_H

#include <QList>
#include <QTextCursor>
#include <QObject>

#include "kccodeeditor.h"

struct UnclosedFileStatus
{
    QString filePath;
    bool untitled;
    int horizontalCursorPosition;
    int verticalCursorPosition;
    int horizontalScrollPosition;
    int verticalScrollPosition;
};

class KCDocumentRecorder : public QObject
{
    Q_OBJECT
public:
    static KCDocumentRecorder *getInstance();
    void appendRecord(KCCodeEditor *editor, bool untitled=false);
    void appendRecord(const QString &filePath,
                      int lineNum,
                      int columnNum,
                      int hScrollNum=0,
                      int vScrollNum=0);
    UnclosedFileStatus getUnclosedFileStatus(int index);
    int getUnclosedFileCount();
    bool setUnclosedUntitledFileDir(const QString &dirPath);
    void setUnclosedSettingFile(const QString &filePath);
    void clear();
    void clearCache();
    void readSettings();
    void writeSettings();
    int getUnclosedCurrentIndex() const;
    void setUnclosedCurrentIndex(int value);

signals:

public slots:

private:
    KCDocumentRecorder();
    static KCDocumentRecorder *instance;
    static QString unclosedUntitledFileDir;
    static QString unclosedSettingFile;

    QList<UnclosedFileStatus> unclosedFileInfos;
    int cacheCount, unclosedCurrentIndex;
};

#endif // KCDOCUMENTRECORDER_H
