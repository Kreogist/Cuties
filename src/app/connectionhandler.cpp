#include "connectionhandler.h"

connectionHandler::connectionHandler(QObject *parent) :
    QObject(parent)
{
}

void connectionHandler::addConnectionHandle(
        const QMetaObject::Connection connection)
{
    connections.append(connection);
}

connectionHandler& connectionHandler::operator += (
        const QMetaObject::Connection connection)
{
    addConnectionHandle(connection);

    return *this;
}

void connectionHandler::disConnectAll()
{
    for(auto i=connections.begin(),end=connections.end();
        i!=end;
        i++)
    {
        if((bool)*i)
        {
            disconnect(*i);
        }
    }

    connections.erase(connections.begin(),connections.end());
}
