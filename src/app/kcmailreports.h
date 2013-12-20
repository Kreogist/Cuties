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
#include <QPropertyAnimation>

#include "kcmailprocessobject.h"

class KCMailSendingStatus : public QWidget
{
    Q_OBJECT
public:
    explicit KCMailSendingStatus(QWidget *parent = 0);
    void resetStatus();
    enum StatusEnum
    {
        Connecting,
        Sending,
        ConnectFailed,
        Success
    };
    void setProgressStatus(StatusEnum progressStatus);

public slots:
    void setStatus(const QString &text=QString(""),
                   const int &value=-1);
    QString currentText();
    int currentValue();
    void showStatus();
    void hideStatus();
    void delayHide();

protected:
    void resizeEvent(QResizeEvent *e);

private:
    void startAnimation();
    void setProgressPalette(QColor progressColor);
    QLabel *reportStatus;
    QProgressBar *mailProgress;
    QPalette pal;

    QPropertyAnimation *statusAnime;
    int destinationTop;
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
    void buttonStatusSet();
    void enabledButtonState();
    void disabledButtonState();
    void setSendButtonState(bool enabled,
                            QColor button,
                            QColor buttonText);
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
    QPalette pal;
};

#endif // KCMAILREPORTS_H
