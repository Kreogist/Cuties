/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *      Wang Luming <wlm199558@126.com>
 *      Miyanaga Saki <tomguts@126.com>
 *      Zhang Jiayi <bf109g2@126.com>
 *
 *  This file is part of Kreogist-Cute-IDE.
 *
 *    Kreogist-Cute-IDE is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cute-IDE is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cute-IDE.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KCICONTROLCENTER_H
#define KCICONTROLCENTER_H

#include <QWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QPalette>
#include <QFrame>
#include <QLabel>
#include <QIcon>
#include <QSize>
#include <QHBoxLayout>
#include <QStackedWidget>

class kciControlCenterBanner : public QWidget
{
    Q_OBJECT
public:
    explicit kciControlCenterBanner(QWidget *parent = 0);

private:
    QLabel *lblBannerTitle;

};

class ccGeneral : public QWidget
{
    Q_OBJECT
public:
    explicit ccGeneral(QWidget *parent = 0);
private:

};

class ccEditor : public QWidget
{
    Q_OBJECT
public:
    explicit ccEditor(QWidget *parent = 0);
private:
};

class ccCompiler : public QWidget
{
    Q_OBJECT
public:
    explicit ccCompiler(QWidget *parent = 0);
private:
};

class ccDebugger : public QWidget
{
    Q_OBJECT
public:
    explicit ccDebugger(QWidget *parent = 0);
private:
};

class ccFileAssociation : public QWidget
{
    Q_OBJECT
public:
    explicit ccFileAssociation(QWidget *parent = 0);
private:
};

class ccLanguage : public QWidget
{
    Q_OBJECT
public:
    explicit ccLanguage(QWidget *parent = 0);
private:
};

class kciControlCenter : public QWidget
{
    Q_OBJECT
public:
    explicit kciControlCenter(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    QStackedWidget *ccMainTabs;
    ccGeneral *tabGeneral;
    ccEditor *tabEditor;
    ccCompiler *tabCompiler;
    ccDebugger *tabDebugger;
    ccFileAssociation *tabFileAssociation;
    ccLanguage *tabLanguage;
    QVBoxLayout *WholeTitleBarSplit;
    kciControlCenterBanner *ccBanner;

    void createLeftList();
    
};

#endif // KCICONTROLCENTER_H
