#ifndef KCSTATUSRECORDER_H
#define KCSTATUSRECORDER_H

#include <QList>
#include <QRect>
#include <QObject>

struct KCEnvironmentVariables
{
    bool available;
    int desktopWidth;
    int desktopHeight;
};

struct KCGeometry
{
    int WindowState;
    /*
     * Window State Explaination
     * -------------------------
     * Here use the same as Qt used.
     *   0 = WindowNoState
     *   1 = WindowMinimized
     *   2 = WindowMaximized
     *   3 = WindowFullScreen
     */
    QRect previousGeometry;
    QRect currentGeometry;
};

class KCStatusRecorder : public QObject
{
    Q_OBJECT
public:
    explicit KCStatusRecorder(QObject *parent = 0);
    static KCStatusRecorder *getInstance();
    static QString getRecordFileName();
    static void setRecordFileName(const QString &value);

    //Read & write, apply.
    void readRecord();
    void writeRecord();
    void applyRecord();

    void clearRecordWidgets();
    int getWidgetIndex(const QString &currentWidgetName);
    QRect getWidgetRect(const QString &currentWidgetName);
    void setWidgetGeometry(const int &widgetIndex,
                           const QRect &widgetGeometry,
                           Qt::WindowStates windowState);
    void setWidgetGeometry(const QString &widgetName,
                           const QRect &widgetGeometry,
                           Qt::WindowStates windowState);
    Qt::WindowStates getWidgetState(const QString &currentWidgetName);
    int windowStateToInt(Qt::WindowStates windowState);

signals:

public slots:

private:
    QRect getGeometry(const int &widgetIndex);
    int appendList(const QString &newWidgetName);

    KCEnvironmentVariables getCurrentStatus();

    QRect defaultGeometry;
    bool useRelative;
    static KCStatusRecorder *instance;
    static QString recordFileName;
    QList<QString> widgetNames;
    QList<KCGeometry> widgetGeometries;

    KCEnvironmentVariables startStatus, finalStatus,
                           recordStatus;
    int defaultLeft, defaultTop, defaultHeight, defaultWidth;
    float defaultX, defaultY, defaultH, defaultW;
};

#endif // KCSTATUSRECORDER_H
