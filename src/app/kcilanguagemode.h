/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist-Cute-IDE.
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

#ifndef KCILANGUAGEMODE_H
#define KCILANGUAGEMODE_H

#include <QReadWriteLock>
#include <QScopedPointer>

#include "kcicodeeditor.h"

#include "compilerbase.h"
#include "compileoutputreceiver.h"
#include "gdb.h"
#include "dbgoutputreceiver.h"

//cpp
#include "gcc.h"
#include "cpphighlighter.h"

//pascal
#include "fpc.h"
#include "pascalhighlighter.h"

class kciCodeEditor;

class kciLanguageMode : public QObject
{
    Q_OBJECT
public:
    enum modeType
    {
        plainText,
        cpp,
        pascal
    };

    enum compileState
    {
        uncompiled,
        compiling,
        compiled
    };

    explicit kciLanguageMode(QWidget *parent = 0);

    void compile();
    gdb* startDebug();
    void setMode(const modeType& type);
    void setFileSuffix(const QString& suffix);
    
    compileOutputReceiver* getCompilerReceiver() const;
    dbgOutputReceiver* getDbgReceiver() const;
    gdb* getGdbInstance() const;

signals:
    void compileSuccessfully(QString execFileName);
    
public slots:
    void onCompileFinished(bool hasError);

private:
    void resetCompilerAndHighlighter();
    void connectCompilerAndOutputReceiver();
    void connectGDBAndDbgReceiver();
    bool checkIfIsCompiling();
    void setCompileState(const compileState& state);

    modeType m_type;
    kciCodeEditor *m_parent;
    QScopedPointer<kciHighlighter> m_highlighter;

    QScopedPointer<compilerBase> compiler;
    compileOutputReceiver *compilerReceiver;
    connectionHandler compilerConnectionHandles,gdbConnectionHandles;
    compileState state;
    QReadWriteLock stateLock;

    gdb *gdbInstance;
    dbgOutputReceiver *dbgReceiver;

    QMetaObject::Connection compilerFinishedConnection;
};

#endif // KCILANGUAGEMODE_H
