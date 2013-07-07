#include "kcistatuscursorinfo.h"

kciStatusCursorInfo::kciStatusCursorInfo(QWidget *parent) :
    QWidget(parent)
{
    setContentsMargins(0,0,0,0);

    QHBoxLayout *TextLayout=new QHBoxLayout(this);
    TextLayout->setContentsMargins(0,0,0,0);
    TextLayout->setSpacing(0);
    setLayout(TextLayout);

    lblCursorPosition=new QLabel(this);
    TextLayout->addWidget(lblCursorPosition);

    spbLineNum=new QSpinBox(this);
    spbLineNum->setContentsMargins(0,0,0,0);
    spbLineNum->setMinimum(1);
    spbLineNum->hide();
    connect(spbLineNum,SIGNAL(valueChanged(int)),
            this,SLOT(gotoLineNumber(int)));
    connect(spbLineNum,SIGNAL(editingFinished()),
            this,SLOT(finishedHideGotoBox()));
    gotoBarShowed=false;

    setFixedHeight(spbLineNum->height());

    gotoHideAnime=new QPropertyAnimation(spbLineNum,"geometry");
    connect(gotoHideAnime,SIGNAL(finished()),
            this,SLOT(setHideGotoBox()));
}

void kciStatusCursorInfo::ShowGotoBox(int currentValue, int MaxValue)
{
    spbLineNum->setValue(currentValue);
    spbLineNum->setMaximum(MaxValue);
    spbLineNum->selectAll();
    spbLineNum->show();

    if(!gotoBarShowed)
    {
        QPropertyAnimation *gotoAnime=new QPropertyAnimation(spbLineNum,"geometry");
        QRect animeEndPos=QRect(0,0,this->width(),this->height());
        QRect animeStartPos=animeEndPos;
        animeStartPos.setTop(animeStartPos.height()+3);
        gotoAnime->setStartValue(animeStartPos);
        gotoAnime->setEndValue(animeEndPos);
        gotoAnime->setEasingCurve(QEasingCurve::OutCubic);
        spbLineNum->show();
        gotoAnime->start();
        gotoBarShowed=true;
    }
    spbLineNum->setFocus();
}

bool kciStatusCursorInfo::getGotoShowed()
{
    return gotoBarShowed;
}

void kciStatusCursorInfo::updateCursorPosition(int LineNum, int ColNum)
{
    if(LineNum>0)
    {
        lblCursorPosition->setText(QString(tr("Line ")) +
                                   QString::number(LineNum) +
                                   QString(tr(", ")) +
                                   QString(tr("Col ")) +
                                   QString::number(ColNum) +
                                   QString(tr(" ")));
    }
    else
    {
        lblCursorPosition->setText("");
    }
    this->resize(lblCursorPosition->size());
}

void kciStatusCursorInfo::finishedHideGotoBox()
{
    HideGotoBox();
}

void kciStatusCursorInfo::gotoLineNumber(int NewNum)
{
    emit ToLineNum(NewNum);
}

void kciStatusCursorInfo::HideGotoBox()
{
    if(gotoBarShowed)
    {
        gotoBarShowed=false;
        QRect animeStartPos=spbLineNum->rect();
        QRect animeEndPos=animeStartPos;
        animeEndPos.setTop(spbLineNum->rect().height()+3);
        gotoHideAnime->setStartValue(animeStartPos);
        gotoHideAnime->setEndValue(animeEndPos);
        gotoHideAnime->setEasingCurve(QEasingCurve::OutCubic);
        gotoHideAnime->start();
    }
}

void kciStatusCursorInfo::setHideGotoBox()
{
    spbLineNum->hide();
}
