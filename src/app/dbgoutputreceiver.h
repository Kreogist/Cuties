#ifndef DBGOUTPUTRECEIVER_H
#define DBGOUTPUTRECEIVER_H

#include <QObject>
#include <QStandardItemModel>
#include <QTextDocument>
#include <QPlainTextDocumentLayout>
#include <QTextCursor>

#include "gdb.h"
#include "connectionhandler.h"

class dbgOutputReceiver : public QObject
{
    Q_OBJECT
public:
    explicit dbgOutputReceiver(QObject *parent = 0);

    void connectGDB(gdb* gdbInstance);
    
    QStandardItemModel *getStackInfoModel() const;
    QStandardItemModel *getLocalVarModel() const;
    QStandardItemModel *getWatchModel() const;
    QTextDocument *getTextStreamOutput() const;

signals:
    
public slots:
    void addText(QString text);

private:
    gdb* gdbInstance;

    QStandardItemModel *stackInfoModel;
    QStandardItemModel *localVarModel;
    QStandardItemModel *watchModel;
    QTextDocument *textStreamOutput;

    connectionHandler connectionHandles;
};

#endif // DBGOUTPUTRECEIVER_H
