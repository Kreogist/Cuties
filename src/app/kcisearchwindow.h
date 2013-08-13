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

#ifndef KCISEARCHWINDOW_H
#define KCISEARCHWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QToolButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDebug>
#include <QPalette>
#include <QKeySequence>
#include <QGraphicsDropShadowEffect>
#include <QFrame>
#include <QLabel>
#include <QMenu>

#include "kcitexteditor.h"
#include "kcitextsearcher.h"

class kciSearchWindow : public QWidget
{
    Q_OBJECT
public:
    explicit kciSearchWindow(kciTextEditor *parent);
    void setTextFocus();

public slots:
    void onTextChanged(const QString &text);
    void onSearcherFinished(QList<searchResult>* results);
    void moveToPrevResult();
    void moveToNextResult();
    void onMenuClicked();

protected:
    void hideEvent(QHideEvent *e);

signals:
    void hideButtonPressed();

private:
    /*kciSearchWindow must be a child of a kciTextEditor,
     *otherwise parent may be NULL.
     *Because we assume parent isn't NULL,
     *so if parent is NULL, the program will crash.
     */
    kciSearchWindow();
    void showCurrResult();

    enum menuItem
    {
        RegularExpress,
        MatchCase,
        WholeWord,
        menuItemCount
    };

    int currResultNum;

    kciTextEditor* parent;

    QHBoxLayout *searchLayout;
    QToolButton *closeButton, *upButton, *downButton;
    QLabel *lblSearchInfo;

    //TextBox
    QWidget *searchText;
    QLineEdit *SearchTexts;
    QHBoxLayout *Layout;
    QPushButton *SearchIcon;
    kciTextSearcher *searcher;

    int resultSize;

    QMenu *menu;
    QAction *menuAction[menuItemCount];
};

#endif // KCISEARCHWINDOW_H
