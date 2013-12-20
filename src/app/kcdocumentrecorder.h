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
};

class KCDocumentRecorder : public QObject
{
    Q_OBJECT
public:
    static KCDocumentRecorder *getInstance();
    void appendRecord(const QString &fileName,
                      QTextCursor cursor);
    void appendRecord(KCCodeEditor *textEditor);
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
