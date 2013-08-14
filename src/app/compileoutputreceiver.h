#ifndef COMPILEOUTPUTRECEIVER_H
#define COMPILEOUTPUTRECEIVER_H

#include <QStandardItemModel>
#include <QTextDocument>
#include <QPlainTextDocumentLayout>
#include <QTextCursor>
#include <QTime>

#include "compilerbase.h"

class compileOutputReceiver : public QObject
{
    Q_OBJECT
public:
    explicit compileOutputReceiver(QObject *parent = 0);
    //Tree View Controls:
    void addRootItem(const ErrInfo& error);
    void clearAllItem();

    //Text Controls:
    void clearText();
    void addText(const QString NewText);
    void addForwardText();

    void reset();

    QStandardItemModel *getCompilerOutputModel() const;
    QTextDocument *getCompilerOutputText() const;
    const QVector<ErrInfo> *getErifList() const;

    bool hasCompileError();

    QString getCompilerVersionString() const;
    void setCompilerVersionString(const QString& strVersion);

signals:
    void requireShowError();
    
public slots:
    void onCompileMsgReceived(ErrInfo error);
    void onCompileFinished(bool hasError);
    
private:
    bool hasOutput;
    QStandardItemModel *compilerOutputModel;
    QTextDocument *compilerOutputText;
    QPlainTextDocumentLayout *plainTextLayout;
    QModelIndex lastSelIndex;
    QVector<ErrInfo> erifList;
    QString compilerVersion;
};

#endif // COMPILEOUTPUTRECEIVER_H
