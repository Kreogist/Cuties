
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QTextBlock>

#include "kcmailreports.h"

KCMailSendingStatus::KCMailSendingStatus(QWidget *parent) :
    QWidget(parent)
{
    setContentsMargins(0,0,0,0);
    setAutoFillBackground(true);
    setMinimumHeight(100);

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
    mainLayout->setAlignment(cancelSending, Qt::AlignCenter);

    QGraphicsDropShadowEffect *wndShadow = new QGraphicsDropShadowEffect(this);
    wndShadow->setBlurRadius(15.0);
    wndShadow->setColor(QColor(0, 0, 0, 200));
    wndShadow->setOffset(0);
    setGraphicsEffect(wndShadow);

    pal=mailProgress->palette();
}

void KCMailSendingStatus::resetStatus()
{
    ;
}

void KCMailSendingStatus::setStatus(const QString &text, const int &value)
{
    if(text.length()>0)
    {
        reportStatus->setText(text);
    }
    if(value>-1)
    {
        mailProgress->setValue(value);
    }
}

QString KCMailSendingStatus::currentText()
{
    return reportStatus->text();
}

int KCMailSendingStatus::currentValue()
{
    return mailProgress->value();
}

KCMailReports::KCMailReports(QWidget *parent) :
    QDialog(parent)
{   
    setMinimumSize(480,320);
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

    buttonLayout=new QHBoxLayout();

    sendReport=new QPushButton(this);
    sendReport->setFixedHeight(30);
    QPalette pal=sendReport->palette();
    pal.setColor(QPalette::Button, QColor(65,99,216));
    pal.setColor(QPalette::ButtonText, QColor(255,255,255));
    sendReport->setPalette(pal);
    buttonLayout->addWidget(sendReport);
    cancelSending=new QPushButton(this);
    cancelSending->setFixedHeight(30);
    cancelSending->setText(tr("Cancel"));
    buttonLayout->addWidget(cancelSending);
    mainLayout->addLayout(buttonLayout);

    setMode(mode);
    instance=KCMailProcessObject::getInstance();
    connect(sendReport, SIGNAL(clicked()),
            this, SLOT(sendReports()));
    connect(instance, SIGNAL(statusChanged(KCMailProcessObject::SendingStatus)),
            this, SLOT(refreshStatus(KCMailProcessObject::SendingStatus)));

    reportStatus=new KCMailSendingStatus(this);
}

KCMailReports::~KCMailReports()
{
    buttonLayout->deleteLater();
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
        reportStatus->setStatus(tr("Configuring mail service"),
                                5);
        break;
    case KCMailProcessObject::ConnectingServer:
        reportStatus->setStatus(tr("Connecting mail server"),
                                5);
        break;
    case KCMailProcessObject::ReadingWelcome:
        reportStatus->setStatus(tr("Do HELO checking"),
                                5);
        break;
    case KCMailProcessObject::StartLogin:
        reportStatus->setStatus(tr("Preparing login"),
                                5);
        break;
    case KCMailProcessObject::Logingin:
        reportStatus->setStatus(tr("Loging in"),
                                5);
        break;
    case KCMailProcessObject::SettingAddress:
        reportStatus->setStatus(tr("Setting receiver"),
                                5);
        break;
    case KCMailProcessObject::RequireSendingData:
        reportStatus->setStatus(tr("Request sending data"),
                                5);
        break;
    case KCMailProcessObject::SendingData:
        reportStatus->setStatus(tr("Sending data"),
                                5);
        break;
    case KCMailProcessObject::Logingout:
        reportStatus->setStatus(tr("Loging out"),
                                5);
        break;
    case KCMailProcessObject::ConnectionFailed:
        reportStatus->setStatus(tr("Server connection failed"),
                                100);
        break;
    case KCMailProcessObject::WelcomeReadFailed:
        reportStatus->setStatus(tr("No response from the server"),
                                100);
        break;
    case KCMailProcessObject::SocketWriteFailed:
        reportStatus->setStatus(tr("Unable to communicate with the server"),
                                100);
        break;
    case KCMailProcessObject::SendSuccess:
        reportStatus->setStatus(tr("Report send success"),
                                100);
        break;
    default:
        //Here should never be come
        reportStatus->setStatus(tr("Unknown Status"),
                                -1);
        break;
    }
}

void KCMailReports::resizeEvent(QResizeEvent *e)
{
    reportStatus->setGeometry(width()/4,
                              reportStatus->y(),
                              width()/2,
                              reportStatus->height());
    QWidget::resizeEvent(e);
}
