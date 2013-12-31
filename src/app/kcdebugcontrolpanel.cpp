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

#include <QToolBar>
#include <QToolButton>
#include <QDebug>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QSizePolicy>

#include "kccolorconfigure.h"
#include "kclanguageconfigure.h"
#include "kcdebugcontrolpanel.h"

KCDebugControlPanel::KCDebugControlPanel(QWidget *parent) :
    QDockWidget(parent)
{
    //Set Langauges.
    retranslate();

    //Set properties.
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);
    setWindowTitle(windowTitleString);
    setObjectName("DebugPanel");
    setAllowedAreas(Qt::RightDockWidgetArea |
                    Qt::BottomDockWidgetArea);
    //setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    //Set compile dock palette
    QPalette pal=palette();
    pal.setColor(QPalette::Base, QColor(0x35, 0x35, 0x35));
    pal.setColor(QPalette::Window, QColor(0x53, 0x53, 0x53));
    pal.setColor(QPalette::Button, QColor(0x53, 0x53, 0x53));
    pal.setColor(QPalette::ButtonText, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::Text, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::WindowText, QColor(0xff, 0xff, 0xff));
    setPalette(pal);

    QWidget *centralWidget=new QWidget(this);
    centralWidget->setAutoFillBackground(true);
    centralWidget->setContentsMargins(0,0,0,0);
    pal=centralWidget->palette();
    pal.setColor(QPalette::Base, QColor(0x35, 0x35, 0x35));
    pal.setColor(QPalette::Button, QColor(0x53, 0x53, 0x53));
    pal.setColor(QPalette::ButtonText, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::Text, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::WindowText, QColor(0xff, 0xff, 0xff));
    centralWidget->setPalette(pal);

    QVBoxLayout *mainLayout=new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    //mainLayout->setSizeConstraint(QLayout::SetMaximumSize);
    centralWidget->setLayout(mainLayout);

    setWidget(centralWidget);

    toolBar=new QToolBar(toolbarTitle, this);
    toolBar->setContentsMargins(0,0,0,0);
    toolBar->setAutoFillBackground(true);
    pal=toolBar->palette();
    pal.setColor(QPalette::Base, QColor(0x35, 0x35, 0x35));
    pal.setColor(QPalette::Button, QColor(0x53, 0x53, 0x53));
    pal.setColor(QPalette::ButtonText, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::Text, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::WindowText, QColor(0xff, 0xff, 0xff));
    toolBar->setPalette(pal);

    QString debugControlIconPath[debugControlButtonCount];
    debugControlIconPath[debugStart]=QString(":/DebugToolBar/image/Debug Docks/StartDebug.png");
    debugControlIconPath[debugStop]=QString(":/DebugToolBar/image/Debug Docks/StopDebug.png");
    debugControlIconPath[debugRunToCursor]=QString(":/DebugToolBar/image/Debug Docks/RunToCursor.png");

    int i;
    for(i=debugStart; i<debugControlButtonCount; i++)
    {
        debugControlButton[i]=new QToolButton(this);
        debugControlButton[i]->setFixedSize(25,25);
        debugControlButton[i]->setIcon(QIcon(debugControlIconPath[i]));
        debugControlButton[i]->setToolTip(debugControlToolTips[i]);
        toolBar->addWidget(debugControlButton[i]);
        if(i==debugStop)
        {
            toolBar->addSeparator();
        }
    }
    mainLayout->addWidget(toolBar);

    QString debugCursorControlIconPath[debugCursorControlButtonCount];
    debugCursorControlIconPath[debugNext]=QString(":/DebugToolBar/image/Debug Docks/next.png");
    debugCursorControlIconPath[debugContinue]=QString(":/DebugToolBar/image/Debug Docks/continue.png");
    debugCursorControlIconPath[debugStep]=QString(":/DebugToolBar/image/Debug Docks/step.png");
    debugCursorControlIconPath[debugNexti]=QString(":/DebugToolBar/image/Debug Docks/nexti.png");
    debugCursorControlIconPath[debugStepi]=QString(":/DebugToolBar/image/Debug Docks/stepi.png");
    debugCursorControlIconPath[debugReturn]=QString(":/DebugToolBar/image/Debug Docks/return.png");

    int maxButtonSizeHint=0;

    for(i=debugNext; i<debugCursorControlButtonCount; i++)
    {
        debugCursorControlButton[i]=new QToolButton(this);
        debugCursorControlButton[i]->setAutoFillBackground(true);
        pal=debugCursorControlButton[i]->palette();
        pal.setColor(QPalette::Base, QColor(0x35, 0x35, 0x35));
        pal.setColor(QPalette::Button, QColor(0x53, 0x53, 0x53));
        pal.setColor(QPalette::ButtonText, QColor(0xff, 0xff, 0xff));
        pal.setColor(QPalette::Text, QColor(0xff, 0xff, 0xff));
        pal.setColor(QPalette::WindowText, QColor(0xff, 0xff, 0xff));
        debugCursorControlButton[i]->setPalette(pal);
        debugCursorControlButton[i]->setAutoRaise(true);
        debugCursorControlButton[i]->setFixedHeight(25);
        debugCursorControlButton[i]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        debugCursorControlButton[i]->setIcon(QIcon(debugCursorControlIconPath[i]));
        debugCursorControlButton[i]->setText(debugCursorControlCaption[i]);
        debugCursorControlButton[i]->setToolTip(debugCursorControlToolTips[i]);
        if(debugCursorControlButton[i]->sizeHint().width() > maxButtonSizeHint)
        {
            maxButtonSizeHint=debugCursorControlButton[i]->sizeHint().width();
        }
        mainLayout->addWidget(debugCursorControlButton[i]);
    }

    for(i=debugNext; i<debugCursorControlButtonCount; i++)
    {
        debugCursorControlButton[i]->setFixedWidth(maxButtonSizeHint);
    }
    setFixedWidth(maxButtonSizeHint);
    mainLayout->addStretch();

    connect(debugControlButton[debugStart],SIGNAL(clicked()),
            this,SLOT(onDebugStartClicked()));
    connect(debugControlButton[debugStop],SIGNAL(clicked()),
            this,SLOT(onDebugStopClicked()));
    connect(debugControlButton[debugRunToCursor], SIGNAL(clicked()),
            this, SLOT(onRunToCursorClicked()));
    connect(debugCursorControlButton[debugNext], SIGNAL(clicked()),
            this, SLOT(onDebugNextClicked()));
    connect(debugCursorControlButton[debugContinue], SIGNAL(clicked()),
            this, SLOT(onDebugContinueClicked()));
    connect(debugCursorControlButton[debugStep], SIGNAL(clicked()),
            this, SLOT(onDebugStepClicked()));
    connect(debugCursorControlButton[debugNexti], SIGNAL(clicked()),
            this, SLOT(onDebugNextiClicked()));
    connect(debugCursorControlButton[debugStepi], SIGNAL(clicked()),
            this, SLOT(onDebugStepiClicked()));
    connect(debugCursorControlButton[debugReturn], SIGNAL(clicked()),
            this, SLOT(onDebugReturnClicked()));

    connect(KCLanguageConfigure::getInstance(), &KCLanguageConfigure::newLanguageSet,
            this, &KCDebugControlPanel::retranslateAndSet);

    debugRunning=false;
}

void KCDebugControlPanel::retranslate()
{
    QString debugCode=tr("GDB Command: ");

    windowTitleString=tr("Debug Panel");
    toolbarTitle=tr("Debug Controls");

    debugControlToolTips[debugStart]=tr("Start Debug");
    debugControlToolTips[debugStop]=tr("Stop Debug");
    debugControlToolTips[debugRunToCursor]=tr("Run to cursor");

    debugCursorControlCaption[debugNext]=tr("Next Line");
    debugCursorControlCaption[debugContinue]=tr("Continue");
    debugCursorControlCaption[debugStep]=tr("Step Into");
    debugCursorControlCaption[debugNexti]=tr("Next Instruction");
    debugCursorControlCaption[debugStepi]=tr("Into Instruction");
    debugCursorControlCaption[debugReturn]=tr("Step Over");

    debugCursorControlToolTips[debugNext]=debugCursorControlCaption[debugNext] + "\n" +
            debugCode + "next\n" +
            tr("Continue to the next source line in the current (innermost) stack frame.") + "\n" +
            tr("This is similar to Step Into, but function calls that appear within the line of code are executed without stopping.");
    debugCursorControlToolTips[debugContinue]=debugCursorControlCaption[debugContinue] + "\n" +
            debugCode + "continue\n" +
            tr("Resume program execution, at the address where your program last stopped; any breakpoints set at that address are bypassed. ");
    debugCursorControlToolTips[debugStep]=debugCursorControlCaption[debugStep] + "\n" +
            debugCode + "step\n" +
            tr("Continue running your program until control reaches a different source line, then stop it and return control to GDB.");
    debugCursorControlToolTips[debugNexti]=debugCursorControlCaption[debugNexti]+ "\n" +
            debugCode + "nexti\n" +
            tr("Execute one machine instruction, but if it is a function call, proceed until the function returns.");
    debugCursorControlToolTips[debugStepi]=debugCursorControlCaption[debugStepi] + "\n" +
            debugCode + "stepi\n" +
            tr("Execute one machine instruction, then stop and return to the debugger.");
    debugCursorControlToolTips[debugReturn]=debugCursorControlCaption[debugReturn] + "\n" +
            debugCode + "return\n" +
            tr("Cancel execution of a function call.");
}

void KCDebugControlPanel::retranslateAndSet()
{
    retranslate();
    int maxButtonSizeHint=0, i;
    setWindowTitle(windowTitleString);
    toolBar->setWindowTitle(toolbarTitle);
    for(i=debugStart; i<debugControlButtonCount; i++)
    {
        debugControlButton[i]->setToolTip(debugControlToolTips[i]);
    }
    for(i=debugNext; i<debugCursorControlButtonCount; i++)
    {
        debugCursorControlButton[i]->setText(debugCursorControlCaption[i]);
        debugCursorControlButton[i]->setToolTip(debugCursorControlToolTips[i]);
        if(debugCursorControlButton[i]->sizeHint().width() > maxButtonSizeHint)
        {
            maxButtonSizeHint=debugCursorControlButton[i]->sizeHint().width();
        }
    }
    for(i=debugNext; i<debugCursorControlButtonCount; i++)
    {
        debugCursorControlButton[i]->setFixedWidth(maxButtonSizeHint);
    }
}

void KCDebugControlPanel::onDebugStartClicked()
{
    debugRunning=true;
    emit debugStarted();
}

void KCDebugControlPanel::onDebugStopClicked()
{
    debugRunning=false;
    emit debugStopped();
}

/*!
 * \brief KCDebugControlPanel::setGdbController sets the pointer of GdbController.
 * \param controller
 */
void KCDebugControlPanel::setGdbController(GdbController* controller)
{
    gdbController=controller;
}

void KCDebugControlPanel::clearGdbController()
{
    gdbController=NULL;
}

void KCDebugControlPanel::onRunToCursorClicked()
{
    //! TODO: doesn't accomplished RunToCursor
}

//-----control program by using gdbController-----
void KCDebugControlPanel::onDebugContinueClicked()
{
    if(gdbController!=NULL)
    {
        gdbController->execContinue();
    }
}

void KCDebugControlPanel::onDebugNextiClicked()
{
    if(gdbController!=NULL)
    {
        gdbController->execNexti();
    }
}

void KCDebugControlPanel::onDebugNextClicked()
{
    if(gdbController!=NULL)
    {
        gdbController->execNext();
    }
}

void KCDebugControlPanel::onDebugReturnClicked()
{
    if(gdbController!=NULL)
    {
        gdbController->execReturn();
    }
}

void KCDebugControlPanel::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Escape:
        emit requireSetTextFocus();
    default:
        QDockWidget::keyPressEvent(e);
    }
}

void KCDebugControlPanel::onDebugStepClicked()
{
    if(gdbController!=NULL)
    {
        gdbController->execStep();
    }
}

void KCDebugControlPanel::onDebugStepiClicked()
{
    if(gdbController!=NULL)
    {
        gdbController->execStepi();
    }
}
//-------------------------------------------------
