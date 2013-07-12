#ifndef KCILANGUAGEMODE_H
#define KCILANGUAGEMODE_H

#include <QObject>
#include <QSyntaxHighlighter>

#include "kcitexteditor.h"
#include "kcicodeeditor.h"

#include "compilerbase.h"
#include "kciexecutor.h"

//c/cpp
#include "gcc.h"
#include "cpphighlighter.h"

//pascal
#include "pascalhighlighter.h"

class kciTextEditor;

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

    explicit kciLanguageMode(QWidget *parent = 0);

    kciExecutor* getExecutor();
    compilerBase* getCompiler();
    void setFileSuffix(const QString& suffix);
    
signals:
    
public slots:

private:
    modeType m_type;
    kciTextEditor *m_parent;
    kciExecutor *m_executor;
    compilerBase *m_compiler;
    QSyntaxHighlighter *m_highlighter;
};

#endif // KCILANGUAGEMODE_H
