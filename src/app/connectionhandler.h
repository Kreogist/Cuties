#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <QObject>
#include <QVector>

class connectionHandler : public QObject
{
    Q_OBJECT
public:
    explicit connectionHandler(QObject *parent = 0);

    void disConnectAll();
    void addConnectionHandle(const QMetaObject::Connection connection);
    connectionHandler& operator += (const QMetaObject::Connection connection);

private:
    QVector<QMetaObject::Connection> connections;
    
};

#endif // CONNECTIONHANDLER_H
