
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>

#include "kcwelcomewindow.h"

KCWelcomeWindow::KCWelcomeWindow(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);

    QVBoxLayout *welcomeLayout=new QVBoxLayout(this);
    welcomeLayout->setContentsMargins(0,0,0,0);
    welcomeLayout->setSpacing(0);
    setLayout(welcomeLayout);

    QPalette pal=palette();
    pal.setColor(QPalette::Window, QColor(255,255,255));
    pal.setColor(QPalette::WindowText, QColor(0,0,0));
    setPalette(pal);

    QWidget *welcomeBanner=new QWidget(this);
    welcomeBanner->setAutoFillBackground(true);
    welcomeBanner->setContentsMargins(15,0,15,0);
    welcomeBanner->setFixedHeight(50);

    pal=welcomeBanner->palette();
    pal.setColor(QPalette::Window, QColor(0x53,0x53,0x53));
    pal.setColor(QPalette::WindowText, QColor(255,255,255));
    welcomeBanner->setPalette(pal);

    QHBoxLayout *bannerLayout=new QHBoxLayout(welcomeBanner);
    bannerLayout->setContentsMargins(0,0,0,0);
    bannerLayout->setSpacing(0);
    welcomeBanner->setLayout(bannerLayout);

    QLabel *cutiesLogo=new QLabel(welcomeBanner);
    cutiesLogo->setContentsMargins(0,0,0,0);
    cutiesLogo->setFixedSize(50,50);
    cutiesLogo->setScaledContents(true);
    cutiesLogo->setPixmap(QPixmap(":/mainicon/image/Cuties.png"));
    bannerLayout->addWidget(cutiesLogo);

    QLabel *cutiesName=new QLabel(welcomeBanner);
    cutiesName->setText("Cuties " + qApp->applicationVersion());
    bannerLayout->addWidget(cutiesName);
    bannerLayout->addStretch();
    welcomeLayout->addWidget(welcomeBanner);

    contentsLayout=new QHBoxLayout();
    contentsLayout->setContentsMargins(0,0,0,0);
    contentsLayout->setSpacing(0);
    welcomeLayout->addLayout(contentsLayout,1);

    QWidget *newFileWidget=new QWidget(this);
    newFileWidget->setContentsMargins(0,0,0,0);
    newFileLayout=new QVBoxLayout();
    newFileLayout->setContentsMargins(0,0,0,0);
    newFileLayout->setSpacing(0);
    newFileWidget->setLayout(newFileLayout);

    QLabel *newFileCaption=new QLabel(this);
    newFileCaption->setText("New Files");
    newFileLayout->addWidget(newFileCaption);

    contentsLayout->addWidget(newFileWidget);
}

KCWelcomeWindow::~KCWelcomeWindow()
{
    contentsLayout->deleteLater();
    newFileLayout->deleteLater();
}
