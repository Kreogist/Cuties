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
#include <QResizeEvent>

#include "kctextsearcher.h"
#include "kcfloattoolbar.h"
#include "kctextpanelmanager.h"
#include "kclinenumberpanel.h"
#include "kcunibodypanel.h"

class KCClipboard;

class KCTextEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit KCTextEditor(QWidget *parent = 0);
    void setCursorPosition(int lineNumber,
                           int columnNumber);
    void backupSearchTextCursor();
    QRectF blockRect(const QTextBlock &block);
    void setVerticalScrollValue(int value);
    void setHorizontalScrollValue(int value);
    int verticalScrollValue();
    int horizontalScrollValue();
    QList<int> getBreakPoints();
    void setUsingBlankInsteadTab(bool value);
    void setSpacePerTab(int value);
    void zoomIn(int range = 1);
    void zoomOut(int range = 1);

    int lineNumberPanelWidth();

signals:
    void requireHideOthers();
    void updated();
    void searchStringChangedByShortCut(QString searchText);
    void overwriteModeChanged(bool newValue);
    void matchedResult();
    void nomatchedResult();

public slots:
    void updateHighlights();
    //void pasteFromeHistory();
    void updatePanelManager();
    bool showPreviousSearchResult();
    bool showNextSearchResult();
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

private slots:
    void updateSearchResults();
    void panelPaintEvent(KCTextPanel *panel,
                                  QPaintEvent *event);

    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &, int);

protected:
    void paintEvent(QPaintEvent *e);
    void contextMenuEvent(QContextMenuEvent *event);
    void keyPressEvent(QKeyEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *event);

    void resizeEvent(QResizeEvent *event);

private:
    void highlightCurrentLine(QList<QTextEdit::ExtraSelection> &selections);
    void highlightSearchResult(QList<QTextEdit::ExtraSelection> &selections);
    int highlightParentheses(QList<QTextEdit::ExtraSelection> &selections);
    void highlightParenthesisPairs(QList<QTextEdit::ExtraSelection> &selections,
                                   int matchedParentheses,
                                   QTextCursor cursor);
    QString parenthesesPair(const QString &parenthesesChar);
    bool findForward();
    bool findBackward();
    bool findFirstSeachResult();
    bool findLastSearchResult();
    void generalSearch(const QTextBlock &block,
                       const int &lines,
                       const bool forward);
    void searchOnOtherThread(QScopedPointer<KCTextSearcher> &searcher,
                             QFuture<void> &thread,
                             const QTextBlock &block,
                             const bool forward);
    void initTextSearcher(QScopedPointer<KCTextSearcher> &searcher);
    void checkWhetherBlockSearchedAndDealWith(const QTextBlock &block);
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
};

#endif // CODEEDITOR_H
