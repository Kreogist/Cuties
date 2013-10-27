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

#include "kccolorconfigure.h"

#include "kcdebugcontrolpanel.h"

KCDebugControlPanel::KCDebugControlPanel(QWidget *parent) :
    QDockWidget(parent)
{
    //Set properties.
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);
    setWindowTitle("Debug Panel");
    setObjectName("DebugPanel");
    setAllowedAreas(Qt::RightDockWidgetArea |
                    Qt::BottomDockWidgetArea);

    //Set compile dock palette
    QPalette pal=palette();
    pal.setColor(QPalette::Base, QColor(0x35, 0x35, 0x35));
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
    centralWidget->setLayout(mainLayout);

    setWidget(centralWidget);

    toolBar=new QToolBar(tr("Debug Controls"), this);
    toolBar->setContentsMargins(0,0,0,0);
    toolBar->setAutoFillBackground(true);
    pal=toolBar->palette();
    pal.setColor(QPalette::Base, QColor(0x35, 0x35, 0x35));
    pal.setColor(QPalette::Button, QColor(0x53, 0x53, 0x53));
    pal.setColor(QPalette::ButtonText, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::Text, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::WindowText, QColor(0xff, 0xff, 0xff));
    toolBar->setPalette(pal);

    QString debugControlIconPath[debugControlButtonCount],
            debugControlToolTips[debugControlButtonCount];
    debugControlIconPath[debugStart]=QString(":/DebugToolBar/image/Debug Docks/StartDebug.png");
    debugControlIconPath[debugStop]=QString(":/DebugToolBar/image/Debug Docks/StopDebug.png");
    debugControlIconPath[debugRunToCursor]=QString(":/DebugToolBar/image/Debug Docks/RunToCursor.png");

    debugControlToolTips[debugStart]=tr("Start Debug");
    debugControlToolTips[debugStop]=tr("Stop Debug");
    debugControlToolTips[debugRunToCursor]=tr("Run to cursor");

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

    connect(debugControlButton[debugStart],SIGNAL(clicked()),
            this,SIGNAL(requireStartDebug()));
    connect(debugControlButton[debugStop],SIGNAL(clicked()),
            this,SIGNAL(requireStopDebug()));

    QString debugCursorControlIconPath[debugCursorControlButtonCount],
            debugCursorControlToolTips[debugCursorControlButtonCount],
            debugCursorControlCaption[debugCursorControlButtonCount];
    debugCursorControlIconPath[debugNextLine]=QString(":/DebugToolBar/image/Debug Docks/NextLine.png");
    debugCursorControlIconPath[debugContinue]=QString(":/DebugToolBar/image/Debug Docks/Continue.png");
    debugCursorControlIconPath[debugIntoFunction]=QString("");
    debugCursorControlIconPath[debugNextInstruction]=QString(":/DebugToolBar/image/Debug Docks/NextInstruction.png");
    debugCursorControlIconPath[debugIntoInstruction]=QString(":/DebugToolBar/image/Debug Docks/IntoInstruction.png");
    debugCursorControlIconPath[debugSkipFunction]=QString(":/DebugToolBar/image/Debug Docks/SkipFunction.png");

    debugCursorControlCaption[debugNextLine]=tr("Next Line");
    debugCursorControlCaption[debugContinue]=tr("Continue");
    debugCursorControlCaption[debugIntoFunction]=tr("Into Function");
    debugCursorControlCaption[debugNextInstruction]=tr("Next Instruction");
    debugCursorControlCaption[debugIntoInstruction]=tr("Into Instruction");
    debugCursorControlCaption[debugSkipFunction]=tr("Skip Function");

    debugCursorControlToolTips[debugNextLine]=debugCursorControlCaption[debugNextLine] + "\n" + tr("Go to next line.");
    debugCursorControlToolTips[debugContinue]=debugCursorControlCaption[debugContinue] + "\n" + tr("Go to next line.");
    debugCursorControlToolTips[debugIntoFunction]=debugCursorControlCaption[debugIntoFunction] + "\n" + tr("Go to next line.");
    debugCursorControlToolTips[debugNextInstruction]=debugCursorControlCaption[debugNextInstruction]+ "\n" + tr("Go to next line.");
    debugCursorControlToolTips[debugIntoInstruction]=debugCursorControlCaption[debugIntoInstruction] + "\n" + tr("Go to next line.");
    debugCursorControlToolTips[debugSkipFunction]=debugCursorControlCaption[debugSkipFunction] + "\n" + tr("Go to next line.");

    for(i=debugNextLine; i<debugCursorControlButtonCount; i++)
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
        mainLayout->addWidget(debugCursorControlButton[i]);
    }
    mainLayout->addStretch();
}
