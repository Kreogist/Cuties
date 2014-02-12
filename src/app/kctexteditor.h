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

/*!
 * \copyright GNU Public License v3
 * \details
 * This file is the function implementation file of class KCTextEditor.
 * KCTextEditor is the basic editor class to all other language. All the other
 * language's text editor will be inherited this class and rewrite
 * keyPressEvent().
 */

#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QTextCursor>
#include <QTextBlock>
#include <QScopedPointer>
#include <QSignalMapper>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QFont>
#include <QFontMetrics>
#include <QList>
#include <QShowEvent>
#include <QResizeEvent>

#include "kctextsearcher.h"
#include "kcfloattoolbar.h"
#include "kctextpanelmanager.h"
#include "kclinenumberpanel.h"
#include "kcunibodypanel.h"
#include "kcdebugmarkpanel.h"

class KCClipboard;

class KCTextEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit KCTextEditor(QWidget *parent = 0);
    //********** Properties **********
    int horizontalScrollValue();
    void resetDebugCursor();
    void setCursorPosition(int lineNumber,
                           int columnNumber);
    void setHorizontalScrollValue(int value);
    void setSpacePerTab(int value);
    void setUsingBlankInsteadTab(bool value);
    void setVerticalScrollValue(int value);
    int verticalScrollValue();

    //********** Functions **********
    //Search & Replace
    void backupSearchTextCursor();

    //Panel values
    QList<int> getBreakPoints();
    int lineNumberWidth();
    void setDebugCursor(int lineNumber);
    void setLinePanelVisible(bool value);
    void setLineColor(const QColor &value);
    void setSearchResultColor(const QColor &value);
    void setNoMatchedParenthesesColor(const QColor &value);
    void setMatchedParenthesesColor(const QColor &value);

signals:
    void requireHideOthers();
    void searchStringChangedByShortCut(QString searchText);
    void overwriteModeChanged(bool newValue);
    void matchedResult();
    void nomatchedResult();

public slots:
    void zoomIn(int range = 1);
    void zoomOut(int range = 1);
    void updateHighlights();
    //void pasteFromeHistory();
    void updateAllPanels();
    bool findNextSearchResult();
    bool findPreviousSearchResult();
    bool findFirstSeachResult();
    bool findLastSearchResult();
    void searchString(QString searchTextSets,
                      bool regularExpressionSets,
                      bool caseSensitivelySets,
                      bool wholeWordSets);
    bool replace(const QString &oldText,const QString &newText);
    bool replaceAndFind(const QString &oldText, const QString &newText);
    bool replaceAll(const QString &oldText, const QString &newText);
    void autoIndent();
    void setTabWidth(int width);
    void setWordWrap(QTextOption::WrapMode wrapMode);
    void setTheCursorWidth(int width);
    void setLineErrorState(QList<int> errorList);
    void setCursorAtLine(int blockNumber);

private slots:
    void updateSearchResults();
    void panelPaintEvent(KCTextPanel *panel,
                         QPaintEvent *event);

    void updatePanelAreaWidth();
    void foldCode(int startFoldBlockIndex);
    void unfoldCode(int startUnfoldBlockIndex);
    void selectBlock(int blockNumber);

protected:
    void showEvent(QShowEvent *event);
    void paintEvent(QPaintEvent *e);
    void contextMenuEvent(QContextMenuEvent *event);
    void keyPressEvent(QKeyEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *event);

    void resizeEvent(QResizeEvent *event);

private:
    bool showPreviousSearchResult(const QTextCursor &cursor);
    bool showNextSearchResult(const QTextCursor &cursor);
    void highlightCurrentLine(QList<QTextEdit::ExtraSelection> &selections);
    void highlightSearchResult(QList<QTextEdit::ExtraSelection> &selections);
    int highlightParentheses(QList<QTextEdit::ExtraSelection> &selections);
    void highlightParenthesisPairs(QList<QTextEdit::ExtraSelection> &selections,
                                   int matchedParentheses,
                                   QTextCursor cursor);
    QString parenthesesPair(const QString &parenthesesChar);
    void generalSearch(const QTextBlock &block,
                       const int &lines,
                       const bool forward);
    void searchOnOtherThread(QScopedPointer<KCTextSearcher> &searcher,
                             QFuture<void> &thread,
                             const QTextBlock &block,
                             const bool forward);
    void initTextSearcher(QScopedPointer<KCTextSearcher> &searcher);
    void checkWhetherBlockSearchedAndDealWith(const QTextBlock &block,
            KCTextBlockData *data);
    int matchParentheses(const char &parenthesesA,
                         const char &parenthesesB,
                         QList<parenthesesInfo>::iterator startPos,
                         QTextBlock block,
                         bool forward);
    int findFirstCharacter(const QTextBlock &block);
    void insertTab(QTextCursor insertTabCursor, int tabCount = 1, bool forceInsert = false);
    void removeTab(QTextCursor removeTabCursor, int tabCount = 1);
    void tabPressEvent(QTextCursor tabPressCursor);

    KCClipboard *clipboard;
    QColor lineColor;
    QColor searchResultColor;
    QColor noMatchedParenthesesColor;
    QColor matchedParenthesesColor;

    bool usingBlankInsteadTab=true;
    int spacePerTab=4;
    int tabSpace=4;

    QString searchText;
    QString leftParenthesesLists=QString("([{");
    QString rightParenthesesLists=QString(")]}");
    bool searchRegularExpression;
    bool searchCaseSensitively;
    bool searchWholeWord;
    unsigned long long int searchCode;
    QScopedPointer<KCTextSearcher> searcherForPrev,searcherForNext;
    QFuture<void> threadPrev,threadNext;
    QTextCursor searchBackupCursor;
    KCFloatToolBar *textFloatToolBar;

    KCTextPanelManager *panelManager;
    KCLineNumberPanel *lineNumberPanel;
    KCUnibodyPanel *unibodyPanel;
    KCDebugMarkPanel *debugMarkPanel;
};

#endif // CODEEDITOR_H
