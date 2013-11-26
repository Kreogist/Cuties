#ifndef KCDEBUGWATCH_H
#define KCDEBUGWATCH_H

#include <QSplitter>
#include <QTreeView>
#include <QToolBar>
#include <QToolButton>
#include <QLabel>
#include <QDockWidget>

class KCDebugWatch : public QDockWidget
{
    Q_OBJECT
public:
    explicit KCDebugWatch(QWidget *parent = 0);

signals:

public slots:
    void retranslate();
    void retranslateAndSet();

private:
    QSplitter *watchDockContainer;
    QTreeView *localWatch;
    QTreeView *customWatch;
    QLabel *localWatchCaption, *customWatchCaption;

    QString windowTitleString,
            localWatchTitle,
            customWatchTitle;
};

#endif // KCDEBUGWATCH_H
