/*
 *  Copyright 2013 Wang Luming <wlm199558@126.com>
 *  Copyright 2013 Miyanaga Saki <tomguts@126.com>
 *
 *  kcitexteditor.cpp is part of Kreogist-Cute-IDE.
 *
 *    Kreogist-Cute-IDE is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cute-IDE is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cute-IDE.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "kcitexteditor.h"

kciTextEditor::kciTextEditor(QWidget *parent) :
    QWidget(parent)
{
    //setWindowFlags(Qt::AnchorPoint);

    mainLayout=new QHBoxLayout(this);
    mainLayout->setSpacing(0);
    setContentsMargins(0,0,0,0);
    mainLayout->setMargin(0);
    setLayout(mainLayout);

    linePanel=new kciLinenumPanel(this);
    mainLayout->addWidget(linePanel);

    editor=new kciCodeEditor(this);
    linePanel->setPlainTextEdit(editor);
    mainLayout->addWidget(editor);
    connect(editor->document(),SIGNAL(modificationChanged(bool)),
            this,SLOT(onModificationChanged(bool)));

    highlighter=new plaintextHighlighter(this);
    highlighter->setDocument(editor->document());

    QPalette pal = palette();
    pal.setColor(QPalette::Base,QColor(0x53,0x53,0x53));
    pal.setColor(QPalette::Text,QColor(255,255,255));
    setPalette(pal);

    strFileFilter=tr("All Support Files")+
            "(*.txt *.h *.hpp *.rh *.hh *.c *.cpp *.cc *.cxx *.c++ *.cp *.pas);;"+
            tr("Plain Text Files")+"(*.txt);;"+
            tr("Hearder Files")+"(*.h *.hpp *.rh *.hh);;"+
            tr("C Source Files")+"(*.c);;"+
            tr("C++ Source Files")+"(*.cpp *.cc *.cxx *.c++ *.cp);;"+
            tr("Pascal Source Files")+"(*.pas);;"+
            tr("All Files")+"(*.*)";

    filePath.clear();
    fileError=QFileDevice::NoError;
}

bool kciTextEditor::open()
{
    QSettings settings(kciGlobal::settingsFileName,QSettings::IniFormat);
    filePath=QFileDialog::getOpenFileName(this,tr("open"),
                                          settings.value("texteditor/historyDir").toString(),
                                          strFileFilter);
    if(!filePath.isEmpty())
    {
        return open(filePath);
    }
    else
    {
        return false;
    }
}

bool kciTextEditor::open(const QString &fileName)
{
    QFile _file(fileName);

    if(_file.open(QIODevice::ReadOnly |QIODevice::Text))
    {
        QTextStream _textIn(&_file);

        editor->clear();
        editor->insertPlainText(QString(_textIn.readAll()));
        editor->document()->setModified(false);

        QFileInfo _fileInfo(_file);
        editor->setDocumentTitle(_fileInfo.fileName());
        emit filenameChanged(_fileInfo.fileName());

        if(highlighter == nullptr)
        {
            highlighter = highlighterFactory::createHighlighterByFileName(
                        _fileInfo.fileName(), this);

            highlighter->setDocument(editor->document());
            highlighter->rehighlight();
        }
        else
        {
            highlighter->deleteLater();
            highlighter = highlighterFactory::createHighlighterByFileName(
                        _fileInfo.fileName(), this);

            highlighter->setDocument(editor->document());
            highlighter->rehighlight();
        }

        filePath=fileName;
        fileError=QFileDevice::NoError;

        QSettings settings(kciGlobal::settingsFileName,QSettings::IniFormat);
        settings.setValue("texteditor/historyDir",_fileInfo.absolutePath());

        return true;
    }
    else
    {
        fileError=_file.error();
        return false;
    }
}

QFileDevice::FileError kciTextEditor::error()
{
    return fileError;
}

bool kciTextEditor::save()
{
    if(!filePath.isEmpty())
    {
        return saveAs(filePath);
    }
    else
    {
        QSettings settings(kciGlobal::settingsFileName,QSettings::IniFormat);
        filePath=QFileDialog::getSaveFileName(this,tr("save"),settings.value("texteditor/historyDir").toString(),strFileFilter);

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
}

bool kciTextEditor::saveAs()
{
    QSettings settings(kciGlobal::settingsFileName,QSettings::IniFormat);
    filePath=QFileDialog::getSaveFileName(this,tr("save as"),settings.value("texteditor/historyDir").toString(),strFileFilter);

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

bool kciTextEditor::saveAs(const QString &fileName)
{

    QFile _file(fileName);

    if(_file.open(QIODevice::WriteOnly |QIODevice::Text))
    {
        QTextStream _textOut(&_file);

        _textOut<<editor->toPlainText()<<flush;

        QFileInfo _fileInfo(_file);
        editor->setDocumentTitle(_fileInfo.fileName());
        emit filenameChanged(_fileInfo.fileName());

        filePath=fileName;
        fileError=QFileDevice::NoError;
        editor->document()->setModified(false);

        QSettings settings(kciGlobal::settingsFileName,QSettings::IniFormat);
        settings.setValue("texteditor/historyDir",_fileInfo.absolutePath());

        if(highlighter == nullptr)
        {
            highlighter = highlighterFactory::createHighlighterByFileName(
                        _fileInfo.fileName(), this);

            highlighter->setDocument(editor->document());
            highlighter->rehighlight();
        }
        else
        {
            highlighter->deleteLater();
            highlighter = highlighterFactory::createHighlighterByFileName(
                        _fileInfo.fileName(), this);

            highlighter->setDocument(editor->document());
            highlighter->rehighlight();
        }

        return true;
    }
    else
    {
        fileError=_file.error();
        return false;
    }
}

void kciTextEditor::closeEvent(QCloseEvent *e)
{
    if(editor->document()->isModified())
    {
        QMessageBox msgbox(this);

        msgbox.setText(tr("The document has been modified.")+"\n"+
                       filePath);
        msgbox.setInformativeText(tr("Do you want to save your changes?"));

        msgbox.setStandardButtons(QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);
        msgbox.setDefaultButton(QMessageBox::Save);
        msgbox.setButtonText(QMessageBox::Save,tr("Save"));
        msgbox.setButtonText(QMessageBox::Discard,tr("Discard"));
        msgbox.setButtonText(QMessageBox::Cancel,tr("Cancel"));

        int ret=msgbox.exec();

        switch (ret)
        {
        case QMessageBox::Save:
            // Save was clicked
            if(!save())
            {
                //Save file failed
                msgbox.setText(tr("Saving file failed!"));
                msgbox.setInformativeText(tr("Please save it again"));
                msgbox.setStandardButtons(QMessageBox::Ok);
                msgbox.setDefaultButton(QMessageBox::Ok);
                msgbox.setIcon(QMessageBox::Warning);

                msgbox.exec();
                e->ignore();
            }

            break;
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
        e->accept();

    return ;
}

void kciTextEditor::setDocumentTitle(const QString& title)
{
    editor->setDocumentTitle(title);
    emit filenameChanged(title);
}

void kciTextEditor::redo()
{
    editor->redo();
}

void kciTextEditor::undo()
{
    editor->undo();
}

void kciTextEditor::copy()
{
    editor->copy();
}

void kciTextEditor::cut()
{
    editor->cut();
}

void kciTextEditor::paste()
{
    editor->paste();
}

void kciTextEditor::selectAll()
{
    editor->selectAll();
}

void kciTextEditor::onModificationChanged(bool changed)
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
