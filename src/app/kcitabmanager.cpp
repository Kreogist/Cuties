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

#include "kcitabmanager.h"

kciTabManager::kciTabManager(QWidget *parent) :
    QTabWidget(parent)
{
    clear();

    connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(on_tab_close_requested(int)));
    connect(this,SIGNAL(currentChanged(int)),this,SLOT(on_current_tab_change(int)));

    strFileFilter = QObject::tr("All Support Files")+
            "(*.txt *.h *.hpp *.rh *.hh *.c *.cpp *.cc *.cxx *.c++ *.cp *.pas);;"+
            QObject::tr("Plain Text Files")+"(*.txt);;"+
            QObject::tr("Hearder Files")+"(*.h *.hpp *.rh *.hh);;"+
            QObject::tr("C Source Files")+"(*.c);;"+
            QObject::tr("C++ Source Files")+"(*.cpp *.cc *.cxx *.c++ *.cp);;"+
            QObject::tr("Pascal Source Files")+"(*.pas);;"+
            QObject::tr("All Files")+"(*.*)";

    QTabBar *tmpTabBar = this->tabBar();
    QPalette pal=tmpTabBar->palette();
    pal.setColor(QPalette::WindowText,QColor(200,200,200));
    pal.setColor(QPalette::HighlightedText,QColor(255,255,255));
    pal.setColor(QPalette::Button,QColor(83,83,83));
    tmpTabBar->setPalette(pal);

    setAcceptDrops(true);
    setDocumentMode(true);
    setMovable(true);
    setTabsClosable(true);
    setElideMode(Qt::ElideRight);
    setTabPosition(QTabWidget::South);

    tab_count=1;
    new_file_count=1;
    currentEditor=NULL;
}

void kciTabManager::openHistoryFiles()
{
    QList<QString> lastTimeUnClosedFiles=kciEditorConfigure::getInstance()->getAllUnClosedFilePaths();
    for(int i=0;i<lastTimeUnClosedFiles.size();i++)
        open(lastTimeUnClosedFiles.at(i));
}

kciCodeEditor* kciTabManager::getCurrentEditor() const
{
    return currentEditor;
}

/*!
 * \brief kciTabManager::open will open the file and switch to it.
 * \param filePath the path of the file that should be opened.
 * \return the index of the tab of this file.
 */
int kciTabManager::open(const QString& filePath)
{
    QString name=QFileInfo(filePath).fileName();
    //Check if file has been opened.
    int i=count();
    while(i--)
    {
        kciCodeEditor *judgeEditor=qobject_cast<kciCodeEditor *>(widget(i));
        if(judgeEditor!=NULL)
        {
            if(judgeEditor->getDocumentTitle() == name)
            {
                return i;
            }
        }
    }
    //File has not been opened, then open it and add tab.
    kciCodeEditor *tmp;
    tmp=new kciCodeEditor(this);
    if(tmp->open(filePath))
    {
        tmp->setDocumentTitle(name);
        connect(tmp,SIGNAL(fileTextCursorChanged()),this,SLOT(currentTextCursorChanged()));
        emit tabAdded();
        return addTab(tmp,name);
    }
    else
    {
        tmp->deleteLater();
        return currentIndex();
    }
}

void kciTabManager::openAndJumpTo(const QString &filePath)
{
    setCurrentIndex(open(filePath));
}

void kciTabManager::open()
{
    QSettings settings(kciGlobal::getInstance()->getSettingsFileName(),QSettings::IniFormat);
    QStringList file_name_list=QFileDialog::getOpenFileNames(this,
                                                             tr("Open File"),
                                                             settings.value("files/historyDir").toString(),
                                                             strFileFilter);
    int i;
    QString name;

    if(!file_name_list.isEmpty())
    {
        name=*file_name_list.begin();
        for(i=name.size()-1;i>=0;i--)
            if(name[i]=='/')
                break;
        settings.setValue("files/historyDir",name.left(i));
    }

    int _last_tab_index=currentIndex();

    while(!file_name_list.isEmpty())
    {
        name=*file_name_list.begin();
        _last_tab_index=open(name);
        file_name_list.pop_front();
    }
    setCurrentIndex(_last_tab_index);
    currentTextCursorChanged();
}

void kciTabManager::new_file()
{
    kciCodeEditor *tmp=new kciCodeEditor(this);
    if(tmp!=NULL)
    {
        tmp->setGeometry(0, -this->height(), this->width(), this->height());
        connect(tmp,SIGNAL(fileTextCursorChanged()),this,SLOT(currentTextCursorChanged()));
        QString _new_file_title=
                tr("Untitled")+ " " +QString::number(new_file_count++);
        tmp->setDocumentTitle(_new_file_title);
        setCurrentIndex(addTab(tmp,_new_file_title));
        currentTextCursorChanged();

        emit tabAdded();
    }
    else
    {
        QErrorMessage error(this);
        error.showMessage(tr("out of memmory!"));
        error.exec();
    }
}

void kciTabManager::switchNextTab()
{
    int current=currentIndex();
    current=(current+1)%count();
    setCurrentIndex(current);
}

void kciTabManager::switchPrevTab()
{
    int current=currentIndex()+count();
    current=(current-1)%count();
    setCurrentIndex(current);
}

void kciTabManager::save()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->save();
    }
}

void kciTabManager::save_as()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->saveAs();
    }
}

void kciTabManager::save_all()
{
    save_all_file();
}

bool kciTabManager::save_all_file()
{
    int i=count();
    while(i--)
    {
        kciCodeEditor *editor = qobject_cast<kciCodeEditor *>(widget(i));

        if(Q_LIKELY(editor != NULL))
        {
            editor->save();
        }
    }
    return true;
}

void kciTabManager::close_all_tab()
{
    int i=count();
    while(i--)
    {
        kciCodeEditor *editor = qobject_cast<kciCodeEditor *>(widget(i));
        if(Q_LIKELY(editor != NULL))
        {
            on_tab_close_requested(i);
        }
    }
}

void kciTabManager::close_all_other_tab()
{
    int i=count();
    while(i--)
    {
        kciCodeEditor *editor = qobject_cast<kciCodeEditor *>(widget(i));

        if(Q_LIKELY(editor!=NULL) && i!=currentIndex())
        {
            on_tab_close_requested(i);
        }
    }
}

void kciTabManager::undo()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->undo();
    }
}

void kciTabManager::redo()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->redo();
    }
}

void kciTabManager::copy()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->copy();
    }
}

void kciTabManager::cut()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->cut();
    }
}

void kciTabManager::paste()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->paste();
    }
}

void kciTabManager::select_all()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->selectAll();
    }
}

void kciTabManager::on_tab_close_requested(int index)
{
    QWidget *tab=widget(index);

    if(tab!=NULL)
    {
        tab->setAttribute(Qt::WA_DeleteOnClose,true);
        if(tab->close())
        {
            removeTab(index);
        }
    }
    if(this->count()==0)
    {
        emit tabClear();
    }
}

void kciTabManager::close_current_tab()
{
    on_tab_close_requested(currentIndex());
}

void kciTabManager::on_current_tab_change(int index)
{
    currentEditor=qobject_cast<kciCodeEditor *>(widget(index));

    if(currentEditor!=NULL)
    {
        currentEditor->setTextFocus();
    }

    currentTextCursorChanged();
}

void kciTabManager::closeEvent(QCloseEvent *e)
{
    e->accept();//set the accept flag

    kciEditorConfigure::getInstance()->clearAllUnClosedFilePaths();
    int i=count();
    while(i--)
    {
        QWidget *page=widget(i);

        kciCodeEditor *editor=qobject_cast<kciCodeEditor*>(page);
        if(editor!=NULL)
            kciEditorConfigure::getInstance()->addUnClosedFilePath(editor->getFilePath());

        if(!page->close())
        {
            e->ignore();//clean the accept flag
            break;
        }
        else
        {
            removeTab(i);
        }
    }
}

void kciTabManager::renameTabTitle(QString title)
{
    QWidget* page=qobject_cast<QWidget*>(sender());
    if(page!=NULL)
    {
        setTabText(indexOf(page),title);
    }
    else
        qWarning()<<"in kciTabManager::renameTabTitle(QString title): a wrong sender!";
}

void kciTabManager::tabInserted(int index)
{
    kciCodeEditor* editor=qobject_cast<kciCodeEditor *>(widget(index));
    if(editor!=NULL)
    {
        connect(editor,SIGNAL(filenameChanged(QString)),this,SLOT(renameTabTitle(QString)));
    }
}

void kciTabManager::currentTextCursorChanged()
{
    if(currentEditor!=NULL)
    {
        currentTextCursor=currentEditor->getTextCursor();
        emit cursorDataChanged(currentTextCursor.blockNumber()+1,
                               currentTextCursor.columnNumber());
    }
    else
    {
        emit cursorDataChanged(-1,-1);
    }
}

void kciTabManager::showSearchBar()
{
    if(currentEditor!=NULL)
        currentEditor->showSearchBar();
}

QString kciTabManager::textNowSelect()
{\
    QString returnValue;
    if(currentEditor!=NULL)
    {
        returnValue=currentEditor->getSelectedText();
        if(returnValue.isEmpty())
        {
            returnValue="";
        }
    }
    else
    {
        returnValue="";
    }
    return returnValue;
}

void kciTabManager::switchCurrentToLine(int nLineNum, int nColNum)
{
    if(currentEditor!=NULL)
    {
        currentEditor->setDocumentCursor(nLineNum,nColNum);
    }
}

void kciTabManager::setFocus()
{
    if(currentEditor!=NULL)
    {
        currentEditor->setTextFocus();
    }
}

int kciTabManager::getCurrentLineCount() const
{
    if(currentEditor!=NULL)
    {
        return currentEditor->document()->blockCount();
    }
    else
    {
        return -1;
    }
}

int kciTabManager::getCurrentLineNum() const
{
    if(currentEditor!=NULL)
    {
        return currentEditor->getTextCursor().blockNumber()+1;
    }
    else
    {
        return -1;
    }
}

