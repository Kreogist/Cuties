#include "kcicompiledock.h"

kcicompiledock::kcicompiledock(QWidget *parent):
    QDockWidget(parent)
{
    //Set Object Name.
    setObjectName(QString("Compile Dock"));

    //Set Dock Style.
    setContentsMargins(0,0,0,0);
    QPalette pal=this->palette();
    //pal.setColor(QPalette::Base,QColor(0x35,0x35,0x35));
    pal.setColor(QPalette::Base,QColor(0x35,0x35,0x35));
    pal.setColor(QPalette::WindowText,QColor(255,255,255));
    pal.setColor(QPalette::Button,QColor(83,83,83));
    pal.setColor(QPalette::Text,QColor(255,255,255));
    pal.setColor(QPalette::ButtonText,QColor(255,255,255));
    this->setPalette(pal);
    setWindowTitle(QString(tr("Compiler")));
    setAllowedAreas(Qt::BottomDockWidgetArea);

    //Set Dock Widget and Layout.
    //objCombine=new QWidget(this);
    //objCombine->setContentsMargins(0,0,0,0);
    splCombine=new QSplitter(Qt::Horizontal, this);
    splCombine->setContentsMargins(0,0,0,0);

    //Set Text Output.
    compileOutput=new QPlainTextEdit(this);
    compileOutput->setContentsMargins(0,0,0,0);
    compileOutput->setWordWrapMode(QTextOption::NoWrap);
    splCombine->addWidget(compileOutput);

    //Set TreeView Controls.
    trevwCompileInfo=new QTreeView(this);
    trevwCompileInfo->setContentsMargins(0,0,0,0);
    pal=trevwCompileInfo->palette();
    pal.setColor(QPalette::Foreground,QColor(255,255,255));
    trevwCompileInfo->setPalette(pal);
    compileInfo=new QStandardItemModel();
    //trevwCompileInfo->setSelectionMode(QAbstractItemView::SingleSelection);
    trevwCompileInfo->setGeometry(0,0,0,0);
    splCombine->addWidget(trevwCompileInfo);
    QList<int> l_sizes;
    l_sizes << width() << 0;
    splCombine->setSizes(l_sizes);

    setWidget(splCombine);
}

void kcicompiledock::animeShowError()
{
    QList<int> l_sizes_finish;
    int dockCompileWidth=this->width();
    dockCompileWidth/=5;
    l_sizes_finish << dockCompileWidth << this->width()-dockCompileWidth;
    splCombine->setSizes(l_sizes_finish);
}

void kcicompiledock::animeHideError()
{
    QList<int> l_sizes_finish;
    l_sizes_finish << width() << 0;
    splCombine->setSizes(l_sizes_finish);
}

void kcicompiledock::clearText()
{
    compileOutput->clear();
}

void kcicompiledock::addText(QString NewText)
{
    QTextDocument *document=compileOutput->document();
    QTextCursor text_cursor=QTextCursor(document);
    text_cursor.movePosition(QTextCursor::End);
    text_cursor.insertText(NewText);
}

void kcicompiledock::addRootItem(QString ItemText)
{
    QStandardItem *itemAdd=new QStandardItem(ItemText);
    compileInfo->appendRow(itemAdd);
}

void kcicompiledock::addLastSubItem(QString ItemText)
{
    QStandardItem *itemAdd=new QStandardItem(ItemText);
    compileInfo->item(compileInfo->rowCount()-1)->appendRow(itemAdd);
}

void kcicompiledock::clearAllItem()
{
    compileInfo->clear();
}

void kcicompiledock::parseMessage(QString msg)
{
    //trevwCompileInfo->
    qDebug()<<msg;
}
