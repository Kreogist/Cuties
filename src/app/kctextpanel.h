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
 *    This file is the function implementation file of class KCTextPanel.
 *    KCTextPanel is the based module of all the panels. Like line number panel,
 *    unibody display panel.
 */

#ifndef KCTEXTPANEL_H
#define KCTEXTPANEL_H

#include <QWidget>
#include <QPaintEvent>
#include <QTextBlock>
#include <QTextCursor>

#include "kctextblockdata.h"

class QMouseEvent;

class KCTextPanel : public QWidget
{
    Q_OBJECT
public:
    explicit KCTextPanel(QWidget *parent = 0);
    /*!
     * \brief This function will be called when the KCTextEditor repaint the
     *        panel. All the KCTextPanel must implement this function.
     */
    virtual void drawContent(int x,
                             int y,
                             int width,
                             int height,
                             QTextBlock *block,
                             KCTextBlockData *data,
                             QTextCursor textCursor)=0;
    /*!
     * \brief This function will calculate the panel's width. You can get a
     *        reference value: the width of the line number panel. The panel's
     *        width must be calculate in this function.
     * \param lineNumberPanelWidth The width of the line number panel.
     */
    virtual void setPanelWidth(int lineNumberPanelWidth)=0;

    QTextBlock getFirstBlock() const;
    void setFirstBlock(const QTextBlock &value);
    QTextBlock getLastBlock() const;
    void setLastBlock(const QTextBlock &value);

signals:
    /*!
     * \brief This signal will be emit when the panel need to be repaint. It
     *        will be emitted inside the paintEvent().
     */
    void requireRepaintPanel(KCTextPanel *panel,
                             QPaintEvent *event);

    /*!
     * \breif This signal will ask the panel manager to repaint all the panels.
     *
     *        If you emit this signal, please check it is REALLY need to repaint
     *        all the other panels. Because this event will cost a HUGE CPU
     *        usage.
     *
     *        Make sure again before you emit this signal.
     */
    void requireUpdateAllPanel();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseClickEventRaised(QTextBlock *block,
                                       KCTextBlockData *data);

private:
    QTextBlock firstBlock;
    QTextBlock lastBlock;
    QPoint pressedPos;
    bool isPressed=false;
};
#endif // KCTEXTPANEL_H
