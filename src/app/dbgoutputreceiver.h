#ifndef DBGOUTPUTRECEIVER_H
#define DBGOUTPUTRECEIVER_H

#include <QStandardItemModel>
#include <QTextDocument>
#include <QPlainTextDocumentLayout>
#include <QTextCursor>

#include "gdbmivalue.h"

class dbgOutputReceiver : public QObject
{
    Q_OBJECT
public:
    explicit dbgOutputReceiver(QObject *parent = 0);
    
    QStandardItemModel *getStackInfoModel() const;
    QStandardItemModel *getLocalVarModel() const;
    QStandardItemModel *getWatchModel() const;
    QTextDocument *getTextStreamOutput() const;

signals:
    
public slots:
    void receiveconsoleOutput(QString text);
    void receivetargetOutput(QString text);
    void receivelogOutput(QString text);
    void receiveError(QString text);
    void receiveLocals(GdbMiValue localVars);
    void receiveExprValue(QString value);
    void addText(const QString& text);

private:
    void insertText(const QString& text,const QTextCharFormat &charFormat);

    QStandardItemModel *stackInfoModel;
    QStandardItemModel *localVarModel;
    QStandardItemModel *watchModel;
    QTextDocument *textStreamOutput;

    QTextCharFormat normalFormat,errorFormat,targetFormat,logFormat;
};

#endif // DBGOUTPUTRECEIVER_H
