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

#include <QFile>
#include <QTextCursor>
#include <QString>
#include <QWidget>

#include <QDebug>

#include "kclanguagemode.h"
#include "kccodecompileprogress.h"
#include "kcconnectionhandler.h"

class QVBoxLayout;
class QHBoxLayout;
class KCEditorConfigure;
class KCSearchWindow;
class KCReplaceWindow;
class KCLanguageMode;
class KCTextEditor;
class KCMarkPanel;
class KCSmartPanel;
class KCLinenumPanel;
class KCSearchWidget;

class KCCodeEditor : public QWidget
{
    Q_OBJECT
public:
    explicit KCCodeEditor(QWidget *parent = 0);
    ~KCCodeEditor();

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
    QTextDocument *document();
    KCLanguageMode *langMode() const;
    void setLanguageMode(KCLanguageMode *value);
    bool getOverwriteMode();

    void insertTextAtCursor(QString insertText);
    bool getCacheNewFileMode() const;
    void setCacheNewFileMode(bool value);
    bool getDebugging() const;
    void setDebugging(bool value);

signals:
    void filenameChanged(QString newName);
    void fileTextCursorChanged();
    void rewriteStateChanged(bool nowValue);
    void requiredHideDocks();

public slots:
    bool open(const QString &fileName,
              bool cacheMode=false);
    bool save();
    bool saveAs();
    bool saveAs(const QString &fileName,
                bool cacheMode=false);
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
    void showCompileBar();
    void setOverwriteMode(bool newValue);
    bool readCacheFile(const QString &cachedfilePath);
    bool writeCacheFile(const QString &filePath);

private slots:
    void onModificationChanged(bool changed);
    void onHideOtherWidgets();
    void onSearchNext(QString searchTextSets,
                      bool regularExpressionSets,
                      bool caseSensitivelySets,
                      bool wholeWordSets);
    void onShowNextSearchResult();
    void setUseLastCuror();

protected:
    void closeEvent(QCloseEvent *e);
    void resizeEvent(QResizeEvent *e);

private:
    bool searchUseLastCursor;
    bool processSaveAsAction(const QString &dialogCaption);
    bool requireSaveAs(const QString &Caption);
    void computeExecFileName();
    void fileInfoChanged(const QFile &file);
    void connectSearchWidgetWithEditor(KCSearchWidget *widget);

    KCEditorConfigure *configureInstance;

    KCLanguageMode *languageMode;

    KCCodeCompileProgress *currentCompileProgress;

    QVBoxLayout *replaceLayout;
    QHBoxLayout *mainLayout;
    KCTextEditor *editor;
    KCLinenumPanel *linePanel;
    KCMarkPanel *markPanel;
    KCSmartPanel *smartPanel;

    QString filePath;
    QString execFileName;
    QFileDevice::FileError fileError;
    QTextCursor fileTextCursor;

    KCSearchWidget *currentSearchWidget;
    KCSearchWindow *searchBar;
    KCReplaceWindow *replaceBar;

    KCConnectionHandler searcherConnections;

    friend class KCLanguageMode;
    bool cacheNewFileMode;
    bool debugging;
};

#endif // TEXTEDITOR_H
