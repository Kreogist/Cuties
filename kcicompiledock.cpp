#include "kcicompiledock.h"

kcicompiledock::kcicompiledock(QWidget *parent):
    QDockWidget(parent)
{
    //Set Object Name.
    setObjectName(QString("Compile Dock"));

    //Set Dock View.
    setContentsMargins(0,0,0,0);
    QPalette pal=this->palette();
    //Base: Content Control Background
    //pal.setColor(QPalette::Base,QColor(0x35,0x35,0x35));
    pal.setColor(QPalette::Base,QColor(0x35,0x35,0x35));
    pal.setColor(QPalette::WindowText,QColor(255,255,255));
    pal.setColor(QPalette::Button,QColor(83,83,83));
    this->setPalette(pal);
    setWindowTitle(QString(tr("Compiler")));

    //Set New Controls.
    QTreeView *trevwCompileInfo=new QTreeView(this);
    pal=trevwCompileInfo->palette();
    pal.setColor(QPalette::Foreground,QColor(255,255,255));
    trevwCompileInfo->setPalette(pal);
    setWidget(trevwCompileInfo);

    //Set Tree View Properties.
    //trevwCompileInfo->setModel(modff());
}

void kcicompiledock::parseMessage(QString msg)
{
    //trevwCompileInfo->
    qDebug()<<msg;
}
