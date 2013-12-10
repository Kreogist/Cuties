
#include "kcmailprocessobject.h"

#include <stdio.h>
#include <iostream>

using namespace std;

KCMailProcessObject *KCMailProcessObject::instance=nullptr;

KCMailProcessObject *KCMailProcessObject::getInstance()
{
    return instance==nullptr?instance=new KCMailProcessObject:instance;
}

void KCMailProcessObject::setHostAddress(const QString &newHostNameAddress)
{
    hostNameAddress=newHostNameAddress;
}

void KCMailProcessObject::setHostPort(const quint16 &newHostPort)
{
    hostPort=newHostPort;
}

void KCMailProcessObject::setTimeoutCounting(const int &newTimeout)
{
    timeoutCount=newTimeout;
}

KCMailProcessObject::KCMailProcessObject()
{
    hostNameAddress="smtp.126.com";
    hostPort=25;
}

void KCMailProcessObject::sendMail()
{
    socket.connectToHost(hostNameAddress, hostPort);
    if (socket.waitForConnected(timeoutCount))
    {
        qDebug()<<"Smtp Server Connected Success.";
        readWelcome();
        createMail();
        smtpCommunication();
        socket.close();
    }
    else
    {
        qDebug() << "connection failed.";
    }
}

void KCMailProcessObject::communication(const char *msg)
{
        char data[1024];

        if (socket.write(msg, qstrlen(msg)) == -1)
                qDebug() << "@@@@@@@@@@@@@@ socket.write failed";
        socket.flush();

        if (socket.waitForReadyRead(-1) == true)
        {
            memset(data, '\0', sizeof(data));
            socket.readLine(data, 1024);
            qDebug() << data;
        }
}

void KCMailProcessObject::smtpCommunication()
{
        communication("helo 126.com\r\n");
        communication("auth login\r\n");
        communication(mailSender.toLatin1().toBase64()+"\r\n");
        communication(mailSenderPassword.toLatin1().toBase64()+"\r\n");
        communication("mail from: <"+mailSender.toLatin1()+">\r\n");
        communication("rcpt to: <"+mailReceiver.toLatin1()+">\r\n");
        communication("data\r\n");
        communication(mailPackage.toLocal8Bit().data());
        communication("quit\r\n");

        qDebug() << "send email ok." << endl;
}

void KCMailProcessObject::createMail()
{
    mailPackage="From: " + mailSenderCaption +
                "\r\nTo: " + mailReceiverCaption + "\r\n" +
                "Subject: " + mailTitle + "\r\n\r\n" +
                mailContent +
                "\r\n.\r\n";
}

void KCMailProcessObject::setMailReceiverCaption(const QString &value)
{
    mailReceiverCaption = value;
}

void KCMailProcessObject::setMailReceiver(const QString &value)
{
    mailReceiver = value;
}

void KCMailProcessObject::setMailSenderCaption(const QString &value)
{
    mailSenderCaption = value;
}

void KCMailProcessObject::setMailSenderPassword(const QString &value)
{
    mailSenderPassword = value;
}

void KCMailProcessObject::setMailSender(const QString &value)
{
    mailSender = value;
}

void KCMailProcessObject::setMailContent(const QString &value)
{
    mailContent = value;
}

void KCMailProcessObject::setMailTitle(const QString &value)
{
    mailTitle = value;
}

void KCMailProcessObject::readWelcome()
{
    char data[1024];
    int len;

    if (socket.waitForReadyRead(-1) == true)
    {
        memset(data, '\0', sizeof(data));
            len = socket.readLine(data, 1024);
            qDebug() << data << endl;;
        }
        qDebug()<<"Read Welcome!!";
}
