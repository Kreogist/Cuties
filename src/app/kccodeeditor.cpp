/*
 *
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

#include <QErrorMessage>
#include <QTextStream>
#include <QFileInfo>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QIcon>
#include <QMessageBox>
#include <QPalette>
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QSettings>
#include <QTimeLine>

#include "kchistoryconfigure.h"
#include "kcgeneralconfigure.h"
#include "kccolorconfigure.h"
#include "kceditorconfigure.h"

#include "kctexteditor.h"
#include "kclinenumpanel.h"
#include "kcmarkpanel.h"
#include "kcsmartpanel.h"
#include "kcsearchwindow.h"
#include "kcreplacewindow.h"

#include "kccodeeditor.h"

KCCodeEditor::KCCodeEditor(QWidget *parent) :
    QWidget(parent)
{
    setObjectName("KCCodeEditor");
    setFont(QString("Monaco"));
    setContentsMargins(0,0,0,0);

    configureInstance=KCEditorConfigure::getInstance();

    replaceLayout=new QVBoxLayout(this);
    replaceLayout->setContentsMargins(0,0,0,0);
    replaceLayout->setSpacing(0);
    setLayout(replaceLayout);

    mainLayout=new QHBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    markPanel=new KCMarkPanel(this);
    mainLayout->addWidget(markPanel);

    linePanel=new KCLinenumPanel(this);
    linePanel->setVisible(configureInstance->getLineNumVisible());
    mainLayout->addWidget(linePanel);

    smartPanel=new KCSmartPanel(this);
    mainLayout->addWidget(smartPanel);

    editor=new KCTextEditor(this);
    markPanel->setTextEditor(editor);
    linePanel->setTextEditor(editor);
    smartPanel->setTextEditor(editor);

    mainLayout->addWidget(editor);
    replaceLayout->addLayout(mainLayout);

    currentCompileProgress=new KCCodeCompileProgress(editor);
    currentCompileProgress->hide();
    searchBar=new KCSearchWindow(editor);
    searchBar->hide();
    replaceBar=new KCReplaceWindow(this);
    replaceBar->hide();
    replaceLayout->addWidget(replaceBar);

    connect(editor->document(), &QTextDocument::modificationChanged,
            this, &KCCodeEditor::onModificationChanged);
    connect(editor, &KCTextEditor::cursorPositionChanged,
            this, &KCCodeEditor::cursorChanged);
    connect(editor, &KCTextEditor::overwriteModeChanged,
            this, &KCCodeEditor::rewriteStateChanged);
    connect(configureInstance, &KCEditorConfigure::lineNumPanelVisibleChanged,
            linePanel, &KCLinenumPanel::setVisible);

    connect(editor, &KCTextEditor::requireHideOthers,
            this, &KCCodeEditor::onHideOtherWidgets);

    //Default Disable Overwrite Mode.
    editor->setOverwriteMode(false);

    languageMode=new KCLanguageMode(this);

    QPalette pal = palette();
    KCColorConfigure::getInstance()->getPalette(pal,objectName());
    setPalette(pal);

    filePath.clear();
    fileError=QFileDevice::NoError;
}

KCCodeEditor::~KCCodeEditor()
{
    mainLayout->deleteLater();
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
    searcherConnections+=connect(widget, &KCSearchWidget::requireSearch,
                                 editor, &KCTextEditor::searchString);
    searcherConnections+=connect(widget, &KCSearchWidget::requireShowNextResult,
                                 editor, &KCTextEditor::showNextSearchResult);
    searcherConnections+=connect(widget, &KCSearchWidget::requireShowPreviousResult,
                                 editor, &KCTextEditor::showPreviousSearchResult);
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
    /*if(!currentCompileProgress->isVisible())
    {*/
        currentCompileProgress->animeShow();
        qDebug()<<"Do this";
    //}
}

void KCCodeEditor::showSearchBar()
{
    if(replaceBar->isVisible())
    {
        searcherConnections.disConnectAll();
        replaceBar->hideAnime();
    }

    if(!searchBar->isVisible())
    {
        editor->backupSearchTextCursor();
        searchBar->animeShow();
        searcherConnections+=connect(searchBar, &KCSearchWidget::requireHide,
                                     this, &KCCodeEditor::hideSearchBar);
        connectSearchWidgetWithEditor(searchBar);
    }

    QTextCursor _textCursor=editor->textCursor();
    if(_textCursor.hasSelection())
    {
        searchBar->setText(_textCursor.selectedText());
    }
    searchBar->setTextFocus();
}

void KCCodeEditor::hideSearchBar()
{
    if(searchBar->isVisible())
    {
        searchBar->animeHide();
    }
    editor->setFocus();
}

void KCCodeEditor::showReplaceBar()
{
    if(searchBar->isVisible())
    {
        hideSearchBar();
        searcherConnections.disConnectAll();
    }

    if(!replaceBar->isVisible())
    {
        replaceBar->showAnime();

        connectSearchWidgetWithEditor(replaceBar);

        searcherConnections+=connect(replaceBar,&KCReplaceWindow::requireReplace,
                                     editor,&KCTextEditor::replace);
        searcherConnections+=connect(replaceBar,&KCReplaceWindow::requireReplaceAndFind,
                                     editor,&KCTextEditor::replaceAndFind);
        searcherConnections+=connect(replaceBar,&KCReplaceWindow::requireReplaceAll,
                                     editor,&KCTextEditor::replaceAll);
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
            QErrorMessage error(this);
            error.showMessage(tr("Saving file failed!"));
            error.exec();
        }
        return false;
    }
    else
    {
        return true;
    }
}

bool KCCodeEditor::requireSaveAs(const QString &Caption)
{
    if(KCGeneralConfigure::getInstance()->getUseDefaultLanguageWhenSave())
    {
        QString defaultSelectFilter;
        switch(KCGeneralConfigure::getInstance()->getDefaultLanguageMode())
        {
        case 1:
            defaultSelectFilter=KCGeneralConfigure::getInstance()->getCfFilter();
            break;
        case 2:
            defaultSelectFilter=KCGeneralConfigure::getInstance()->getCppfFilter();
            break;
        case 3:
            defaultSelectFilter=KCGeneralConfigure::getInstance()->getPasfFilter();
            break;
        default:
            defaultSelectFilter=KCGeneralConfigure::getInstance()->getAsfFilter();
        }
        filePath=QFileDialog::getSaveFileName(this,
                                              Caption,
                                              KCHistoryConfigure::getInstance()->getHistoryDir(),
                                              KCGeneralConfigure::getInstance()->getStrFileFilter(),
                                              &defaultSelectFilter);
    }
    else
    {
        filePath=QFileDialog::getSaveFileName(this,
                                              Caption,
                                              KCHistoryConfigure::getInstance()->getHistoryDir(),
                                              KCGeneralConfigure::getInstance()->getStrFileFilter());
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

void KCCodeEditor::closeEvent(QCloseEvent *e)
{
    if(!cacheNewFileMode && editor->document()->isModified())
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
    }
    else
    {
        e->accept();
    }

    return ;
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
    hideSearchBar();
    replaceBar->hideAnime();
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
    fileTextCursor=editor->textCursor();
    emit fileTextCursorChanged();
}

QTextCursor KCCodeEditor::getTextCursor()
{
    return fileTextCursor;
}

int KCCodeEditor::getTextLines()
{
    return editor->document()->blockCount();
}

void KCCodeEditor::setDocumentCursor(int nLine, int linePos)
{
    editor->setDocumentCursor(nLine,linePos);
}

void KCCodeEditor::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    searchBar->updateGeometry();
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
