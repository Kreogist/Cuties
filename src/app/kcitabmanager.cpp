/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *      Wang Luming <wlm199558@126.com>
 *      Miyanaga Saki <tomguts@126.com>
 *      Zhang Jiayi <bf109g2@126.com>
 *
 *  This file is part of Kreogist-Cute-IDE.
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

    setDocumentMode(true);
    setMovable(true);
    setTabsClosable(true);
    setElideMode(Qt::ElideRight);
    setTabPosition(QTabWidget::South);
    tab_count=1;
    new_file_count=1;
}

kciTextEditor* kciTabManager::getCurrentEditor()
{
    return currentEditor;
}

int kciTabManager::open(const QString& filePath)
{
    QString name=QFileInfo(filePath).fileName();
    //Check if file has been opened.
    int i=count();
    while(i--)
    {
        kciTextEditor *judgeEditor=qobject_cast<kciTextEditor *>(widget(i));
        if(judgeEditor!=NULL)
        {
            if(judgeEditor->getDocumentTitle() == name)
            {
                return i;
            }
        }
    }
    //File has not been opened, then open it and add tab.
    kciTextEditor *tmp;
    tmp=new kciTextEditor(this);
    tmp->open(filePath);
    tmp->setDocumentTitle(name);
    connect(tmp,SIGNAL(fileTextCursorChanged()),this,SLOT(currentTextCursorChanged()));
    return addTab(tmp,name);
}

void kciTabManager::openAndJumpTo(const QString &filePath)
{
    setCurrentIndex(open(filePath));

}

void kciTabManager::open()
{
    QSettings settings(kciGlobal::settingsFileName,QSettings::IniFormat);
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
    emit tabAdded();
}

void kciTabManager::new_file()
{
    kciTextEditor *tmp=new kciTextEditor(this);
    if(tmp!=NULL)
    {
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
    if(++current>=count())
    {
        current=0;
    }
    setCurrentIndex(current);
}

void kciTabManager::switchPrevTab()
{
    int current=currentIndex();
    if(--current<0)
    {
        current=count()-1;
    }
    setCurrentIndex(current);
}

void kciTabManager::save()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {

        if(Q_UNLIKELY(!currentEditor->save()))
        {
            QErrorMessage error(this);
            error.showMessage(tr("Saving file failed!"));
            error.exec();
        }
    }
}

void kciTabManager::save_as()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        if(Q_UNLIKELY(!currentEditor->saveAs()))
        {
            QErrorMessage error(this);
            error.showMessage(tr("Saving file failed!"));
            error.exec();
        }
    }
}

void kciTabManager::save_all()
{
    int i=count();
    while(i--)
    {
        kciTextEditor *editor = qobject_cast<kciTextEditor *>(widget(i));

        if(Q_LIKELY(editor != NULL))
        {
            if(Q_UNLIKELY(!editor->save()))
            {
                QErrorMessage error(this);
                error.showMessage(tr("Saving file failed!"));
                error.exec();
            }
        }
    }
}

void kciTabManager::close_all_tab()
{
    int i=count();
    while(i--)
    {
        kciTextEditor *editor = qobject_cast<kciTextEditor *>(widget(i));

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
        kciTextEditor *editor = qobject_cast<kciTextEditor *>(widget(i));

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
    kciTextEditor* editor=qobject_cast<kciTextEditor *>(widget(index));
    if(editor!=NULL)
    {
        currentEditor=editor;
        editor->setTextFocus();
    }
    else
    {
        currentEditor=NULL;
    }
    currentTextCursorChanged();
}

void kciTabManager::closeEvent(QCloseEvent *e)
{
    e->accept();//set the accept flag
    int i=count();
    while(i--)
    {
        QWidget *page=widget(i);
        if(!page->close())
        {
            e->ignore();//clean the accept flag
            break;
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
    kciTextEditor* editor=qobject_cast<kciTextEditor *>(widget(index));
    if(editor!=NULL)
    {
        connect(editor,SIGNAL(filenameChanged(QString)),this,SLOT(renameTabTitle(QString)));
    }
}

void kciTabManager::currentTextCursorChanged()
{
    kciTextEditor* editor=qobject_cast<kciTextEditor *>(widget(this->currentIndex()));
    if(editor!=NULL)
    {
        currentTextCursor=editor->getTextCursor();
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
    kciTextEditor* editor=qobject_cast<kciTextEditor *>(widget(this->currentIndex()));

    if(editor!=NULL)
        editor->showSearchBar();
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

int kciTabManager::getCurrentLineCount()
{
    if(currentEditor!=NULL)
    {
        return currentEditor->document->blockCount();
    }
    else
    {
        return -1;
    }
}

int kciTabManager::getCurrentLineNum()
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

//TODO: Fixed Me!!!!!!

void kciTabManager::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat("text/uri-list"))
    {
        event->acceptProposedAction();
    }
}

void kciTabManager::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
    {
        return;
    }
    for(int i=0;i<urls.count();i++)
    {
        qDebug()<<urls[i];
    }
}
