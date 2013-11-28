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

#ifndef KCPREFERENCEITEMINT_H
#define KCPREFERENCEITEMINT_H

#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QDial>

#include "kcpreferenceitembase.h"

class KCPreferenceItemInt : public KCPreferenceItemBase
{
    Q_OBJECT
public:
    explicit KCPreferenceItemInt(QWidget *parent = 0);
    ~KCPreferenceItemInt();
    void setOriginalValue(const QVariant &value);
    void setIntCaptionText(const QString &value);
    void setMaximumInt(const int &itemMax);
    void setMinimumInt(const int &itemMin);

signals:

public slots:

private slots:
    void syncValue(int newValue);

protected:
    QVariant getUserNewValue();
    void refreshValueDisplay();
    void setEditWidgetStatus(bool states);
    void setWidgetValue(QVariant newWidgeValue);

private:
    QString intCaptionText;

    QLabel *intCaption;
    QHBoxLayout *intLayout, *dialLayout, *intSliderLayout;
    QSpinBox *intSpinValueChanger;
    QSlider *intSliderValueChanger;
    QDial *intDialValueChanger;
};

#endif // KCPREFERENCEITEMINT_H
