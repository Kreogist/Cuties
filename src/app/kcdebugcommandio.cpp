#include "kcdebugcommandio.h"

KCDebugCommandIO::KCDebugCommandIO(QWidget *parent) :
    QDockWidget(parent)
{
    //Set properties.
    setObjectName("DebugCommandIO");
    setContentsMargins(0,0,0,0);

    //Set palette.
    QPalette pal=this->palette();
    pal.setColor(QPalette::Base, QColor(0x35, 0x35, 0x35));
    pal.setColor(QPalette::Button, QColor(0x53, 0x53, 0x53));
    pal.setColor(QPalette::ButtonText, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::Text, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::WindowText, QColor(0xff, 0xff, 0xff));
    setPalette(pal);

    QWidget *contentWidget=new QWidget(this);
    setWidget(contentWidget);

    //Set Layout.
    mainLayout=new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    contentWidget->setLayout(mainLayout);

    //Set command line input.
    debugInput=new QComboBox(this);
    debugInput->setEditable(true);
    debugInput->setAutoCompletion(true);
    debugInput->setStyle(QStyleFactory::create("fusion"));
    mainLayout->addWidget(debugInput);

    //Set output text browser.
    debugOutputTextBrowser=new KCPlainTextBrowser(this);
    mainLayout->addWidget(debugOutputTextBrowser,1);

}
