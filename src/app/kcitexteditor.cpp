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

#include "kcitexteditor.h"

static int elideWidth=500;

kciTextEditor::kciTextEditor(QWidget *parent) :
    QPlainTextEdit(parent)
{
    setContentsMargins(0,0,0,0);

    setFrameStyle(QFrame::NoFrame);
    setFont(QString("Monaco"));
    setAcceptDrops(false);

    clipboard=kciClipboard::getInstance();
    clipboardHistoryMenuSignalMapper=new QSignalMapper(this);
    connect(clipboardHistoryMenuSignalMapper,SIGNAL(mapped(QString)),
            this,SLOT(insertPlainText(QString)));

    //Set TextEditor Properties.
    setTabStopWidth(fontMetrics().width(' ')<<2);

    QPalette pal = palette();
    pal.setColor(QPalette::Base,QColor(0x38,0x38,0x38));
    pal.setColor(QPalette::Text,QColor(255,255,255));
    pal.setColor(QPalette::Button,QColor(83,83,83));
    setPalette(pal);
    setFrameStyle(0);

    lineColor = QColor(0x64,0x64,0x64);
    searchResultColor = QColor(0xf7,0xcf,0x3d);

    searchCode=0;

    //Solve the default line's bug.
    updateHighlights();

    connect(this,&kciTextEditor::cursorPositionChanged,
            this,&kciTextEditor::updateHighlights);
    connect(this,SIGNAL(textChanged()),
            this,SLOT(updateSearchResults()));
    connect(verticalScrollBar(),SIGNAL(valueChanged(int)),
            this,SLOT(updateSearchResults()));
    connect(verticalScrollBar(),SIGNAL(valueChanged(int)),
            this,SLOT(updateHighlights()));
}

void kciTextEditor::paintEvent(QPaintEvent *e)
{
    QPlainTextEdit::paintEvent(e);
    emit updated();
}

void kciTextEditor::checkWhetherBlockSearchedAndDealWith(
        const QTextBlock& block)
{
    kciTextBlockData *data=(kciTextBlockData*)block.userData();
    //check whether the block has been searched
    data->beginUsingDatas();
    bool hasSearched=data->isSearched(searchCode);
    if(!hasSearched)
    {
        data->endUsingDatas();
        generalSearch(block,50,true);    //search 50 lines
        data->beginUsingDatas();
    }
    data->endUsingDatas();
}

void kciTextEditor::showPreviousSearchResult()
{
    findString(false);
}

void kciTextEditor::showNextSearchResult()
{
    findString(true);
}

void kciTextEditor::findString(bool forward)
{
    QTextCursor _textCursor;

    bool hasMatch=false;
    _textCursor=textCursor();
    if(!forward)
        _textCursor.setPosition(_textCursor.selectionStart());

    for(QTextBlock i=_textCursor.block();
        i.isValid() && !hasMatch;
        i=(forward==true)?i.next():i.previous())
    {
        kciTextBlockData *blockData=(kciTextBlockData *)i.userData();

        checkWhetherBlockSearchedAndDealWith(i);

        blockData->beginUsingDatas();
        if(blockData->hasMatched())
        {
            if(forward)
            {
                auto end=blockData->getEndMatchedTextPosition();
                for(auto j=blockData->getFirstMatchedTextPosition();
                    j<end;
                    j++)
                {
                    if(j->pos >= ((i.blockNumber() == _textCursor.blockNumber())?
                            _textCursor.positionInBlock():0))
                    {
                        hasMatch=true;
                        _textCursor.setPosition(i.position()+j->pos);
                        _textCursor.movePosition(QTextCursor::NextCharacter,
                                                 QTextCursor::KeepAnchor,
                                                 j->matchedLength);
                        break;
                    }
                }
            }
            else
            {
                auto end=blockData->getFirstMatchedTextPosition();
                for(auto j=blockData->getEndMatchedTextPosition()-1;
                    j>=end;
                    j--)
                {
                    if((i.blockNumber() == _textCursor.blockNumber() &&
                        j->pos < _textCursor.positionInBlock()) ||
                        i.blockNumber() != _textCursor.blockNumber())
                    {
                        hasMatch=true;
                        _textCursor.setPosition(i.position()+j->pos);
                        _textCursor.movePosition(QTextCursor::NextCharacter,
                                                 QTextCursor::KeepAnchor,
                                                 j->matchedLength);
                        break;
                    }
                }
            }
        }
        blockData->endUsingDatas();
    }

    if(!hasMatch)
    {
        int endBlockNumber=_textCursor.blockNumber();
        for(QTextBlock i= (forward==true)?
            document()->firstBlock():
            document()->lastBlock().previous();

            i.isValid() &&
            (forward==true?
             i.blockNumber()<endBlockNumber:
             i.blockNumber()>endBlockNumber) &&
            !hasMatch;

            i=(forward==true)?i.next():i.previous())
        {
            kciTextBlockData *blockData=(kciTextBlockData *)i.userData();
            checkWhetherBlockSearchedAndDealWith(i);

            blockData->beginUsingDatas();
            if(blockData->hasMatched())
            {
                if(forward)
                {
                    auto end=blockData->getEndMatchedTextPosition();
                    for(auto j=blockData->getFirstMatchedTextPosition();
                        j<end;
                        j++)
                    {
                        if(j->pos >= (i.blockNumber() == _textCursor.blockNumber())?
                                _textCursor.positionInBlock():0)
                        {
                            hasMatch=true;
                            _textCursor.setPosition(i.position()+j->pos);
                            _textCursor.movePosition(QTextCursor::NextCharacter,
                                                     QTextCursor::KeepAnchor,
                                                     j->matchedLength);
                            break;
                        }
                    }
                }
                else
                {
                    auto end=blockData->getFirstMatchedTextPosition();
                    for(auto j=blockData->getEndMatchedTextPosition()-1;
                        j>=end;
                        j--)
                    {
                        if((i.blockNumber() == _textCursor.blockNumber() &&
                            j->pos < _textCursor.positionInBlock()) ||
                            i.blockNumber() != _textCursor.blockNumber())
                        {
                            hasMatch=true;
                            _textCursor.setPosition(i.position()+j->pos);
                            _textCursor.movePosition(QTextCursor::NextCharacter,
                                                     QTextCursor::KeepAnchor,
                                                     j->matchedLength);
                            break;
                        }
                    }
                }
            }
            blockData->endUsingDatas();
        }
    }

    if(hasMatch)
    {
        setTextCursor(_textCursor);
    }
}

void kciTextEditor::searchString(QString text,
                                 bool regularExpression,
                                 bool caseSensitively,
                                 bool wholeWord)
{
    this->text=text;
    this->regularExpression=regularExpression;
    this->caseSensitively=caseSensitively;
    this->wholeWord=wholeWord;
    searchCode++;

    if(wholeWord)
    {
        if(!regularExpression)
            this->text=QRegularExpression::escape(text);

        this->text.prepend(QString("\\b("));
        this->text.append(QString(")\\b"));
    }

    updateSearchResults();

    searchOnOtherThread(searcherForNext,threadNext,firstVisibleBlock(),true);
    searchOnOtherThread(searcherForPrev,threadPrev,firstVisibleBlock(),false);
}

void kciTextEditor::updateSearchResults()
{
    generalSearch(firstVisibleBlock(),
                  height()/fontMetrics().lineSpacing()+2,
                  true);

    updateHighlights();
}

void kciTextEditor::generalSearch(const QTextBlock &block,
                                  const int lines,
                                  const bool forward)
{
    QScopedPointer<kciTextSearcher> searcher;

    initTextSearcher(searcher);

    searcher->search(block,
                     lines,
                     searchCode,
                     forward);
}

void kciTextEditor::searchOnOtherThread(QScopedPointer<kciTextSearcher> &searcher,
                                        QFuture<void> &thread,
                                        const QTextBlock &block,
                                        const bool forward)
{
    if(!searcher.isNull())
    {
        searcher->requireStop();
        thread.waitForFinished();
    }

    initTextSearcher(searcher);

    thread=QtConcurrent::run(searcher.data(),
                             &kciTextSearcher::search,
                             block,
                             SEARCH_UNTIL_END_MARK,
                             searchCode,
                             forward);
}

void kciTextEditor::initTextSearcher(QScopedPointer<kciTextSearcher> &searcher)
{
    if(regularExpression || wholeWord)
    {
        searcher.reset(new kciTextSearcherRegexp);
    }
    else
    {
        searcher.reset(new kciTextSearcherStringMatcher);
    }

    searcher->setPatternString(text);
    searcher->setIsCaseSensitive(caseSensitively);
}

void kciTextEditor::setDocumentCursor(int nLine, int linePos)
{
     QTextCursor cursor = textCursor();
     cursor.setPosition(document()->findBlockByNumber(nLine).position());
     cursor.movePosition(QTextCursor::NextCharacter,
                          QTextCursor::MoveAnchor,
                          linePos);
     setTextCursor(cursor);
}

void kciTextEditor::updateHighlights()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    highlightCurrentLine(extraSelections);
    highlightSearchResult(extraSelections);

    setExtraSelections(extraSelections);
}

void kciTextEditor::highlightCurrentLine(QList<QTextEdit::ExtraSelection>& selections)
{
    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        selections.append(selection);
    }
}

void kciTextEditor::highlightSearchResult(QList<QTextEdit::ExtraSelection>& selections)
{
    QTextCursor _cursor(document());

    QTextBlock block=firstVisibleBlock();
    int bottom=height()/fontMetrics().lineSpacing()+block.lineCount();

    for(;block.isValid() && bottom>0;block=block.next())
    {
        bottom-=block.lineCount();
        kciTextBlockData* currBlockData=(kciTextBlockData*)block.userData();
        if(currBlockData==NULL)
            continue;
        checkWhetherBlockSearchedAndDealWith(block);
        currBlockData->beginUsingDatas();
        if(currBlockData->hasMatched())
        {
            for(auto i=currBlockData->getFirstMatchedTextPosition(),
                end=currBlockData->getEndMatchedTextPosition();
                i<end;
                i++)
            {
                QTextEdit::ExtraSelection selection;

                _cursor.clearSelection();
                _cursor.setPosition(block.position()+i->pos);
                _cursor.movePosition(QTextCursor::NextCharacter,
                                     QTextCursor::KeepAnchor,
                                     i->matchedLength);
                selection.cursor=_cursor;

                selection.format.setBackground(searchResultColor);
                selections.append(selection);
            }
        }
        currBlockData->endUsingDatas();
    }
}

void kciTextEditor::pasteFromeHistory()
{
    QMenu* menu=new QMenu(this);

    QStringList texts=clipboard->getClipboardTexts();
    for(int i=0,l=texts.size();
        i<l;
        i++)
    {
        QString elidedText=fontMetrics().elidedText(texts.at(i),
                                                    Qt::ElideRight,
                                                    elideWidth);
        QAction *action=menu->addAction(elidedText,
                                        clipboardHistoryMenuSignalMapper,
                                        SLOT(map()));

        clipboardHistoryMenuSignalMapper->setMapping(action,texts.at(i));
    }

    menu->exec(contextMenuPos);

    delete menu;
}

void kciTextEditor::contextMenuEvent(QContextMenuEvent *event)
{
    contextMenuPos=event->globalPos();

    QMenu *menu=createStandardContextMenu();
    menu->addAction(tr("paste from clipboard history"),
                    this,SLOT(pasteFromeHistory()));
    menu->exec(event->globalPos());
    delete menu;
}

void kciTextEditor::autoCompleteParentheses(QKeyEvent *e,
                                            QTextCursor& currTextCursor,
                                            const QChar& rightParentheses)
{
    QPlainTextEdit::keyPressEvent(e);
    insertPlainText(QString(rightParentheses));
    currTextCursor.movePosition(QTextCursor::Left);
    setTextCursor(currTextCursor);
}

void kciTextEditor::keyPressEvent(QKeyEvent *e)
{
    QTextCursor _textCursor=textCursor();
    switch (e->key()) {
    case Qt::Key_ParenLeft:
    {
        autoCompleteParentheses(e,_textCursor,')');
        break;
    }
    case Qt::Key_QuoteDbl:
    {
        QString text=_textCursor.selectedText();
        if(text.isEmpty())
        {
            autoCompleteParentheses(e,_textCursor,'\"');
        }
        else
        {
            int start=_textCursor.selectionStart(),
                    end=_textCursor.selectionEnd();
            _textCursor.beginEditBlock();
            _textCursor.clearSelection();
            _textCursor.setPosition(start);
            _textCursor.insertText("\"");
            _textCursor.setPosition(end+1);
            _textCursor.insertText("\"");
            _textCursor.endEditBlock();
            setTextCursor(_textCursor);
        }
        break;
    }
    case Qt::Key_Apostrophe:
    {
        autoCompleteParentheses(e,_textCursor,'\'');
        break;
    }
    case Qt::Key_BracketLeft:
    {
        autoCompleteParentheses(e,_textCursor,']');
        break;
    }
    default:
        QPlainTextEdit::keyPressEvent(e);
        break;
    }
}
