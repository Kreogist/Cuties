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

#include <QToolButton>
#include <QApplication>
#include <QMessageBox>

#include "kctabmanager.h"
#include "kcdocumentrecorder.h"
#include "kclanguageconfigure.h"

KCTabManager::KCTabManager(QWidget *parent) :
    QTabWidget(parent)
{
    retranslate();
    setObjectName("KCTabManager");
    clear();

    editorConfigureInstance=KCEditorConfigure::getInstance();

    setAcceptDrops(true);
    setDocumentMode(true);
    setContentsMargins(0,0,0,0);
    setMovable(editorConfigureInstance->getTabMoveable());
    setTabsClosable(editorConfigureInstance->getTabCloseable());
    setElideMode(Qt::ElideRight);
    setTabPosition(QTabWidget::South);

    createTabMenu();

    tabBarControl = this->tabBar();
    QPalette pal=tabBarControl->palette();
    KCColorConfigure::getInstance()->getPalette(pal,objectName());
    tabBarControl->setPalette(pal);
    tabBarControl->setMinimumHeight(0);
    tabBarControl->setContentsMargins(0,0,0,0);
    tabBarControl->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tabBarControl, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(popupTabMenu(QPoint)));

    connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(onTabCloseRequested(int)));
    connect(this,SIGNAL(currentChanged(int)),this,SLOT(onCurrentTabChange(int)));
    connect(editorConfigureInstance, SIGNAL(tabMoveableChanged(bool)),this,SLOT(setTabMoveableValue(bool)));
    connect(editorConfigureInstance, SIGNAL(tabCloseableChanged(bool)),this,SLOT(setTabCloseable(bool)));

    connect(KCLanguageConfigure::getInstance(), &KCLanguageConfigure::newLanguageSet,
            this, &KCTabManager::retranslateAndSet);

    newFileCount=1;
    currentEditor=NULL;
    globalInstance=KCGlobal::getInstance();
}

void KCTabManager::restoreUnclosedFiles()
{
    int unclosedFileNum=KCDocumentRecorder::getInstance()->getUnclosedFileCount(),
        currentUnclosedFileIndex=KCDocumentRecorder::getInstance()->getUnclosedCurrentIndex(),
        unclosedFileItem;
    for(int i=0; i<unclosedFileNum; i++)
    {
        UnclosedFileStatus currentFileStatus=KCDocumentRecorder::getInstance()->getUnclosedFileStatus(i);
        KCCodeEditor *editor;
        if(currentFileStatus.untitled)
        {
            //New file and cache it.
            unclosedFileItem=newFile();
            editor=qobject_cast<KCCodeEditor *>(widget(unclosedFileItem));
            editor->readCacheFile(currentFileStatus.filePath);
        }
        else
        {
            //Open file
            unclosedFileItem=open(currentFileStatus.filePath);
            editor=qobject_cast<KCCodeEditor *>(widget(unclosedFileItem));
        }
        editor->setDocumentCursor(currentFileStatus.horizontalCursorPosition,
                                  currentFileStatus.verticalCursorPosition);
    }
    if(currentUnclosedFileIndex<count() && currentUnclosedFileIndex>-1)
    {
        setCurrentIndex(currentUnclosedFileIndex);
    }
}

KCCodeEditor *KCTabManager::getCurrentEditor() const
{
    return currentEditor;
}

/*!
 * \brief KCTabManager::open will open the file and switch to it.
 * \param filePath the path of the file that should be opened.
 * \return the index of the tab of this file.
 */
int KCTabManager::open(const QString &filePath)
{
    QString name=QFileInfo(filePath).fileName();
    //Check if file has been opened.
    int i=count();
    while(i--)
    {
        KCCodeEditor *judgeEditor=qobject_cast<KCCodeEditor *>(widget(i));
        if(judgeEditor!=NULL)
        {
            if(judgeEditor->getFilePath() == filePath)
            {
                return i;
            }
        }
    }
    //File has not been opened, then open it and add tab.
    KCCodeEditor *tmp=new KCCodeEditor(this);
    if(tmp->open(filePath))
    {
        tmp->setDocumentTitle(name);
        connect(tmp,SIGNAL(fileTextCursorChanged()),this,SLOT(currentTextCursorChanged()));
        connect(tmp,SIGNAL(rewriteStateChanged(bool)),this,SIGNAL(rewriteDataChanged(bool)));
        connect(tmp,SIGNAL(requiredHideDocks()),this,SIGNAL(requiredHideDocks()));
        emit tabAdded();
        if(count()==0)  //before the tab be added, count() == 0
        {
            emit tabNonClear();
        }
        return addTab(tmp,name);
    }
    else
    {
        tmp->deleteLater();
        return currentIndex();
    }
}

void KCTabManager::openAndJumpTo(const QString &filePath)
{
    setCurrentIndex(open(filePath));
}

void KCTabManager::open()
{
    QStringList fileNameList;
    QString historyDirPath=KCHistoryConfigure::getInstance()->getHistoryDir();
    QFileInfo historyDirDetect(historyDirPath);
    if(!historyDirDetect.exists())
    {
        historyDirPath=qApp->applicationDirPath();
    }
    if(KCGeneralConfigure::getInstance()->getUseDefaultLanguageWhenOpen())
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
        fileNameList=QFileDialog::getOpenFileNames(this,
                       tr("Open File"),
                       historyDirPath,
                       KCGeneralConfigure::getInstance()->getStrFileFilter(),
                       &defaultSelectFilter);
    }
    else
    {
        fileNameList=QFileDialog::getOpenFileNames(this,
                       tr("Open File"),
                       historyDirPath,
                       KCGeneralConfigure::getInstance()->getStrFileFilter());
    }

    QString name;

    if(!fileNameList.isEmpty())
    {
        QFileInfo _fileInfo(*fileNameList.begin());
        KCHistoryConfigure::getInstance()->setHistoryDir(_fileInfo.absolutePath());
    }

    int lastTabIndex=currentIndex();

    while(!fileNameList.isEmpty())
    {
        name=*fileNameList.begin();
        lastTabIndex=open(name);
        fileNameList.pop_front();
    }
    setCurrentIndex(lastTabIndex);
    currentTextCursorChanged();
}

int KCTabManager::newFile()
{
    KCCodeEditor *tmp=new KCCodeEditor(this);
    if(tmp!=NULL)
    {
        tmp->setGeometry(0, -this->height(), this->width(), this->height());
        connect(tmp,SIGNAL(fileTextCursorChanged()),this,SLOT(currentTextCursorChanged()));
        connect(tmp,SIGNAL(rewriteStateChanged(bool)),this,SIGNAL(rewriteDataChanged(bool)));
        QString newFileTitle=
            tr("Untitled")+ " " +QString::number(newFileCount++);
        tmp->setDocumentTitle(newFileTitle);
        connect(tmp,SIGNAL(requiredHideDocks()),this,SIGNAL(requiredHideDocks()));
        emit tabAdded();
        if(count()==0)  //before the tab be added, count() == 1
        {
            emit tabNonClear();
        }
        int newTabIndex=addTab(tmp,newFileTitle);
        setCurrentIndex(newTabIndex);
        currentTextCursorChanged();
        return newTabIndex;
    }
    QErrorMessage error(this);
    error.showMessage(tr("out of memmory!"));
    error.exec();
    return -1;
}

int KCTabManager::newFileWithHighlight(const QString &fileSuffix)
{
    int newTabIndex=newFile();
    if(newTabIndex>-1 && Q_LIKELY(currentEditor!=NULL))
    {
        KCLanguageMode *newFileLanguageMode=currentEditor->langMode();
        newFileLanguageMode->setFileSuffix(fileSuffix);
        currentEditor->setLanguageMode(newFileLanguageMode);
    }
    return newTabIndex;
}

void KCTabManager::switchNextTab()
{
    int current=currentIndex();
    current=(current+1)%count();
    setCurrentIndex(current);
}

void KCTabManager::switchPrevTab()
{
    int current=currentIndex()+count();
    current=(current-1)%count();
    setCurrentIndex(current);
}

void KCTabManager::save()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->save();
    }
}

void KCTabManager::saveAs()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->saveAs();
    }
}

void KCTabManager::saveAll()
{
    int i=count();
    while(i--)
    {
        KCCodeEditor *editor = qobject_cast<KCCodeEditor *>(widget(i));

        if(Q_LIKELY(editor != NULL))
        {
            editor->save();
        }
    }
}

void KCTabManager::setTabMoveableValue(bool newValue)
{
    setMovable(newValue);
}

void KCTabManager::closeAllTab()
{
    int i=count();
    while(i--)
    {
        KCCodeEditor *editor = qobject_cast<KCCodeEditor *>(widget(i));
        if(Q_LIKELY(editor != NULL))
        {
            onTabCloseRequested(i);
        }
    }
}

void KCTabManager::closeAllOtherTab()
{
    int i=count();
    while(i--)
    {
        KCCodeEditor *editor = qobject_cast<KCCodeEditor *>(widget(i));

        if(Q_LIKELY(editor!=NULL) && i!=currentIndex())
        {
            onTabCloseRequested(i);
        }
    }
}

void KCTabManager::undo()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->undo();
    }
}

void KCTabManager::redo()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->redo();
    }
}

void KCTabManager::copy()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->copy();
    }
}

void KCTabManager::cut()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->cut();
    }
}

void KCTabManager::paste()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->paste();
    }
}

void KCTabManager::selectAll()
{
    if(Q_LIKELY(currentEditor!=NULL))
    {
        currentEditor->selectAll();
    }
}

void KCTabManager::onTabCloseRequested(int index)
{
    KCCodeEditor *tab=qobject_cast<KCCodeEditor *>(widget(index));

    if(tab!=NULL)
    {
        //Check this tab is on debugging or not
        if(tab->getDebugging())
        {
            return;
        }
        tab->setAttribute(Qt::WA_DeleteOnClose, true);
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

void KCTabManager::closeCurrentTab()
{
    onTabCloseRequested(currentIndex());
}

void KCTabManager::onCurrentTabChange(int index)
{
    currentEditor=qobject_cast<KCCodeEditor *>(widget(index));

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

void KCTabManager::closeEvent(QCloseEvent *e)
{
    int i,tabCounts=count();
    //Check all tab states
    for(i=0; i<tabCounts; i++)
    {
        KCCodeEditor *editor=qobject_cast<KCCodeEditor *>(widget(i));
        if(editor->getDebugging())
        {
            //This editor is debugging
            QMessageBox msg;
            msg.setText("File " + editor->getDocumentTitle() + " is debugging.");
            msg.exec();
            return;
        }
    }
    //set the accept flag
    e->accept();
    //Cleae the last UnClosed File Paths.
    KCHistoryConfigure::getInstance()->clearAllUnClosedFilePaths();
    KCDocumentRecorder::getInstance()->clear();
    KCDocumentRecorder::getInstance()->setUnclosedCurrentIndex(currentIndex());
    while(i--)
    {
        QWidget *page=widget(i);

        //Save the current opened file.
        KCCodeEditor *editor=qobject_cast<KCCodeEditor *>(page);
        if(KCGeneralConfigure::getInstance()->getRememberUnclosedFile() && editor!=NULL)
        {
            editor->setCacheNewFileMode(true);
            if(editor->getFilePath().isEmpty())
            {
                if(editor->isModified())
                {
                    KCDocumentRecorder::getInstance()->appendRecord(editor);
                }
            }
            else
            {
                KCDocumentRecorder::getInstance()->appendRecord(editor->getFilePath(),
                                                                editor->getTextCursor());
            }
        }
        if(!page->close())
        {
            e->ignore();
            break;
        }
        else
        {
            removeTab(i);
        }
    }
    KCDocumentRecorder::getInstance()->writeSettings();
    KCHistoryConfigure::getInstance()->writeConfigure();
}

void KCTabManager::renameTabTitle(QString title)
{
    QWidget *page=qobject_cast<QWidget *>(sender());
    if(page!=NULL)
    {
        setTabText(indexOf(page),title);
    }
    else
    {
        qWarning()<<"in KCTabManager::renameTabTitle(QString title): a wrong sender!";
    }
}

void KCTabManager::tabInserted(int index)
{
    KCCodeEditor *editor=qobject_cast<KCCodeEditor *>(widget(index));
    if(editor!=NULL)
    {
        connect(editor,SIGNAL(filenameChanged(QString)),this,SLOT(renameTabTitle(QString)));
    }
}

void KCTabManager::currentTextCursorChanged()
{
    if(currentEditor!=NULL)
    {
        emit cursorDataChanged(currentEditor->getTextCursor().blockNumber(),
                               currentEditor->getTextCursor().columnNumber());
    }
    else
    {
        emit cursorDataChanged(-1,-1);
    }
}

void KCTabManager::showSearchBar()
{
    if(currentEditor!=NULL)
    {
        currentEditor->showSearchBar();
    }
}

void KCTabManager::showReplaceBar()
{
    if(currentEditor!=NULL)
    {
        currentEditor->showReplaceBar();
    }
}

QString KCTabManager::textNowSelect()
{
    QString returnValue;
    if(currentEditor!=NULL)
    {
        returnValue=currentEditor->getSelectedText();
        if(!returnValue.isEmpty())
        {
            return returnValue;
        }
    }
    return QString("");
}

void KCTabManager::retranslate()
{
    tabMenuActionCaption[closeTab]=tr("Close Tab");
    tabMenuActionCaption[closeOtherTab]=tr("Close Other Tabs");
    tabMenuActionCaption[browseFile]=tr("Browse File");
}

void KCTabManager::retranslateAndSet()
{
    retranslate();
    for(int i=closeTab; i<TabMenuActionCount; i++)
    {
        tabMenuActionItem[i]->setText(tabMenuActionCaption[i]);
    }
}

void KCTabManager::switchCurrentToLine(int nLineNum, int nColNum)
{
    if(currentEditor!=NULL)
    {
        currentEditor->setDocumentCursor(nLineNum,nColNum);
    }
}

void KCTabManager::setFocus()
{
    if(currentEditor!=NULL)
    {
        currentEditor->setTextFocus();
    }
}

int KCTabManager::getCurrentLineCount() const
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

int KCTabManager::getCurrentLineNum() const
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

void KCTabManager::insertToCurrentEditor(QString insertText)
{
    if(currentEditor!=NULL)
    {
        currentEditor->insertTextAtCursor(insertText);
    }
}

void KCTabManager::setTabCloseable(bool newValue)
{
    setTabsClosable(newValue);
}

void KCTabManager::popupTabMenu(const QPoint &point)
{
    if(point.isNull())
    {
        return;
    }
    int tabIndex = tabBar()->tabAt(point);
    if(tabIndex>-1 && tabIndex==currentIndex())
    {
        tabMenu->exec(tabBar()->mapToGlobal(point));
    }
}

void KCTabManager::browseCurrentFile()
{
    globalInstance->showInGraphicalShell(currentEditor->getFilePath());
}

void KCTabManager::createTabMenu()
{
    tabMenu=new KCNormalContentMenu(this);
    for(int i=closeTab; i<TabMenuActionCount; i++)
    {
        tabMenuActionItem[i]=new QAction(this);
        tabMenuActionItem[i]->setText(tabMenuActionCaption[i]);
        tabMenu->addAction(tabMenuActionItem[i]);
    }
    connect(tabMenuActionItem[closeTab], SIGNAL(triggered()),
            this, SLOT(closeCurrentTab()));
    connect(tabMenuActionItem[closeOtherTab], SIGNAL(triggered()),
            this, SLOT(closeAllOtherTab()));
    connect(tabMenuActionItem[browseFile], SIGNAL(triggered()),
            this, SLOT(browseCurrentFile()));
}
