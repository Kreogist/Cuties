#ifndef KCISEARCHTEXTBOX_H
#define KCISEARCHTEXTBOX_H

#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPalette>
#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QTextDocument>
#include <QTextCursor>

#include "kcitextsearcher.h"

class kciSearchTextBox : public QWidget
{
    Q_OBJECT
public:
    explicit kciSearchTextBox(QWidget *parent = 0);
    void setTheFocus();
    void setDocument(QTextDocument* doc);

signals:
    void textChanged(const QString& text);

public slots:
    void onTextChanged(const QString& text);
    void onSearcherFinished();

private:
    enum menuItem
    {
        RegularExpress,
        MatchCase,
        WholeWord,
        menuItemCount
    };

    QLineEdit *SearchTexts;
    QHBoxLayout *Layout;
    QPushButton *SearchIcon;
    kciTextSearcher *searcher;
    QList<searchResult> result;

    QTextDocument *document;
    QTextCharFormat selectedCharFormat;
    QTextCharFormat normalCharFormat;

    QMenu *menu;
    QAction *menuAction[menuItemCount];
};

#endif // KCISEARCHTEXTBOX_H
