/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist Cuties.
 *
 *    Kreogist Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KCPREFERENCEITEMBOOLEAN_H
#define KCPREFERENCEITEMBOOLEAN_H

#include "kcpreferenceitembase.h"

class QCheckBox;
class QLabel;

class KCPreferenceItemBoolean : public KCPreferenceItemBase
{
    Q_OBJECT
public:
    explicit KCPreferenceItemBoolean(QWidget *parent = 0);
    ~KCPreferenceItemBoolean();
    void setOriginalValue(const QVariant &value);
    void refreshBooleanText();
    QString getBooleanText() const;
    void setBooleanText(const QString &value);
    void setBooleanCaptionText(const QString &value);

signals:

public slots:
    void retranslate();
    void retranslateAndSet();

protected:
    QVariant getUserNewValue();
    void refreshValueDisplay();
    void setEditWidgetStatus(bool states);
    void setWidgetValue(QVariant newWidgeValue);

private:
    QString booleanText;
    QString booleanDataText,
            booleanStatusText[2];

    QHBoxLayout *booleanLayout;
    QLabel *booleanCaption;
    QCheckBox *booleanData;

    QColor enabledColor, disabledColor;
    QPalette displayPalette;
};

#endif // KCPREFERENCEITEMBOOLEAN_H
