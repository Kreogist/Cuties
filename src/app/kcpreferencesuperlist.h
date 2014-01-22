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

#ifndef KCPREFERENCESUPERLIST_H
#define KCPREFERENCESUPERLIST_H

#include <QFont>
#include <QScrollArea>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QList>
#include <QResizeEvent>
#include <QSignalMapper>

#include "kcconfigure.h"

#include "Controls/Preference/kcpreferenceitembase.h"
#include "Controls/Preference/kcpreferenceitemcombo.h"
#include "Controls/Preference/kcpreferenceitemboolean.h"
#include "Controls/Preference/kcpreferenceitemint.h"
#include "Controls/Preference/kcpreferenceitembooleangroup.h"
#include "Controls/Preference/kcpreferenceitempath.h"

class KCPreferenceSuperListContent : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferenceSuperListContent(QWidget *parent = 0);
    void appendTitle(QLabel *newTitleWidget);
    void appendItem(KCPreferenceItemBase *newItemWidget);
    void appendStretch();

    int getItemCount();
    QString getItemKey(int itemIndex);
    QVariant getItemValue(int itemIndex);

signals:
    void changeHeight(int changedHeight);

public slots:
    void resetCurrentIndex();

private slots:
    void transferCurrentIndex(int newIndex);

private:
    int currentItemIndex;
    int originalHeight;
    QVBoxLayout *superListLayout;
    QList<QLabel *> superListTitles;
    QList<KCPreferenceItemBase *> superListItems;
    QSignalMapper *superListItemSignalProcessor;
};

class KCPreferenceSuperList : public QScrollArea
{
    Q_OBJECT
public:
    explicit KCPreferenceSuperList(QWidget *parent = 0);
    QLabel *addTitle(const QString &titleText);
    KCPreferenceItemCombo *addItemCombo(const QString &captionText,
                                        const QList<QString> &comboItemList,
                                        const QString &key);
    KCPreferenceItemCombo *addItemCombo(KCPreferenceItemCombo *newComboItem);
    KCPreferenceItemBoolean *addItemBoolean(const QString &captionText,
                                            const QString &key);
    KCPreferenceItemBoolean *addItemBoolean(KCPreferenceItemBoolean *newBooleanItem);
    KCPreferenceItemInt *addItemInt(const QString &captionText,
                                    const QString &key,
                                    int maxValue=100,
                                    int minValue=0);
    KCPreferenceItemInt *addItemInt(KCPreferenceItemInt *newIntItem);
    KCPreferenceItemBooleanGroup *addItemBooleanGroup(const QString &captionText,
                                                      const QString &key);
    KCPreferenceItemPath *addItemPath(KCPreferenceItemPath *newPathItem);
    KCPreferenceItemPath *addItemPath(const QString &captionText,
                                      const QString &key,
                                      QString defaultTitleValue=QString(""));
    void addStretch();

signals:

public slots:
    void resetCurrentIndex();
    virtual void applyPreference();

protected:
    void resizeEvent(QResizeEvent *event);
    QFont titleFont;
    KCPreferenceSuperListContent *contents;
    KCConfigure *instance;

};

#endif // KCPREFERENCESUPERLIST_H
