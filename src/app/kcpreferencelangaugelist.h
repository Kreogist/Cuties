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

#ifndef KCPREFERENCELANGAUGELIST_H
#define KCPREFERENCELANGAUGELIST_H

#include <QLabel>
#include <QResizeEvent>
#include <QWidget>
#include <QScrollArea>

#include "kclanguageconfigure.h"

class KCPreferenceLangaugeListItem : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferenceLangaugeListItem(QWidget *parent = 0);
    void setLanguageIcon(const QPixmap &languagePixmap);
    void setLanguageName(const QString &captionText);

signals:
    void requireChangeLanguage();

private slots:
    void setBackgroundAlpha(int newAlpha);

protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);

private:
    QLabel *languageIcon, *languageName;
    QPalette pal;
    QColor backgroundColor;
};

class KCPreferenceLangaugeList : public QScrollArea
{
    Q_OBJECT
public:
    explicit KCPreferenceLangaugeList(QWidget *parent = 0);
    KCPreferenceLangaugeListItem *addLanguageItem(const QString &languageName,
                                                  const QPixmap &languageIcon);

signals:
    void requireChangeLanguage(int languageIndex);

public slots:

protected:
    void resizeEvent(QResizeEvent *e);

private:
    KCLanguageConfigure *instance;
    QList<KCPreferenceLangaugeListItem *> languageItems;
    QWidget *languageContents;
};

#endif // KCPREFERENCELANGAUGELIST_H
