#ifndef KCILANGUAGEMODE_H
#define KCILANGUAGEMODE_H

#include <QReadWriteLock>

#include "kcicodeeditor.h"

#include "compilerbase.h"
#include "compileoutputreceiver.h"
#include "gdb.h"
#include "dbgoutputreceiver.h"

//c/cpp
#include "gcc.h"
#include "cpphighlighter.h"

//pascal
#include "fpc.h"
#include "pascalhighlighter.h"

class kciCodeEditor;

class kciLanguageMode : public QObject
{
    Q_OBJECT
public:
    enum modeType
    {
        plainText,
        cpp,
        pascal
    };

    enum compileState
    {
        uncompiled,
        compiling,
        compiled
    };

    explicit kciLanguageMode(QWidget *parent = 0);

    void compile();
    gdb* startDebug();
    void setMode(const modeType& type);
    void setFileSuffix(const QString& suffix);
    
    compileOutputReceiver* getCompilerReceiver() const;
    dbgOutputReceiver* getDbgReceiver() const;
    gdb* getGdbInstance() const;

signals:
    void compileSuccessfully(QString execFileName);
    
public slots:
    void onCompileFinished(bool hasError);

private:
    void resetCompilerAndHighlighter();
    void connectCompilerAndOutputReceiver();
    void connectGDBAndDbgReceiver();

    modeType m_type;
    kciCodeEditor *m_parent;
    QSyntaxHighlighter *m_highlighter;

    compilerBase *compiler;
    compileOutputReceiver *compilerReceiver;
    connectionHandler compilerConnectionHandles,gdbConnectionHandles;
    compileState state;
    QReadWriteLock stateLock;

    gdb *gdbInstance;
    dbgOutputReceiver *dbgReceiver;

    QMetaObject::Connection compilerFinishedConnection;
};

#endif // KCILANGUAGEMODE_H
