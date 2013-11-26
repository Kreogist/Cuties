#ifndef KCDEBUGWATCH_H
#define KCDEBUGWATCH_H

#include <QSplitter>
#include <QTreeView>
#include <QToolBar>
#include <QToolButton>
#include <QLabel>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

class KCDebugWatch : public QDockWidget
{
    Q_OBJECT
public:
    explicit KCDebugWatch(QWidget *parent = 0);
    ~KCDebugWatch();

signals:

public slots:
    void retranslate();
    void retranslateAndSet();

private:
    QSplitter *watchDockContainer;
    QTreeView *localWatch;
    QTreeView *customWatch;
    QLabel *localWatchCaption, *customWatchCaption;
    QToolBar *customWatchControl;

    enum CustomWatchCommand
    {
        customWatchAdd,
        customWatchEdit,
        customWatchRemove,
        CustomWatchCommandCount
    };
    QToolButton *customWatchCommands[CustomWatchCommandCount];
    QString customWatchCommandTitle[CustomWatchCommandCount];

    QHBoxLayout *customWatchControlLayout;

    QString windowTitleString,
            localWatchTitle,
            customWatchTitle;
};

#endif // KCDEBUGWATCH_H
