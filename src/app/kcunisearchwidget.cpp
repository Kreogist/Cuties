
#include <QBoxLayout>
#include <QEvent>
#include <QToolButton>
#include <QKeyEvent>
#include <QUrl>
#include <QTextCodec>
#include <QNetworkReply>
#include <QHeaderView>
#include <QKeyEvent>
#include <QRegularExpressionMatch>
#include <QLineEdit>
#include <QTreeWidgetItem>
#include <QDesktopServices>
#include <QTimeLine>

#include "kcgeneralconfigure.h"
#include "kccolorconfigure.h"

#include "kcunisearchwidget.h"

KCSearchSuggestionWidget::KCSearchSuggestionWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    ;
}

void KCSearchSuggestionWidget::emulatePressedEvent(QEvent *keyPressEvent)
{
    event(keyPressEvent);
}

KCSearchSuggestionProcessor::KCSearchSuggestionProcessor(QObject *parent) :
    QObject(parent)
{
    instance=KCGeneralConfigure::getInstance();
    m_suggestionURL="http://bj1.api.bing.com/qsonhs.aspx?FORM=ASAPIH&mkt=zh-CN&type=cb&cb=sa_inst.apiCB&cp=12&q=%1&o=ds+ds+h+p";
    gbkcodec=QTextCodec::codecForName("GBK");
    connect(&m_networkManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleNetworkData(QNetworkReply*)));
}

void KCSearchSuggestionProcessor::handleNetworkData(QNetworkReply *networkReply)
{
    QStringList suggestion;
    if(!networkReply->error())
    {
        QByteArray response(networkReply->readAll());
        QString resultSuggestion(response);
        QString elements;
        QRegularExpression regexp, regexp2;
        QRegularExpressionMatchIterator matchIterator, elementIterator;
        QRegularExpressionMatch match, match2;
        switch(m_engineIndex)
        {
        case 1:
            //Yahoo
            regexp.setPattern("\\[\"[\\s\\S]+?\",\\d\\]");
            regexp2.setPattern("\"[\\s\\S]+?\"");
            matchIterator=regexp.globalMatch(resultSuggestion);
            if(matchIterator.hasNext())
            {
                match=matchIterator.next(); //Ignore a bug like string: ["k","m"].
            }
            else
            {
                break;
            }
            while(matchIterator.hasNext())
            {
                match=matchIterator.next();
                elements=resultSuggestion.mid(match.capturedStart()+1,
                                              match.capturedLength()-2);
                elementIterator=regexp2.globalMatch(elements);
                match2=elementIterator.next();
                elements=elements.mid(match2.capturedStart()+1,
                                      match2.capturedLength()-2);
                elements.replace(QRegularExpression("<[\\s\\S]+?>"), QString(""));
                suggestion<<elements;
            }
            break;
        case 2:
            //Bing
            regexp.setPattern("\\{\"Txt\":\"[\\s\\S]+?\",\"Type\":\"AS\",\"Sk\":\"[\\s\\S]+?\",\"HCS\":[\\s\\S]+?\\}");
            regexp2.setPattern("\"[\\s\\S]+?\"");
            matchIterator=regexp.globalMatch(resultSuggestion);
            while(matchIterator.hasNext())
            {
                match=matchIterator.next();
                elements=resultSuggestion.mid(match.capturedStart()+1,
                                              match.capturedLength()-2);
                elementIterator=regexp2.globalMatch(elements);
                match2=elementIterator.next();//Ignore the Txt string.
                match2=elementIterator.next();
                elements=elements.mid(match2.capturedStart()+1,
                                      match2.capturedLength()-2);
                elements.replace(QRegularExpression("<[\\s\\S]+?>"), QString(""));
                suggestion<<elements;
            }
            break;
        case 3:
            //Baidu
            resultSuggestion=gbkcodec->toUnicode(response);
            regexp.setPattern("\"[\\s\\S]+?\"");
            matchIterator=regexp.globalMatch(resultSuggestion);
            while(matchIterator.hasNext())
            {
                match=matchIterator.next();
                elements=resultSuggestion.mid(match.capturedStart()+1,
                                              match.capturedLength()-2);
                suggestion<<elements;
            }
            break;
        default:
            break;
        }
        if(!suggestion.isEmpty())
        {
            emit requireUpdateList(suggestion);
        }
    }
}

void KCSearchSuggestionProcessor::searchKeyWord(const QString &keyword)
{
    m_keyword=keyword;
    m_engineIndex=instance->getValue("SearchEngineIndex").toInt();
    QString originalURL=
            instance->getSearchEngineList().at(m_engineIndex).suggestionURL;
    if(originalURL.isEmpty())
    {
        return;
    }
    suggestionRequest.setUrl(QString(originalURL).arg(keyword));
    suggestionConfig.setProtocol(QSsl::AnyProtocol);
    suggestionRequest.setSslConfiguration(suggestionConfig);
    m_networkManager.get(suggestionRequest);
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
    setContentsMargins(7,7,7,7);
    setAutoFillBackground(true);
    setFixedSize(216, fixedHeight);

    instance=KCGeneralConfigure::getInstance();

    QBoxLayout *layout=new QBoxLayout(QBoxLayout::LeftToRight ,this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    setLayout(layout);

    editor=new QLineEdit(this);
    //editor->setFixedWidth(200);
    editor->installEventFilter(this);
    layout->addWidget(editor);

    searchSuggestion=new KCSearchSuggestionWidget;
    searchSuggestion->setWindowFlags(Qt::ToolTip);
    searchSuggestion->setFocusPolicy(Qt::NoFocus);
    searchSuggestion->setMouseTracking(true);
    searchSuggestion->setFocusProxy(editor);
    searchSuggestion->setColumnCount(1);
    searchSuggestion->setUniformRowHeights(true);
    searchSuggestion->setRootIsDecorated(false);
    searchSuggestion->setEditTriggers(QTreeWidget::NoEditTriggers);
    searchSuggestion->setSelectionBehavior(QTreeWidget::SelectRows);
    searchSuggestion->setFrameStyle(QFrame::Box | QFrame::Plain);
    searchSuggestion->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    searchSuggestion->header()->hide();
    searchSuggestion->installEventFilter(this);

    suggestionCatcher=new KCSearchSuggestion(searchSuggestion);

    /*connect(searchSuggestion, SIGNAL(highlighted(QString)),
            this, SLOT(onActionHighlight()));*/
    connect(editor, &QLineEdit::textChanged,
            this, &KCUniSearchWidget::onActionTextChanged);
    connect(suggestionCatcher, &KCSearchSuggestion::requireUpdateList,
            this, &KCUniSearchWidget::onActionNewList);

    QToolButton *closeButton=new QToolButton(this);
    closeButton->setObjectName("KCSearchWindowCloseButton");
    closeButton->setIcon(QIcon(":/toolbutton/image/TabCloseNormal.png"));
    closeButton->setAutoRaise(true);
    closeButton->setFixedWidth(16);
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

KCUniSearchWidget::~KCUniSearchWidget()
{
    searchSuggestion->deleteLater();
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
        switch(keyPress->key())
        {
        case Qt::Key_Enter:
        case Qt::Key_Return:
            if(searchSuggestion->isVisible())
            {
                if(searchSuggestion->model()->rowCount()>0)
                {
                    highlightTest=true; //Just fake to ignore get suggestion.
                    editor->setText(searchSuggestion->currentItem()->text(0));
                }
                searchSuggestion->hide();
                editor->setFocus();
            }
            else
            {
                onActionFinishedEdit();
            }
            return true;

        case Qt::Key_Escape:
            onActionClose();
        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_Home:
        case Qt::Key_End:
        case Qt::Key_PageUp:
        case Qt::Key_PageDown:
            searchSuggestion->emulatePressedEvent(keyPress);
            return true;
        default:
            editor->event(event);
            if(editor->text().isEmpty())
            {
                editor->clear();
                highlightTest=true; //Just fake to ignore get suggestion.
                searchSuggestion->hide();
            }
            editor->setFocus();
            return true;
        }
    }
    return QWidget::eventFilter(object, event);
}

void KCUniSearchWidget::animateShow()
{
    if(showMark)
    {
        return;
    }
    animation->stop();
    move(0, -fixedHeight);
    animation->setFrameRange(geometry().top(), 0);
    show();
    animation->start();
    showMark=true;
}

void KCUniSearchWidget::animateHide()
{
    if(!showMark)
    {
        return;
    }
    animation->stop();
    searchSuggestion->hide();
    animation->setFrameRange(geometry().top(), -fixedHeight);
    animation->start();
    showMark=false;
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
    searchSuggestion->setUpdatesEnabled(false);
    searchSuggestion->clear();
    for (int i=0; i<list.count(); ++i)
    {
        QTreeWidgetItem *item=new QTreeWidgetItem(searchSuggestion);
        item->setText(0, list[i]);
        item->setTextAlignment(1, Qt::AlignRight);
        //item->setTextColor(1, color);
    }
    searchSuggestion->setCurrentItem(searchSuggestion->topLevelItem(0));
    searchSuggestion->resizeColumnToContents(0);
    searchSuggestion->resizeColumnToContents(1);
    searchSuggestion->adjustSize();
    searchSuggestion->setUpdatesEnabled(true);

    int h = searchSuggestion->sizeHintForRow(0) * qMin(7, list.count()) + 3;
    searchSuggestion->resize(searchSuggestion->width(), h);

    searchSuggestion->move(editor->mapToGlobal(QPoint(0, editor->height())));
    searchSuggestion->setFocus();
    searchSuggestion->show();
}

void KCUniSearchWidget::onActionHighlight()
{
    highlightTest=true;
}

void KCUniSearchWidget::onActionFinishedEdit()
{
    searchSuggestion->hide();
    if(!editor->text().isEmpty())
    {
        doWebSearch(editor->text());
    }
    animateHide();
}

void KCUniSearchWidget::onActionTextChanged(const QString &text)
{
    if(highlightTest)
    {
        highlightTest=false;
        return;
    }
    suggestionCatcher->searchKeyWord(text);
}

void KCUniSearchWidget::doWebSearch(const QString &text)
{
    QDesktopServices::openUrl(QUrl(instance->getSearchEngineList().at(instance->getValue("SearchEngineIndex").toInt()).engineURL.arg(text)));
}
