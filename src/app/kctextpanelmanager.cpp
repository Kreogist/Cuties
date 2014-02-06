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

#include <QDebug>
#include <QHBoxLayout>
#include <QPaintEvent>

#include "kctextpanel.h"

#include "kctextpanelmanager.h"

/*!
 * \brief Constructs a KCTextPanelManager with the given parent and the
 * specified widget flags.
 * \param parent Specifies the parent QWidget.
 */
KCTextPanelManager::KCTextPanelManager(QWidget *parent) :
    QWidget(parent)
{
    setContentsMargins(0,0,0,0);
    layout=new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    setLayout(layout);
}

/*!
 * \brief Add a panel to the panel manager, connect the repaint require signal
 * to the manager's require signal, and repaint all the widget signal to the
 * updateAllPanel() slot.
 * \param panel Specifies the panel will be add to the manager.
 */
void KCTextPanelManager::addPanel(KCTextPanel *panel)
{
    connect(panel, &KCTextPanel::requireRepaintPanel,
            this,  &KCTextPanelManager::requirePaintPanel);
    connect(panel, &KCTextPanel::requireUpdateAllPanel,
            this,  &KCTextPanelManager::requireUpdateAllPanel);
    connect(this,  SIGNAL(requireUpdatePanel()),
            panel, SLOT(update()));
    layout->addWidget(panel);
}

/*!
 * \brief resizeManagerWidth() function will call all the virtual function
 * setPanelWidth() of the panels which beyond its control to resize panels. And
 * it will also calculate the manager's width, set the manager's width and
 * return it.
 * The manager will get the line number panel's width. Because there're only two
 * kinds of panels: The width relate to the total line number and not. So tell
 * every panel what the line number panel's width is, panels will auto calculate
 * their owns.
 * \param lineNumberPanelWidth The width of the line number panel width.
 * \return the width of KCTextPanelManager.
 */
int KCTextPanelManager::resizeManagerWidth(int lineNumberPanelWidth)
{
    int panelCount=layout->count(), managerWidth=0;
    for(int i=0;i<panelCount;i++)
    {
        KCTextPanel *panel=static_cast<KCTextPanel *>(layout->itemAt(i)->widget());
        panel->setPanelWidth(lineNumberPanelWidth);
        managerWidth+=panel->width();
    }
    setFixedWidth(managerWidth);
    return managerWidth;
}

/*!
 * \brief This slot function is used to emit panel paint signal. To ask every
 * panel to update themselves.
 */
void KCTextPanelManager::updateAllPanels()
{
    emit requireUpdatePanel();
}
