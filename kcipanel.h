/*
 *  Copyright 2013 Wang Luming
 *
 *  kcipanel.h is part of Kreogist-Cute-IDE.
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

#include <QDebug>

class kciPanel : public QWidget
{
    Q_OBJECT
public:
    explicit kciPanel(QWidget *parent = 0);
    void setPlainTextEdit(QPlainTextEdit* editor);
    
signals:
    
public slots:

protected:
    void paintEvent(QPaintEvent *event);
    virtual void draw(QPainter *painter, QTextBlock *block ,
                      int x, int y, int w, int h,
                      bool isCurrentLine) = 0;
    
private:
    QPlainTextEdit *e;

    QMetaObject::Connection eConnection,edConnection,etConnection;
};

#endif // PANEL_H
