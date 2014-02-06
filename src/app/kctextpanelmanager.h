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

/*!
 * \details
 *    This file is the function implementation file of class KCTextPanelManager.
 *    KCTextPanelManager is designed to manage all the panels which will be used
 * at KCTextEditor. It also control the repaint of all the panels. All the data
 * the panels need can be get when it repaint. KCTextPanelManager will give
 * every panel the block and the block data pointer to the panel.
 */

#ifndef KCTEXTPANELMANAGER_H
#define KCTEXTPANELMANAGER_H

#include <QWidget>

class QHBoxLayout;
class QPaintEvent;
class KCTextPanel;

class KCTextPanelManager : public QWidget
{
    Q_OBJECT
public:
    explicit KCTextPanelManager(QWidget *parent = 0);
    void addPanel(KCTextPanel *panel);
    int resizeManagerWidth(int lineNumberPanelWidth);

signals:
    /*!
     * \brief This signal is used to ask text editor to paint every panel,
     * because the text editor knows all the panel should paint at where.
     */
    void requirePaintPanel(KCTextPanel *panel,
                           QPaintEvent *event);
    /*!
     * \brief This signal is used to ask text editor tell every panels to update
     * themselves.
     */
    void requireUpdateAllPanel();
    /*!
     * \brief This signal is used to ask every panels to update themselves.
     */
    void requireUpdatePanel();

public slots:
    void updateAllPanels();

protected:

private:
    QHBoxLayout *layout;

};

#endif // KCTEXTPANELMANAGER_H
