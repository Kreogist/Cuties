
#include <QVBoxLayout>

#include "kcdebugwatch.h"

KCDebugWatch::KCDebugWatch(QWidget *parent) :
    QDockWidget(parent)
{
    //Set Langauges.
    retranslate();

    //Set properties.
    setAutoFillBackground(true);
    setContentsMargins(0,0,0,0);
    setWindowTitle(windowTitleString);
    setObjectName("DebugWatchPanel");
    setAllowedAreas(Qt::RightDockWidgetArea |
                    Qt::BottomDockWidgetArea);

    //Set compile dock palette
    QPalette pal=palette();
    pal.setColor(QPalette::Base, QColor(0x35, 0x35, 0x35));
    pal.setColor(QPalette::Button, QColor(0x53, 0x53, 0x53));
    pal.setColor(QPalette::ButtonText, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::Text, QColor(0xff, 0xff, 0xff));
    pal.setColor(QPalette::WindowText, QColor(0xff, 0xff, 0xff));
    setPalette(pal);

    //Set central widget
    watchDockContainer=new QSplitter(this);
    watchDockContainer->setOrientation(Qt::Vertical);

    QWidget *localWatchCombine=new QWidget(watchDockContainer);
    localWatchCombine->setContentsMargins(0,0,0,0);
    QVBoxLayout *localWatchCombineLayout=new QVBoxLayout(localWatchCombine);
    localWatchCombineLayout->setContentsMargins(0,0,0,0);
    localWatchCombineLayout->setSpacing(0);
    localWatchCombine->setLayout(localWatchCombineLayout);

    localWatchCaption=new QLabel(localWatchCombine);
    localWatchCaption->setText(localWatchTitle);
    localWatchCombineLayout->addWidget(localWatchCaption);
    localWatch=new QTreeView(watchDockContainer);
    localWatchCombineLayout->addWidget(localWatch);
    watchDockContainer->addWidget(localWatchCombine);

    QWidget *customWatchCombine=new QWidget(watchDockContainer);
    customWatchCombine->setContentsMargins(0,0,0,0);
    QVBoxLayout *customWatchCombineLayout=new QVBoxLayout(customWatchCombine);
    customWatchCombineLayout->setContentsMargins(0,0,0,0);
    customWatchCombineLayout->setSpacing(0);
    customWatchCombine->setLayout(customWatchCombineLayout);

    customWatchCaption=new QLabel(customWatchCombine);
    customWatchCaption->setText(customWatchTitle);
    customWatchCombineLayout->addWidget(customWatchCaption);
    customWatch=new QTreeView(watchDockContainer);
    customWatchCombineLayout->addWidget(customWatch);
    watchDockContainer->addWidget(customWatchCombine);

    setWidget(watchDockContainer);
}

void KCDebugWatch::retranslate()
{
    windowTitleString=tr("Watch");
    localWatchTitle=tr("Local Watch");
    customWatchTitle=tr("Custom Watch");
}

void KCDebugWatch::retranslateAndSet()
{
    retranslate();
}
