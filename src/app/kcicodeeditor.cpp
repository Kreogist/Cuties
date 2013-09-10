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

#include "kcicodeeditor.h"

static const int SearchBarOffset = 20;

kciCodeEditor::kciCodeEditor(QWidget *parent) :
    QWidget(parent)
{
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

    strFileFilter = QObject::tr("All Support Files")+
            "(*.txt *.h *.hpp *.rh *.hh *.c *.cpp *.cc *.cxx *.c++ *.cp *.pas);;"+
            QObject::tr("Plain Text Files")+"(*.txt);;"+
            QObject::tr("Hearder Files")+"(*.h *.hpp *.rh *.hh);;"+
            QObject::tr("C Source Files")+"(*.c);;"+
            QObject::tr("C++ Source Files")+"(*.cpp *.cc *.cxx *.c++ *.cp);;"+
            QObject::tr("Pascal Source Files")+"(*.pas);;"+
            QObject::tr("All Files")+"(*.*)";

    markPanel=new kciMarkPanel(this);
    mainLayout->addWidget(markPanel);

    linePanel=new kciLinenumPanel(this);
    mainLayout->addWidget(linePanel);

    editor=new kciTextEditor(this);
    linePanel->setKciTextEditor(editor);
    markPanel->setKciTextEditor(editor);
    document=editor->document();
    mainLayout->addWidget(editor);

    replaceLayout->addLayout(mainLayout);

    replaceBar=new kciReplaceDock(this);
    replaceBar->hide();
    replaceLayout->addWidget(replaceBar);

    connect(editor->document(),SIGNAL(modificationChanged(bool)),
            this,SLOT(onModificationChanged(bool)));
    connect(editor,SIGNAL(cursorPositionChanged()),
            this,SLOT(cursorChanged()));

    m_langMode=new kciLanguageMode(this);

    QPalette pal = palette();
    pal.setColor(QPalette::Base,QColor(0x53,0x53,0x53));
    pal.setColor(QPalette::Text,QColor(255,255,255));
    setPalette(pal);

    filePath.clear();
    fileError=QFileDevice::NoError;

    searchBar=new kciSearchWindow(editor);
    searchBar->hide();
    connect(searchBar,SIGNAL(hideButtonPressed()),editor,SLOT(setFocus()));
    connect(searchBar,&kciSearchWindow::requireSearch,
            editor,&kciTextEditor::searchString);
    connect(searchBar,&kciSearchWindow::requireShowNextResult,
            editor,&kciTextEditor::showNextSearchResult);
    connect(searchBar,&kciSearchWindow::requireShowPreviousResult,
            editor,&kciTextEditor::showPreviousSearchResult);
}

kciCodeEditor::~kciCodeEditor()
{
    mainLayout->deleteLater();
}

QString kciCodeEditor::getExecFileName()
{
    return execFileName;
}

void kciCodeEditor::computeExecFileName()
{
    QFileInfo _fileInfo(filePath);
    execFileName=_fileInfo.absolutePath()+QString("/")+_fileInfo.completeBaseName();
    #ifdef Q_OS_WIN32
            execFileName+=".exe";
    #endif
}

void kciCodeEditor::showSearchBar()
{
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
    }

    QTextCursor _textCursor=editor->textCursor();
    if(_textCursor.hasSelection())
        searchBar->setText(_textCursor.selectedText());
    searchBar->setTextFocus();
}

void kciCodeEditor::showReplaceBar()
{
    replaceBar->show();
}

bool kciCodeEditor::open(const QString &fileName)
{
    QFile _file(fileName);

    if(_file.open(QIODevice::ReadOnly |QIODevice::Text))
    {
        QTextStream _textIn(&_file);

        editor->clear();
        editor->setPlainText(QString(_textIn.readAll()));

        fileInfoChanged(_file);

        return true;
    }
    else
    {
        fileError=_file.error();
        return false;
    }
}

QFileDevice::FileError kciCodeEditor::error()
{
    return fileError;
}

bool kciCodeEditor::save()
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

bool kciCodeEditor::saveAs()
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

bool kciCodeEditor::dosaveas(const QString &Caption)
{
    QSettings settings(kciGlobal::getInstance()->getSettingsFileName(),
                       QSettings::IniFormat);
    filePath=QFileDialog::getSaveFileName(this,Caption,settings.value("texteditor/historyDir").toString(),strFileFilter);

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

bool kciCodeEditor::saveAs(const QString &fileName)
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

void kciCodeEditor::closeEvent(QCloseEvent *e)
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

        switch (ret)
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

void kciCodeEditor::setDocumentTitle(const QString& title)
{
    editor->setDocumentTitle(title);
    emit filenameChanged(title);
}

QString kciCodeEditor::getDocumentTitle()
{
    return editor->documentTitle();
}

void kciCodeEditor::redo()
{
    editor->redo();
}

void kciCodeEditor::undo()
{
    editor->undo();
}

void kciCodeEditor::copy()
{
    editor->copy();
}

void kciCodeEditor::cut()
{
    editor->cut();
}

void kciCodeEditor::paste()
{
    editor->paste();
}

void kciCodeEditor::selectAll()
{
    editor->selectAll();
}

void kciCodeEditor::setTextFocus()
{
    editor->setFocus();
}

void kciCodeEditor::onModificationChanged(bool changed)
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

QString kciCodeEditor::getFilePath()
{
    return filePath;
}

QString kciCodeEditor::getSelectedText()
{
    return editor->textCursor().selectedText();
}

void kciCodeEditor::cursorChanged()
{
    fileTextCursor=editor->textCursor();
    emit fileTextCursorChanged();
}

QTextCursor kciCodeEditor::getTextCursor()
{
    return fileTextCursor;
}

int kciCodeEditor::getTextLines()
{
    return editor->document()->blockCount();
}

void kciCodeEditor::setDocumentCursor(int nLine, int linePos)
{
     editor->setDocumentCursor(nLine,linePos);
}

void kciCodeEditor::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);

    searchBar->setGeometry(editor->width()-searchBar->width()-SearchBarOffset,
                           0,
                           searchBar->width(),
                           searchBar->height());
}

void kciCodeEditor::fileInfoChanged(const QFile &file)
{
    QFileInfo _fileInfo(file);
    editor->setDocumentTitle(_fileInfo.fileName());
    emit filenameChanged(_fileInfo.fileName());

    m_langMode->setFileSuffix(_fileInfo.suffix());

    filePath=file.fileName();
    fileError=QFileDevice::NoError;
    editor->document()->setModified(false);

    computeExecFileName();

    QSettings settings(kciGlobal::getInstance()->getSettingsFileName(),
                       QSettings::IniFormat);
    settings.setValue("texteditor/historyDir",_fileInfo.absolutePath());
}

kciLanguageMode *kciCodeEditor::langMode() const
{
    return m_langMode;
}

bool kciCodeEditor::isModified()
{
    return editor->document()->isModified();
}

QScrollBar *kciCodeEditor::getHScrollBar()
{
    return editor->horizontalScrollBar();
}

QScrollBar *kciCodeEditor::getVScrollBar()
{
    return editor->verticalScrollBar();
}

void kciCodeEditor::setHScrollValue(int x)
{
    editor->horizontalScrollBar()->setValue(x);
}

void kciCodeEditor::setVScrollValue(int y)
{
    editor->verticalScrollBar()->setValue(y);
}

void kciCodeEditor::setScrollValue(int x, int y)
{
    editor->scroll(x, y);
}
