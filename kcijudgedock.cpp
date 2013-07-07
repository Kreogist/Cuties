#include "kcijudgedock.h"

kciJudgeFileEdit::kciJudgeFileEdit(QWidget *parent) :
    QWidget(parent)
{
    lblInput=new QLabel(tr("Input File:"),this);
    lblOutput=new QLabel(tr("Output File:"),this);
    lblUserOutput=new QLabel(tr("Execute Output:"),this);
    InputFileEdit=new QPlainTextEdit(this);
    OutputFileEdit=new QPlainTextEdit(this);
    UserOutput=new QPlainTextEdit(this);

    EditLayout=new QVBoxLayout(this);
    EditLayout->setContentsMargins(0,0,0,0);
    EditLayout->addWidget(lblInput);
    EditLayout->addWidget(InputFileEdit);
    EditLayout->addWidget(lblOutput);
    EditLayout->addWidget(OutputFileEdit);
    EditLayout->addWidget(lblUserOutput);
    EditLayout->addWidget(UserOutput);
}

kciJudgeDock::kciJudgeDock(QWidget *parent) :
    QDockWidget(parent)
{
    //Set Object Name.
    setObjectName(QString("Judge Dock"));

    //Set Dock Style.
    setContentsMargins(0,0,0,0);
    QPalette pal=this->palette();
    pal.setColor(QPalette::Base,QColor(0x35,0x35,0x35));
    pal.setColor(QPalette::WindowText,QColor(255,255,255));
    pal.setColor(QPalette::Button,QColor(83,83,83));
    pal.setColor(QPalette::Text,QColor(255,255,255));
    pal.setColor(QPalette::ButtonText,QColor(255,255,255));
    this->setPalette(pal);
    setWindowTitle(QString(tr("Judge")));
    setAllowedAreas(Qt::RightDockWidgetArea);

    //Set Main Split.
    splCombine=new QSplitter(Qt::Vertical,this);
    splCombine->setContentsMargins(0,0,0,0);
    //Set Judge Files Tab.
    tabJudgeFiles=new QTabWidget(this);

    pal=tabJudgeFiles->palette();
    pal.setColor(QPalette::HighlightedText, QColor(255,255,255));
    tabJudgeFiles->setPalette(pal);

    tabJudgeFiles->setDocumentMode(true);
    tabJudgeFiles->setMovable(true);
    tabJudgeFiles->setTabsClosable(true);
    tabJudgeFiles->setTabPosition(QTabWidget::South);
    addANewTab=new QToolButton(tabJudgeFiles);
    tabJudgeFiles->setCornerWidget(addANewTab,Qt::BottomRightCorner);

    splCombine->addWidget(tabJudgeFiles);

    //Set Judge List
    trevwJudgeList=new QTreeView(this);
    trevwJudgeList->setContentsMargins(0,0,0,0);
    pal=trevwJudgeList->palette();
    pal.setColor(QPalette::WindowText,QColor(255,255,255));
    trevwJudgeList->setPalette(pal);
    splCombine->addWidget(trevwJudgeList);

    //Init Widget Height.
    l_sizes << height() << 0;
    splCombine->setSizes(l_sizes);

    //Set Widget
    setWidget(splCombine);
}
