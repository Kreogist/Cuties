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

#ifndef DBGOUTPUTRECEIVER_H
#define DBGOUTPUTRECEIVER_H

#include <QStandardItemModel>
#include <QTextDocument>
#include <QPlainTextDocumentLayout>
#include <QTextCursor>

#include "gdbmivalue.h"

class dbgOutputReceiver : public QObject
{
    Q_OBJECT
public:
    explicit dbgOutputReceiver(QObject *parent = 0);

    QStandardItemModel *getStackInfoModel() const;
    QStandardItemModel *getLocalVarModel() const;
    QStandardItemModel *getWatchModel() const;
    QTextDocument *getTextStreamOutput() const;
    QStringList getWatchExpList() const;
    QString getWatchExp(const int &index) const;
    void setWatchExps(const QStringList &value);

public slots:
    void retranslate();
    void retranslateAndSet();
    void clearOutput();
    void clearTextStream();
    void addConsoleOutput(QString text);
    void addTargetOutput(QString text);
    void addLogOutput(QString text);
    void addErrorText(QString text);
    void addLocals(GdbMiValue localVars);
    void addExprValue(QString value);
    void resetExprValue();
    void addText(const QString &text);
    void appendExpr(const QString &value);
    void insertExpr(int expIndex, const QString &value);
    void modifyExpr(int expIndex, const QString &value);
    void removeExpr(int expIndex);

private:
    void insertText(const QString &text,const QTextCharFormat &charFormat);

    int watchIndex;
    QStandardItemModel *stackInfoModel;
    QStandardItemModel *localVarModel;
    QStandardItemModel *watchModel;
    QStringList watchExps;
    QTextDocument *textStreamOutput;

    QTextCharFormat normalFormat,errorFormat,targetFormat,logFormat;
    QStringList labels;
};

#endif // DBGOUTPUTRECEIVER_H
