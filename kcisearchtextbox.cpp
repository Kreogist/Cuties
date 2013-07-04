#include "kcisearchtextbox.h"

kciSearchTextBox::kciSearchTextBox(QWidget *parent) :
    QWidget(parent)
{
    //Set Background Fill.
    setAutoFillBackground(true);

    //Palette Set.
    QPalette pal=this->palette();
    pal.setColor(QPalette::Window,QColor(255,255,255));
    pal.setColor(QPalette::Base,QColor(255,255,255));
    pal.setColor(QPalette::Text,QColor(0,0,0));
    pal.setColor(QPalette::WindowText,QColor(50,50,50));
    setPalette(pal);

    //Set New Layout
    Layout=new QHBoxLayout(this);
    Layout->setContentsMargins(0,0,0,0);
    Layout->setSpacing(0);
    setLayout(Layout);

    //Set Icon PushButton
    SearchIcon=new QPushButton(this);
    SearchIcon->setIcon(QIcon(QString(":/img/image/SearchIcon.png")));
    SearchIcon->setFixedSize(24,24);
    SearchIcon->setContentsMargins(0,0,0,0);
    SearchIcon->setFlat(true);
    Layout->addWidget(SearchIcon);

    searcher=new kciTextSearcher(this);

    SearchTexts=new QLineEdit(this);
    SearchTexts->setFrame(false);
    SearchTexts->setPlaceholderText(QString(tr("Search")));
    connect(SearchTexts,SIGNAL(textChanged(QString)),
            this,SLOT(onTextChanged(QString)));
    connect(searcher,SIGNAL(finished()),this,SLOT(onSearcherFinished()));

    //Init menu
    menu=new QMenu(this);
    menuAction[RegularExpress]=menu->addAction(tr("Regular Expression"));
    menuAction[MatchCase]=menu->addAction(tr("Match Case"));
    menuAction[WholeWord]=menu->addAction(tr("Match whole word"));

    for(int i=0;i<menuItemCount;i++)
        menuAction[i]->setCheckable(true);

    SearchIcon->setMenu(menu);

    Layout->addWidget(SearchTexts);

    selectedCharFormat.setBackground(QBrush(QColor(0xf7,0xcf,0x3d)));
}

void kciSearchTextBox::setDocument(QTextDocument *doc)
{
    document=doc;
    searcher->setDocument(doc);
}

void kciSearchTextBox::onTextChanged(const QString &text)
{
    searcher->setSubString(text);

    int flags=0;
    if(menuAction[RegularExpress]->isChecked())
        flags|=kciTextSearcher::RegularExpress;
    if(menuAction[WholeWord]->isChecked())
        flags|=kciTextSearcher::WholeWord;
    if(menuAction[MatchCase]->isChecked())
        flags|=kciTextSearcher::MatchCase;

    searcher->setFlags(flags);
    searcher->setSubString(text);
    searcher->search();
}

void kciSearchTextBox::setTheFocus()
{
    SearchTexts->setFocus();
}

void kciSearchTextBox::onSearcherFinished()
{
    bool docModified=document->isModified();

    QTextCursor _cursor(document);
    int l=result.size();

    for(int i=0;i<l;i++)
    {
        const searchResult r=result.at(i);

        _cursor.movePosition(QTextCursor::Start);
        _cursor.movePosition(QTextCursor::NextBlock,
                             QTextCursor::MoveAnchor,
                             r.lineNum);
        _cursor.movePosition(QTextCursor::NextCharacter,
                             QTextCursor::MoveAnchor,
                             r.startPos);
        _cursor.movePosition(QTextCursor::NextCharacter,
                             QTextCursor::KeepAnchor,
                             r.length);
        _cursor.setCharFormat(normalCharFormat);
    }

    normalCharFormat=document->begin().charFormat();

    result=searcher->resultList;

    l=result.size();

    for(int i=0;i<l;i++)
    {
        const searchResult r=result.at(i);

        _cursor.movePosition(QTextCursor::Start);
        _cursor.movePosition(QTextCursor::NextBlock,
                             QTextCursor::MoveAnchor,
                             r.lineNum);
        _cursor.movePosition(QTextCursor::NextCharacter,
                             QTextCursor::MoveAnchor,
                             r.startPos);
        _cursor.movePosition(QTextCursor::NextCharacter,
                             QTextCursor::KeepAnchor,
                             r.length);
        _cursor.setCharFormat(selectedCharFormat);

    }

    if(l>0)
    {
        const searchResult r=result.at(0);
        QCursor _curr_cursor=;
    }

    document->setModified(docModified);
}
