/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist Cuties.
 *
 *    Kreogist Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QHBoxLayout>
#include <QDebug>
#include <QPainter>
#include <QApplication>

#include "kcmessagebox.h"

KCMessageBoxTitle::KCMessageBoxTitle(QWidget *parent) :
    QLabel(parent)
{
    //Set properties
    setContentsMargins(0,0,0,0);
    setFixedHeight(60);
    setScaledContents(true);
    setPixmap(QPixmap(":/MsgBox/image/MessageBox/Title.png"));
    setMinimumWidth(0);

    //Set font
    QFont titleFont;
    titleFont.setFamily("sao");
    titleFont.setPixelSize(20);

    //Set widgets
    titleCaption=new QLabel(this);
    titleCaption->setFont(titleFont);
    titleCaption->setAlignment(Qt::AlignHCenter);
    titleCaption->resize(width(), titleCaption->height());
    titleCaption->setGeometry(0,
                              (height()-titleCaption->height())/2,
                              width(),
                              height());
    setTitleText(QApplication::applicationName());

    hasPressed=false;
}

void KCMessageBoxTitle::setTitleText(const QString &text)
{
    titleCaption->setText(text);
    widthSizeHint=titleCaption->sizeHint().width()+70;
    if(widthSizeHint<300)
    {
        widthSizeHint=300;
    }
}

int KCMessageBoxTitle::getTitleWidthHint()
{
    return widthSizeHint;
}

void KCMessageBoxTitle::resizeEvent(QResizeEvent *e)
{
    QLabel::resizeEvent(e);
    titleCaption->resize(width(), titleCaption->height());
}

void KCMessageBoxTitle::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        hasPressed=true;
        mousePosStart=event->pos();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void KCMessageBoxTitle::mouseMoveEvent(QMouseEvent *event)
{
    if(hasPressed && event->buttons() == Qt::LeftButton)
    {
        parentWidget()->move(parentWidget()->pos() + event->pos() - mousePosStart);
    }
}

void KCMessageBoxTitle::mouseReleaseEvent(QMouseEvent *event)
{
    if(hasPressed)
    {
        hasPressed=false;
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

KCMessageBoxPanel::KCMessageBoxPanel(QWidget *parent) :
    QLabel(parent)
{
    //Set properties
    setFixedHeight(66);
    setScaledContents(true);
    setPixmap(QPixmap(":/MsgBox/image/MessageBox/Bottom.png"));
    setMinimumWidth(0);

    panelLayout=new QHBoxLayout(this);
    panelLayout->setContentsMargins(0,0,0,0);
    panelLayout->setSpacing(50);
    setLayout(panelLayout);

    panelLayout->addStretch();
    buttonMapper=new QSignalMapper(this);

    okButton=new KCGraphicButtonOK(this);
    panelLayout->addWidget(okButton);
    connect(okButton, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    buttonMapper->setMapping(okButton, 1);
    connect(okButton, SIGNAL(clicked()), this, SIGNAL(requiredExit()));

    cancelButton=new KCGraphicButtonCancel(this);
    panelLayout->addWidget(cancelButton);
    cancelButton->hide();
    connect(cancelButton, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    buttonMapper->setMapping(cancelButton, 2);
    connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(requiredExit()));

    panelLayout->addStretch();

    connect(buttonMapper, SIGNAL(mapped(int)),
            this, SLOT(sendSignals(int)));
}

void KCMessageBoxPanel::enabledCancel()
{
    cancelButton->show();
}

void KCMessageBoxPanel::sendSignals(int buttonIndex)
{
    switch(buttonIndex)
    {
    case 1:
        emit requiredMessage(buttonOK);
        break;
    case 2:
        emit requiredMessage(buttonCancel);
        break;
    default:
        emit requiredMessage(none);
        break;
    }
}

KCMessageBoxContext::KCMessageBoxContext(QWidget *parent) :
    QWidget(parent)
{
    setMinimumWidth(0);
    setMinimumHeight(0);
    context=new QWidget(this);
    context->setContentsMargins(0,0,0,0);
    context->setAutoFillBackground(true);
    QPalette pal=context->palette();
    pal.setColor(QPalette::Window, QColor(0xdd, 0xdd, 0xdd));
    context->setPalette(pal);

    contextLayout=new QVBoxLayout(context);
    contextLayout->setContentsMargins(0,0,0,0);
    contextLayout->setSpacing(0);
    contextLayout->setAlignment(Qt::AlignHCenter);
    context->setLayout(contextLayout);

    upIndicator=new QLabel(context);
    downIndicator=new QLabel(context);

    upIndicator->setScaledContents(true);
    upIndicator->setPixmap(QPixmap(":/MsgBox/image/MessageBox/UpBound.png"));
    downIndicator->setScaledContents(true);
    downIndicator->setPixmap(QPixmap(":/MsgBox/image/MessageBox/DownBound.png"));

    contextLayout->addWidget(upIndicator);
    contextLayout->addSpacing(15);
    contextLayout->addStretch();
    contextLayout->addSpacing(15);
    contextLayout->addWidget(downIndicator);

    insertPlace=2;
}

void KCMessageBoxContext::addWidget(QWidget *widget)
{
    contextLayout->insertWidget(insertPlace++, widget, 0, Qt::AlignCenter);
    int cacheHint;
    cacheHint=contextLayout->sizeHint().height();
    if(heightSizeHint<cacheHint)
    {
        heightSizeHint=cacheHint;
    }
    cacheHint=widget->sizeHint().width()+40;
    if(widthSizeHint < cacheHint)
    {
        widthSizeHint = cacheHint;
    }
}

void KCMessageBoxContext::addText(const QString &text)
{
    QLabel *insertCaption=new QLabel(context);
    insertCaption->setText(text);
    insertCaption->setAlignment(Qt::AlignHCenter);
    addWidget(insertCaption);
}

void KCMessageBoxContext::addSpacing(const int &value)
{
    contextLayout->insertSpacing(insertPlace++, value);
}

void KCMessageBoxContext::addImage(const QString &path,
                                   int width,
                                   int height)
{
    addImage(QPixmap(path), width, height);
}

void KCMessageBoxContext::addImage(QPixmap pixmap,
                                   int width,
                                   int height)
{
    QLabel *insertCaption=new QLabel(context);
    insertCaption->setPixmap(pixmap);
    insertCaption->setAlignment(Qt::AlignHCenter);
    if(width > 0)
    {
        insertCaption->setScaledContents(true);
        insertCaption->setFixedWidth(width);
    }
    if(height > 0)
    {
        insertCaption->setScaledContents(true);
        insertCaption->setFixedHeight(height);
    }
    addWidget(insertCaption);
}

void KCMessageBoxContext::resizeEvent(QResizeEvent *e)
{
    context->resize(e->size());
    upIndicator->setFixedWidth(e->size().width());
    downIndicator->setFixedWidth(e->size().width());
    QWidget::resizeEvent(e);
}

int KCMessageBoxContext::getWidthSizeHint() const
{
    return widthSizeHint;
}

int KCMessageBoxContext::getHeightSizeHint() const
{
    return heightSizeHint;
}

//Message Box Title
KCMessageBox::KCMessageBox(QWidget *parent) :
    QDialog(parent)
{
    //Set properties
    setWindowFlags(windowFlags() | Qt::ToolTip);
    setWindowOpacity(0.95);

    //Set default value
    messageState=KCMessageBoxPanel::none;

    //Set layout
    mainLayout=new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    //Set title
    title=new KCMessageBoxTitle(this);
    mainLayout->addWidget(title);

    context=new KCMessageBoxContext(this);
    mainLayout->addWidget(context, 1);

    //Set panel
    panel=new KCMessageBoxPanel(this);
    mainLayout->addWidget(panel);

    connect(panel, SIGNAL(requiredMessage(KCMessageBoxPanel::buttonState)),
            this, SLOT(messageFilter(KCMessageBoxPanel::buttonState)));
    connect(panel, SIGNAL(requiredExit()),
            this, SLOT(animateClose()));

    showAnimation=new QSequentialAnimationGroup(this);

    widthExpand=new QPropertyAnimation(this, "geometry", this);
    widthExpand->setDuration(100);

    heightExpand=new QPropertyAnimation(this, "geometry", this);
    heightExpand->setDuration(150);
    heightExpand->setEasingCurve(QEasingCurve::OutCubic);

    exitAnimation=new QPropertyAnimation(this, "geometry", this);
    exitAnimation->setDuration(100);
    connect(exitAnimation, SIGNAL(finished()),
            this, SLOT(close()));
}

void KCMessageBox::setTitle(const QString &text)
{
    title->setTitleText(text);
}

void KCMessageBox::addText(const QString &text)
{
    context->addText(text);
}

void KCMessageBox::addImage(const QString &path,
                            int width,
                            int height)
{
    context->addImage(path, width, height);
}

void KCMessageBox::addImage(QPixmap pixmap,
                            int width,
                            int height)
{
    context->addImage(pixmap, width, height);
}

void KCMessageBox::addSpacing(int value)
{
    context->addSpacing(value);
}

void KCMessageBox::addWidget(QWidget *widget)
{
    context->addWidget(widget);
}

void KCMessageBox::enabledCancel()
{
    panel->enabledCancel();
}

KCMessageBoxPanel::buttonState KCMessageBox::messageBoxState()
{
    return messageState;
}

void KCMessageBox::showEvent(QShowEvent *e)
{
    QRect parentGeometry=parentWidget()->geometry();
    int originalX, originalY, expectedX, expectedY, originalWidth,
        beginY, cacheExpected, minimumHeight=190;
    originalWidth=width();
    beginHeight=height();
    cacheExpected=title->getTitleWidthHint();
    expectedWidth=context->getWidthSizeHint();
    if(expectedWidth < cacheExpected)
    {
        expectedWidth=cacheExpected;
    }
    cacheExpected=context->getHeightSizeHint()+beginHeight;
    if(cacheExpected > minimumHeight)
    {
        expectedHeight=cacheExpected;
    }
    else
    {
        expectedHeight=minimumHeight;
    }

    originalX=parentGeometry.x()+parentGeometry.width()/2;
    originalY=parentGeometry.y()+parentGeometry.height()/2;
    expectedX=originalX-expectedWidth/2;
    expectedY=originalY-expectedHeight/2;
    beginY=originalY-height()/2;
    beginState=QRect(originalX-originalWidth/2,
                     beginY,
                     originalWidth,
                     beginHeight);
    heightExState=QRect(expectedX,
                        beginY,
                        expectedWidth,
                        beginHeight);
    finalState=heightExState;
    finalState.setY(expectedY);
    finalState.setHeight(expectedHeight);
    widthExpand->setStartValue(beginState);
    widthExpand->setEndValue(heightExState);
    showAnimation->addAnimation(widthExpand);

    heightExpand->setStartValue(heightExState);
    heightExpand->setEndValue(finalState);
    showAnimation->addAnimation(heightExpand);

    setGeometry(beginState);
    showAnimation->start();
    QWidget::showEvent(e);
}

void KCMessageBox::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        messageFilter(KCMessageBoxPanel::buttonOK);
        animateClose();
        break;
    case Qt::Key_Escape:
        messageFilter(KCMessageBoxPanel::buttonCancel);
        animateClose();
        break;
    default:
        QDialog::keyPressEvent(e);
        break;
    }
}

void KCMessageBox::messageFilter(KCMessageBoxPanel::buttonState message)
{
    messageState=message;
}

void KCMessageBox::animateClose()
{
    if(showAnimation->state()==QAbstractAnimation::Running)
    {
        showAnimation->stop();
    }
    QRect startGeometry=geometry();
    QRect endGeometry=startGeometry;
    endGeometry.setTop(startGeometry.top()+
                       startGeometry.height()/2-
                       beginHeight/2);
    endGeometry.setHeight(beginHeight);
    exitAnimation->setStartValue(startGeometry);
    exitAnimation->setEndValue(endGeometry);
    exitAnimation->start();
}
