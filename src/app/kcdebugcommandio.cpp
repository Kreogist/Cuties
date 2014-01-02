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
#include <QKeyEvent>

#include "kcplaintextbrowser.h"
#include "gdbcontroller.h"
#include "kclanguageconfigure.h"
#include "kcfontconfigure.h"

#include "kcdebugcommandio.h"

KCDebugInput::KCDebugInput(QWidget *parent) :
    QComboBox(parent)
{
    //Set Properties.
    setEditable(true);
    setAutoCompletion(true);
    setStyle(QStyleFactory::create("fusion"));
}

void KCDebugInput::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        emit execCommand(lineEdit()->text());
        addItem(lineEdit()->text());
        lineEdit()->clear();
        break;
    default:
        QComboBox::keyPressEvent(e);
        break;
    }
}

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
    QPalette pal=palette();
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
    debugInput=new KCDebugInput(this);
    mainLayout->addWidget(debugInput);

    //Set output text browser.
    debugOutputTextBrowser=new KCPlainTextBrowser(this);
    debugOutputTextBrowser->setFont(KCFontConfigure::getInstance()->getCodeFont());
    mainLayout->addWidget(debugOutputTextBrowser,1);
    connect(debugInput,SIGNAL(execCommand(QString)),
            this,SLOT(onCurrentIndexChanged(QString)));

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
    debugOutputTextBrowser->setDocument(resetBackup->document());
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

void KCDebugCommandIO::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Escape:
        emit requireSetTextFocus();
    default:
        QDockWidget::keyPressEvent(e);
    }
}

void KCDebugCommandIO::onCurrentIndexChanged(QString command)
{
    instance->execGdbCommand(qPrintable(command));
    debugInput->lineEdit()->selectAll();
}
