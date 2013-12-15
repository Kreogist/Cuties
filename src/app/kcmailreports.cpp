
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QTextBlock>

#include "kcmailreports.h"

KCMailSendingStatus::KCMailSendingStatus(QWidget *parent) :
    QWidget(parent)
{
    setContentsMargins(0,0,0,0);
    setAutoFillBackground(true);
    setFixedHeight(100);

    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    mainLayout->setContentsMargins(7,7,7,7);
    mainLayout->setSpacing(7);
    setLayout(mainLayout);

    reportStatus=new QLabel(this);
    mainLayout->addWidget(reportStatus);
    mailProgress=new QProgressBar(this);
    mainLayout->addWidget(mailProgress);

    cancelSending=new QToolButton(this);
    cancelSending->setText(tr("Cancel"));
    mainLayout->addWidget(cancelSending);

    QGraphicsDropShadowEffect *wndShadow = new QGraphicsDropShadowEffect(this);
    wndShadow->setBlurRadius(15.0);
    wndShadow->setColor(QColor(0, 0, 0, 200));
    wndShadow->setOffset(0);
    setGraphicsEffect(wndShadow);
}

void KCMailSendingStatus::setText(const QString &text)
{
    reportStatus->setText(text);
}

void KCMailSendingStatus::setValue(const int &value)
{
    mailProgress->setValue(value);
}

KCMailReports::KCMailReports(QWidget *parent) :
    QDialog(parent)
{   
    mode=BugReportMode;
    titlePrefix[BugReportMode]="Bug: ";
    titlePrefix[FeedbackReportMode]="Feedback: ";
    retranslate();

    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    setLayout(mainLayout);
    mailTitle=new QLineEdit(this);
    mainLayout->addWidget(mailTitle);
    mailContent=new QPlainTextEdit(this);
    mainLayout->addWidget(mailContent, 1);
    sendReport=new QPushButton(this);
    mainLayout->addWidget(sendReport);

    setMode(mode);
    instance=KCMailProcessObject::getInstance();
    connect(sendReport, SIGNAL(clicked()),
            this, SLOT(sendReports()));
    connect(instance, SIGNAL(statusChanged(KCMailProcessObject::SendingStatus)),
            this, SLOT(refreshStatus(KCMailProcessObject::SendingStatus)));

    reportStatus=new KCMailSendingStatus(this);
}

void KCMailReports::setMode(SendingMode value)
{
    mode = value;
    setWindowTitle(windowTitleString[mode]);
    mailTitle->setPlaceholderText(titlePlaceHolderText[mode]);
    sendReport->setText(buttonText[mode]);
}

void KCMailReports::retranslate()
{
    senderCaptions[BugReportMode]=tr("BugReporter");
    senderCaptions[FeedbackReportMode]=tr("Feedback");

    windowTitleString[BugReportMode]=tr("Bug Report");
    windowTitleString[FeedbackReportMode]=tr("Feedback");

    titlePlaceHolderText[BugReportMode]=tr("Please input the brief bug description.");
    titlePlaceHolderText[FeedbackReportMode]=tr("Please input the feedback title.");

    buttonText[BugReportMode]=tr("Send Bug Report");
    buttonText[FeedbackReportMode]=tr("Send Feedback");
}

void KCMailReports::sendReports()
{
    refreshStatus(KCMailProcessObject::Preparing);
    instance->setHostAddress("smtp.126.com");
    instance->setHostPort(25);
    instance->setMailReceiver("kreogistdevteam@126.com");
    instance->setMailReceiverCaption("Kreogist Dev Team");
    instance->setMailSender("kreogist@126.com");
    instance->setMailSenderPassword("moc.621@tsigoerk");
    instance->setMailSenderCaption(senderCaptions[mode]);
    instance->setMailTitle(titlePrefix[mode] + mailTitle->text());
    QString reportContent;
    reportContent.clear();
    for(QTextBlock textBlock=mailContent->document()->begin();
                   textBlock!=mailContent->document()->end();
                   textBlock=textBlock.next() )
    {
        reportContent+=textBlock.text()+"\n";
    }
    instance->setMailContent(reportContent);
    instance->sendMail();
}

void KCMailReports::refreshStatus(KCMailProcessObject::SendingStatus status)
{
    switch(status)
    {
    case KCMailProcessObject::Preparing:
        reportStatus->setText(tr("Configuring Mail Service"));
        reportStatus->setValue(5);
        break;
    case KCMailProcessObject::ConnectionFailed:
        reportStatus->setText(tr("Connection Failed"));
        reportStatus->setValue(5);
        break;
    }
}
