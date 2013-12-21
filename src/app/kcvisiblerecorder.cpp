#include "kcvisiblerecorder.h"

KCVisibleRecorder *KCVisibleRecorder::instance=nullptr;

KCVisibleRecorder *KCVisibleRecorder::getInstance()
{
    return instance==nullptr?instance=new KCVisibleRecorder:instance;
}

KCVisibleRecorder::KCVisibleRecorder()
{
    clearList();
}

void KCVisibleRecorder::clearList()
{
    recorderList.clear();
}

int KCVisibleRecorder::addWidget(QWidget *widget)
{
    visibleRecordItem widgetRecord;
    widgetRecord.widget=widget;
    widgetRecord.recordVisible=widget->isVisible();
    recorderList.append(widgetRecord);
    return recorderList.count()-1;
}

bool KCVisibleRecorder::getWidgetVisible(int widgetIndex)
{
    return recorderList.at(widgetIndex).recordVisible;
}

void KCVisibleRecorder::backupWidgetVisible()
{
    for(int i=0;i<recorderList.count();i++)
    {
        visibleRecordItem widgetRecord=recorderList.at(i);
        widgetRecord.recordVisible=recorderList.at(i).widget->isVisible();
        recorderList.removeAt(i);
        recorderList.insert(i, widgetRecord);
    }
}

void KCVisibleRecorder::restoreWidgetVisible()
{
    for(int i=0;i<recorderList.count();i++)
    {
        recorderList.at(i).widget->setVisible(recorderList.at(i).recordVisible);
    }
}

void KCVisibleRecorder::hideAll()
{
    for(int i=0;i<recorderList.count();i++)
    {
        recorderList.at(i).widget->setVisible(false);
    }
}
