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

#ifndef PANEL_H
#define PANEL_H

#include <QMetaObject>
#include <QPlainTextEdit>
#include <QTextBlock>
#include <QPainter>
#include <QScrollBar>
#include <QFontMetrics>
#include <QDebug>

#include "kctexteditor.h"
#include "kcconnectionhandler.h"

class KCPanel : public QWidget
{
    Q_OBJECT
public:
    explicit KCPanel(QWidget *parent = 0);
    void setKciTextEditor(KCTextEditor *editor);
    void setAutoAdaptWidth(bool newValue);
    bool autoAdaptWidth();

signals:

public slots:

protected:
    QTextBlock getFirstVisiableBlock();
    QTextBlock getLastVisiableBlock();
    int getFirstVisiableBlockNumber();
    int getLastVisiableBlockNumber();
    void paintEvent(QPaintEvent *event);
    virtual void draw(QPainter *painter, QTextBlock *block ,
                      int x, int y, int w, int h,
                      bool isCurrentLine) = 0;

private:
    int getRealLineCount(const QTextBlock& block, const int &offset);
    KCTextEditor *e;

    int first,last;

    bool autoWidth;

    KCConnectionHandler connectionHandles;
};

#endif // PANEL_H
