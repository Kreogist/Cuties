#ifndef KCILANGUAGEMODE_H
#define KCILANGUAGEMODE_H

#include <QObject>
#include <QSyntaxHighlighter>
#include <QReadWriteLock>

#include "kcitexteditor.h"
#include "kcicodeeditor.h"

#include "compilerbase.h"
#include "compileoutputreceiver.h"

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

    void run();
    void compile();
    void setMode(const modeType& type);
    void setFileSuffix(const QString& suffix);
    
    compileOutputReceiver *getReceiver() const;

signals:
    void compileSuccessfully(QString execFileName);
    
public slots:
    void onCompileFinished();

private:
    void resetCompilerAndHighlighter();

    modeType m_type;
    kciCodeEditor *m_parent;
    compilerBase *m_compiler;
    QSyntaxHighlighter *m_highlighter;

    compileOutputReceiver *receiver;

    compileState state;
    QReadWriteLock stateLock;

    QMetaObject::Connection compilerFinishedConnection;
};

#endif // KCILANGUAGEMODE_H
