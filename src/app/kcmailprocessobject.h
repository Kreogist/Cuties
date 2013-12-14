#ifndef KCMAILPROCESSOBJECT_H
#define KCMAILPROCESSOBJECT_H

#include <QObject>

#include <QTcpSocket>
#include <QThread>
#include <QDebug>

class KCMailProcessObject: public QObject
{
    Q_OBJECT
public:
    static KCMailProcessObject *getInstance();
    void setHostAddress(const QString &newHostNameAddress);
    void setHostPort(const quint16 &newHostPort);
    void setTimeoutCounting(const int &newTimeout);
    void sendMail();
    void setMailTitle(const QString &value);
    void setMailContent(const QString &value);
    void setMailSender(const QString &value);
    void setMailSenderPassword(const QString &value);
    void setMailSenderCaption(const QString &value);
    void setMailReceiver(const QString &value);
    void setMailReceiverCaption(const QString &value);

signals:

public slots:

private:
    KCMailProcessObject();
    QTcpSocket socket;
    void communication(const char *msg);
    void readWelcome();
    void smtpCommunication();
    void createMail();
    void createMailFrom();
    void createMailRcptTo();

    static KCMailProcessObject *instance;
    QString hostNameAddress;
    quint16 hostPort;
    int timeoutCount;
    QString mailTitle;
    QString mailContent;
    QString mailSender, mailSenderPassword, mailSenderCaption;
    QString mailReceiver, mailReceiverCaption;
    QString mailPackage, mailFrom, mailRcptTo;
};

#endif // KCMAILPROCESSOBJECT_H
