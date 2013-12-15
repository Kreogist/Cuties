
#include <QApplication>
#include <QSettings>
#include <QDesktopWidget>

#include <QDebug>

#include "kcstatusrecorder.h"

KCStatusRecorder *KCStatusRecorder::instance=nullptr;
QString KCStatusRecorder::recordFileName;

KCStatusRecorder *KCStatusRecorder::getInstance()
{
    return instance==nullptr?instance=new KCStatusRecorder:instance;
}

KCStatusRecorder::KCStatusRecorder()
{
    setRecordFileName("Settings/Record.db");

    //Clear record widgets list
    clearRecordWidgets();
    startStatus=getCurrentStatus();

    //Set default value
    defaultX=0.1;
    defaultY=0.1;
    defaultW=0.8;
    defaultH=0.8;

    defaultLeft=startStatus.desktopWidth*defaultX;
    defaultTop=startStatus.desktopHeight*defaultY;
    defaultWidth=startStatus.desktopWidth*defaultW;
    defaultHeight=startStatus.desktopHeight*defaultH;

    defaultGeometry=QRect(defaultLeft,
                          defaultTop,
                          defaultWidth,
                          defaultHeight);
}

void KCStatusRecorder::clearRecordWidgets()
{
    widgetGeometries.clear();
    widgetNames.clear();
}

int KCStatusRecorder::getWidgetIndex(const QString &currentWidgetName)
{
    int widgetIndex=widgetNames.indexOf(currentWidgetName);
    if(widgetIndex==-1)
    {
        //There's no widget name in the name list, append list.
        return appendList(currentWidgetName);
    }
    return widgetIndex;
}

QRect KCStatusRecorder::getWidgetRect(const QString &currentWidgetName)
{
    return getGeometry(getWidgetIndex(currentWidgetName));
}

void KCStatusRecorder::setWidgetGeometry(const QString &widgetName,
                                         const QRect &widgetGeometry,
                                         Qt::WindowStates windowState)
{
    int widgetIndex=widgetNames.indexOf(widgetName);
    setWidgetGeometry(widgetIndex, widgetGeometry, windowState);
}

void KCStatusRecorder::setWidgetGeometry(const int &widgetIndex,
                                         const QRect &widgetGeometry,
                                         Qt::WindowStates windowState)
{
    KCGeometry currentWidgetGeometry=widgetGeometries.at(widgetIndex);
    currentWidgetGeometry.WindowState=windowStateToInt(windowState);
    if(currentWidgetGeometry.WindowState==2)
    {
        //Means previous is maximum
        currentWidgetGeometry.currentGeometry=currentWidgetGeometry.previousGeometry;
    }
    else if(currentWidgetGeometry.WindowState==3)
    {
        //Means current is fullscreen state, I don't know why.
        currentWidgetGeometry.currentGeometry=currentWidgetGeometry.previousGeometry;
    }
    else
    {
        currentWidgetGeometry.previousGeometry=currentWidgetGeometry.currentGeometry;
        currentWidgetGeometry.currentGeometry=widgetGeometry;
    }
    widgetGeometries.removeAt(widgetIndex);
    widgetGeometries.insert(widgetIndex, currentWidgetGeometry);
}

Qt::WindowStates KCStatusRecorder::getWidgetState(const QString &currentWidgetName)
{
    int widgetIndex=widgetNames.indexOf(currentWidgetName);
    switch(widgetGeometries.at(widgetIndex).WindowState)
    {
    case 1:
        return Qt::WindowMinimized;
    case 2:
        return Qt::WindowMaximized;
    case 3:
#ifdef Q_OS_WIN32
        return Qt::WindowMaximized;
#else
        return Qt::WindowFullScreen;
#endif
    }
    return Qt::WindowNoState;
}

int KCStatusRecorder::windowStateToInt(Qt::WindowStates windowState)
{
    if(windowState==Qt::WindowMinimized)
    {
        return 1;
    }
    if(windowState==Qt::WindowMaximized)
    {
        return 2;
    }
    if(windowState==Qt::WindowFullScreen)
    {
        return 3;
    }
    return 0;
}

QRect KCStatusRecorder::getGeometry(const int &widgetIndex)
{
    return widgetGeometries.at(widgetIndex).currentGeometry;
}

int KCStatusRecorder::appendList(const QString &newWidgetName)
{
    //Name list append
    int widgetIndex=widgetNames.count();
    widgetNames.append(newWidgetName);
    //Geometry list append
    KCGeometry newWidgetGeometry;
    QRect newGeometry=defaultGeometry;
    newWidgetGeometry.currentGeometry=newGeometry;
    newWidgetGeometry.previousGeometry=newGeometry;
    newWidgetGeometry.WindowState=0;
    widgetGeometries.append(newWidgetGeometry);
    return widgetIndex;
}

KCEnvironmentVariables KCStatusRecorder::getCurrentStatus()
{
    KCEnvironmentVariables currentStatus;
    QDesktopWidget *currentDesktop=QApplication::desktop();
    currentStatus.available=true;
    currentStatus.desktopHeight=currentDesktop->height();
    currentStatus.desktopWidth=currentDesktop->width();
    return currentStatus;
}

QString KCStatusRecorder::getRecordFileName()
{
    return recordFileName;
}

void KCStatusRecorder::setRecordFileName(const QString &value)
{
    recordFileName = value;
}

void KCStatusRecorder::readRecord()
{
    QSettings settings(getRecordFileName(),
                       QSettings::IniFormat);

    //Read desktop status
    settings.beginGroup("DesktopStatus");
    recordStatus.desktopHeight=settings.value("Height", startStatus.desktopHeight).toInt();
    recordStatus.desktopWidth=settings.value("Width", startStatus.desktopWidth).toInt();
    settings.endGroup();

    //Check if the status is the same as current
    useRelative=(recordStatus.desktopHeight==startStatus.desktopHeight &&
                 recordStatus.desktopHeight==startStatus.desktopHeight);

    //Read widget status
    settings.beginGroup("WidgetStatus");
    int widgetNum=settings.beginReadArray("Widgets");
    QRect itemGeometry;
    for(int i=0;i<widgetNum;i++)
    {
        settings.setArrayIndex(i);
        widgetNames.append(settings.value("ObjectName", "NoName" + QString::number(i)).toString());
        KCGeometry recordGeometry;
        if(useRelative)
        {
            itemGeometry=QRect(settings.value("x", 0.1).toFloat() * startStatus.desktopWidth,
                               settings.value("y", 0.1).toFloat() * startStatus.desktopHeight,
                               settings.value("w", 0.8).toFloat() * startStatus.desktopWidth,
                               settings.value("h", 0.8).toFloat() * startStatus.desktopHeight);
        }
        else
        {
            itemGeometry=QRect(settings.value("Left", defaultLeft).toInt(),
                               settings.value("Top", defaultTop).toInt(),
                               settings.value("Width", defaultWidth).toInt(),
                               settings.value("Height", defaultHeight).toInt());
        }
        recordGeometry.currentGeometry=itemGeometry;
        recordGeometry.previousGeometry=itemGeometry;
        recordGeometry.WindowState=settings.value("WindowState", 0).toInt();
        widgetGeometries.append(recordGeometry);
    }
    settings.endArray();
    settings.endGroup();
}

void KCStatusRecorder::writeRecord()
{
    QSettings settings(getRecordFileName(),
                       QSettings::IniFormat);

    settings.beginGroup("DesktopStatus");
    settings.setValue("Height", startStatus.desktopHeight);
    settings.setValue("Width", startStatus.desktopWidth);
    settings.endGroup();

    //Write widget status
    settings.beginGroup("WidgetStatus");
    settings.beginWriteArray("Widgets", widgetNames.count());
    for(int i=0;i<widgetNames.count();i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("ObjectName", widgetNames.at(i));

        //Output relative geometry
        QRect itemGeometry=widgetGeometries.at(i).currentGeometry;
        settings.setValue("x", float(itemGeometry.x()) / startStatus.desktopWidth);
        settings.setValue("y", float(itemGeometry.y()) / startStatus.desktopHeight);
        settings.setValue("h", float(itemGeometry.height())/ startStatus.desktopHeight);
        settings.setValue("w", float(itemGeometry.width())/startStatus.desktopWidth);

        //Output absolute geometry
        settings.setValue("Left", itemGeometry.x());
        settings.setValue("Top", itemGeometry.y());
        settings.setValue("Width", itemGeometry.width());
        settings.setValue("Height", itemGeometry.height());

        //Output window state
        settings.setValue("WindowState", widgetGeometries.at(i).WindowState);
    }
    settings.endArray();
    settings.endGroup();
}

