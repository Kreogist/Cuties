#ifndef KCPREFERENCESUPERLIST_H
#define KCPREFERENCESUPERLIST_H

#include <QFont>
#include <QScrollArea>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QList>
#include <QResizeEvent>

class KCPreferenceSuperListContent : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferenceSuperListContent(QWidget *parent = 0);
    void appendTitle(QLabel *newTitleWidget);

private:
    QVBoxLayout *superListLayout;
    QList<QLabel *> superListTitles;
};

class KCPreferenceSuperList : public QScrollArea
{
    Q_OBJECT
public:
    explicit KCPreferenceSuperList(QWidget *parent = 0);
    void addTitle(const QString &titleText);

signals:

public slots:

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QFont titleFont;
    KCPreferenceSuperListContent *contents;
};

#endif // KCPREFERENCESUPERLIST_H
