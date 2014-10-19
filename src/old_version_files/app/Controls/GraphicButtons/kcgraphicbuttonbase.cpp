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

#include <QPoint>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>

#include "kcgraphicbuttonbase.h"

/*!
 * \brief Constructs a KCGraphicButtonBase with the given parent and the
 * specified widget flags.
 * \param parent Specifies the parent QWidget.
 */
KCGraphicButtonBase::KCGraphicButtonBase(QWidget *parent) :
    QWidget(parent)
{
    //Initialize widget properties.
    setContentsMargins(0,0,0,0);
    setFixedSize(32,32);

    //Initial visible properties.
    QHBoxLayout *buttonLayout=new QHBoxLayout(this);
    buttonLayout->setContentsMargins(0,0,0,0);
    buttonLayout->setSpacing(0);
    setLayout(buttonLayout);

    //Initial child widgets.
    buttonGraphic=new QLabel(this);
    buttonGraphic->setContentsMargins(0,0,0,0);
    buttonGraphic->setScaledContents(true);
    buttonLayout->addWidget(buttonGraphic);
}

/*!
 * \brief Change the graphic to the image when the mouse in. If user don't
 * pressed mouse key before, this will be hover image, or else will be the
 * pressed image.
 * \param event The mouse enter event.
 */
void KCGraphicButtonBase::enterEvent(QEvent *event)
{
    buttonGraphic->setPixmap(isPressed?pressedGraphic:hoverGraphic);
    QWidget::enterEvent(event);
}

/*!
 * \brief Change the graphic to the normal image when the mouse leave.
 * \param event The mouse leave event.
 */
void KCGraphicButtonBase::leaveEvent(QEvent *event)
{
    buttonGraphic->setPixmap(normalGraphic);
    QWidget::leaveEvent(event);
}

/*!
 * \brief Change the graphic to the pressed image when the mouse press down, and
 * emit the pressed() signal at the same time.
 * \param event The mouse pressed event.
 */
void KCGraphicButtonBase::mousePressEvent(QMouseEvent *event)
{
    buttonGraphic->setPixmap(pressedGraphic);
    isPressed=true;
    QWidget::mousePressEvent(event);
    emit pressed();
}

/*!
 * \brief Change the graphic to the hover image when the mouse release, and emit
 * the clicked signal if the mouse pointer is still in the button rect.
 * \param event The mouse release event.
 */
void KCGraphicButtonBase::mouseReleaseEvent(QMouseEvent *event)
{
    buttonGraphic->setPixmap(hoverGraphic);
    isPressed=false;
    if(rect().contains(event->pos()))
    {
        emit clicked();
    }
    QWidget::mouseReleaseEvent(event);
}

/*!
 * \brief Get the pressed graphic of the button
 * \return The graphic when the mouse button is pressed.
 */
QPixmap KCGraphicButtonBase::getPressedGraphic() const
{
    return pressedGraphic;
}

/*!
 * \brief Set the pressed graphic of the button
 * \param value The graphic when the button is pressed.
 */
void KCGraphicButtonBase::setPressedGraphic(const QPixmap &value)
{
    pressedGraphic = value;
}

/*!
 * \brief Get the hover graphic of the button
 * \return The graphic when the mouse pointer is above the button.
 */
QPixmap KCGraphicButtonBase::getHoverGraphic() const
{
    return hoverGraphic;
}

/*!
 * \brief Set the hover graphic of the button
 * \param value The graphic when the mouse pointer is above the button.
 */
void KCGraphicButtonBase::setHoverGraphic(const QPixmap &value)
{
    hoverGraphic = value;
}

/*!
 * \brief Get the normal graphic of the button
 * \return The graphic when the button is doing nothing.
 */
QPixmap KCGraphicButtonBase::getNormalGraphic() const
{
    return normalGraphic;
}

/*!
 * \brief Set the normal graphic of the button
 * \param value The graphic when the button is doing nothing.
 */
void KCGraphicButtonBase::setNormalGraphic(const QPixmap &value)
{
    normalGraphic = value;
    buttonGraphic->setPixmap(normalGraphic);
}
