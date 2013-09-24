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


#ifndef KCILINENUMPANEL_H
#define KCILINENUMPANEL_H

#include <QFont>
#include <QColor>

#include <QDebug>

#include "kcipanel.h"

class kciLinenumPanel : public kciPanel
{
    Q_OBJECT
public:
    explicit kciLinenumPanel(QWidget *parent = 0);
    
signals:
    
public slots:

protected:
    void draw(QPainter *painter, QTextBlock *block,
              int x, int y, int w, int h,
              bool isCurrentLine);

private:
    QColor textColor;
    
};

#endif // KCILINENUMPANEL_H
