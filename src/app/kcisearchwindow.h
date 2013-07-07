#ifndef KCISEARCHWINDOW_H
#define KCISEARCHWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QToolButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDebug>
#include <QPalette>
#include <QKeySequence>
#include <QGraphicsDropShadowEffect>
#include <QFrame>
#include <QLabel>
#include <QMenu>
#include <QTextDocument>

#include "kcitexteditor.h"
#include "kcitextsearcher.h"

class kciSearchWindow : public QWidget
{
    Q_OBJECT
public:
    explicit kciSearchWindow(QWidget *parent = 0);
    void setTextFocus();
    void setDocument(QTextDocument* doc);

public slots:
    void onTextChanged(const QString &text);
    void onSearcherFinished();
    void moveToPrevResult();
    void moveToNextResult();
    void onMenuClicked();

protected:
    void hideEvent(QHideEvent *e);

signals:
    void hideButtonPressed();

private:
    enum menuItem
    {
        RegularExpress,
        MatchCase,
        WholeWord,
        menuItemCount
    };

    int currResultNum;

    QHBoxLayout *searchLayout;
    QToolButton *closeButton, *upButton, *downButton;
    QLabel *lblSearchInfo;

    //TextBox
    QWidget *searchText;
    QLineEdit *SearchTexts;
    QHBoxLayout *Layout;
    QPushButton *SearchIcon;
    kciTextSearcher *searcher;
    QTextDocument *document;
    QList<searchResult> result;

    QTextCharFormat selectedCharFormat;
    QTextCharFormat normalCharFormat;

    QMenu *menu;
    QAction *menuAction[menuItemCount];

    void showCurrResult();
    void setSelectedCharFormat(const QTextCharFormat& format);
};

#endif // KCISEARCHWINDOW_H
