#include "kcicontrolcenter.h"

kciControlCenter::kciControlCenter(QWidget *parent) :
    QWidget(parent)
{
    setFont(QFont(QString("Hiragino Sans GB W3")));

    //WholeTitleBarSplit=new QVBoxLayout(this);
    //setLayout(WholeTitleBarSplit);

    LeftListButtons=new QVBoxLayout(this);
    LeftListButtons->setContentsMargins(0,0,0,0);
    LeftListButtons->setSpacing(0);
    createLeftList();

    //WholeTitleBarSplit->addLayout();
}


void kciControlCenter::createLeftList()
{
    QSize *IconSize=new QSize(32,32);
    LeftListItem[cciGeneral]=new QToolButton(this);

    QPalette pal=LeftListItem[cciGeneral]->palette();
    pal.setColor(QPalette::Button,QColor(0xf7,0xcf,0x3d));
    LeftListItem[cciGeneral]->setPalette(pal);

    LeftListItem[cciGeneral]->setFixedSize(220,34);
    LeftListItem[cciGeneral]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    LeftListItem[cciGeneral]->setIcon(QIcon(":/controlcenter/image/Control Center/cciGeneral.png"));
    LeftListItem[cciGeneral]->setText(tr("General"));
    LeftListItem[cciGeneral]->setIconSize(*IconSize);
    LeftListItem[cciGeneral]->setAutoRaise(true);
    LeftListButtons->addWidget(LeftListItem[cciGeneral]);

    LeftListItem[cciEditor]=new QToolButton(this);
    LeftListItem[cciEditor]->setFixedSize(220,34);
    LeftListItem[cciEditor]->setPalette(pal);
    LeftListItem[cciEditor]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    LeftListItem[cciEditor]->setIcon(QIcon(":/controlcenter/image/Control Center/cciEditor.png"));
    LeftListItem[cciEditor]->setText(tr("Editor"));
    LeftListItem[cciEditor]->setIconSize(*IconSize);
    LeftListItem[cciEditor]->setAutoRaise(true);
    LeftListButtons->addWidget(LeftListItem[cciEditor]);

    LeftListItem[cciCompiler]=new QToolButton(this);
    LeftListItem[cciCompiler]->setFixedSize(220,34);
    LeftListItem[cciCompiler]->setPalette(pal);
    LeftListItem[cciCompiler]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    LeftListItem[cciCompiler]->setIcon(QIcon(":/controlcenter/image/Control Center/cciCompiler.png"));
    LeftListItem[cciCompiler]->setAutoRaise(true);
    LeftListItem[cciCompiler]->setIconSize(*IconSize);
    LeftListItem[cciCompiler]->setText(tr("Compiler"));
    LeftListButtons->addWidget(LeftListItem[cciCompiler]);

    LeftListItem[cciDebugger]=new QToolButton(this);
    LeftListItem[cciDebugger]->setFixedSize(220,34);
    LeftListItem[cciDebugger]->setPalette(pal);
    LeftListItem[cciDebugger]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    LeftListItem[cciDebugger]->setIcon(QIcon(":/controlcenter/image/Control Center/cciDebugger.png"));
    LeftListItem[cciDebugger]->setAutoRaise(true);
    LeftListItem[cciDebugger]->setIconSize(*IconSize);
    LeftListItem[cciDebugger]->setText(tr("Debugger"));
    LeftListButtons->addWidget(LeftListItem[cciDebugger]);

    LeftListItem[cciFileAssociation]=new QToolButton(this);
    LeftListItem[cciFileAssociation]->setFixedSize(220,34);
    LeftListItem[cciFileAssociation]->setPalette(pal);
    LeftListItem[cciFileAssociation]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    LeftListItem[cciFileAssociation]->setIcon(QIcon(":/controlcenter/image/Control Center/cciFileAssociation.png"));
    LeftListItem[cciFileAssociation]->setAutoRaise(true);
    LeftListItem[cciFileAssociation]->setIconSize(*IconSize);
    LeftListItem[cciFileAssociation]->setText(tr("File Association"));
    LeftListButtons->addWidget(LeftListItem[cciFileAssociation]);

    IconSize->setHeight(32);
    IconSize->setWidth(200);
    LeftListItem[cciLanguage]=new QToolButton(this);
    LeftListItem[cciLanguage]->setAutoRaise(true);
    LeftListItem[cciLanguage]->setFixedSize(220,34);
    LeftListItem[cciLanguage]->setPalette(pal);
    LeftListItem[cciLanguage]->setIcon(QIcon(":/controlcenter/image/Control Center/cciLanguage.png"));
    LeftListItem[cciLanguage]->setIconSize(*IconSize);
    LeftListButtons->addWidget(LeftListItem[cciLanguage]);

    LeftListButtons->addStretch(0);
}
