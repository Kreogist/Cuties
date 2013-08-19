#include "kcihighlighter.h"

kciHighlighter::kciHighlighter(QObject *parent) :
    QSyntaxHighlighter(parent)
{
}

void kciHighlighter::highlightBlock(const QString &text)
{
    /* This function is used to associate kciTextBlockData with QTextBlock.
     * And then call kciHighlightBlock() which highlight the source code.
     */
    QTextBlockUserData* data=currentBlockUserData();
    if(data==NULL)
        setCurrentBlockUserData(new kciTextBlockData);

    kciHighlightBlock(text);
}
