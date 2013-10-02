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

#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QHBoxLayout>
#include <QPalette>
#include <QFile>
#include <QPlainTextEdit>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
#include <QTextCursor>
#include <QErrorMessage>
#include <QSettings>
#include <QIcon>
#include <QPropertyAnimation>
#include <QTimeLine>
#include <QScrollBar>
#include <QGraphicsOpacityEffect>
#include <QScrollBar>
#include <QDebug>

#include "kchistoryconfigure.h"
#include "kcgeneralconfigure.h"
#include "kctexteditor.h"
#include "kclinenumpanel.h"
#include "kcmarkpanel.h"
#include "kcsearchwindow.h"
#include "kclanguagemode.h"
#include "kcreplacedock.h"
#include "kcconnectionhandler.h"

class KCISearchWindow;
class KCILanguageMode;

class KCICodeEditor : public QWidget
{
    Q_OBJECT
public:
    explicit KCICodeEditor(QWidget *parent = 0);
    ~KCICodeEditor();

    QFileDevice::FileError error();
    void setDocumentTitle(const QString &title);
    QString getDocumentTitle();
    void setDocumentCursor(int nLine, int linePos);
    void setTextFocus();
    QString getFilePath();
    QString getExecFileName();
    QTextCursor getTextCursor();

    int getTextLines();
    bool isModified();
    QTextDocument* document();
    KCILanguageMode *langMode() const;
    bool getOverwriteMode();

    void insertTextAtCursor(QString insertText);

signals:
    void filenameChanged(QString newName);
    void fileTextCursorChanged();
    void rewriteStateChanged(bool nowValue);

public slots:
    bool open(const QString &fileName);
    bool save();
    bool saveAs();
    bool saveAs(const QString &fileName);
    void redo();
    void undo();
    void copy();
    void cut();
    void paste();
    void selectAll();
    void cursorChanged();
    QString getSelectedText();
    void showSearchBar();
    void showReplaceBar();
    void hideSearchBar();
    void setOverwriteMode(bool newValue);

private slots:
    void onModificationChanged(bool changed);

protected:
    void closeEvent(QCloseEvent *e);
    void resizeEvent(QResizeEvent *e);

private:
    void computeExecFileName();
    void fileInfoChanged(const QFile &file);
    bool dosaveas(const QString &Caption);
    void connectSearchWidgetWithEditor(KCISearchWidget *widget);

    QGraphicsOpacityEffect *initEffect;

    KCILanguageMode *m_langMode;

    QVBoxLayout *replaceLayout;
    QHBoxLayout *mainLayout;
    KCITextEditor *editor;
    KCILinenumPanel *linePanel;
    KCIMarkPanel *markPanel;

    QString filePath,strFileFilter;
    QString execFileName;
    QFileDevice::FileError fileError;
    QTextCursor fileTextCursor;

    KCISearchWindow *searchBar;
    KCIReplaceDock *replaceBar;

    KCConnectionHandler searcherConnections;

    friend class KCILanguageMode;
};

#endif // TEXTEDITOR_H
