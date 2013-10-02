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

#include "kccodeeditor.h"

static const int SearchBarOffset = 20;

KCCodeEditor::KCCodeEditor(QWidget *parent) :
    QWidget(parent)
{
    setFont(QString("Monaco"));

    replaceLayout=new QVBoxLayout(this);
    replaceLayout->setContentsMargins(0,0,0,0);
    replaceLayout->setMargin(0);
    replaceLayout->setSpacing(0);
    setLayout(replaceLayout);

    //setWindowFlags(Qt::AnchorPoint);
    mainLayout=new QHBoxLayout();
    mainLayout->setSpacing(0);
    setContentsMargins(0,0,0,0);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    markPanel=new KCMarkPanel(this);
    markPanel->setVisible(false);
    markPanel->setEnabled(false);
    mainLayout->addWidget(markPanel);

    linePanel=new KCLinenumPanel(this);
    mainLayout->addWidget(linePanel);

    editor=new KCTextEditor(this);
    linePanel->setKciTextEditor(editor);
    markPanel->setKciTextEditor(editor);
    mainLayout->addWidget(editor);

    replaceLayout->addLayout(mainLayout);

    replaceBar=new KCReplaceDock(this);
    replaceBar->hide();
    replaceLayout->addWidget(replaceBar);

    connect(editor->document(),SIGNAL(modificationChanged(bool)),
            this,SLOT(onModificationChanged(bool)));
    connect(editor,SIGNAL(cursorPositionChanged()),
            this,SLOT(cursorChanged()));
    connect(editor,SIGNAL(overwriteModeChanged(bool)),
            this, SIGNAL(rewriteStateChanged(bool)));

    //Default Disable Overwrite Mode.
    editor->setOverwriteMode(false);

    m_langMode=new KCLanguageMode(this);

    QPalette pal = palette();
    pal.setColor(QPalette::Base,QColor(0x53,0x53,0x53));
    pal.setColor(QPalette::Text,QColor(255,255,255));
    setPalette(pal);

    filePath.clear();
    fileError=QFileDevice::NoError;

    searchBar=new KCSearchWindow(editor);
    searchBar->hide();
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
    searcherConnections+=connect(widget, &KCSearchWidget::requireHide,
                                 this, &KCCodeEditor::hideSearchBar);
    searcherConnections+=connect(widget,&KCSearchWidget::requireSearch,
                                 editor,&KCTextEditor::searchString);
    searcherConnections+=connect(widget,&KCSearchWidget::requireShowNextResult,
                                 editor,&KCTextEditor::showNextSearchResult);
    searcherConnections+=connect(widget,&KCSearchWidget::requireShowPreviousResult,
                                 editor,&KCTextEditor::showPreviousSearchResult);
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
        QPropertyAnimation *searchAnime=new QPropertyAnimation(searchBar,"geometry");
        QRect animeEndPos=searchBar->rect();
        animeEndPos.setX(editor->width()-searchBar->width()-SearchBarOffset);
        QRect animeStartPos=animeEndPos;
        animeStartPos.setTop(-animeStartPos.height());
        searchAnime->setStartValue(animeStartPos);
        searchAnime->setDuration(300);
        searchAnime->setEndValue(animeEndPos);
        searchAnime->setEasingCurve(QEasingCurve::OutCubic);
        searchBar->show();
        searchAnime->start(QPropertyAnimation::DeleteWhenStopped);

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
        QPropertyAnimation *searchAnime=new QPropertyAnimation(searchBar,"geometry");
        QRect animeStartPos=searchBar->geometry();
        QRect animeEndPos=animeStartPos;
        animeEndPos.setTop(-animeStartPos.height() - 20);
        searchAnime->setStartValue(animeStartPos);
        searchAnime->setDuration(300);
        searchAnime->setEndValue(animeEndPos);
        searchAnime->setEasingCurve(QEasingCurve::OutCubic);
        connect(searchAnime, SIGNAL(finished()),
                searchBar, SLOT(hide()));
        searchAnime->start(QPropertyAnimation::DeleteWhenStopped);
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

        searcherConnections+=connect(replaceBar,&KCReplaceDock::requireReplace,
                                     editor,&KCTextEditor::replace);
        searcherConnections+=connect(replaceBar,&KCReplaceDock::requireReplaceAndFind,
                                     editor,&KCTextEditor::replaceAndFind);
        searcherConnections+=connect(replaceBar,&KCReplaceDock::requireReplaceAll,
                                     editor,&KCTextEditor::replaceAll);
    }

    QTextCursor _textCursor=editor->textCursor();
    if(_textCursor.hasSelection())
    {
        replaceBar->setText(_textCursor.selectedText());
    }
    replaceBar->setTextFocus();
}

bool KCCodeEditor::open(const QString &fileName)
{
    QFile _file(fileName);

    if(_file.open(QIODevice::ReadOnly |QIODevice::Text))
    {
        QTextStream _textIn(&_file);

        editor->clear();
        editor->setPlainText(QString(_textIn.readAll()));

        fileInfoChanged(_file);
        KCHistoryConfigure::getInstance()->addRecentFileRecord(filePath);
        return true;
    }
    else
    {
        fileError=_file.error();
        return false;
    }
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
        if(!dosaveas(tr("Save")))
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
}

bool KCCodeEditor::saveAs()
{
    if(!dosaveas(tr("Save As")))
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

bool KCCodeEditor::dosaveas(const QString &Caption)
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

bool KCCodeEditor::saveAs(const QString &fileName)
{

    QFile _file(fileName);

    if(_file.open(QIODevice::WriteOnly |QIODevice::Text))
    {
        QTextStream _textOut(&_file);
        _textOut<<editor->toPlainText()<<flush;
        fileInfoChanged(_file);
        return true;
    }
    else
    {
        fileError=_file.error();
        return false;
    }
}

void KCCodeEditor::closeEvent(QCloseEvent *e)
{
    if(editor->document()->isModified())
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

    searchBar->setGeometry(editor->width()-searchBar->width()-SearchBarOffset,
                           0,
                           searchBar->width(),
                           searchBar->height());
}

void KCCodeEditor::fileInfoChanged(const QFile &file)
{
    QFileInfo _fileInfo(file);
    editor->setDocumentTitle(_fileInfo.fileName());
    emit filenameChanged(_fileInfo.fileName());

    m_langMode->setFileSuffix(_fileInfo.suffix());

    filePath=file.fileName();
    fileError=QFileDevice::NoError;
    editor->document()->setModified(false);

    computeExecFileName();
    KCHistoryConfigure::getInstance()->setHistoryDir(_fileInfo.absolutePath());
}

KCLanguageMode *KCCodeEditor::langMode() const
{
    return m_langMode;
}

bool KCCodeEditor::isModified()
{
    return editor->document()->isModified();
}

void KCCodeEditor::insertTextAtCursor(QString insertText)
{
    editor->insertPlainText(insertText);
}

