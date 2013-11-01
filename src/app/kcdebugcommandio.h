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

#ifndef KCGDBCOMMANDIO_H
#define KCGDBCOMMANDIO_H

#include <QDockWidget>

#include "kcconnectionhandler.h"

class QVBoxLayout;
class QComboBox;
class QTextDocument;
class KCPlainTextBrowser;
class gdb;

class KCDebugCommandIO : public QDockWidget
{
    Q_OBJECT
public:
    explicit KCDebugCommandIO(QWidget *parent = 0);
    void setDocument(QTextDocument *document);
    void setGdbInstance(gdb *gdbInstance);

public slots:
    void retranslate();
    void retranslateAndSet();

private slots:
    void onCurrentIndexChanged(QString command);

private:
    QString windowTitleString;
    QVBoxLayout *mainLayout;
    KCPlainTextBrowser *debugOutputTextBrowser;
    QComboBox *debugInput;
    gdb *instance;
};

#endif // KCGDBCOMMANDIO_H
