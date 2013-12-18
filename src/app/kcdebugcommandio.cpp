/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist-Cuties.
 *
 *    Kreogist-Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QVBoxLayout>
#include <QComboBox>
#include <QStyleFactory>
#include <QTextDocument>
#include <QLineEdit>

#include "kcplaintextbrowser.h"
#include "gdbcontroller.h"
#include "kclanguageconfigure.h"

#include "kcdebugcommandio.h"

KCDebugCommandIO::KCDebugCommandIO(QWidget *parent) :
    QDockWidget(parent)
{
    //Set translate.
    retranslate();

    //Set properties.
    setObjectName("DebugCommandIO");
    setWindowTitle(windowTitleString);
    setContentsMargins(0,0,0,0);

    //Set palette.
    QPalette pal=this->palette();
    pal.setColor(QPalette::Base, QColor(0x35, 0x35, 0x35));
    pal.setColor(QPalette::Window, QColor(0x35, 0x35, 0x35));
    pal.setColor(QPalette::Button, QColor(0x53, 0x53, 0x53));
    pal.setColor(QPalette::ButtonText, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::Text, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::WindowText, QColor(0xff, 0xff, 0xff));
    setPalette(pal);

    QWidget *contentWidget=new QWidget(this);
    setWidget(contentWidget);

    //Set Layout.
    mainLayout=new QVBoxLayout(contentWidget);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(2);
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
    connect(debugInput,SIGNAL(currentIndexChanged(QString)),
            this,SLOT(onCurrentIndexChanged(QString)));
    /*connect(debugInput, SIGNAL(activated(QString)),
            this, SLOT(onCurrentIndexChanged(QString)));*/

    connect(KCLanguageConfigure::getInstance(), &KCLanguageConfigure::newLanguageSet,
            this, &KCDebugCommandIO::retranslateAndSet);

    resetBackup=new KCPlainTextBrowser(this);
    resetBackup->setVisible(false);
}

void KCDebugCommandIO::setGdbInstance(GdbController *gdbInstance)
{
    instance=gdbInstance;
    debugOutputTextBrowser->setDocument(gdbInstance->getDbgOutputs()->getTextStreamOutput());
}

void KCDebugCommandIO::clearInstance()
{
    instance=NULL;
    resetBackup->clear();
    qDebug()<<"Find?";
    debugOutputTextBrowser->setDocument(resetBackup->document());
    qDebug()<<"Find?";
}

void KCDebugCommandIO::retranslate()
{
    windowTitleString=tr("Debug Command Prompt");
}

void KCDebugCommandIO::retranslateAndSet()
{
    retranslate();
    setWindowTitle(windowTitleString);
}

void KCDebugCommandIO::onCurrentIndexChanged(QString command)
{
    instance->execGdbCommand(qPrintable(command+'\n'));
    debugInput->lineEdit()->selectAll();
}

