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

KCITabManager::KCITabManager(QWidget *parent) :
    QTabWidget(parent)
{
    clear();

    editorConfigureInstance=kciEditorConfigure::getInstance();

    tabBarControl = this->tabBar();
    QPalette pal=tabBarControl->palette();
    pal.setColor(QPalette::WindowText,QColor(200,200,200));
    pal.setColor(QPalette::HighlightedText,QColor(255,255,255));
    pal.setColor(QPalette::Button,QColor(83,83,83));
    tabBarControl->setPalette(pal);
    tabBarControl->setMinimumHeight(0);
    tabBarControl->setContentsMargins(0,0,0,0);

    setAcceptDrops(true);
    setDocumentMode(true);
    setContentsMargins(0,0,0,0);
    setMovable(editorConfigureInstance->getTabMoveable());
    setTabsClosable(editorConfigureInstance->getTabCloseable());
    setElideMode(Qt::ElideRight);
    setTabPosition(QTabWidget::South);

    connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(on_tab_close_requested(int)));
    connect(this,SIGNAL(currentChanged(int)),this,SLOT(on_current_tab_change(int)));
    connect(editorConfigureInstance, SIGNAL(tabMoveableChanged(bool)),this,SLOT(setTabMoveableValue(bool)));
    connect(editorConfigureInstance, SIGNAL(tabCloseableChanged(bool)),this,SLOT(setTabCloseable(bool)));

    tab_count=1;
    new_file_count=1;
    currentEditor=NULL;
}

void KCITabManager::openHistoryFiles()
{
    QList<QString> lastTimeUnClosedFiles=kciHistoryConfigure::getInstance()->getAllUnClosedFilePaths();
    QList<int> lastTimeUnClosedHs=kciHistoryConfigure::getInstance()->getAllUnClosedFileHs();
    QList<int> lastTimeUnClosedVs=kciHistoryConfigure::getInstance()->getAllUnClosedFileVs();

    int hisItem;
    for(int i=0; i<lastTimeUnClosedFiles.size(); i++)
    {
        hisItem=open(lastTimeUnClosedFiles.at(i));
        KCICodeEditor *editor = qobject_cast<KCICodeEditor *>(widget(hisItem));

        editor->setDocumentCursor(lastTimeUnClosedHs.at(i), lastTimeUnClosedVs.at(i));
    }
    if(kciHistoryConfigure::getInstance()->getUnClosedCurrent()>-1)
    {
        setCurrentIndex(kciHistoryConfigure::getInstance()->getUnClosedCurrent());
    }
}

KCICodeEditor *KCITabManager::getCurrentEditor() const
{
    return currentEditor;
}

/*!
 * \brief kciTabManager::open will open the file and switch to it.
 * \param filePath the path of the file that should be opened.
 * \return the index of the tab of this file.
 */
int KCITabManager::open(const QString &filePath)
{
    QString name=QFileInfo(filePath).fileName();
    //Check if file has been opened.
    int i=count();
    while(i--)
    {
        KCICodeEditor *judgeEditor=qobject_cast<KCICodeEditor *>(widget(i));
        if(judgeEditor!=NULL)
        {
            if(judgeEditor->getDocumentTitle() == name)
            {
                return i;
            }
        }
    }
    //File has not been opened, then open it and add tab.
    KCICodeEditor *tmp;
    tmp=new KCICodeEditor(this);
    if(tmp->open(filePath))
    {
        tmp->setDocumentTitle(name);
        connect(tmp,SIGNAL(fileTextCursorChanged()),this,SLOT(currentTextCursorChanged()));
        connect(tmp,SIGNAL(rewriteStateChanged(bool)),this,SIGNAL(rewriteDataChanged(bool)));
        emit tabAdded();
        return addTab(tmp,name);
    }
    else
    {
        tmp->deleteLater();
        return currentIndex();
    }
}

void KCITabManager::openAndJumpTo(const QString &filePath)
{
    setCurrentIndex(open(filePath));
}

void KCITabManager::open()
{
    QStringList file_name_list;
    if(kciGeneralConfigure::getInstance()->getUseDefaultLanguageWhenOpen())
    {
        QString defaultSelectFilter;
        switch(kciGeneralConfigure::getInstance()->getDefaultLanguageMode())
        {
        case 1:
            defaultSelectFilter=kciGeneralConfigure::getInstance()->getCfFilter();
            break;
        case 2:
            defaultSelectFilter=kciGeneralConfigure::getInstance()->getCppfFilter();
            break;
        case 3:
            defaultSelectFilter=kciGeneralConfigure::getInstance()->getPasfFilter();
            break;
        default:
            defaultSelectFilter=kciGeneralConfigure::getInstance()->getAsfFilter();
        }
        file_name_list=QFileDialog::getOpenFileNames(this,
                       tr("Open File"),
                       kciHistoryConfigure::getInstance()->getHistoryDir(),
                       kciGeneralConfigure::getInstance()->getStrFileFilter(),
                       &defaultSelectFilter);
    }
    else
    {
        file_name_list=QFileDialog::getOpenFileNames(this,
                       tr("Open File"),
                       kciHistoryConfigure::getInstance()->getHistoryDir(),
                       kciGeneralConfigure::getInstance()->getStrFileFilter());
    }

    QString name;

    if(!file_name_list.isEmpty())
    {
        QFileInfo _fileInfo(*file_name_list.begin());
        kciHistoryConfigure::getInstance()->setHistoryDir(_fileInfo.absolutePath());
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

void KCITabManager::new_file()
{
    KCICodeEditor *tmp=new KCICodeEditor(this);
    if(tmp!=NULL)
    {
        tmp->setGeometry(0, -this->height(), this->width(), this->height());
        connect(tmp,SIGNAL(fileTextCursorChanged()),this,SLOT(currentTextCursorChanged()));
        connect(tmp,SIGNAL(rewriteStateChanged(bool)),this,SIGNAL(rewriteDataChanged(bool)));
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

void KCITabManager::switchNextTab()
{
    int current=currentIndex();
    current=(current+1)%count();
    setCurrentIndex(current);
}

void KCITabManager::switchPrevTab()
{
    int current=currentIndex()+count();
    current=(current-1)%count();
    setCurrentIndex(current);
}

void KCITabManager::save()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->save();
    }
}

void KCITabManager::save_as()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->saveAs();
    }
}

void KCITabManager::save_all()
{
    save_all_file();
}

bool KCITabManager::save_all_file()
{
    int i=count();
    while(i--)
    {
        KCICodeEditor *editor = qobject_cast<KCICodeEditor *>(widget(i));

        if(Q_LIKELY(editor != NULL))
        {
            editor->save();
        }
    }
    return true;
}

void KCITabManager::setTabMoveableValue(bool newValue)
{
    setMovable(newValue);
}

void KCITabManager::close_all_tab()
{
    int i=count();
    while(i--)
    {
        KCICodeEditor *editor = qobject_cast<KCICodeEditor *>(widget(i));
        if(Q_LIKELY(editor != NULL))
        {
            on_tab_close_requested(i);
        }
    }
}

void KCITabManager::close_all_other_tab()
{
    int i=count();
    while(i--)
    {
        KCICodeEditor *editor = qobject_cast<KCICodeEditor *>(widget(i));

        if(Q_LIKELY(editor!=NULL) && i!=currentIndex())
        {
            on_tab_close_requested(i);
        }
    }
}

void KCITabManager::undo()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->undo();
    }
}

void KCITabManager::redo()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->redo();
    }
}

void KCITabManager::copy()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->copy();
    }
}

void KCITabManager::cut()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->cut();
    }
}

void KCITabManager::paste()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->paste();
    }
}

void KCITabManager::select_all()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->selectAll();
    }
}

void KCITabManager::on_tab_close_requested(int index)
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

void KCITabManager::close_current_tab()
{
    on_tab_close_requested(currentIndex());
}

void KCITabManager::on_current_tab_change(int index)
{
    currentEditor=qobject_cast<KCICodeEditor *>(widget(index));

    if(currentEditor!=NULL)
    {
        currentEditor->setTextFocus();
        emit rewriteDataChanged(currentEditor->getOverwriteMode());
    }
    else
    {
        emit rewriteDisVisible();
    }

    currentTextCursorChanged();
}

void KCITabManager::closeEvent(QCloseEvent *e)
{
    //set the accept flag
    e->accept();

    //Cleae the last UnClosed File Paths.
    kciHistoryConfigure::getInstance()->clearAllUnClosedFilePaths();
    int i=count(), cIndex=currentIndex();
    while(i--)
    {
        QWidget *page=widget(i);

        //Save the current opened file.
        KCICodeEditor *editor=qobject_cast<KCICodeEditor *>(page);
        if(kciGeneralConfigure::getInstance()->getRememberUnclosedFile())
        {
            if(editor!=NULL)
            {
                if(editor->getFilePath().length()>0)
                {
                    kciHistoryConfigure::getInstance()->addUnClosedFilePath(editor->getFilePath(),
                            editor->getTextCursor().blockNumber(),
                            editor->getTextCursor().columnNumber());

                }
                else
                {
                    if(i<cIndex)
                    {
                        cIndex--;
                    }
                }
            }
        }

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
    kciHistoryConfigure::getInstance()->setUnClosedCurrent(cIndex);
    kciHistoryConfigure::getInstance()->writeConfigure();
}

void KCITabManager::renameTabTitle(QString title)
{
    QWidget *page=qobject_cast<QWidget *>(sender());
    if(page!=NULL)
    {
        setTabText(indexOf(page),title);
    }
    else
    {
        qWarning()<<"in kciTabManager::renameTabTitle(QString title): a wrong sender!";
    }
}

void KCITabManager::tabInserted(int index)
{
    KCICodeEditor *editor=qobject_cast<KCICodeEditor *>(widget(index));
    if(editor!=NULL)
    {
        connect(editor,SIGNAL(filenameChanged(QString)),this,SLOT(renameTabTitle(QString)));
    }
}

void KCITabManager::currentTextCursorChanged()
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

void KCITabManager::showSearchBar()
{
    if(currentEditor!=NULL)
    {
        currentEditor->showSearchBar();
    }
}

void KCITabManager::showReplaceBar()
{
    if(currentEditor!=NULL)
    {
        currentEditor->showReplaceBar();
    }
}

QString KCITabManager::textNowSelect()
{
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

void KCITabManager::switchCurrentToLine(int nLineNum, int nColNum)
{
    if(currentEditor!=NULL)
    {
        currentEditor->setDocumentCursor(nLineNum,nColNum);
    }
}

void KCITabManager::setFocus()
{
    if(currentEditor!=NULL)
    {
        currentEditor->setTextFocus();
    }
}

int KCITabManager::getCurrentLineCount() const
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

int KCITabManager::getCurrentLineNum() const
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

void KCITabManager::insertToCurrentEditor(QString insertText)
{
    if(currentEditor!=NULL)
    {
        currentEditor->insertTextAtCursor(insertText);
    }
}

void KCITabManager::setTabCloseable(bool newValue)
{
    setTabsClosable(newValue);
}
