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

#ifndef KCGRAPHICBUTTONBASE_H
#define KCGRAPHICBUTTONBASE_H

#include <QLabel>
#include <QWidget>

class KCGraphicButtonBase : public QWidget
{
    Q_OBJECT
public:
    explicit KCGraphicButtonBase(QWidget *parent = 0);
    QPixmap getNormalGraphic() const;
    QPixmap getHoverGraphic() const;
    QPixmap getPressedGraphic() const;
    void setNormalGraphic(const QPixmap &value);
    void setHoverGraphic(const QPixmap &value);
    void setPressedGraphic(const QPixmap &value);

signals:
    void pressed();
    void clicked();

public slots:

protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    QLabel *buttonGraphic;
    QPixmap normalGraphic, hoverGraphic, pressedGraphic;
};

#endif // KCGRAPHICBUTTONBASE_H
