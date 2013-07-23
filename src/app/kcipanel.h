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

#ifndef PANEL_H
#define PANEL_H

#include <QMetaObject>
#include <QWidget>
#include <QPlainTextEdit>
#include <QTextBlock>
#include <QPainter>
#include <QScrollBar>
#include <QAbstractTextDocumentLayout>
#include <QFont>
#include <QFontMetrics>
#include <QDebug>

#include "kcitexteditor.h"

class kciPanel : public QWidget
{
    Q_OBJECT
public:
    explicit kciPanel(QWidget *parent = 0);
    void setKciCodeEditor(kciTextEditor *editor);
    
signals:
    
public slots:

protected:
    int getFirstVisiableBlockNumber();
    int getLastVisiableBlockNumber();
    void paintEvent(QPaintEvent *event);
    virtual void draw(QPainter *painter, QTextBlock *block ,
                      int x, int y, int w, int h,
                      bool isCurrentLine) = 0;
    
private:
    kciTextEditor *e;

    int first,last;

    QMetaObject::Connection edConnection,etConnection,euConnection;
};

#endif // PANEL_H
