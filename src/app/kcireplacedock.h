#ifndef KCIREPLACEDOCK_H
#define KCIREPLACEDOCK_H

#include <QWidget>
#include <QLabel>
#include <QMenu>
#include <QIcon>
#include <QLineEdit>
#include <QPushButton>
#include <QToolButton>
#include <QResizeEvent>
#include <QTimeLine>
#include <QKeyEvent>
#include <QSignalMapper>
#include <QDebug>

#include "kcisearchwidget.h"

class kciReplaceDock : public kciSearchWidget
{
    Q_OBJECT
public:
    explicit kciReplaceDock(QWidget *parent = 0);

signals:
    void requireReplace(const QString &oldText,const QString &newText);
    void requireReplaceAndFind(const QString &oldText, const QString &newText);
    void requireReplaceAll(const QString &oldText, const QString &newText);

public slots:
    void showAnime();
    void hideAnime();

private slots:
    void resizeDock(int newHeight);
    void onOneOfReplaceButtonsClicked(int type);

private:
    enum replaceButtonType
    {
        replace,
        findAndReplace,
        replaceAll,
        typeCount
    };

    QGridLayout *mainLayout;
    QLineEdit *replaceText;
    QToolButton *replaceButtons[typeCount];
    QToolButton *closeButton;

    QSignalMapper *mapper;
};

#endif // KCIREPLACEDOCK_H
