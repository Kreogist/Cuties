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

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QTimerEvent>

class KCMessageBoxTitle : public QWidget
{
    Q_OBJECT
public:
    explicit KCMessageBoxTitle(QWidget *parent = 0);
    void setTitleText(QString newTitleText);

private:
    QLabel *titleCaption;
};

class KCMessageBoxPanel : public QWidget
{
    Q_OBJECT
public:
    explicit KCMessageBoxPanel(QWidget *parent = 0);

private:

};

class KCMessageBoxContent : public QWidget
{
    Q_OBJECT
public:
    explicit KCMessageBoxContent(QWidget *parent = 0);
    ~KCMessageBoxContent();
    void addText(QString displayText);

private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *contentLayout;
};

class KCMessageBox : public QWidget
{
    Q_OBJECT
public:
    explicit KCMessageBox(QWidget *parent = 0);
    void addText(QString displayText);

signals:

public slots:
    void show();
    void setTitle(QString messageBoxTitle);

private slots:

private:
    QVBoxLayout *mainLayout;

    //Basic widgets
    KCMessageBoxTitle *titleWidget;
    KCMessageBoxPanel *panelWidget;
    KCMessageBoxContent *contentWidget;
};

#endif // KCMESSAGEBOX_H
