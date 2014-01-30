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

#ifndef KCPREFERENCEITEMPATH_H
#define KCPREFERENCEITEMPATH_H

#include <QLineEdit>
#include <QPushButton>
#include <QFileInfo>
#include <QFileDialog>

#include "kcpreferenceitembase.h"
#include "kclanguageconfigure.h"

class KCPreferenceItemPath : public KCPreferenceItemBase
{
    Q_OBJECT
public:
    explicit KCPreferenceItemPath(QWidget *parent = 0);
    ~KCPreferenceItemPath();
    void setOriginalValue(const QVariant &value);
    void setPathText(const QString &value);
    void setPathCaptionText(const QString &value);
    void setDialogTitle(const QString &newDialogTitle);
    bool getGuaranteeFileExsist() const;
    void setGuaranteeFileExsist(bool value);

signals:

public slots:
    void retranslate();
    void retranslateAndSet();
    void heightState(bool newState);

protected:
    QVariant getUserNewValue();
    void refreshValueDisplay();
    void setEditWidgetStatus(bool states);
    void setWidgetValue(QVariant newWidgeValue);

private slots:
    void getFilePath();

private:
    bool guaranteeFileExsist;

    QString pathText,
            browseText,
            dialogTitleText;

    QHBoxLayout *pathLayout;
    QLabel *pathCaption;
    QLineEdit *filePathData;
    QPushButton *browseFileAction;
};

#endif // KCPREFERENCEITEMPATH_H
