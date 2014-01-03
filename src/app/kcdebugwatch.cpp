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

#include <QSplitter>
#include <QTreeView>
#include <QToolBar>
#include <QToolButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QKeyEvent>
#include <QLineEdit>

#include "kcdebugwatch.h"
#include "kclanguageconfigure.h"
#include "kcmessagebox.h"

KCDebugWatch::KCDebugWatch(QWidget *parent) :
    QDockWidget(parent)
{
    //Set Langauges.
    retranslate();

    //Set properties.
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);
    setWindowTitle(windowTitleString);
    setObjectName("DebugWatchPanel");
    setAllowedAreas(Qt::RightDockWidgetArea |
                    Qt::BottomDockWidgetArea);

    //Set compile dock palette
    QPalette pal=palette();
    pal.setColor(QPalette::Base, QColor(0x35, 0x35, 0x35));
    pal.setColor(QPalette::Window, QColor(0x53, 0x53, 0x53));
    pal.setColor(QPalette::Button, QColor(0x53, 0x53, 0x53));
    pal.setColor(QPalette::ButtonText, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::Text, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::WindowText, QColor(0xff, 0xff, 0xff));
    setPalette(pal);

    //Set central widget
    watchDockContainer=new QSplitter(this);
    watchDockContainer->setOrientation(Qt::Vertical);

    QWidget *localWatchCombine=new QWidget(watchDockContainer);
    localWatchCombine->setContentsMargins(0,0,0,0);
    QVBoxLayout *localWatchCombineLayout=new QVBoxLayout(localWatchCombine);
    localWatchCombineLayout->setContentsMargins(0,0,0,0);
    localWatchCombineLayout->setSpacing(0);
    localWatchCombine->setLayout(localWatchCombineLayout);

    localWatchCaption=new QLabel(localWatchCombine);
    localWatchCaption->setText(localWatchTitle);
    localWatchCombineLayout->addWidget(localWatchCaption);
    localWatch=new QTreeView(watchDockContainer);
    localWatchCombineLayout->addWidget(localWatch);
    watchDockContainer->addWidget(localWatchCombine);

    QWidget *customWatchCombine=new QWidget(watchDockContainer);
    customWatchCombine->setContentsMargins(0,0,0,0);
    QVBoxLayout *customWatchCombineLayout=new QVBoxLayout(customWatchCombine);
    customWatchCombineLayout->setContentsMargins(0,0,0,0);
    customWatchCombineLayout->setSpacing(0);
    customWatchCombine->setLayout(customWatchCombineLayout);

    customWatchControlLayout=new QHBoxLayout();
    customWatchControlLayout->setContentsMargins(0,0,0,0);
    customWatchControlLayout->setSpacing(0);
    customWatchCaption=new QLabel(customWatchCombine);
    customWatchCaption->setText(customWatchTitle);
    customWatchControlLayout->addWidget(customWatchCaption);
    customWatchControl=new QToolBar(watchDockContainer);

    customWatchCommands[customWatchAdd]=new QToolButton(watchDockContainer);
    customWatchCommands[customWatchAdd]->setToolTip(customWatchCommandTitle[customWatchAdd]);
    customWatchCommands[customWatchAdd]->setIcon(QPixmap(":/DebugToolBar/image/Debug Docks/AddWatch.png"));
    connect(customWatchCommands[customWatchAdd], SIGNAL(clicked()),
            this, SLOT(onActionAddWatch()));
    customWatchControl->addWidget(customWatchCommands[customWatchAdd]);
    customWatchCommands[customWatchEdit]=new QToolButton(watchDockContainer);
    customWatchCommands[customWatchEdit]->setToolTip(customWatchCommandTitle[customWatchEdit]);
    customWatchCommands[customWatchEdit]->setIcon(QPixmap(":/DebugToolBar/image/Debug Docks/ModifyWatch.png"));
    connect(customWatchCommands[customWatchEdit], SIGNAL(clicked()),
            this, SLOT(onActionModifyWatch()));
    customWatchControl->addWidget(customWatchCommands[customWatchEdit]);
    customWatchControl->addSeparator();
    customWatchCommands[customWatchRemove]=new QToolButton(watchDockContainer);
    customWatchCommands[customWatchRemove]->setToolTip(customWatchCommandTitle[customWatchRemove]);
    customWatchCommands[customWatchRemove]->setIcon(QPixmap(":/DebugToolBar/image/Debug Docks/RemoveWatch.png"));
    connect(customWatchCommands[customWatchRemove], SIGNAL(clicked()),
            this, SLOT(onActionRemoveWatch()));
    customWatchControl->addWidget(customWatchCommands[customWatchRemove]);

    customWatchControlLayout->addWidget(customWatchControl);
    customWatchControlLayout->addStretch();
    customWatchCombineLayout->addLayout(customWatchControlLayout);
    customWatch=new QTreeView(watchDockContainer);
    customWatchCombineLayout->addWidget(customWatch);
    watchDockContainer->addWidget(customWatchCombine);

    setWidget(watchDockContainer);

    connect(KCLanguageConfigure::getInstance(), &KCLanguageConfigure::newLanguageSet,
            this, &KCDebugWatch::retranslateAndSet);
}

KCDebugWatch::~KCDebugWatch()
{
    customWatchControlLayout->deleteLater();
}

void KCDebugWatch::setGdbController(GdbController *controller)
{
    gdbController=controller;
    setLocalWatchModel(gdbController->getDbgOutputs()->getLocalVarModel());
    setCustomWatchModel(gdbController->getDbgOutputs()->getWatchModel());
}

void KCDebugWatch::clearLocalWatchModel()
{
    localWatch->setModel(NULL);
}

void KCDebugWatch::clearCustomWatchModel()
{
    customWatch->setModel(NULL);
}

void KCDebugWatch::setLocalWatchModel(QStandardItemModel *model)
{
    localWatch->setModel(model);
}

void KCDebugWatch::setCustomWatchModel(QStandardItemModel *model)
{
    customWatch->setModel(model);
}

void KCDebugWatch::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Escape:
        emit requireSetTextFocus();
    default:
        QDockWidget::keyPressEvent(e);
    }
}

void KCDebugWatch::retranslate()
{
    windowTitleString=tr("Watch");
    localWatchTitle=tr("Local Watch");
    customWatchTitle=tr("Custom Watch");

    customWatchCommandTitle[customWatchAdd]=tr("Add watch");
    customWatchCommandTitle[customWatchEdit]=tr("Edit watch");
    customWatchCommandTitle[customWatchRemove]=tr("Remove watch");
}

void KCDebugWatch::retranslateAndSet()
{
    retranslate();
    setWindowTitle(windowTitleString);
    localWatchCaption->setText(localWatchTitle);
    customWatchCaption->setText(customWatchTitle);
    customWatchCommands[customWatchAdd]->setToolTip(customWatchCommandTitle[customWatchAdd]);
    customWatchCommands[customWatchEdit]->setToolTip(customWatchCommandTitle[customWatchEdit]);
    customWatchCommands[customWatchRemove]->setToolTip(customWatchCommandTitle[customWatchRemove]);
}

void KCDebugWatch::onActionAddWatch()
{
    KCMessageBox *addWatchEquation=new KCMessageBox(this->parentWidget());
    QLineEdit *equation=new QLineEdit(this);
    equation->setFixedWidth(250);
    QPalette pal=equation->palette();
    pal.setColor(QPalette::Base, QColor(255,255,255,50));
    equation->setPalette(pal);
    addWatchEquation->enabledCancel();
    addWatchEquation->setTitle("New Watch");
    addWatchEquation->addText(tr("Enter variable equation/name:"));
    addWatchEquation->addSpacing(10);
    addWatchEquation->addWidget(equation);
    addWatchEquation->exec();
    if(addWatchEquation->messageBoxState()==KCMessageBoxPanel::buttonOK)
    {
        if(!equation->text().isEmpty())
        {
            gdbController->getDbgOutputs()->appendExpr(equation->text());
        }
    }
}

void KCDebugWatch::onActionModifyWatch()
{
    int currentIndex=customWatch->currentIndex().row();
    if(currentIndex==-1)
    {
        return;
    }
    KCMessageBox *modifyWatchEquation=new KCMessageBox(this->parentWidget());
    QLineEdit *equation=new QLineEdit(this);
    QString originalData=gdbController->getDbgOutputs()->getWatchExp(currentIndex);
    equation->setFixedWidth(250);
    equation->setText(originalData);
    equation->selectAll();
    QPalette pal=equation->palette();
    pal.setColor(QPalette::Base, QColor(255,255,255,50));
    equation->setPalette(pal);
    modifyWatchEquation->enabledCancel();
    modifyWatchEquation->setTitle("Modify Watch");
    modifyWatchEquation->addText(tr("Change equation/variable name:"));
    modifyWatchEquation->addSpacing(10);
    modifyWatchEquation->addText(originalData);
    modifyWatchEquation->addSpacing(5);
    modifyWatchEquation->addWidget(equation);
    modifyWatchEquation->exec();
    if(modifyWatchEquation->messageBoxState()==KCMessageBoxPanel::buttonOK)
    {
        if(!equation->text().isEmpty())
        {
            gdbController->getDbgOutputs()->appendExpr(equation->text());
        }
    }
}

void KCDebugWatch::onActionRemoveWatch()
{
    int currentIndex=customWatch->currentIndex().row();
    if(currentIndex==-1)
    {
        return;
    }
    KCMessageBox *deleteWatch=new KCMessageBox(this->parentWidget());
    deleteWatch->enabledCancel();
    deleteWatch->setTitle("Remove Watch");
    deleteWatch->addText(tr("Are you sure to remove to watch this?"));
    deleteWatch->addSpacing(10);
    deleteWatch->addText(gdbController->getDbgOutputs()->getWatchExp(currentIndex));
    deleteWatch->exec();
    if(deleteWatch->messageBoxState()==KCMessageBoxPanel::buttonOK)
    {
        gdbController->getDbgOutputs()->removeExprValue(currentIndex);
    }
}
