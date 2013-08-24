#include "kciplaintextbrowser.h"

kciPlainTextBrowser::kciPlainTextBrowser(QWidget *parent) :
    QPlainTextEdit(parent)
{
    connect(verticalScrollBar(),&QScrollBar::valueChanged,
            this,&kciPlainTextBrowser::onScrollValueChanged);

    autoScrollEnabled=true;
    autoScrollHandle=connect(this,&QPlainTextEdit::textChanged,
                             this,&kciPlainTextBrowser::scrollToEnd);
    setReadOnly(true);
}

void kciPlainTextBrowser::scrollToEnd()
{
    QTextCursor currCursor=textCursor();
    currCursor.movePosition(QTextCursor::End);
    setTextCursor(currCursor);
}

void kciPlainTextBrowser::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);
    if(autoScrollEnabled)
        scrollToEnd();
}

void kciPlainTextBrowser::onScrollValueChanged(int value)
{
    bool shouldAutoScrollEnabled=(value==verticalScrollBar()->maximum());
    if(autoScrollEnabled==shouldAutoScrollEnabled)
        return ;

    autoScrollEnabled=shouldAutoScrollEnabled;
    if(autoScrollEnabled)
    {
        autoScrollHandle=connect(this,&QPlainTextEdit::textChanged,
                                 this,&kciPlainTextBrowser::scrollToEnd);
    }
    else
    {
        disconnect(autoScrollHandle);
    }
}
