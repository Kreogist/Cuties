#ifndef KCMAILREPORTS_H
#define KCMAILREPORTS_H

#include <QDialog>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include <QProgressBar>
#include <QHBoxLayout>

#include "kcmailprocessobject.h"

class KCMailSendingStatus : public QWidget
{
    Q_OBJECT
public:
    explicit KCMailSendingStatus(QWidget *parent = 0);
    void resetStatus();

public slots:
    void setStatus(const QString &text=QString(""),
                   const int &value=-1);
    QString currentText();
    int currentValue();

private:
    QLabel *reportStatus;
    QProgressBar *mailProgress;
    QToolButton *cancelSending;
    QPalette pal;
};

class KCMailReports : public QDialog
{
    Q_OBJECT
public:
    explicit KCMailReports(QWidget *parent = 0);
    ~KCMailReports();
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
    void refreshStatus(KCMailProcessObject::SendingStatus status);

protected:
    void resizeEvent(QResizeEvent *e);

private:
    QHBoxLayout *buttonLayout;

    SendingMode mode;
    QLineEdit *mailTitle;
    QPlainTextEdit *mailContent;
    QPushButton *sendReport, *cancelSending;

    KCMailProcessObject *instance;

    KCMailSendingStatus *reportStatus;

    QString titlePlaceHolderText[ModeCount];
    QString senderCaptions[ModeCount];
    QString buttonText[ModeCount];
    QString windowTitleString[ModeCount];
    QString titlePrefix[ModeCount];
};

#endif // KCMAILREPORTS_H
