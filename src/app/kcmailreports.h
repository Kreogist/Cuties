#ifndef KCMAILREPORTS_H
#define KCMAILREPORTS_H

#include <QDialog>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>

#include "kcmailprocessobject.h"

class KCMailSendingStatus : public QWidget
{
    Q_OBJECT
public:
    explicit KCMailSendingStatus(QWidget *parent = 0);

private:
};

class KCMailReports : public QDialog
{
    Q_OBJECT
public:
    explicit KCMailReports(QWidget *parent = 0);
    enum SendingMode
    {
        BugReportMode,
        FeedbackReportMode,
        ModeCount
    };
    void setMode(SendingMode value);

signals:

public slots:
    void retranslate();

private slots:
    void sendReports();

private:
    SendingMode mode;
    QLineEdit *mailTitle;
    QPlainTextEdit *mailContent;
    QPushButton *sendReport;

    KCMailProcessObject *instance;

    QString titlePlaceHolderText[ModeCount];
    QString senderCaptions[ModeCount];
    QString buttonText[ModeCount];
    QString windowTitleString[ModeCount];
    QString titlePrefix[ModeCount];
};

#endif // KCMAILREPORTS_H
