
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QTextBlock>
#include <QTimer>

#include "kcmailreports.h"

KCMailSendingStatus::KCMailSendingStatus(QWidget *parent) :
    QWidget(parent)
{
    setContentsMargins(0,0,0,0);
    setAutoFillBackground(true);
    setMinimumHeight(50);

    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    mainLayout->setContentsMargins(7,7,7,7);
    mainLayout->setSpacing(7);
    setLayout(mainLayout);

    reportStatus=new QLabel(this);
    reportStatus->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(reportStatus);
    mailProgress=new QProgressBar(this);
    mailProgress->setTextVisible(false);
    mainLayout->addWidget(mailProgress);

    QGraphicsDropShadowEffect *wndShadow = new QGraphicsDropShadowEffect(this);
    wndShadow->setBlurRadius(15.0);
    wndShadow->setColor(QColor(0, 0, 0, 200));
    wndShadow->setOffset(0);
    setGraphicsEffect(wndShadow);

    pal=mailProgress->palette();

    statusAnime=new QPropertyAnimation(this, "geometry", this);
    statusAnime->setEasingCurve(QEasingCurve::OutCubic);
}

void KCMailSendingStatus::delayHide()
{
    QTimer::singleShot(2000, this, SLOT(hideStatus()));
}

void KCMailSendingStatus::hideStatus()
{
    destinationTop=-height()-30;
    startAnimation();
}

void KCMailSendingStatus::showStatus()
{
    destinationTop=0;
    startAnimation();
}

void KCMailSendingStatus::resetStatus()
{
    setProgressStatus(Connecting);
    setStatus("",0);
}

void KCMailSendingStatus::setProgressStatus(KCMailSendingStatus::StatusEnum progressStatus)
{
    switch(progressStatus)
    {
    case Connecting:
        setProgressPalette(QColor(204,204,204));
        break;
    case Sending:
        setProgressPalette(QColor(153,153,153));
        break;
    case ConnectFailed:
        setProgressPalette(QColor(255,0,0));
        break;
    case Success:
        setProgressPalette(QColor(51,204,51));
        break;
    }
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

void KCMailSendingStatus::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}

void KCMailSendingStatus::startAnimation()
{
    statusAnime->stop();
    QRect startGeometry=geometry();
    QRect endGeometry=startGeometry;
    endGeometry.setTop(destinationTop);
    endGeometry.setHeight(50);
    statusAnime->setStartValue(startGeometry);
    statusAnime->setEndValue(endGeometry);
    statusAnime->start();
}

void KCMailSendingStatus::setProgressPalette(QColor progressColor)
{
    pal.setColor(QPalette::Highlight, progressColor);
    mailProgress->setPalette(pal);
}

KCMailReports::KCMailReports(QWidget *parent) :
    QDialog(parent)
{
    setMinimumSize(480,320);
    mode=BugReportMode;
    titlePrefix[BugReportMode]="Bug: ";
    titlePrefix[FeedbackReportMode]="Feedback: ";
    retranslate();

    pal=palette();
    pal.setColor(QPalette::Highlight, QColor(0,0,0,255));
    setPalette(pal);

    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    setLayout(mainLayout);
    mailTitle=new QLineEdit(this);
    pal=mailTitle->palette();
    pal.setColor(QPalette::Highlight, QColor(0xf7,0xcf,0x3d));
    mailTitle->setPalette(pal);
    mainLayout->addWidget(mailTitle);

    mailContent=new QPlainTextEdit(this);
    pal=mailContent->palette();
    pal.setColor(QPalette::Highlight, QColor(0xf7,0xcf,0x3d));
    mailContent->setPalette(pal);
    mainLayout->addWidget(mailContent, 1);

    buttonLayout=new QHBoxLayout();

    sendReport=new QPushButton(this);
    sendReport->setFixedHeight(30);
    pal=sendReport->palette();
    disabledButtonState();
    buttonLayout->addWidget(sendReport);
    cancelSending=new QPushButton(this);
    cancelSending->setFixedHeight(30);
    cancelSending->setText(tr("Cancel"));
    buttonLayout->addWidget(cancelSending);
    mainLayout->addLayout(buttonLayout);

    setMode(mode);
    instance=KCMailProcessObject::getInstance();
    connect(mailContent, SIGNAL(textChanged()),
            this, SLOT(buttonStatusSet()));
    connect(mailTitle, SIGNAL(textChanged(QString)),
            this, SLOT(buttonStatusSet()));
    connect(sendReport, SIGNAL(clicked()),
            this, SLOT(sendReports()));
    connect(instance, SIGNAL(statusChanged(KCMailProcessObject::SendingStatus)),
            this, SLOT(refreshStatus(KCMailProcessObject::SendingStatus)));
    connect(cancelSending, SIGNAL(clicked()),
            this, SLOT(close()));

    reportStatus=new KCMailSendingStatus(this);
    reportStatus->setGeometry(reportStatus->x(),
                              0-reportStatus->height()-30,
                              reportStatus->width(),
                              reportStatus->height());
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

void KCMailReports::buttonStatusSet()
{
    if(!mailTitle->text().isEmpty() && !mailContent->document()->isEmpty())
    {
        enabledButtonState();
        return;
    }
    disabledButtonState();
}

void KCMailReports::enabledButtonState()
{
    setSendButtonState(true,
                       QColor(0x00,0x33,0x99),
                       QColor(255,255,255));

}

void KCMailReports::disabledButtonState()
{
    setSendButtonState(false,
                       QColor(0xc9, 0xcb, 0xce),
                       QColor(100,100,100));
}

void KCMailReports::setSendButtonState(bool enabled,
                                       QColor button,
                                       QColor buttonText)
{
    sendReport->setEnabled(enabled);
    pal.setColor(QPalette::Button, button);
    pal.setColor(QPalette::ButtonText, buttonText);
    sendReport->setPalette(pal);
}

void KCMailReports::sendReports()
{
    disabledButtonState();
    reportStatus->showStatus();
    refreshStatus(KCMailProcessObject::Preparing);
    reportStatus->resetStatus();
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
        textBlock=textBlock.next())
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
                                10);
        break;
    case KCMailProcessObject::ConnectingServer:
        reportStatus->setStatus(tr("Connecting mail server"),
                                20);
        break;
    case KCMailProcessObject::ReadingWelcome:
        reportStatus->setStatus(tr("Do HELO checking"),
                                30);
        reportStatus->setProgressStatus(KCMailSendingStatus::Sending);
        break;
    case KCMailProcessObject::StartLogin:
        reportStatus->setStatus(tr("Preparing login"),
                                40);
        break;
    case KCMailProcessObject::Logingin:
        reportStatus->setStatus(tr("Loging in"),
                                50);
        break;
    case KCMailProcessObject::SettingAddress:
        reportStatus->setStatus(tr("Setting receiver"),
                                60);
        break;
    case KCMailProcessObject::RequireSendingData:
        reportStatus->setStatus(tr("Request sending data"),
                                70);
        break;
    case KCMailProcessObject::SendingData:
        reportStatus->setStatus(tr("Sending data"),
                                80);
        break;
    case KCMailProcessObject::Logingout:
        reportStatus->setStatus(tr("Loging out"),
                                90);
        break;
    case KCMailProcessObject::ConnectionFailed:
        reportStatus->setStatus(tr("Server connection failed"),
                                100);
        reportStatus->setProgressStatus(KCMailSendingStatus::ConnectFailed);
        reportStatus->delayHide();
        enabledButtonState();
        break;
    case KCMailProcessObject::WelcomeReadFailed:
        reportStatus->setStatus(tr("No response from the server"),
                                100);
        reportStatus->delayHide();
        enabledButtonState();
        break;
    case KCMailProcessObject::SocketWriteFailed:
        reportStatus->setStatus(tr("Unable to communicate with the server"),
                                100);
        reportStatus->delayHide();
        enabledButtonState();
        break;
    case KCMailProcessObject::SendSuccess:
        reportStatus->setStatus(tr("Report send success"),
                                100);
        reportStatus->setProgressStatus(KCMailSendingStatus::Success);
        reportStatus->delayHide();
        enabledButtonState();
        break;
    default:
        //Here should never be come
        reportStatus->setStatus(tr("Unknown Status"),
                                -1);
        enabledButtonState();
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
