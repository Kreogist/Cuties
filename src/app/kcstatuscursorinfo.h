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

#ifndef KCSTATUSCURSORINFO_H
#define KCSTATUSCURSORINFO_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QSpinBox>

class KCStatusCursorInfo : public QWidget
{
    Q_OBJECT
public:
    explicit KCStatusCursorInfo(QWidget *parent = 0);
    void showGotoBox(int currentValue, int maxValue);
    void hideGotoBox();
    bool getGotoShowed();

signals:
    void toNewLineNum(int newLineNumber);

public slots:
    void retranslate();
    void retranslateAndSet();
    void updateCursorPosition(int newLineNum, int newColumnNum);
    void gotoLineNumber(int newLineNum);
    void finishedHideGotoBox();

private slots:
    void setHideGotoBox();

private:
    void refresh();
    QSpinBox *gotoLineNum;
    QLabel *cursorPosition;
    bool gotoBarShowed;
    QString lineNumString, columnNumString;
    QPropertyAnimation *gotoHideAnime;

    QString lineTextBegin, lineTextEnd, colTextBegin, colTextEnd;

};

#endif // KCSTATUSCURSORINFO_H
