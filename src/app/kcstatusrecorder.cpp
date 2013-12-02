
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

KCStatusRecorder::KCStatusRecorder(QObject *parent) :
    QObject(parent)
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
        widgetIndex=widgetNames.count();
        widgetNames.append(currentWidgetName);
    }
    return widgetIndex;
}

QRect KCStatusRecorder::getWidgetRect(const QString &currentWidgetName)
{
    int widgetIndex=widgetNames.indexOf(currentWidgetName);
    if(widgetIndex==-1)
    {
        //There's no widget name in the name list, append list.
        return appendList(currentWidgetName);
    }
    if(useRelative)
    {
        return getAbsoluteGeometry(widgetIndex);
    }
    return getGeometry(widgetIndex);
}

void KCStatusRecorder::setWidgetGeometry(const QString &widgetName,
                                         const QRect &widgetGeometry,
                                         int windowState)
{
    int widgetIndex=widgetNames.indexOf(widgetName);
    setWidgetGeometry(widgetIndex, widgetGeometry, windowState);
}

void KCStatusRecorder::setWidgetGeometry(const int &widgetIndex,
                                         const QRect &widgetGeometry,
                                         int windowState)
{
    KCGeometry currentGeometry=widgetGeometries.at(widgetIndex);
    currentGeometry.WindowState=windowState;
    if(currentGeometry.WindowState<2)
    {
        currentGeometry.Left=widgetGeometry.left();
        currentGeometry.Top=widgetGeometry.top();
        currentGeometry.Height=widgetGeometry.height();
        currentGeometry.Width=widgetGeometry.width();
        currentGeometry.x=startStatus.desktopWidth/currentGeometry.Left;
        currentGeometry.y=startStatus.desktopHeight/currentGeometry.Top;
        currentGeometry.w=startStatus.desktopWidth/currentGeometry.Width;
        currentGeometry.h=startStatus.desktopHeight/currentGeometry.Height;
    }
    widgetGeometries.removeAt(widgetIndex);
    widgetGeometries.insert(widgetIndex, currentGeometry);
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
        return Qt::WindowFullScreen;
    default:
        return Qt::WindowNoState;
    }
}

QRect KCStatusRecorder::getGeometry(const int &widgetIndex)
{
    return QRect(widgetGeometries.at(widgetIndex).x * startStatus.desktopWidth,
                 widgetGeometries.at(widgetIndex).y * startStatus.desktopHeight,
                 widgetGeometries.at(widgetIndex).w * startStatus.desktopWidth,
                 widgetGeometries.at(widgetIndex).h * startStatus.desktopHeight);
}

QRect KCStatusRecorder::getAbsoluteGeometry(const int &widgetIndex)
{
    return QRect(widgetGeometries.at(widgetIndex).Left,
                 widgetGeometries.at(widgetIndex).Top,
                 widgetGeometries.at(widgetIndex).Width,
                 widgetGeometries.at(widgetIndex).Height);
}

QRect KCStatusRecorder::appendList(const QString &newWidgetName)
{
    int currentIndex=getWidgetIndex(newWidgetName);
    KCGeometry newWidgetGeometry;
    newWidgetGeometry.x=defaultX;
    newWidgetGeometry.y=defaultY;
    newWidgetGeometry.h=defaultH;
    newWidgetGeometry.w=defaultW;
    newWidgetGeometry.Left=defaultLeft;
    newWidgetGeometry.Top=defaultTop;
    newWidgetGeometry.Height=defaultHeight;
    newWidgetGeometry.Width=defaultWidth;
    newWidgetGeometry.WindowState=0;
    widgetGeometries.append(newWidgetGeometry);
    return getAbsoluteGeometry(currentIndex);
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
    for(int i=0;i<widgetNum;i++)
    {
        settings.setArrayIndex(i);
        widgetNames.append(settings.value("ObjectName", "NoName" + QString::number(i)).toString());
        KCGeometry recordGeometry;
        recordGeometry.x=settings.value("x", 0.1).toFloat();
        recordGeometry.y=settings.value("y", 0.1).toFloat();
        recordGeometry.w=settings.value("w", 0.8).toFloat();
        recordGeometry.h=settings.value("h", 0.8).toFloat();
        recordGeometry.Left=settings.value("Left", defaultLeft).toInt(),
        recordGeometry.Top=settings.value("Top", defaultTop).toInt(),
        recordGeometry.Width=settings.value("Width", defaultWidth).toInt(),
        recordGeometry.Height=settings.value("Height", defaultHeight).toInt();
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
        settings.setValue("x", widgetGeometries.at(i).x);
        settings.setValue("y", widgetGeometries.at(i).y);
        settings.setValue("h", widgetGeometries.at(i).h);
        settings.setValue("w", widgetGeometries.at(i).w);
        settings.setValue("Left", widgetGeometries.at(i).Left);
        settings.setValue("Top", widgetGeometries.at(i).Top);
        settings.setValue("Width", widgetGeometries.at(i).Width);
        settings.setValue("Height", widgetGeometries.at(i).Height);
        settings.setValue("WindowState", widgetGeometries.at(i).WindowState);
    }
    settings.endArray();
    settings.endGroup();
}

