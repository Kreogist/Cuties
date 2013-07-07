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

#include "kcicontrolcenter.h"

kciControlCenterBanner::kciControlCenterBanner(QWidget *parent):
    QWidget(parent)
{
    lblBannerTitle=new QLabel(this);
    lblBannerTitle->setText(tr("Cuties Control Center"));
}

ccGeneral::ccGeneral(QWidget *parent):
    QWidget(parent)
{

}

ccEditor::ccEditor(QWidget *parent):
    QWidget(parent)
{

}

ccCompiler::ccCompiler(QWidget *parent):
    QWidget(parent)
{

}

ccDebugger::ccDebugger(QWidget *parent):
    QWidget(parent)
{

}

ccFileAssociation::ccFileAssociation(QWidget *parent):
    QWidget(parent)
{

}

ccLanguage::ccLanguage(QWidget *parent):
    QWidget(parent)
{

}

kciControlCenter::kciControlCenter(QWidget *parent) :
    QWidget(parent)
{
    setFont(QFont(QString("Hiragino Sans GB W3")));

    //Set Whole Layout
    WholeTitleBarSplit=new QVBoxLayout(this);
    setLayout(WholeTitleBarSplit);

    //Set Banner
    ccBanner=new kciControlCenterBanner(this);
    WholeTitleBarSplit->addWidget(ccBanner);

    //Set Tabs
    ccMainTabs=new QStackedWidget(this);
    tabGeneral=new ccGeneral(this);
    tabEditor=new ccEditor(this);
    tabCompiler=new ccCompiler(this);
    tabDebugger=new ccDebugger(this);
    tabFileAssociation=new ccFileAssociation(this);
    tabLanguage=new ccLanguage(this);

    WholeTitleBarSplit->addWidget(tabGeneral);
    WholeTitleBarSplit->addWidget(tabEditor);
    WholeTitleBarSplit->addWidget(tabCompiler);
    WholeTitleBarSplit->addWidget(tabDebugger);
    WholeTitleBarSplit->addWidget(tabFileAssociation);
    WholeTitleBarSplit->addWidget(tabLanguage);
}
