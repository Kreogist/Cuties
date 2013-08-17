#include "kciclipboard.h"

kciClipboard* kciClipboard::instance=nullptr;
int kciClipboard::maxDataCount=10;

kciClipboard::kciClipboard()
{
    connect(qApp->clipboard(),&QClipboard::dataChanged,
            this,&kciClipboard::onSystemClipboardChanged);
}

kciClipboard* kciClipboard::getInstance()
{
    return instance==nullptr?
                (instance=new kciClipboard):
                instance;
}

void kciClipboard::onSystemClipboardChanged()
{
    QClipboard* _clipboard=qApp->clipboard();
    QString _text=_clipboard->text();
    int index=clipboardTexts.indexOf(_text);
    if(index==-1)
    {
        clipboardTexts.prepend(_text);
    }
    else
    {
        clipboardTexts.removeAt(index);
        clipboardTexts.prepend(_text);
    }

    removeLastTextIfNeeded();
}

void kciClipboard::removeLastTextIfNeeded()
{
    int size=clipboardTexts.size();
    while(size>maxDataCount)
    {
        clipboardTexts.removeLast();
        size--;
    }
}
