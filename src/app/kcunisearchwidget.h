#ifndef KCUNISEARCHWIDGET_H
#define KCUNISEARCHWIDGET_H

#include <QWidget>
#include <QThread>
#include <QLineEdit>
#include <QNetworkAccessManager>

class QTimeLine;
class QNetworkReply;
class QEvent;
class QKeyEvent;
class QTreeWidget;
class QStringListModel;

class KCGeneralConfigure;

class KCUniSearchLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit KCUniSearchLineEdit(QWidget *parent = 0);

signals:
    void requireDoSearch();

protected:
    void keyPressEvent(QKeyEvent *event);

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

private slots:
    void animateShow();
    void animateHide();
    void setWidgetTop(int widgetTop);
    void onActionClose();
    void onActionNewList(QStringList list);
    void onActionHighlight();
    void onActionFinishedEdit();
    void onActionTextChanged(const QString &text);

private:
    void doWebSearch(const QString &text);
    KCGeneralConfigure *instance;
    KCUniSearchLineEdit *editor;

    QTimeLine *animation;
    QTreeWidget *searchSuggestion;

    KCSearchSuggestion *suggestionCatcher;

    int fixedHeight=26;
    bool highlightTest=false;
};

#endif // KCUNISEARCHWIDGET_H
