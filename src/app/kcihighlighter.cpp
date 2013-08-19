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
    kciTextBlockData* data=(kciTextBlockData*)currentBlockUserData();
    if(data==NULL)
        setCurrentBlockUserData(new kciTextBlockData);
    else
    {
        data->beginUsingDatas();
        data->onBlockChanged();
        data->endUsingDatas();
    }

    kciHighlightBlock(text);
}
