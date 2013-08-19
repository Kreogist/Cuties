#ifndef KCIHIGHLIGHTER_H
#define KCIHIGHLIGHTER_H

#include <QSyntaxHighlighter>

#include "kcitextblockdata.h"

class kciHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit kciHighlighter(QObject *parent = 0);

protected:
    void highlightBlock(const QString &text);
    virtual void kciHighlightBlock(const QString &text) {Q_UNUSED(text);}
};

#endif // KCIHIGHLIGHTER_H
