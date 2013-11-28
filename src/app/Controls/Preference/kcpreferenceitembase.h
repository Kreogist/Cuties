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

#ifndef KCPREFERENCEITEMBASE_H
#define KCPREFERENCEITEMBASE_H

#include <QVariant>
#include <QWidget>
#include <QTimeLine>
#include <QLabel>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>

class KCPreferenceOriginalLabel : public QLabel
{
    Q_OBJECT
public:
    explicit KCPreferenceOriginalLabel(QWidget *parent = 0);

signals:
    void requireResetCurrentValue();

protected:
    void mouseReleaseEvent(QMouseEvent *event);
};

class KCPreferenceItemBase : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferenceItemBase(QWidget *parent = 0);
    QVariant getCurrentValue() const;
    void setCurrentValue(const QVariant &value);
    QVariant getOriginalValue() const;
    void setOriginalValue(const QVariant &value);
    void editFinished();
    void setExpandFinishedHeight(const int &endHeight);
    int getExpandFinishedHeight() const;

signals:
    void editFocusCapture();
    void requireValueChanged();

public slots:
    void retranslate();
    void retranslateAndSet();
    void heightState(bool newState);
    void animateShow();
    void animateHide();
    void resetCurrentValue();

private slots:
    void setBackgroundAlpha(int newAlpha);
    void showEditWidget();
    void hideEditWidget();

protected slots:
    virtual void valueChangedEvent();
    void setItemHeight(int newHeight);

protected:
    virtual void setEditWidgetStatus(bool states)=0;
    virtual QVariant getUserNewValue()=0;
    virtual void refreshValueDisplay()=0;
    virtual void setWidgetValue(QVariant newWidgeValue)=0;
    void setOriginalDisplayVisible(bool statue);
    void mousePressEvent(QMouseEvent *e);
    bool valueChanged;
    bool editMode;
    QVariant originalValue, currentValue;
    int valueChangedAlpha;
    int expandEndHeight;
    QTimeLine *fadeMeOut;
    QTimeLine *expandAnimation;
    QTimeLine *foldAnimation;
    QTimeLine *showAnimation;
    QTimeLine *hideAnimation;
    QPalette pal;
    QColor backgroundColor;
    QVBoxLayout *editLayout;
    QLabel *valueDisplayer;
    KCPreferenceOriginalLabel *originalValueDisplayer;
    QString originalValueIs;
};

#endif // KCPREFERENCEITEMBASE_H
