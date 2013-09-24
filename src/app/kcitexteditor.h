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
#include <QPalette>
#include <QScrollBar>
#include <QScopedPointer>
#include <QMenu>
#include <QSignalMapper>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QDebug>
#include <QCommonStyle>

#include "kcitextsearcher.h"
#include "kcitextblockdata.h"
#include "kciclipboard.h"
#include "kcieditorconfigure.h"

class kciTextEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit kciTextEditor(QWidget *parent = 0);
    void setDocumentCursor(int nLine, int linePos);
    
signals:
    void updated();
    void searchStringChangedByShortCut(QString text);
    void overwriteModeChanged(bool newValue);

public slots:
    void updateHighlights();
    //void pasteFromeHistory();
    void showPreviousSearchResult();
    void showNextSearchResult();
    void searchString(QString text,
                      bool regularExpression,
                      bool caseSensitively,
                      bool wholeWord);
    void autoIndent();
    void setTabWidth(int width);
    void setWordWrap(QTextOption::WrapMode wrapMode);
    void setTheCursorWidth(int width);

private slots:
    void updateSearchResults();

protected:
    void paintEvent(QPaintEvent *e);
    void contextMenuEvent (QContextMenuEvent * event);
    void keyPressEvent(QKeyEvent *e);

private:
    void highlightCurrentLine(QList<QTextEdit::ExtraSelection>& selections);
    void highlightSearchResult(QList<QTextEdit::ExtraSelection>& selections);
    void highlightParenthesis(QList<QTextEdit::ExtraSelection>& selections);
    /*void autoCompleteParentheses(QKeyEvent *e,
                                 QTextCursor &currTextCursor,
                                 const QChar &rightParentheses);*/
    void findString(bool forward);
    void generalSearch(const QTextBlock& block,
                       const int& lines,
                       const bool forward);
    void searchOnOtherThread(QScopedPointer<kciTextSearcher> &searcher,
                             QFuture<void> &thread,
                             const QTextBlock &block,
                             const bool forward);
    void initTextSearcher(QScopedPointer<kciTextSearcher> &searcher);
    void checkWhetherBlockSearchedAndDealWith(const QTextBlock &block);
    int matchParentheses(const char& parenthesesA,
                         const char& parenthesesB,
                         QList<parenthesesInfo>::iterator startPos,
                         QTextBlock block,
                         bool forward);
    int findFirstCharacter(const QTextBlock& block);
    void insertTab(QTextCursor cursor, int count = 1);
    void removeTab(QTextCursor cursor, int count = 1);

    kciEditorConfigure* configureInstance;
    kciClipboard* clipboard;
    QColor lineColor,searchResultColor;
    QColor noMatchedParenthesesColor,matchedParenthesesColor;
    QPoint contextMenuPos;

    QString text;
    bool regularExpression;
    bool caseSensitively;
    bool wholeWord;
    unsigned long long int searchCode;
    QScopedPointer<kciTextSearcher> searcherForPrev,searcherForNext;
    QFuture<void> threadPrev,threadNext;
};

#endif // CODEEDITOR_H
