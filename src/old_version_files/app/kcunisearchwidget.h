#ifndef KCUNISEARCHWIDGET_H
#define KCUNISEARCHWIDGET_H

#include <QWidget>
#include <QThread>
#include <QTreeWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QSslConfiguration>

class QTimeLine;
class QNetworkReply;
class QEvent;
class QKeyEvent;
class QFocusEvent;
class QLineEdit;
class QStringListModel;

class KCGeneralConfigure;

class KCSearchSuggestionWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit KCSearchSuggestionWidget(QWidget *parent = 0);
    void emulatePressedEvent(QEvent *keyPressEvent);

private:
};

class KCSearchSuggestionProcessor : public QObject
{
    Q_OBJECT
public:
    explicit KCSearchSuggestionProcessor(QObject *parent = 0);
    void searchKeyWord(const QString &keyword);

signals:
    void requireUpdateList(QStringList suggestionList);

private slots:
    void handleNetworkData(QNetworkReply *networkReply);

private:
    QNetworkAccessManager m_networkManager;
    QString m_keyword;
    QString m_suggestionURL;
    QTextCodec *gbkcodec;
    KCGeneralConfigure *instance;
    QNetworkRequest suggestionRequest;
    QSslConfiguration suggestionConfig;
    int m_engineIndex;
};

class KCSearchSuggestion : public QObject
{
    Q_OBJECT
public:
    explicit KCSearchSuggestion(QObject *parent = 0);
    ~KCSearchSuggestion();

signals:
    void requireUpdateList(QStringList suggestionList);

public slots:
    void searchKeyWord(const QString &keyword);

private slots:

private:
    KCSearchSuggestionProcessor *processor;
    QThread suggestionThread;
};

class KCUniSearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KCUniSearchWidget(QWidget *parent = 0);
    ~KCUniSearchWidget();

signals:
    void requireLostFocus();

public slots:
    void searchOnline(const QString &text);
    void setFocus();

protected:
    bool eventFilter(QObject *object, QEvent *event);
    void focusOutEvent(QFocusEvent *event);

private slots:
    void animateShow();
    void animateHide();
    void setWidgetTop(int widgetTop);
    void onActionNewList(QStringList list);
    void onActionHighlight();
    void onActionFinishedEdit();
    void onActionTextChanged(const QString &text);

private:
    void doWebSearch(const QString &text);
    KCGeneralConfigure *instance;
    QLineEdit *editor;

    QTimeLine *animation;
    KCSearchSuggestionWidget *searchSuggestion;

    KCSearchSuggestion *suggestionCatcher;

    int fixedHeight=38;
    bool highlightTest=false, showMark=false;
};

#endif // KCUNISEARCHWIDGET_H
