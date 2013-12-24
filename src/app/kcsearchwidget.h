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

#ifndef KCSEARCHWIDGET_H
#define KCSEARCHWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QToolButton>
#include <QResizeEvent>
#include <QMenu>

class KCSearchTextBox : public QLineEdit
{
    Q_OBJECT
public:
    explicit KCSearchTextBox(QWidget *parent = 0);

signals:
    void requireSearchNext();
    void requireLostFocus();

protected:
    void keyPressEvent(QKeyEvent *e);

private:
};

class KCSearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KCSearchWidget(QWidget *parent = 0);
    void setTextFocus();
    void setText(const QString &text);
    QString text() const;
    static const int searchTextPartWidth;
    void restoreLastSearchText();

    bool getConnected() const;
    void setConnected(bool value);

signals:
    void requireShowPreviousResult();
    void requireShowNextResult();
    void requireSearch(QString text,
                       bool regularExpression,
                       bool caseSensitively,
                       bool wholeWorld);
    void requireLostFocus();

public slots:
    void onTextChanged(const QString &text);
    void onMenuClicked();
    void setResultMatchStyle();
    void setResultUnmatchStyle();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    enum menuItem
    {
        menuRegularExpress,
        menuMatchCase,
        menuWholeWord,
        menuItemCount
    };

    int currResultNum;
    bool connected;

    QGridLayout *searchLayout;
    QToolButton *prevResult, *nextResult;
    QWidget *searchTextWidget;
    KCSearchTextBox *searchText;
    QHBoxLayout *mainLayout;
    QPushButton *searchIcon;
    QMenu *menu;
    QAction *menuAction[menuItemCount];
    QString lastSearchText;
};

#endif // KCSEARCHWIDGET_H
