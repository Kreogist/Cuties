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

#include <QScrollBar>
#include <QPainter>
#include <QPalette>
#include <QMenu>
#include <QStyleFactory>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

#include "kctextblockdata.h"
#include "kcclipboard.h"
#include "kcfontconfigure.h"
#include "kccolorconfigure.h"
#include "kctexteditor.h"

KCTextEditor::KCTextEditor(QWidget *parent) :
    QPlainTextEdit(parent)
{
    //Initialize properties.
    setObjectName("KCTextEditor");
    setAcceptDrops(false);

    //Initialize visual properties.
    setContentsMargins(0,0,0,0);
    setFrameShape(QFrame::NoFrame);
    QFont editorFont=KCFontConfigure::getInstance()->getCodeFont();
    setFont(editorFont);
    QPalette pal=palette();
    KCColorConfigure::getInstance()->getPalette(pal,objectName());
    setPalette(pal);

    //Initialize variables.
    /***Colors***/
    lineColor = QColor(0x40,0x40,0x40);
    searchResultColor = QColor(98,147,221);
    searchResultColor = QColor(0x5A,0x86,0xCA);
    noMatchedParenthesesColor = QColor(0xdb,0x3a,0x42);
    matchedParenthesesColor = QColor(0xf8,0x9b,0x9b);
    /***Search code***/
    searchCode=0;
    /***Clipboard Menu***/
    /*clipboard=KCClipboard::getInstance();
    clipboardHistoryMenuSignalMapper=new QSignalMapper(this);
    connect(clipboardHistoryMenuSignalMapper,SIGNAL(mapped(QString)),
            this,SLOT(insertPlainText(QString)));*/

    //Initial child widgets
    /***Float toolbar***/
    //textFloatToolBar=new KCFloatToolBar(this);
    /***Panel Manager & Panels***/
    panelManager=new KCTextPanelManager(this);
    debugMarkPanel=new KCDebugMarkPanel(this);
    panelManager->addPanel(debugMarkPanel);
    lineNumberPanel=new KCLineNumberPanel(this);
    panelManager->addPanel(lineNumberPanel);
    unibodyPanel=new KCUnibodyPanel(this);
    panelManager->addPanel(unibodyPanel);

    //Connect signals and signals/slots.
    connect(this, &KCTextEditor::cursorPositionChanged,
            this, &KCTextEditor::updateHighlights);
    connect(this, &KCTextEditor::textChanged,
            this, &KCTextEditor::updateHighlights);
    connect(verticalScrollBar(),SIGNAL(valueChanged(int)),
            this,SLOT(updateSearchResults()));
    connect(verticalScrollBar(),SIGNAL(valueChanged(int)),
            this,SLOT(updateHighlights()));
    connect(this, &KCTextEditor::blockCountChanged,
            this, &KCTextEditor::updateLineNumberAreaWidth);
    connect(this, &KCTextEditor::updateRequest,
            this, &KCTextEditor::updateLineNumberArea);
    connect(panelManager, &KCTextPanelManager::requirePaintPanel,
            this, &KCTextEditor::panelPaintEvent);
    connect(unibodyPanel, &KCUnibodyPanel::requireFoldStartAt,
            this, &KCTextEditor::foldCode);
    connect(unibodyPanel, &KCUnibodyPanel::requireUnfoldStartAt,
            this, &KCTextEditor::unfoldCode);
    connect(lineNumberPanel, &KCLineNumberPanel::requireSelectBlock,
            this, &KCTextEditor::selectBlock);

    //Called initialize widget procedure.
    updateLineNumberAreaWidth(0);
    updateHighlights();
}

void KCTextEditor::checkWhetherBlockSearchedAndDealWith(const QTextBlock &block,
                                                        KCTextBlockData *data)
{
    //check whether the block has been searched
    data->beginUsingSearchDatas();
    if(!data->isSearched(searchCode))
    {
        data->endUsingSearchDatas();
        generalSearch(block,
                      height()/fontMetrics().lineSpacing()+2,
                      true);    //search a screen lines.
        data->beginUsingSearchDatas();
    }
    data->endUsingSearchDatas();
}

void KCTextEditor::setTabWidth(int width)
{
    setTabStopWidth(fontMetrics().width(' ')*width);
}

bool KCTextEditor::showPreviousSearchResult()
{
    //Simbol to match a string
    bool hasMatch=false, isCursorLine;
    //Backup current cursor
    QTextCursor searchCursor=textCursor();
    //Check search position
    int currentCursorPostion=searchCursor.selectionStart(),
        matchedCount;
    searchCursor.setPosition(currentCursorPostion);
    KCTextBlockData::matchedInfo currentMatch;
    KCTextBlockData *blockData;
    //Search from current place to next place
    for(QTextBlock i=searchCursor.block();   //From current block
        i.isValid() && !hasMatch;           //to the destination block
        i=i.previous())  //If search forward, to previous
    {                                       //otherwise to the next.
        blockData=static_cast<KCTextBlockData *>(i.userData());
        checkWhetherBlockSearchedAndDealWith(i, blockData);
        blockData->beginUsingSearchDatas();
        if(blockData->hasMatched())         //If current have search result
        {
            isCursorLine=i.blockNumber() == searchCursor.blockNumber();
            //If position is forward
            matchedCount=blockData->matchedCount();
            for(int j=matchedCount-1; j>=0; j--)
            {
                currentMatch=blockData->getMatchedInfo(j);
                if((isCursorLine && currentMatch.pos<searchCursor.positionInBlock())
                        || !isCursorLine)
                {
                    hasMatch=true;
                    searchCursor.setPosition(i.position()+currentMatch.pos);
                    searchCursor.movePosition(QTextCursor::NextCharacter,
                                              QTextCursor::KeepAnchor,
                                              currentMatch.matchedLength);
                    break;
                }
            }
        }
        blockData->endUsingSearchDatas();
    }
    if(hasMatch)
    {
        setTextCursor(searchCursor);
        return true;
    }
    return findLastSearchResult();
}

bool KCTextEditor::showNextSearchResult()
{
    QTextCursor searchCursor=textCursor();
    //Simbol to match a string
    bool hasMatch=false, isCursorLine;
    //Backup current cursor
    //Check search position
    int currentCursorPostion=searchCursor.position(),
        matchedCount, comparePosition;
    searchCursor.setPosition(currentCursorPostion);
    KCTextBlockData *blockData;
    KCTextBlockData::matchedInfo currentMatch;
    //Search from current place to next place
    for(QTextBlock i=searchCursor.block();
        i.isValid() && !hasMatch;
        i=i.next())
    {
        blockData=static_cast<KCTextBlockData *>(i.userData());
        checkWhetherBlockSearchedAndDealWith(i, blockData);
        blockData->beginUsingSearchDatas();
        if(blockData->hasMatched())         //If current have search result
        {
            isCursorLine=i.blockNumber() == searchCursor.blockNumber();
            matchedCount=blockData->matchedCount();
            comparePosition=isCursorLine?searchCursor.position()-i.position():0;
            for(int j=0; j<matchedCount; j++)
            {
                currentMatch=blockData->getMatchedInfo(j);
                if(currentMatch.pos>=comparePosition)
                {
                    hasMatch=true;
                    searchCursor.setPosition(i.position()+currentMatch.pos);
                    searchCursor.movePosition(QTextCursor::NextCharacter,
                                             QTextCursor::KeepAnchor,
                                             currentMatch.matchedLength);
                    break;
                }
            }
        }
        blockData->endUsingSearchDatas();
    }
    if(hasMatch)
    {
        setTextCursor(searchCursor);
        return true;
    }
    return findFirstSeachResult();
}

bool KCTextEditor::findFirstSeachResult()
{
    //Backup current cursor
    QTextCursor searchCursor=textCursor();
    //Simbol to match a string
    bool hasMatch=false;
    KCTextBlockData::matchedInfo currentMatch;
    //Search from current place to next place
    for(QTextBlock i=document()->begin();
        i.isValid() && !hasMatch;
        i=i.next())
    {
        KCTextBlockData *blockData=(KCTextBlockData *) i.userData();
        checkWhetherBlockSearchedAndDealWith(i, blockData);
        blockData->beginUsingSearchDatas();
        if(blockData->hasMatched())         //If current have search result
        {
            hasMatch=true;
            currentMatch=blockData->getMatchedInfo(0);
            searchCursor.setPosition(i.position()+currentMatch.pos);
            searchCursor.movePosition(QTextCursor::NextCharacter,
                                     QTextCursor::KeepAnchor,
                                     currentMatch.matchedLength);
        }
        blockData->endUsingSearchDatas();
    }
    if(hasMatch)
    {
        setTextCursor(searchCursor);
    }
    return hasMatch;
}

bool KCTextEditor::findLastSearchResult()
{
    //Backup current cursor
    QTextCursor searchCursor=textCursor();
    //Simbol to match a string
    bool hasMatch=false;
    KCTextBlockData::matchedInfo currentMatch;
    //Search from current place to next place
    //Set the end block number, it will be the current block
    //If search forward, to the last block, else to the first
    for(QTextBlock i=document()->lastBlock();
        //Here, we should check to the end block
        i.isValid() && !hasMatch;
        //Continue to the next one
        i=i.previous())
    {
        KCTextBlockData *blockData=(KCTextBlockData *)i.userData();
        checkWhetherBlockSearchedAndDealWith(i, blockData);

        blockData->beginUsingSearchDatas();
        if(blockData->hasMatched())
        {
            //If we search to the forward, do the same things.
            currentMatch=blockData->getMatchedInfo(blockData->matchedCount()-1);
            hasMatch=true;
            searchCursor.setPosition(i.position()+currentMatch.pos);
            searchCursor.movePosition(QTextCursor::NextCharacter,
                                      QTextCursor::KeepAnchor,
                                      currentMatch.matchedLength);
        }
        blockData->endUsingSearchDatas();
    }
    if(hasMatch)
    {
        setTextCursor(searchCursor);
    }
    return hasMatch;
}

void KCTextEditor::searchString(QString searchTextSets,
                                bool regularExpressionSets,
                                bool caseSensitivelySets,
                                bool wholeWordSets)
{
    searchText=searchTextSets;
    searchRegularExpression=regularExpressionSets;
    searchCaseSensitively=caseSensitivelySets;
    searchWholeWord=wholeWordSets;
    searchCode++;

    if(searchText.isEmpty())
    {
        updateSearchResults();
        searchBackupCursor.clearSelection();
        setTextCursor(searchBackupCursor);
    }
    else
    {
        setTextCursor(searchBackupCursor);
        if(wholeWordSets)
        {
            if(!searchRegularExpression)
            {
                searchText=QRegularExpression::escape(searchTextSets);
            }
            searchText.prepend(QString("\\b("));
            searchText.append(QString(")\\b"));
        }
        updateSearchResults();
        searchOnOtherThread(searcherForNext,threadNext,firstVisibleBlock(),true);
        searchOnOtherThread(searcherForPrev,threadPrev,firstVisibleBlock(),false);
        showNextSearchResult();
    }
}

void KCTextEditor::updateSearchResults()
{
    generalSearch(firstVisibleBlock(),
                  height()/fontMetrics().lineSpacing()+2,
                  true);
    updateHighlights();
}

void KCTextEditor::generalSearch(const QTextBlock &block,
                                 const int &lines,
                                 const bool forward)
{
    QScopedPointer<KCTextSearcher> searcher;
    initTextSearcher(searcher);
    searcher->search(block,
                     lines,
                     searchCode,
                     forward);
}

void KCTextEditor::searchOnOtherThread(QScopedPointer<KCTextSearcher> &searcher,
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
                             &KCTextSearcher::search,
                             block,
                             SEARCH_UNTIL_END_MARK,
                             searchCode,
                             forward);
}

void KCTextEditor::initTextSearcher(QScopedPointer<KCTextSearcher> &searcher)
{
    if(searchRegularExpression || searchWholeWord)
    {
        searcher.reset(new KCTextSearcherRegexp);
    }
    else
    {
        searcher.reset(new KCTextSearcherStringMatcher);
    }

    searcher->setPatternString(searchText);
    searcher->setIsCaseSensitive(searchCaseSensitively);
}

bool KCTextEditor::replace(const QString &oldText, const QString &newText)
{
    QTextCursor _cursor=textCursor();

    if(_cursor.hasSelection() && _cursor.selectedText() == oldText)
    {
        _cursor.beginEditBlock();
        _cursor.removeSelectedText();
        _cursor.insertText(newText);
        _cursor.endEditBlock();
        setTextCursor(_cursor);
        return true;
    }

    return false;
}

bool KCTextEditor::replaceAndFind(const QString &oldText,
                                  const QString &newText)
{
    bool ret=replace(oldText,newText);
    return ret|showNextSearchResult();
}

bool KCTextEditor::replaceAll(const QString &oldText, const QString &newText)
{
    int matchedCount=0;
    //Search from the very beginning to the last
    for(QTextBlock i=document()->begin();
        i.isValid();
        i=i.next())
    {
        KCTextBlockData *blockData=(KCTextBlockData *) i.userData();
        checkWhetherBlockSearchedAndDealWith(i, blockData);
        blockData->beginUsingSearchDatas();
        matchedCount+=blockData->matchedCount();
        blockData->endUsingSearchDatas();
    }
    while(replaceAndFind(oldText,newText) && --matchedCount)
    {
        ;
    }
    return true;
}

void KCTextEditor::autoIndent()
{   
    QTextCursor _textCursor=textCursor();
    QTextBlock currBlock=_textCursor.block();
    QTextBlock prevBlock=currBlock.previous();
    _textCursor.setPosition(currBlock.position());
    int basePos=findFirstCharacter(prevBlock);
    int pos=findFirstCharacter(currBlock);
    if(basePos==-1)
    {
        basePos=prevBlock.text().length();
    }
    if(pos==-1)
    {
        pos=currBlock.text().length();
    }

    QTextCursor _prevTextCursor(prevBlock);
    _prevTextCursor.movePosition(QTextCursor::Right,
                                 QTextCursor::KeepAnchor,
                                 basePos);
    QString tabs=_prevTextCursor.selectedText();

    _textCursor.setPosition(currBlock.position()+pos);
    _textCursor.movePosition(QTextCursor::StartOfBlock,QTextCursor::KeepAnchor);
    _textCursor.removeSelectedText();
    _textCursor.insertText(tabs);

    KCTextBlockData *prevData=static_cast<KCTextBlockData *>(prevBlock.userData());
    KCTextBlockData *currData=static_cast<KCTextBlockData *>(currBlock.userData());
    int baseLevel=prevData->getCodeLevel();
    int currLevel=currData->getCodeLevel();

    if(currLevel>=baseLevel)
    {
        insertTab(_textCursor,currLevel-baseLevel);
    }
    else
    {
        removeTab(_textCursor,baseLevel-currLevel-1);
    }
}

void KCTextEditor::insertTab(QTextCursor insertTabCursor, int tabCount, bool forceInsert)
{
    if(tabCount>0)
    {
        insertTabCursor.clearSelection();
        QString spaceChar=usingBlankInsteadTab?
                          QString(" ").repeated(spacePerTab):
                          "\t";
        if(insertTabCursor.document()->characterAt(insertTabCursor.position())=='}' && !forceInsert)
        {
            insertTabCursor.insertText(spaceChar.repeated(tabCount-1));
        }
        else
        {
            insertTabCursor.insertText(spaceChar.repeated(tabCount));
        }
    }
}

void KCTextEditor::removeTab(QTextCursor removeTabCursor, int tabCount)
{
    removeTabCursor.clearSelection();

    //We have to judge whether we are using tab or space.
    if(usingBlankInsteadTab)
    {
        int expectLength=tabCount*spacePerTab;
        if(expectLength > removeTabCursor.positionInBlock())
        {
            /*
             * Here means: we don't have so much space to remove,
             * just remove all of them
             */
            removeTabCursor.movePosition(QTextCursor::Left,
                                         QTextCursor::KeepAnchor,
                                         removeTabCursor.positionInBlock());
        }
        else
        {
            //Remove the expect length
            removeTabCursor.movePosition(QTextCursor::Left,
                                         QTextCursor::KeepAnchor,
                                         expectLength);
        }
    }
    else
    {
        //Test for first time.

    }
    removeTabCursor.removeSelectedText();
}

void KCTextEditor::tabPressEvent(QTextCursor tabPressCursor)
{
    tabPressCursor.beginEditBlock();

    if (tabPressCursor.hasSelection()) {
        // Indent or unindent the selected lines
        int pos = tabPressCursor.position();
        int anchor = tabPressCursor.anchor();
        int start = qMin(anchor, pos);
        int end = qMax(anchor, pos);

        QTextDocument *doc = document();
        QTextBlock startBlock = doc->findBlock(start);
        QTextBlock endBlock = doc->findBlock(end-1).next();

        if (startBlock.next() == endBlock
                && (start > startBlock.position() || end < endBlock.position() - 1)) {
            // Only one line partially selected.
            tabPressCursor.removeSelectedText();
        } else {
            QString spaceChar=usingBlankInsteadTab?
                              QString(" ").repeated(spacePerTab):
                              "\t";
            for (QTextBlock block = startBlock; block != endBlock; block = block.next()) {
                int indentPosition = findFirstCharacter(block);
                if(indentPosition<0)
                {
                    //Current link is blank or full of space
                    indentPosition=block.text().length();
                }
                tabPressCursor.setPosition(block.position() + indentPosition);
                tabPressCursor.insertText(spaceChar);
            }
            tabPressCursor.endEditBlock();
            return;
        }
    }
    insertTab(tabPressCursor, 1, true);
    tabPressCursor.endEditBlock();
}

void KCTextEditor::setSpacePerTab(int value)
{
    spacePerTab = value;
}

void KCTextEditor::setUsingBlankInsteadTab(bool value)
{
    usingBlankInsteadTab = value;
}


int KCTextEditor::findFirstCharacter(const QTextBlock &block)
{
    return block.text().indexOf(QRegularExpression("\\S"));
}

/*!
 * \brief This function will set the text cursor to the position located by line
 *        number and column number.
 * \param lineNumber Line number of the destionation position.
 * \param columnNumber Column number of the destionation position.
 */
void KCTextEditor::setCursorPosition(int lineNumber,
                                     int columnNumber)
{
    QTextCursor cursor = textCursor();
    cursor.setPosition(document()->findBlockByNumber(lineNumber).position());
    cursor.movePosition(QTextCursor::NextCharacter,
                        QTextCursor::MoveAnchor,
                        columnNumber);
    setTextCursor(cursor);
}

/*!
 * \brief This function will backup the current cursor. The backuped cursor will
 *        be set at the time the search content changed. This function is used
 *        to let the search function begin to search at the same place.
 */
void KCTextEditor::backupSearchTextCursor()
{
    searchBackupCursor=textCursor();
}

int KCTextEditor::highlightParentheses(QList<QTextEdit::ExtraSelection> &selections)
{
    QTextCursor cursor = textCursor();
    cursor.clearSelection();
    int pos=cursor.position()-cursor.block().position();

    char all[]="{[()]}";
    int len=strlen(all);

    KCTextBlockData *blockData=static_cast<KCTextBlockData *>(cursor.block().userData());
    if(blockData!=NULL)
    {
        int matchedParentheses=-2;

        for(auto i=blockData->getFirstParenthesesInfo(),
            l=blockData->getEndParenthesesInfo();
            i<l;
            i++)
        {
            if(i->pos == pos-1)
            {
                for(int j=0; j<(len>>1); j++)
                {
                    if(i->character == all[j])
                    {
                        cursor.movePosition(QTextCursor::Left,
                                            QTextCursor::KeepAnchor);
                        matchedParentheses=matchParentheses(
                                            all[j],
                                            all[len-j-1],
                                            i,
                                            cursor.block(),
                                            true);
                        break;
                    }
                }
            }
            else if(i->pos == pos)
            {
                for(int j=(len>>1); j<len; j++)
                {
                    if(i->character == all[j])
                    {
                        cursor.movePosition(QTextCursor::Right,
                                            QTextCursor::KeepAnchor);
                        matchedParentheses=matchParentheses(
                                           all[j],
                                           all[len-j-1],
                                           i,
                                           cursor.block(),
                                           false);
                        break;
                    }
                }
            }
            else
            {
                continue;
            }

            highlightParenthesisPairs(selections,
                                      matchedParentheses,
                                      cursor);

            cursor=textCursor();
            cursor.clearSelection();
        }
        return matchedParentheses;
    }
    return -2;
}

void KCTextEditor::highlightParenthesisPairs(QList<QTextEdit::ExtraSelection> &selections,
                                             int matchedParentheses,
                                             QTextCursor cursor)
{
    switch(matchedParentheses)
    {
    case -2:
        //no parenthesis in the block
        break;
    case -1:
    {
        QTextEdit::ExtraSelection selection;

        selection.cursor = cursor;
        selection.format.setBackground(noMatchedParenthesesColor);
        selections.append(selection);

        break;
    }
    default:
    {
        QTextEdit::ExtraSelection selection;

        selection.cursor = cursor;
        selection.format.setBackground(matchedParenthesesColor);
        selections.append(selection);

        cursor.setPosition(matchedParentheses);
        cursor.movePosition(QTextCursor::Right,
                            QTextCursor::KeepAnchor);
        selection.cursor = cursor;
        selection.format.setBackground(matchedParenthesesColor);
        selections.append(selection);

        break;
    }
    }
}


int KCTextEditor::matchParentheses(const char &parenthesesA,
                                   const char &parenthesesB,
                                   QList<parenthesesInfo>::iterator startPos,
                                   QTextBlock block,
                                   bool forward)
{
    int count=0;
    KCTextBlockData *blockData=static_cast<KCTextBlockData *>(block.userData());
    if(blockData!=NULL)
    {
        auto i=startPos,
             l= forward?
                blockData->getEndParenthesesInfo() :
                blockData->getFirstParenthesesInfo() - 1;
        while(block.isValid())
        {
            for(;
                i!=l;
                i+= forward?1:-1)
            {
                if(i->character == parenthesesA)
                {
                    count++;
                }
                else if(i->character == parenthesesB)
                {
                    count--;
                }
                if(count == 0)
                {
                    return block.position() + i->pos;
                }
            }
            block= forward? block.next() : block.previous();
            blockData=static_cast<KCTextBlockData *>(block.userData());
            if(blockData == NULL)
            {
                break;
            }
            if(forward)
            {
                i= blockData->getFirstParenthesesInfo();
                l= blockData->getEndParenthesesInfo();
            }
            else
            {
                i= blockData->getEndParenthesesInfo()-1;
                l= blockData->getFirstParenthesesInfo()-1;
            }
        }
    }
    return -1;
}

void KCTextEditor::updateHighlights()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    highlightCurrentLine(extraSelections);
    highlightSearchResult(extraSelections);
    highlightParentheses(extraSelections);

    setExtraSelections(extraSelections);
}

void KCTextEditor::updatePanelManager()
{
    panelManager->update();
}

void KCTextEditor::highlightCurrentLine(QList<QTextEdit::ExtraSelection> &selections)
{ 
    if(!isReadOnly())
    {
        QTextEdit::ExtraSelection selection;
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor=textCursor();
        selection.cursor.clearSelection();
        selections.append(selection);
    }
}

void KCTextEditor::highlightSearchResult(QList<QTextEdit::ExtraSelection> &selections)
{
    QTextCursor _cursor(document());

    QTextBlock block=firstVisibleBlock();
    int bottom=height()/fontMetrics().lineSpacing()+block.lineCount();

    for(; block.isValid() && bottom>0; block=block.next())
    {
        bottom-=block.lineCount();
        KCTextBlockData *currBlockData=static_cast<KCTextBlockData *>(block.userData());
        if(currBlockData==NULL)
        {
            continue;
        }
        checkWhetherBlockSearchedAndDealWith(block, currBlockData);
        currBlockData->beginUsingSearchDatas();
        if(currBlockData->hasMatched())
        {
            int i;
            KCTextBlockData::matchedInfo currentMatched;
            for(i=0; i<currBlockData->matchedCount(); i++)
            {
                currentMatched=currBlockData->getMatchedInfo(i);
                QTextEdit::ExtraSelection selection;

                _cursor.clearSelection();
                _cursor.setPosition(block.position()+currentMatched.pos);
                _cursor.movePosition(QTextCursor::NextCharacter,
                                     QTextCursor::KeepAnchor,
                                     currentMatched.matchedLength);
                selection.cursor=_cursor;

                selection.format.setBackground(searchResultColor);
                selections.append(selection);
            }
        }
        currBlockData->endUsingSearchDatas();
    }
}

/*void KCTextEditor::pasteFromeHistory()
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
}*/

void KCTextEditor::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu=createStandardContextMenu();
    menu->setStyle(QStyleFactory::create("fusion"));
    menu->exec(event->globalPos());
    delete menu;
}

QString KCTextEditor::parenthesesPair(const QString &parenthesesChar)
{
    if(!parenthesesChar.isEmpty())
    {
        int parenthesesIndex=leftParenthesesLists.indexOf(parenthesesChar);
        if(parenthesesIndex>-1)
        {
            return QString(rightParenthesesLists.at(parenthesesIndex));
        }
    }
    return QString("");
}

void KCTextEditor::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Escape:
        QPlainTextEdit::keyPressEvent(e);
        emit requireHideOthers();
        return;
    }
    QTextCursor _textCursor=textCursor();
    QString pairParethesesChar;
    pairParethesesChar=parenthesesPair(e->text());
    if(!pairParethesesChar.isEmpty())
    {
        if(_textCursor.selectedText().isEmpty())
        {
            QPlainTextEdit::keyPressEvent(e);
            insertPlainText(pairParethesesChar);
            _textCursor.movePosition(QTextCursor::Left);
            setTextCursor(_textCursor);
        }
        else
        {
            //If pressed '{', we should do autoindent all lines.
            /*if(e->text()=='{')
            {
                QTextBlock currBlock=_textCursor.block();
                QTextBlock prevBlock=currBlock.previous();
                QTextBlock nextBlock=currBlock.next();
            }
            else
            {*/
            int start=_textCursor.selectionStart(),
                end=_textCursor.selectionEnd();
            _textCursor.beginEditBlock();
            _textCursor.clearSelection();
            _textCursor.setPosition(start);
            _textCursor.insertText(e->text());
            _textCursor.setPosition(end+1);
            _textCursor.insertText(pairParethesesChar);
            _textCursor.endEditBlock();
            setTextCursor(_textCursor);
            //}
        }
        return;
    }
    if(e->text()==")" || e->text()=="]")
    {
        if(QString(_textCursor.document()->characterAt(_textCursor.position())) == e->text())
        {
            KCTextBlockData *blockData=static_cast<KCTextBlockData *>(_textCursor.block().userData());

            if(blockData!=NULL)
            {
                for(auto i=blockData->getFirstParenthesesInfo(),
                    l=blockData->getEndParenthesesInfo();
                    i<l;
                    i++)
                {
                    if(i->pos == _textCursor.positionInBlock())
                    {
                        if(matchParentheses(e->text().at(0).toLatin1(),
                                            e->text()==")"?'(':'[',
                                            i,
                                            _textCursor.block(),
                                            false) > -1)
                        {
                            _textCursor.movePosition(QTextCursor::Right);
                            setTextCursor(_textCursor);
                            return;
                        }
                    }
                }
            }
        }
        QPlainTextEdit::keyPressEvent(e);
        return;
    }
    if(e->text()=="\"")
    {
        if(_textCursor.selectedText().isEmpty())
        {
            KCTextBlockData *currData=static_cast<KCTextBlockData *>(_textCursor.block().userData());
            if(_textCursor.document()->characterAt(_textCursor.position())==QChar('\"') &&
                    currData->getQuotationStatus()!=-1)
            {
                _textCursor.movePosition(QTextCursor::Right);
                setTextCursor(_textCursor);
                return;
            }
            QPlainTextEdit::keyPressEvent(e);
            if(_textCursor.document()->characterAt(_textCursor.position()-1)!=QChar('\\') &&
                    currData->getQuotationStatus()==-1)
            {
                insertPlainText("\"");
                _textCursor.movePosition(QTextCursor::Left);
                setTextCursor(_textCursor);
            }
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
        return;
    }
    switch(e->key())
    {
    case Qt::Key_Tab:
    {
        tabPressEvent(_textCursor);
        break;
    }
    case Qt::Key_Backspace:
    {
        //If there's text selected, just delete them.
        if(_textCursor.selectedText().length()>0)
        {
            QPlainTextEdit::keyPressEvent(e);
            break;
        }
        //Now we have to judge the status.
        QChar previousChar=_textCursor.document()->characterAt(_textCursor.position()-1),
              currentChar=_textCursor.document()->characterAt(_textCursor.position());
        //If the previous is a panethese and there's the other part of the current panethese,
        //Delete all of them.
        if(parenthesesPair(previousChar)==currentChar)
        {
            _textCursor.deleteChar();
            QPlainTextEdit::keyPressEvent(e);
            break;
        }
        //So as quotations.
        KCTextBlockData *currData=static_cast<KCTextBlockData *>(_textCursor.block().userData());
        if(previousChar==QChar('\"') &&
           currentChar==QChar('\"') &&
           currData->getQuotationStatus()!=0)
        {
            _textCursor.deleteChar();
            QPlainTextEdit::keyPressEvent(e);
            break;
        }
        QPlainTextEdit::keyPressEvent(e);
        break;
    }
    case Qt::Key_Return:
    case Qt::Key_Enter:
    {
        if(_textCursor.position()>0)
        {
            QChar previousChar=_textCursor.document()->characterAt(_textCursor.position()-1),
                  currentChar=_textCursor.document()->characterAt(_textCursor.position());
            if(previousChar == '{')
            {
                if(currentChar == '}')
                {
                    //It's a pair of char '{}'
                    // Indent it!
                    QPlainTextEdit::keyPressEvent(e);
                    _textCursor.insertBlock();
                    QTextBlock nextBlock=_textCursor.block();
                    QTextBlock currBlock=nextBlock.previous();
                    QTextBlock prevBlock=currBlock.previous();
                    KCTextBlockData *prevData=static_cast<KCTextBlockData *>(prevBlock.userData());
                    KCTextBlockData *currData=static_cast<KCTextBlockData *>(currBlock.userData());
                    KCTextBlockData *nextData=static_cast<KCTextBlockData *>(nextBlock.userData());
                    currData->setCodeLevel(prevData->getCodeLevel() + 1);
                    nextData->setCodeLevel(prevData->getCodeLevel() + 1);
                    _textCursor.setPosition(nextBlock.position());
                    setTextCursor(_textCursor);
                    insertTab(_textCursor, prevData->getCodeLevel() + 1);
                    _textCursor.movePosition(QTextCursor::PreviousBlock);
                    setTextCursor(_textCursor);
                    insertTab(_textCursor, prevData->getCodeLevel() + 1);
                    break;
                }
                KCTextBlockData *currData=static_cast<KCTextBlockData *>(_textCursor.block().userData());
                if(currData->getHasFolded())
                {
                    unfoldCode(_textCursor.block().blockNumber());
                }
            }
            if(currentChar == ')' || currentChar == ']')
            {
                QPlainTextEdit::keyPressEvent(e);
                QTextBlock currBlock=_textCursor.block();
                QTextBlock prevBlock=currBlock.previous();
                KCTextBlockData *prevData=static_cast<KCTextBlockData *>(prevBlock.userData());
                KCTextBlockData *currData=static_cast<KCTextBlockData *>(currBlock.userData());
                currData->setCodeLevel(prevData->getCodeLevel());
                int matchedStatus;
                for(auto i=currData->getFirstParenthesesInfo(),
                    l=currData->getEndParenthesesInfo();
                    i<l;
                    i++)
                {
                    if(i->pos == _textCursor.positionInBlock())
                    {
                        matchedStatus=matchParentheses(currentChar.toLatin1(),
                                                       currentChar==')'?'(':'[',
                                                       i,
                                                       currBlock,
                                                       false);
                        if(matchedStatus > -1)
                        {
                            QTextCursor meterCursor(document());
                            meterCursor.setPosition(matchedStatus);
                            QString blankFill=QString(" ").repeated(meterCursor.positionInBlock()+1);
                            _textCursor.insertText(blankFill);
                            return;
                        }
                    }
                }
                break;
            }
        }
        QPlainTextEdit::keyPressEvent(e);
        autoIndent();
        break;
    }
    case Qt::Key_Insert:
    {
        setOverwriteMode(!overwriteMode());
        emit overwriteModeChanged(overwriteMode());
        break;
    }
    default:
    {
        QPlainTextEdit::keyPressEvent(e);
        break;
    }
    }
}

void KCTextEditor::mouseReleaseEvent(QMouseEvent *e)
{
    QPlainTextEdit::mouseReleaseEvent(e);
    /*if(!textCursor().selectedText().isEmpty())
    {
        int newXPosition, newYPosition;
        newXPosition=e->globalX()+textFloatToolBar->width() > QApplication::desktop()->width()?
             e->globalX()-textFloatToolBar->width():
             e->globalX();
        newYPosition=e->globalY()+textFloatToolBar->width() > QApplication::desktop()->height()?
             e->globalY()-textFloatToolBar->height():
             e->globalY();
        textFloatToolBar->setGeometry(newXPosition,
                                      newYPosition,
                                      textFloatToolBar->width(),
                                      textFloatToolBar->height());
        textFloatToolBar->show();
    }
    else
    {
        textFloatToolBar->hide();
    }*/
}

void KCTextEditor::wheelEvent(QWheelEvent *event)
{
    if(event->modifiers() & Qt::ControlModifier)
    {
        zoomIn(event->angleDelta().y()/56);
        event->ignore();
        return;
    }
    QPlainTextEdit::wheelEvent(event);
}

void KCTextEditor::setWordWrap(QTextOption::WrapMode wrapMode)
{
    setWordWrapMode(wrapMode);
}

void KCTextEditor::setTheCursorWidth(int width)
{
    setCursorWidth(width);
}

void KCTextEditor::setLineErrorState(QList<int> errorList)
{
    for(QTextBlock i=document()->begin(); i.isValid(); i=i.next())
    {
        KCTextBlockData *blockData=static_cast<KCTextBlockData *>(i.userData());
        blockData->setHasError((errorList.indexOf(i.blockNumber())!=-1));
    }
}

void KCTextEditor::setCursorAtLine(int blockNumber)
{
    setCursorPosition(blockNumber,0);
}

/*!
 * \brief Set the vertical scroll bar value.
 * \param value The scroll bar value.
 */
void KCTextEditor::setVerticalScrollValue(int value)
{
    verticalScrollBar()->setValue(value);
}

/*!
 * \brief Set the horizontal scroll bar value.
 * \param value The scroll bar value.
 */
void KCTextEditor::setHorizontalScrollValue(int value)
{
    horizontalScrollBar()->setValue(value);
}

/*!
 * \brief Get the vertical scroll bar value.
 */
int KCTextEditor::verticalScrollValue()
{
    return verticalScrollBar()->value();
}

/*!
 * \brief Get the horizontal scroll bar value.
 */
int KCTextEditor::horizontalScrollValue()
{
    return horizontalScrollBar()->value();
}

QList<int> KCTextEditor::getBreakPoints()
{
    QList<int> breakPointList;
    for(QTextBlock i=document()->begin();
        i.isValid();
        i=i.next())
    {
        KCTextBlockData *blockData=static_cast<KCTextBlockData *>(i.userData());
        if(blockData->getMarkInfo().marked)
        {
            breakPointList.append(i.blockNumber());
        }
    }
    return breakPointList;
}

void KCTextEditor::zoomIn(int range)
{
    QFont zoomFont = font();
    const int newSize = zoomFont.pixelSize()+range;
    if(newSize<=0)
    {
        return;
    }
    zoomFont.setPixelSize(newSize);
    setFont(zoomFont);
}

void KCTextEditor::zoomOut(int range)
{
    zoomIn(-range);
}

void KCTextEditor::resetDebugCursor()
{
    debugMarkPanel->resetDebugCursor();
}

void KCTextEditor::setDebugCursor(int lineNumber)
{
    setCursorPosition(lineNumber, 0);
    debugMarkPanel->setDebugCursor(lineNumber);
}

int KCTextEditor::lineNumberPanelWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void KCTextEditor::setLinePanelVisible(bool value)
{
    lineNumberPanel->setVisible(value);
    updateLineNumberAreaWidth(0);
}

void KCTextEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(panelManager->resizeManagerWidth(lineNumberPanelWidth()), 0, 0, 0);
}

void KCTextEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    Q_UNUSED(dy);
    panelManager->update();
    if (rect.contains(viewport()->rect()))
    {
        updateLineNumberAreaWidth(0);
    }
}

void KCTextEditor::foldCode(int startFoldBlockIndex)
{
    QTextBlock foldBlock=document()->findBlockByNumber(startFoldBlockIndex);
    KCTextBlockData *data=static_cast<KCTextBlockData *>(foldBlock.userData());
    int startCodeLevel=data->getCodeLevel();
    foldBlock=foldBlock.next();
    while(foldBlock.isValid())
    {
        data=static_cast<KCTextBlockData *>(foldBlock.userData());
        if(data->getCodeLevel()==startCodeLevel)
        {
            break;
        }
        foldBlock.setVisible(false);
        foldBlock=foldBlock.next();
    }
    viewport()->update();
}

void KCTextEditor::unfoldCode(int startUnfoldBlockIndex)
{
    QTextBlock foldBlock=document()->findBlockByNumber(startUnfoldBlockIndex);
    KCTextBlockData *data=static_cast<KCTextBlockData *>(foldBlock.userData());
    data->setHasFolded(false);
    foldBlock=foldBlock.next();
    while(foldBlock.isValid() && (!foldBlock.isVisible()))
    {
        data=static_cast<KCTextBlockData *>(foldBlock.userData());
        data->setHasFolded(false);
        foldBlock.setVisible(true);
        foldBlock=foldBlock.next();
    }
    viewport()->update();
}

void KCTextEditor::selectBlock(int blockNumber)
{
    QTextCursor cursor=textCursor();
    QTextBlock selectedBlock=document()->findBlockByNumber(blockNumber);
    cursor.setPosition(selectedBlock.position());
    cursor.movePosition(QTextCursor::NextCharacter,
                        QTextCursor::KeepAnchor,
                        selectedBlock.length()-1);
    setTextCursor(cursor);
    setHorizontalScrollValue(0);
}

void KCTextEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);
    updateHighlights();
    updateSearchResults();
    QRect cr = contentsRect();
    panelManager->setGeometry(QRect(cr.left(),
                                    cr.top(),
                                    panelManager->resizeManagerWidth(lineNumberPanelWidth()),
                                    cr.height()));
    setViewportMargins(panelManager->width(), 0, 0, 0);
}

void KCTextEditor::panelPaintEvent(KCTextPanel *panel,
                                   QPaintEvent *event)
{
    QTextBlock block=firstVisibleBlock();
    int blockNumber=block.blockNumber();
    int top=(int)blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom=top+(int)blockBoundingRect(block).height();
    panel->setFirstBlock(block);
    while (top <= event->rect().bottom())
    {
        KCTextBlockData *data=static_cast<KCTextBlockData *>(block.userData());
        data->setRect(blockBoundingGeometry(block).toAlignedRect());
        if (block.isVisible() && bottom >= event->rect().top())
        {
            panel->drawContent(0, top, panel->width(), fontMetrics().height()*block.lineCount(),
                               &block, data, textCursor());
        }
        block=block.next();
        if(block.isValid())
        {
            panel->setLastBlock(block);
        }
        else
        {
            break;
        }
        top=bottom;
        bottom=top+(int)blockBoundingRect(block).height();
        ++blockNumber;
    }
}
