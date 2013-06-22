#include "kcitabmanager.h"

kciTabManager::kciTabManager(QWidget *parent) :
    QTabWidget(parent)
{
    clear();

    connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(on_tab_close_requested(int)));
    connect(this,SIGNAL(currentChanged(int)),this,SLOT(on_current_tab_change(int)));

/*    QPalette tabpal=this->palette();
    tabpal.setColor(QPalette::Background, QColor(83,83,83));
    tabpal.setColor(QPalette::Foreground, QColor(56,56,56));
    this->setPalette(tabpal);*/

    setDocumentMode(true);
    setMovable(true);
    setTabsClosable(true);
    setElideMode(Qt::ElideRight);
    setTabPosition(QTabWidget::South);
    tab_count=1;
    new_file_count=1;
    isEditor=false;
}

void kciTabManager::open()
{
    QSettings settings(kciGlobal::settingsFileName,QSettings::IniFormat);
    QStringList file_name_list=QFileDialog::getOpenFileNames(this,tr("Open File"),settings.value("files/historyDir").toString());
    kciTextEditor *tmp;
    QString name;

    int i;

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

        tmp=new kciTextEditor(this);
        tmp->open(name);

        name=QFileInfo(name).fileName();
        tmp->setDocumentTitle(name);

        _last_tab_index=addTab(tmp,name);

        file_name_list.pop_front();
    }

    setCurrentIndex(_last_tab_index);
}

void kciTabManager::new_file()
{
    kciTextEditor *tmp=new kciTextEditor(this);
    if(tmp!=NULL)
    {
        QString _new_file_title=
                tr("Untitled")+QString::number(new_file_count++);
        tmp->setDocumentTitle(_new_file_title);
        setCurrentIndex(addTab(tmp,_new_file_title));
    }
    else
    {
        QErrorMessage error(this);
        error.showMessage(tr("out of memmory!"));
        error.exec();
    }
}

void kciTabManager::save()
{
    if(Q_LIKELY(this->isEditor))
    {
        kciTextEditor *currentEditor=qobject_cast<kciTextEditor *>(this->currentWidget());

        Q_ASSERT(currentEditor!=NULL);

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
    if(Q_LIKELY(this->isEditor))
    {
        kciTextEditor *currentEditor=qobject_cast<kciTextEditor *>(currentWidget());

        Q_ASSERT(currentEditor!=NULL);

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

void kciTabManager::undo()
{
    if(Q_LIKELY(this->isEditor))
    {
        kciTextEditor *currentEditor=qobject_cast<kciTextEditor *>(currentWidget());

        Q_ASSERT(currentEditor!=NULL);
        currentEditor->undo();
    }
}

void kciTabManager::redo()
{
    if(Q_LIKELY(this->isEditor))
    {
        kciTextEditor *currentEditor=qobject_cast<kciTextEditor *>(this->currentWidget());

        Q_ASSERT(currentEditor!=NULL);
        currentEditor->redo();
    }
}

void kciTabManager::copy()
{
    if(Q_LIKELY(this->isEditor))
    {
        kciTextEditor *currentEditor=qobject_cast<kciTextEditor *>(this->currentWidget());

        Q_ASSERT(currentEditor!=NULL);
        currentEditor->copy();
    }
}

void kciTabManager::cut()
{
    if(Q_LIKELY(this->isEditor))
    {
        kciTextEditor *currentEditor=qobject_cast<kciTextEditor *>(this->currentWidget());

        Q_ASSERT(currentEditor!=NULL);
        currentEditor->cut();
    }
}

void kciTabManager::paste()
{
    if(Q_LIKELY(this->isEditor))
    {
        kciTextEditor *currentEditor=qobject_cast<kciTextEditor *>(this->currentWidget());

        Q_ASSERT(currentEditor!=NULL);
        currentEditor->paste();
    }
}

void kciTabManager::select_all()
{
    if(Q_LIKELY(this->isEditor))
    {
        kciTextEditor *currentEditor=qobject_cast<kciTextEditor *>(this->currentWidget());

        Q_ASSERT(currentEditor!=NULL);
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
            removeTab(index);
    }

}

void kciTabManager::on_current_tab_change(int index)
{
    kciTextEditor* editor=qobject_cast<kciTextEditor *>(widget(index));
    if(editor!=NULL)
        isEditor=true;
    else
        isEditor=false;
}

void kciTabManager::compile_current_file()
{
    if(Q_LIKELY(this->isEditor))
    {
        kciTextEditor *currentEditor=qobject_cast<kciTextEditor *>(this->currentWidget());

        Q_ASSERT(currentEditor!=NULL);
        //currentEditor->compile();
    }
}

void kciTabManager::closeEvent(QCloseEvent *e)
{
    e->accept();//set the accept flag
    int i=count();
    while(i--)
    {
        QWidget *page=widget(i);

        if(!page->close())
            e->ignore();//clean the accept flag
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

void kciTabManager::tabRemoved(int index)
{

}

void kciTabManager::tabInserted(int index)
{
    kciTextEditor* editor=qobject_cast<kciTextEditor *>(widget(index));
    if(editor!=NULL)
    {
        connect(editor,SIGNAL(filenameChanged(QString)),this,SLOT(renameTabTitle(QString)));
    }
}
