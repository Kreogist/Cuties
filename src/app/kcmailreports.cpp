
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBlock>

#include "kcmailreports.h"

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
