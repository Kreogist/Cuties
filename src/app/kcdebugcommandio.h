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
#include <QLineEdit>
#include <QComboBox>

#include "kcconnectionhandler.h"

class QVBoxLayout;
class QTextDocument;
class KCPlainTextBrowser;
class GdbController;
class QKeyEvent;

class KCDebugInput : public QComboBox
{
    Q_OBJECT
public:
    explicit KCDebugInput(QWidget *parent = 0);

signals:
    void execCommand(QString cmd);

protected:
    void keyPressEvent(QKeyEvent *e);

private:

};

class KCDebugCommandIO : public QDockWidget
{
    Q_OBJECT
public:
    explicit KCDebugCommandIO(QWidget *parent = 0);
    void setDocument(QTextDocument *document);
    void setGdbInstance(GdbController *gdbInstance);
    void clearInstance();

signals:
    void requireSetTextFocus();

public slots:
    void retranslate();
    void retranslateAndSet();

protected:
    void keyPressEvent(QKeyEvent *e);

private slots:
    void onCurrentIndexChanged(QString command);

private:
    QString windowTitleString;
    QVBoxLayout *mainLayout;
    KCPlainTextBrowser *debugOutputTextBrowser;
    //QComboBox *debugInput;
    KCDebugInput *debugInput;
    GdbController *instance;

    KCPlainTextBrowser *resetBackup;
};

#endif // KCGDBCOMMANDIO_H
