
#include <QBoxLayout>
#include <QEvent>
#include <QToolButton>
#include <QKeyEvent>
#include <QUrl>
#include <QCompleter>
#include <QTextCodec>
#include <QNetworkReply>
#include <QKeyEvent>
#include <QRegularExpressionMatch>
#include <QStringListModel>
#include <QDesktopServices>
#include <QTimeLine>

#include "kcgeneralconfigure.h"
#include "kccolorconfigure.h"

#include "kcunisearchwidget.h"

KCUniSearchLineEdit::KCUniSearchLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    ;
}

void KCUniSearchLineEdit::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        emit requireDoSearch();
        return;
    }

    QLineEdit::keyPressEvent(event);
}

KCSearchSuggestionProcessor::KCSearchSuggestionProcessor(QObject *parent) :
    QObject(parent)
{
    m_suggestionURL="http://suggestion.baidu.com/su?wd=%1&p=3&cb=window.bdsug.sug&t=1326789467239";
    connect(&m_networkManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleNetworkData(QNetworkReply*)));
}

void KCSearchSuggestionProcessor::handleNetworkData(QNetworkReply *networkReply)
{
    QStringList suggestion;
    if(!networkReply->error())
    {
        QByteArray response(networkReply->readAll());
        QTextCodec *gbkcodec=QTextCodec::codecForName("GBK");
        QString resultSuggestion=gbkcodec->toUnicode(response);
        QString elements;
        QRegularExpression regexp("\"[\\s\\S]+?\"");
        QRegularExpressionMatchIterator matchIterator=regexp.globalMatch(resultSuggestion);
        while(matchIterator.hasNext())
        {
            QRegularExpressionMatch match=matchIterator.next();
            elements=resultSuggestion.mid(match.capturedStart()+1,
                                          match.capturedLength()-2);
            suggestion<<elements;
        }
        emit requireUpdateList(suggestion);
    }
}

void KCSearchSuggestionProcessor::searchKeyWord(const QString &keyword)
{
    m_keyword=keyword;
    QString generateURL=QString(m_suggestionURL).arg(keyword);
    m_networkManager.get(QNetworkRequest(generateURL));
}

KCSearchSuggestion::KCSearchSuggestion(QObject *parent) :
    QObject(parent)
{
    processor=new KCSearchSuggestionProcessor;
    processor->moveToThread(&suggestionThread);
    connect(processor, SIGNAL(requireUpdateList(QStringList)),
            this, SIGNAL(requireUpdateList(QStringList)));
    suggestionThread.start();
}

KCSearchSuggestion::~KCSearchSuggestion()
{
    suggestionThread.quit();
    suggestionThread.wait();
    processor->deleteLater();
}

void KCSearchSuggestion::searchKeyWord(const QString &keyword)
{
    processor->searchKeyWord(keyword);
}

KCUniSearchWidget::KCUniSearchWidget(QWidget *parent) :
    QWidget(parent)
{
    setContentsMargins(0,0,0,0);
    setAutoFillBackground(true);
    setFixedSize(216, fixedHeight);

    instance=KCGeneralConfigure::getInstance();

    QBoxLayout *layout=new QBoxLayout(QBoxLayout::LeftToRight ,this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    setLayout(layout);

    editor=new KCUniSearchLineEdit(this);
    editor->setFixedWidth(200);
    editor->installEventFilter(this);
    layout->addWidget(editor);

    searchSuggestion=new QCompleter(editor);
    searchSuggestion->setCaseSensitivity(Qt::CaseInsensitive);
    searchSuggestion->setMaxVisibleItems(8);
    searchSuggestion->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    editor->setCompleter(searchSuggestion);

    suggestionCatcher=new KCSearchSuggestion(searchSuggestion);
    suggestionList=new QStringListModel(searchSuggestion);
    searchSuggestion->setModel(suggestionList);

    connect(searchSuggestion, SIGNAL(highlighted(QString)),
            this, SLOT(onActionHighlight()));
    connect(editor, &KCUniSearchLineEdit::textChanged,
            this, &KCUniSearchWidget::onActionTextChanged);
    connect(editor, &KCUniSearchLineEdit::requireDoSearch,
            this, &KCUniSearchWidget::onActionFinishedEdit);
    connect(suggestionCatcher, &KCSearchSuggestion::requireUpdateList,
            this, &KCUniSearchWidget::onActionNewList);

    QToolButton *closeButton=new QToolButton(this);
    closeButton->setObjectName("KCSearchWindowCloseButton");
    closeButton->setIcon(QIcon(":/toolbutton/image/TabCloseNormal.png"));
    closeButton->setAutoRaise(true);
    closeButton->setFixedSize(16,fixedHeight);
    QPalette pal=closeButton->palette();
    KCColorConfigure::getInstance()->getPalette(pal,closeButton->objectName());
    closeButton->setPalette(pal);
    layout->addWidget(closeButton);
    connect(closeButton, SIGNAL(clicked()),
            this, SLOT(onActionClose()));

    animation=new QTimeLine(100, this);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->setUpdateInterval(5);
    connect(animation, SIGNAL(frameChanged(int)),
            this, SLOT(setWidgetTop(int)));
    hide();
}

void KCUniSearchWidget::searchOnline(const QString &text)
{
    if(text.isEmpty())
    {
        animateShow();
        return;
    }
    highlightTest=true; //Just fake to ignore get suggestion.
    editor->setText(text);
    doWebSearch(text);
}

void KCUniSearchWidget::setFocus()
{
    editor->setFocus();
}

bool KCUniSearchWidget::eventFilter(QObject *object, QEvent *event)
{
    if(event->type()==QEvent::KeyPress)
    {
        QKeyEvent *keyPress=static_cast<QKeyEvent *>(event);
        if(keyPress->key()==Qt::Key_Escape)
        {
            onActionClose();
            return true;
        }
    }
    return QWidget::eventFilter(object, event);
}

void KCUniSearchWidget::animateShow()
{
    editor->setEnabled(true);
    animation->stop();
    move(0, -fixedHeight);
    animation->setFrameRange(geometry().top(), 0);
    show();
    animation->start();
}

void KCUniSearchWidget::animateHide()
{
    editor->setEnabled(false);
    animation->stop();
    animation->setFrameRange(geometry().top(), -fixedHeight);
    animation->start();
}

void KCUniSearchWidget::setWidgetTop(int widgetTop)
{
    move(0, widgetTop);
}

void KCUniSearchWidget::onActionClose()
{
    emit requireLostFocus();
    animateHide();
}

void KCUniSearchWidget::onActionNewList(QStringList list)
{
    qDebug()<<list;
    suggestionList->setStringList(list);
}

void KCUniSearchWidget::onActionHighlight()
{
    highlightTest=true;
}

void KCUniSearchWidget::onActionFinishedEdit()
{
    doWebSearch(editor->text());
    animateHide();
}

void KCUniSearchWidget::onActionTextChanged(const QString &text)
{
    if(highlightTest)
    {
        highlightTest=false;
        return;
    }
    suggestionList->setStringList(QStringList());
    suggestionCatcher->searchKeyWord(text);
}

void KCUniSearchWidget::doWebSearch(const QString &text)
{
    QDesktopServices::openUrl(QUrl(instance->getSearchEngineList().at(instance->getValue("SearchEngineIndex").toInt()).engineURL +
                                   text));
}
