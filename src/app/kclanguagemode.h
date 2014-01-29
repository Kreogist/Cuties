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

#ifndef KCLANGUAGEMODE_H
#define KCLANGUAGEMODE_H

#include <QReadWriteLock>
#include <QScopedPointer>

#include "kccodeeditor.h"

#include "kchighlighter.h"
#include "kccompileoutputreceiver.h"
#include "gdbcontroller.h"

class KCCodeEditor;

class KCLanguageMode : public QObject
{
    Q_OBJECT
public:
    enum modeType
    {
        Invalid,
        PlainText,
        Cpp,
        C,
        Pascal,
        ModeTypeCount
    };

    enum compileState
    {
        uncompiled,
        compiling,
        compiled
    };

    explicit KCLanguageMode(QWidget *parent = 0);
    bool compilerIsNull();
    bool compilerIsExsist();
    void compile();
    void stopCompile();
    GdbController *startDebug(int lineNumber);
    void stopDebug();
    void setMode(const modeType &type);
    void setFileSuffix(const QString &suffix);

    KCCompileOutputReceiver *getCompilerReceiver() const;
    GdbController *getGdbController() const;

signals:
    void compileSuccessfully(QString execFileName);
    void requireHideCompileDock();
    void requireDisconnectDebug();
    void compileFinished();
    void compileErrorOccur(int errors);
    void requireSmartPanelError(int errorLine);
    void requireDrawError();
    void requireDebugJumpLine(int debugLine);

public slots:
    void onCompileFinished(bool hasError);
    void setBreakPointAtLine(int line);

private:
    void resetCompilerAndHighlighter();
    void connectCompilerAndOutputReceiver();
    void connectGDBAndDbgReceiver();
    bool checkIfIsCompiling();
    void setCompileState(const compileState &state);

    modeType m_type;
    KCCodeEditor *m_parent;
    QScopedPointer<KCHighlighter> m_highlighter;

    QScopedPointer<KCCompilerBase> compiler;
    KCCompileOutputReceiver *compilerReceiver;
    KCConnectionHandler compilerConnectionHandles;
    compileState state;
    QReadWriteLock stateLock;
    QString languageName[ModeTypeCount];

    GdbController *gdbControllerInstance;

    QMetaObject::Connection compilerFinishedConnection;
};

#endif // KCLANGUAGEMODE_H
