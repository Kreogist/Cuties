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

#ifndef KCISTATUSCURSORINFO_H
#define KCISTATUSCURSORINFO_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QSpinBox>

class kciStatusCursorInfo : public QWidget
{
    Q_OBJECT
public:
    explicit kciStatusCursorInfo(QWidget *parent = 0);
    void ShowGotoBox(int currentValue, int MaxValue);
    void HideGotoBox();
    bool getGotoShowed();
    
signals:
    void ToLineNum(int LineNum);

protected:
    void resizeEvent(QResizeEvent *e);

public slots:
    void updateCursorPosition(int LineNum, int ColNum);
    void gotoLineNumber(int NewNum);
    void finishedHideGotoBox();

private slots:
    void setHideGotoBox();

private:
    QSpinBox *spbLineNum;
    QLabel *lblCursorPosition;
    bool gotoBarShowed;

    QPropertyAnimation *gotoHideAnime;

};

#endif // KCISTATUSCURSORINFO_H
