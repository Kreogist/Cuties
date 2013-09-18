#include "kcistatusrewriteinfo.h"

kciStatusRewriteInfo::kciStatusRewriteInfo(QWidget *parent) :
    QLabel(parent)
{
    rewriteText=tr("Overwrite");
    unrewriteText=tr("Insert");

    //Text Mode is always the same as insert mode status.
    textMode=false;

    //Set Default Text.
    setText(unrewriteText);
}

bool kciStatusRewriteInfo::getTextMode() const
{
    return textMode;
}

void kciStatusRewriteInfo::setTextMode(bool value)
{
    textMode = value;
    //When text mode is changed, refresh the text.
    if(textMode)
    {
        setText(rewriteText);
    }
    else
    {
        setText(unrewriteText);
    }
}


