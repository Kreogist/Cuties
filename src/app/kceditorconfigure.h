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

#ifndef KCEDITORCONFIGURE_H
#define KCEDITORCONFIGURE_H

#include <QList>
#include <QDebug>
#include <QTextOption>

#include "kcconfigure.h"

class KCEditorConfigure : public KCConfigure
{
    Q_OBJECT

public:
    void readConfigure();
    void writeConfigure();
    static KCEditorConfigure *getInstance();

    QTextOption::WrapMode indexToWrapMode(int index);
    int getWrapModeNumber(QTextOption::WrapMode destinationWrapMode) const;

protected:
    QString getGroupName() const;

signals:
    void editorConfigureRefresh();

private:
    KCEditorConfigure() {}
    static KCEditorConfigure *instance;
};


#endif // KCEDITORCONFIGURE_H
