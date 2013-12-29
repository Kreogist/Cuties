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

#ifndef KCREPLACEWINDOW_H
#define KCREPLACEWINDOW_H

#include <QTimeLine>
#include <QSignalMapper>

#include "kcsearchwidget.h"

class KCReplaceWindow : public KCSearchWidget
{
    Q_OBJECT
public:
    explicit KCReplaceWindow(QWidget *parent = 0);

signals:
    void requireReplace(const QString &oldText,const QString &newText);
    void requireReplaceAndFind(const QString &oldText, const QString &newText);
    void requireReplaceAll(const QString &oldText, const QString &newText);

public slots:
    void animeShow();
    void animeHide();

private slots:
    void resizeDock(int newHeight);
    void onOneOfReplaceButtonsClicked(int type);

private:
    enum replaceButtonType
    {
        replace,
        findAndReplace,
        replaceAll,
        typeCount
    };

    QGridLayout *mainLayout;
    QLineEdit *replaceText;
    QToolButton *replaceButtons[typeCount];
    QToolButton *closeButton;

    QSignalMapper *mapper;
    QTimeLine *showAnimation, *hideAnimation;
};

#endif // KCREPLACEWINDOW_H
