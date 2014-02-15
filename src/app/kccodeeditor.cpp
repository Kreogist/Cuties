/*
 *
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

#include <QDebug>

#include <QTextStream>
#include <QFileInfo>
#include <QFileDialog>
#include <QBoxLayout>
#include <QIcon>
#include <QMessageBox>
#include <QPalette>
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QTimeLine>
#include <QShowEvent>

#include "kchistoryconfigure.h"
#include "kcgeneralconfigure.h"
#include "kccolorconfigure.h"

#include "kcmessagebox.h"

#include "kctexteditor.h"
#include "kcsearchwindow.h"
#include "kcreplacewindow.h"

#include "kccodeeditor.h"

KCCodeEditor::KCCodeEditor(QWidget *parent) :
    QWidget(parent)
{
    setObjectName("KCCodeEditor");
    setFont(QString("Monaco"));
    setContentsMargins(0,0,0,0);

    mainLayout=new QBoxLayout(QBoxLayout::TopToBottom ,this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    editor=new KCTextEditor(this);
    mainLayout->addWidget(editor);

    currentCompileProgress=new KCCodeCompileProgress(editor);
    currentCompileProgress->hide();
    searchBar=new KCSearchWindow(editor);
    searchBar->hide();
    replaceBar=new KCReplaceWindow(this);
    replaceBar->hide();
    mainLayout->addWidget(replaceBar);

    connect(editor->document(), &QTextDocument::modificationChanged,
            this, &KCCodeEditor::onModificationChanged);
    connect(editor, &KCTextEditor::cursorPositionChanged,
            this, &KCCodeEditor::cursorChanged);
    connect(editor, &KCTextEditor::overwriteModeChanged,
            this, &KCCodeEditor::rewriteStateChanged);

    connect(editor, &KCTextEditor::requireHideOthers,
            this, &KCCodeEditor::onHideOtherWidgets);

    currentCompileProgress->regeometry(width());

    //Default Disable Overwrite Mode.
    editor->setOverwriteMode(false);
    searchUseLastCursor=false;

    languageMode=new KCLanguageMode(this);

    connect(languageMode, SIGNAL(compileSuccessfully(QString)),
            currentCompileProgress, SLOT(showCompileSuccess()));
    connect(languageMode, SIGNAL(compileFinished()),
            currentCompileProgress, SLOT(delayHide()));
    connect(languageMode, SIGNAL(compileErrorOccur(int)),
            currentCompileProgress, SLOT(showCompileError(int)));
    connect(languageMode, &KCLanguageMode::requireSmartPanelError,
            this, &KCCodeEditor::addErrorsToStack);
    connect(languageMode, &KCLanguageMode::requireDrawError,
            this, &KCCodeEditor::redrawSmartPanel);
    connect(languageMode, &KCLanguageMode::requireDebugJumpLine,
            this, &KCCodeEditor::onDebugJumpLine);
    connect(currentCompileProgress, SIGNAL(requireCompile()),
            this, SIGNAL(requiredCompileFile()));

    QPalette pal = palette();
    KCColorConfigure::getInstance()->getPalette(pal,objectName());
    setPalette(pal);

    filePath.clear();
    fileError=QFileDevice::NoError;

    cacheNewFileMode=false;
    debugging=false;
}

void KCCodeEditor::applyEditorSettings(KCCodeEditor::KCCodeEditorSettings settings)
{
    editor->setCursorWidth(settings.cursorWidth);
    editor->setWordWrapMode(settings.wrapMode);
    editor->setTabStopWidth(fontMetrics().width(' ')*settings.tabSpace);
    editor->setUsingBlankInsteadTab(settings.usingBlankInsteadTab);
    editor->setSpacePerTab(settings.spacePerTab);
    editor->setLinePanelVisible(settings.lineNumberPanelVisible);
    editor->setLineColor(settings.lineColor);
    editor->setSearchResultColor(settings.searchResultColor);
    editor->setNoMatchedParenthesesColor(settings.noMatchedParenthesesColor);
    editor->setMatchedParenthesesColor(settings.matchedParenthesesColor);
    editor->updateHighlights();
}

bool KCCodeEditor::getOverwriteMode()
{
    return editor->overwriteMode();
}

void KCCodeEditor::setOverwriteMode(bool newValue)
{
    editor->setOverwriteMode(newValue);
    emit rewriteStateChanged(newValue);
}

QString KCCodeEditor::getExecFileName()
{
    return execFileName;
}

QTextDocument *KCCodeEditor::document()
{
    return editor->document();
}

void KCCodeEditor::computeExecFileName()
{
    QFileInfo _fileInfo(filePath);
    execFileName=_fileInfo.absolutePath()+QString("/")+_fileInfo.completeBaseName();
#ifdef Q_OS_WIN32
    execFileName+=".exe";
#endif
}

void KCCodeEditor::connectSearchWidgetWithEditor(KCSearchWidget *widget)
{
    currentSearchWidget=widget;
    searcherConnections+=connect(widget, &KCSearchWidget::requireSearch,
                                 this, &KCCodeEditor::onSearchNext);
    searcherConnections+=connect(widget, &KCSearchWidget::requireShowNextResult,
                                 this, &KCCodeEditor::onShowNextSearchResult);
    searcherConnections+=connect(widget, &KCSearchWidget::requireShowPreviousResult,
                                 this, &KCCodeEditor::onShowPreviousSearchResult);
    searcherConnections+=connect(editor, &KCTextEditor::matchedResult,
                                 widget, &KCSearchWidget::setResultMatchStyle);
    searcherConnections+=connect(editor, &KCTextEditor::nomatchedResult,
                                 widget, &KCSearchWidget::setResultUnmatchStyle);
}

bool KCCodeEditor::getDebugging() const
{
    return debugging;
}

void KCCodeEditor::setDebugging(bool value)
{
    debugging = value;
    if(!debugging)
    {
        editor->resetDebugCursor();
    }
}

void KCCodeEditor::hideCompileBar()
{
    currentCompileProgress->animeHide();
}

void KCCodeEditor::setCompileBarState(KCCodeCompileProgress::CompileState state)
{
    currentCompileProgress->setCompileState(state);
}

void KCCodeEditor::resetCompileErrorCache()
{
    errorOccurLines.clear();
}

void KCCodeEditor::onShowNextSearchResult()
{
    editor->findNextSearchResult();
    currentSearchWidget->setTextFocus();
}

void KCCodeEditor::onShowPreviousSearchResult()
{
    editor->findPreviousSearchResult();
    currentSearchWidget->setTextFocus();
}

void KCCodeEditor::onSearchNext(QString searchTextSets,
                                bool regularExpressionSets,
                                bool caseSensitivelySets,
                                bool wholeWordSets)
{
    editor->searchString(searchTextSets,
                         regularExpressionSets,
                         caseSensitivelySets,
                         wholeWordSets);
    currentSearchWidget->setTextFocus();
}

bool KCCodeEditor::getCacheNewFileMode() const
{
    return cacheNewFileMode;
}

void KCCodeEditor::setCacheNewFileMode(bool value)
{
    cacheNewFileMode = value;
}

void KCCodeEditor::setLanguageMode(KCLanguageMode *value)
{
    languageMode = value;
}

void KCCodeEditor::showCompileBar()
{
    if(!currentCompileProgress->isVisible())
    {
        currentCompileProgress->animeShow();
    }
    currentCompileProgress->countToCompile();
    return;
}

void KCCodeEditor::setUseLastCuror()
{
    searchUseLastCursor=true;
}

void KCCodeEditor::addErrorsToStack(int lineNum)
{
    //lineNum begins from 1, so we have to reduce 1.
    errorOccurLines.append(lineNum-1);
}

void KCCodeEditor::redrawSmartPanel()
{
    editor->setLineErrorState(errorOccurLines);
}

void KCCodeEditor::showSearchBar()
{
    if(replaceBar->getConnected())
    {
        searcherConnections.disConnectAll();
        replaceBar->setConnected(false);
        replaceBar->animeHide();
    }

    if(!searchBar->isVisible())
    {
        if(!searchUseLastCursor)
        {
            editor->backupSearchTextCursor();
        }
        searchBar->animeShow();
        if(!searchBar->getConnected())
        {
            searchBar->setConnected(true);
            connectSearchWidgetWithEditor(searchBar);
            searcherConnections+=connect(searchBar, SIGNAL(requireLostFocus()),
                                         this, SLOT(setUseLastCuror()));
            searcherConnections+=connect(searchBar, SIGNAL(requireLostFocus()),
                                         editor, SLOT(setFocus()));
        }
    }

    QTextCursor _textCursor=editor->textCursor();
    if(_textCursor.hasSelection())
    {
        searchBar->setText(_textCursor.selectedText());
    }
    searchBar->setTextFocus();
}

void KCCodeEditor::showReplaceBar()
{
    if(searchBar->getConnected())
    {
        searcherConnections.disConnectAll();
        searchBar->setConnected(false);
        searchBar->animeHide();
    }

    if(!replaceBar->isVisible())
    {
        if(!searchUseLastCursor)
        {
            editor->backupSearchTextCursor();
        }
        replaceBar->animeShow();
        if(!replaceBar->getConnected())
        {
            replaceBar->setConnected(true);
            connectSearchWidgetWithEditor(replaceBar);
            searcherConnections+=connect(replaceBar, SIGNAL(requireLostFocus()),
                                         this, SLOT(setUseLastCuror()));
            searcherConnections+=connect(replaceBar, SIGNAL(requireLostFocus()),
                                         editor, SLOT(setFocus()));
            searcherConnections+=connect(replaceBar,&KCReplaceWindow::requireReplace,
                                         editor,&KCTextEditor::replace);
            searcherConnections+=connect(replaceBar,&KCReplaceWindow::requireReplaceAndFind,
                                         editor,&KCTextEditor::replaceAndFind);
            searcherConnections+=connect(replaceBar,&KCReplaceWindow::requireReplaceAll,
                                         editor,&KCTextEditor::replaceAll);
        }
    }

    QTextCursor _textCursor=editor->textCursor();
    if(_textCursor.hasSelection())
    {
        replaceBar->setText(_textCursor.selectedText());
    }
    replaceBar->setTextFocus();
}

bool KCCodeEditor::open(const QString &fileName,
                        bool cacheMode)
{
    QFile _file(fileName);

    if(_file.open(QIODevice::ReadOnly |QIODevice::Text))
    {
        QTextStream _textIn(&_file);
        QString titleText=editor->documentTitle();

        editor->clear();
        editor->setPlainText(QString(_textIn.readAll()));

        if(cacheMode)
        {
            setDocumentTitle(titleText);
            editor->document()->setModified(true);
        }
        else
        {
            fileInfoChanged(_file);
            KCHistoryConfigure::getInstance()->addRecentFileRecord(filePath);
        }
        return true;
    }
    fileError=_file.error();
    return false;
}

bool KCCodeEditor::readCacheFile(const QString &cachedfilePath)
{
    return open(cachedfilePath, true);
}

QFileDevice::FileError KCCodeEditor::error()
{
    return fileError;
}

bool KCCodeEditor::save()
{
    if(!filePath.isEmpty())
    {
        return saveAs(filePath);
    }
    else
    {
        return processSaveAsAction(tr("Save"));
    }
}

bool KCCodeEditor::saveAs()
{
    return processSaveAsAction(tr("Save As"));
}

bool KCCodeEditor::processSaveAsAction(const QString &dialogCaption)
{
    if(!requireSaveAs(dialogCaption))
    {
        if(fileError!=QFileDevice::AbortError)
        {
            KCMessageBox *error=new KCMessageBox(this);
            error->setTitle("Error");
            error->addText(tr("Saving file failed."));
            error->exec();
        }
        return false;
    }
    else
    {
        return true;
    }
}

bool KCCodeEditor::requireSaveAs(const QString &caption)
{
    KCGeneralConfigure *instance=KCGeneralConfigure::getInstance();
    if(instance->getValue("UseDefaultLanguageModeWhenSave").toBool())
    {
        QString defaultSelectFilter;
        switch(instance->getValue("DefaultLanguageMode").toInt())
        {
        case 1:
            defaultSelectFilter=instance->getFilter(KCGeneralConfigure::cFiles);
            break;
        case 2:
            defaultSelectFilter=instance->getFilter(KCGeneralConfigure::cppFiles);
            break;
        case 3:
            defaultSelectFilter=instance->getFilter(KCGeneralConfigure::pascalFiles);
            break;
        default:
            defaultSelectFilter=instance->getFilter(KCGeneralConfigure::allFiles);
        }
        filePath=QFileDialog::getSaveFileName(this,
                                              caption,
                                              KCHistoryConfigure::getInstance()->getHistoryDir(),
                                              instance->getTotalFileFilter(),
                                              &defaultSelectFilter);
    }
    else
    {
        filePath=QFileDialog::getSaveFileName(this,
                                              caption,
                                              KCHistoryConfigure::getInstance()->getHistoryDir(),
                                              instance->getTotalFileFilter());
    }
    if(!filePath.isEmpty())
    {
        return saveAs(filePath);
    }
    else
    {
        fileError=QFileDevice::AbortError;
        return false;
    }
}

bool KCCodeEditor::saveAs(const QString &fileName,
                          bool cacheMode)
{
    QFile _file(fileName);

    if(_file.open(QIODevice::WriteOnly |QIODevice::Text))
    {
        QTextStream _textOut(&_file);
        _textOut<<editor->toPlainText()<<flush;
        if(!cacheMode)
        {
            fileInfoChanged(_file);
        }
        return true;
    }
    fileError=_file.error();
    return false;
}

bool KCCodeEditor::writeCacheFile(const QString &filePath)
{
    return saveAs(filePath, true);
}

QList<int> KCCodeEditor::getBreakpoints()
{
    return editor->getBreakPoints();
}

void KCCodeEditor::onDebugJumpLine(int blockNumber)
{
    editor->setDebugCursor(blockNumber-1);
}

void KCCodeEditor::closeEvent(QCloseEvent *e)
{
    if(editor->document()->isModified() &&
       ((filePath.isEmpty() && !cacheNewFileMode) ||
        !filePath.isEmpty()))
    {
        QMessageBox msgbox(this);
        QString strDisplayFileName;

        if(filePath.isEmpty())
        {
            strDisplayFileName=editor->documentTitle();
        }
        else
        {
            strDisplayFileName=filePath;
        }

        msgbox.setText(tr("Will you save changes to the the following file?") + "\n" +
                       strDisplayFileName);
        msgbox.setInformativeText(tr("If you don't save the changes, all the changes will be lost."));

        msgbox.setStandardButtons(QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);
        msgbox.setDefaultButton(QMessageBox::Save);
        msgbox.setButtonText(QMessageBox::Save,tr("&Save"));
        msgbox.setButtonText(QMessageBox::Discard,tr("&Don't Save"));
        msgbox.setButtonText(QMessageBox::Cancel,tr("&Cancel"));

        int ret=msgbox.exec();

        switch(ret)
        {
        case QMessageBox::Save:
            // Save was clicked
            if(!save())
            {
                e->ignore();
                break;
            }
            else
            {
                e->accept();
                break;
            }
        case QMessageBox::Discard:
            // Don't Save was clicked
            e->accept();

            break;
        case QMessageBox::Cancel:
            // Cancel was clicked
            e->ignore();

            break;
        default:
            // should never be reached
            qWarning("codeeditor.cpp: switch(ret) reached an unexcepted line!");
            break;
        }
        return ;
    }
    else
    {
        e->accept();
        QWidget::closeEvent(e);
    }

    return ;
}

void KCCodeEditor::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    currentCompileProgress->regeometry(width());
}

void KCCodeEditor::setDocumentTitle(const QString &title)
{
    editor->setDocumentTitle(title);
    emit filenameChanged(title);
}

QString KCCodeEditor::getDocumentTitle()
{
    return editor->documentTitle();
}

void KCCodeEditor::redo()
{
    editor->redo();
}

void KCCodeEditor::undo()
{
    editor->undo();
}

void KCCodeEditor::copy()
{
    editor->copy();
}

void KCCodeEditor::cut()
{
    editor->cut();
}

void KCCodeEditor::paste()
{
    editor->paste();
}

void KCCodeEditor::selectAll()
{
    editor->selectAll();
}

void KCCodeEditor::setTextFocus()
{
    editor->setFocus();
}

void KCCodeEditor::onModificationChanged(bool changed)
{
    if(changed)
    {
        emit filenameChanged(editor->documentTitle()+"*");
    }
    else
    {
        emit filenameChanged(editor->documentTitle());
    }
}

void KCCodeEditor::onHideOtherWidgets()
{
    searchBar->animeHide();
    replaceBar->animeHide();
    emit requiredHideDocks();
}

QString KCCodeEditor::getFilePath()
{
    return filePath;
}

QString KCCodeEditor::getSelectedText()
{
    return editor->textCursor().selectedText();
}

void KCCodeEditor::cursorChanged()
{
    searchUseLastCursor=false;
    emit fileTextCursorChanged();
}

QTextCursor KCCodeEditor::getTextCursor()
{
    return editor->textCursor();
}

void KCCodeEditor::setVScrollValue(int value)
{
    editor->setVerticalScrollValue(value);
}

void KCCodeEditor::setHScrollValue(int value)
{
    editor->setHorizontalScrollValue(value);
}

int KCCodeEditor::getVScrollValue()
{
    return editor->verticalScrollValue();
}

int KCCodeEditor::getHScrollValue()
{
    return editor->horizontalScrollValue();
}

int KCCodeEditor::getTextLines()
{
    return editor->document()->blockCount();
}

void KCCodeEditor::setDocumentCursor(int nLine, int linePos)
{
    editor->setCursorPosition(nLine,linePos);
}

void KCCodeEditor::fileInfoChanged(const QFile &file)
{
    QFileInfo _fileInfo(file);
    editor->setDocumentTitle(_fileInfo.fileName());
    emit filenameChanged(_fileInfo.fileName());

    languageMode->setFileSuffix(_fileInfo.suffix());

    filePath=file.fileName();
    fileError=QFileDevice::NoError;
    editor->document()->setModified(false);

    computeExecFileName();
    KCHistoryConfigure::getInstance()->setHistoryDir(_fileInfo.absolutePath());
}

KCLanguageMode *KCCodeEditor::langMode() const
{
    return languageMode;
}

bool KCCodeEditor::isModified()
{
    return editor->document()->isModified();
}

void KCCodeEditor::insertTextAtCursor(QString insertText)
{
    editor->insertPlainText(insertText);
}
