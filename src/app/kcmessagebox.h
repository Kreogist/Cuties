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

#ifndef KCMESSAGEBOX_H
#define KCMESSAGEBOX_H

#include <QLabel>
#include <QVBoxLayout>
#include <QDialog>
#include <QResizeEvent>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QMouseEvent>
#include <QSignalMapper>
#include <QHBoxLayout>
#include <QKeyEvent>

#include "Controls/GraphicButtons/kcgraphicbuttonok.h"
#include "Controls/GraphicButtons/kcgraphicbuttoncancel.h"

class KCMessageBoxTitle : public QLabel
{
    Q_OBJECT
public:
    explicit KCMessageBoxTitle(QWidget *parent = 0);
    void setTitleText(const QString &text);
    int getTitleWidthHint();

protected:
    void resizeEvent(QResizeEvent *e);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool hasPressed;
    QPoint mousePosStart;
    QLabel *titleCaption;
    int widthSizeHint;
};

class KCMessageBoxPanel : public QLabel
{
    Q_OBJECT
public:
    explicit KCMessageBoxPanel(QWidget *parent = 0);
    void enabledCancel();
    enum buttonState
    {
        none = 0,
        buttonOK = 1,
        buttonCancel = 2
    };

signals:
    void requiredMessage(KCMessageBoxPanel::buttonState value);
    void requiredExit();

private slots:
    void sendSignals(int buttonIndex);

private:
    KCGraphicButtonOK *okButton;
    KCGraphicButtonCancel *cancelButton;
    QSignalMapper *buttonMapper;
    QHBoxLayout *panelLayout;
};

class KCMessageBoxContext : public QWidget
{
    Q_OBJECT
public:
    explicit KCMessageBoxContext(QWidget *parent = 0);
    void addWidget(QWidget *widget);
    void addText(const QString &text);
    void addSpacing(const int &value);
    void addImage(const QString &path, int width=-1, int height=-1);
    void addImage(QPixmap pixmap, int width=-1, int height=-1);
    int getHeightSizeHint() const;
    int getWidthSizeHint() const;

protected:
    void resizeEvent(QResizeEvent *e);

public slots:

private:
    QLabel *upIndicator, *downIndicator;
    QWidget *context;
    QVBoxLayout *contextLayout;
    int insertPlace;
    int heightSizeHint=0, widthSizeHint=0;
};

class KCMessageBox : public QDialog
{
    Q_OBJECT
public:
    explicit KCMessageBox(QWidget *parent = 0);
    void setTitle(const QString &text);
    void addText(const QString &text);
    void addImage(const QString &path,
                  int width=-1,
                  int height=-1);
    void addImage(QPixmap pixmap,
                  int width=-1,
                  int height=-1);
    void addSpacing(int value);
    void addWidget(QWidget *widget);
    void enabledCancel();

    KCMessageBoxPanel::buttonState messageBoxState();

signals:

public slots:

protected:
    void showEvent(QShowEvent *e);
    void keyPressEvent(QKeyEvent *e);

private slots:
    void messageFilter(KCMessageBoxPanel::buttonState message);

private:
    KCMessageBoxPanel::buttonState messageState;
    QVBoxLayout *mainLayout;
    QPropertyAnimation *widthExpand, *heightExpand;
    QSequentialAnimationGroup *showAnimation;

    int expectedWidth, expectedHeight;

    KCMessageBoxTitle *title;
    KCMessageBoxPanel *panel;
    KCMessageBoxContext *context;

    QRect beginState, heightExState, finalState;
};

#endif // KCMESSAGEBOX_H
