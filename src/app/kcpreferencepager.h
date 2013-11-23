#ifndef KCPREFERENCEPAGER_H
#define KCPREFERENCEPAGER_H

#include <QList>
#include <QWidget>
#include <QResizeEvent>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

#include "kcpreferencesuperlist.h"

class KCPreferencePager : public QWidget
{
    Q_OBJECT
public:
    explicit KCPreferencePager(QWidget *parent = 0);
    void addSuperList(KCPreferenceSuperList *newSuperList);
    void initPager();
    void setPageVisible(int pageIndex, bool visible);

signals:

public slots:
    void switchToPage(int pageIndex);

private slots:
    void hideBackupPage();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QList<KCPreferenceSuperList *> preferenceSuperLists;
    int currentPageIndex;
    int backupPage;
    QParallelAnimationGroup *moveAnimationGroup;
};

#endif // KCPREFERENCEPAGER_H
