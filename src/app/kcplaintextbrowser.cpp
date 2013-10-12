#include "kcplaintextbrowser.h"

KCPlainTextBrowser::KCPlainTextBrowser(QWidget *parent) :
    QPlainTextEdit(parent)
{
    connect(verticalScrollBar(),&QScrollBar::valueChanged,
            this,&KCPlainTextBrowser::onScrollValueChanged);

    autoScrollEnabled=true;
    autoScrollHandle=connect(this,&QPlainTextEdit::textChanged,
                             this,&KCPlainTextBrowser::scrollToEnd);
    setReadOnly(true);
}

void KCPlainTextBrowser::scrollToEnd()
{
    QTextCursor currCursor=textCursor();
    currCursor.movePosition(QTextCursor::End);
    setTextCursor(currCursor);
}

void KCPlainTextBrowser::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);
    if(autoScrollEnabled)
    {
        scrollToEnd();
    }
}

void KCPlainTextBrowser::onScrollValueChanged(int value)
{
    bool shouldAutoScrollEnabled=(value==verticalScrollBar()->maximum());
    if(autoScrollEnabled==shouldAutoScrollEnabled)
    {
        return ;
    }

    autoScrollEnabled=shouldAutoScrollEnabled;
    if(autoScrollEnabled)
    {
        autoScrollHandle=connect(this,&QPlainTextEdit::textChanged,
                                 this,&KCPlainTextBrowser::scrollToEnd);
    }
    else
    {
        disconnect(autoScrollHandle);
    }
}
