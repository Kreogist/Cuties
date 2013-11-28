
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QToolButton>
#include <QResizeEvent>

#include "kcwelcomewindow.h"

KCWelcomeWindowNewFileButton::KCWelcomeWindowNewFileButton(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);

    buttonLayout=new QHBoxLayout(this);
    buttonLayout->setContentsMargins(0,0,0,0);
    buttonLayout->setSpacing(5);
    setLayout(buttonLayout);

    pal=palette();

    buttonLayout->addSpacing(20);

    imageLabel=new QLabel(this);
    buttonLayout->addWidget(imageLabel);

    textLabel=new QLabel(this);
    buttonLayout->addWidget(textLabel);

    buttonLayout->addStretch();
}

void KCWelcomeWindowNewFileButton::setImage(const QString &filePath)
{
    imageLabel->setPixmap(QPixmap(filePath));
}

void KCWelcomeWindowNewFileButton::setText(const QString &buttonCaption)
{
    textLabel->setText(buttonCaption);
}

void KCWelcomeWindowNewFileButton::setFileSuffix(const QString &newFileSuffix)
{
    emitFileSuffix=newFileSuffix;
}

void KCWelcomeWindowNewFileButton::setEmitFileSuffix(const QString &value)
{
    emitFileSuffix=value;
}

void KCWelcomeWindowNewFileButton::enterEvent(QEvent *e)
{
    QWidget::enterEvent(e);
    setBackgroundAlpha(255);
}

void KCWelcomeWindowNewFileButton::leaveEvent(QEvent *e)
{
    QWidget::leaveEvent(e);
    setBackgroundAlpha(0);
}

void KCWelcomeWindowNewFileButton::setBackgroundColor(const QColor &value)
{
    backgroundColor = value;
}

void KCWelcomeWindowNewFileButton::setBackgroundAlpha(int newAlpha)
{
    backgroundColor.setAlpha(newAlpha);
    pal.setColor(QPalette::Window, backgroundColor);
    setPalette(pal);
}

KCWelcomeWindowNewFile::KCWelcomeWindowNewFile(QWidget *parent) :
    QWidget(parent)
{
    retranslate();
    setContentsMargins(0,0,0,0);

    setFixedWidth(400);

    QFont titleFont=font();
    titleFont.setBold(true);
    titleFont.setPixelSize(16);

    QFont labelFont=font();
    labelFont.setPixelSize(16);

    QVBoxLayout *newFileWidgetLayout=new QVBoxLayout(this);
    newFileWidgetLayout->setContentsMargins(0,0,0,0);
    newFileWidgetLayout->setSpacing(0);
    setLayout(newFileWidgetLayout);

    QWidget *newFileCaptionWidget=new QWidget(this);
    QHBoxLayout *newFileCaptionWidgetLayout=new QHBoxLayout(newFileCaptionWidget);
    newFileCaptionWidget->setFixedHeight(80);
    newFileCaptionWidgetLayout->setSpacing(0);
    newFileCaptionWidget->setLayout(newFileCaptionWidgetLayout);

    QLabel *newFileIcon=new QLabel(this);
    newFileIcon->setFixedSize(64,64);
    newFileIcon->setScaledContents(true);
    newFileIcon->setPixmap(QPixmap(":/WelcomeWindow/image/Welcome/CreateNewFile.png"));
    newFileCaptionWidgetLayout->addWidget(newFileIcon);

    newFileCaption=new QLabel(this);
    newFileCaption->setText(newFileTitleCaption);
    newFileCaption->setFont(titleFont);
    newFileCaptionWidgetLayout->addWidget(newFileCaption);
    newFileCaptionWidgetLayout->addStretch();

    newFileWidgetLayout->addWidget(newFileCaptionWidget);

    QWidget *newFileListWidget=new QWidget(this);
    newFileListWidget->setContentsMargins(0,0,0,0);
    QVBoxLayout *newFileListWidgetLayout=new QVBoxLayout(newFileListWidget);
    newFileListWidgetLayout->setContentsMargins(0,0,0,0);
    newFileListWidgetLayout->setSpacing(0);
    newFileListWidget->setLayout(newFileListWidgetLayout);

    QString fileSuffixs[NewFileSuffixCount],
            fileIcons[NewFileSuffixCount];
    fileSuffixs[plainTextType]="txt";
    fileSuffixs[cppType]="cpp";
    fileSuffixs[cType]="c";
    fileSuffixs[pascalType]="pas";

    fileIcons[plainTextType]=":/WelcomeWindow/image/FileAssociate/PlainText/PlainText_64x64.png";
    fileIcons[cppType]=":/WelcomeWindow/image/FileAssociate/Cpp/Cpp_64x64.png";
    fileIcons[cType]=":/WelcomeWindow/image/FileAssociate/C/C_64x64.png";
    fileIcons[pascalType]=":/WelcomeWindow/image/FileAssociate/Pas/Pas_64x64.png";

    for(int i=plainTextType; i<NewFileSuffixCount; i++)
    {
        newFileButtons[i]=new KCWelcomeWindowNewFileButton(this);
        newFileButtons[i]->setText(newFileButtonCaption[i]);
        newFileButtons[i]->setBackgroundColor(QColor(0xf7,0xcf,0x3d));
        newFileButtons[i]->setFileSuffix(fileSuffixs[i]);
        newFileButtons[i]->setFont(labelFont);
        newFileButtons[i]->setImage(fileIcons[i]);
        newFileListWidgetLayout->addWidget(newFileButtons[i]);
    }
    newFileListWidgetLayout->addStretch();
    newFileWidgetLayout->addWidget(newFileListWidget);
}

void KCWelcomeWindowNewFile::retranslate()
{
    newFileTitleCaption=tr("New Source File");

    newFileButtonCaption[plainTextType]="New Plain Text File";
    newFileButtonCaption[cppType]="New C++ Source Code File";
    newFileButtonCaption[cType]="New C Source Code File";
    newFileButtonCaption[pascalType]="New Pascal Source Code File";
}

void KCWelcomeWindowNewFile::retranslateAndSet()
{
    retranslate();
    newFileCaption->setText(newFileTitleCaption);
}


KCWelcomeWindowOpenFile::KCWelcomeWindowOpenFile(QWidget *parent) :
    QWidget(parent)
{
    retranslate();

    setAutoFillBackground(true);

    pal=palette();
    backgroundColor=QColor(0xf7,0xcf,0x3d);

    QHBoxLayout *openFileLayout=new QHBoxLayout(this);
    openFileLayout->setContentsMargins(0,0,0,0);
    openFileLayout->setSpacing(0);
    setLayout(openFileLayout);

    QFont titleFont=font();
    titleFont.setBold(true);
    titleFont.setPixelSize(16);

    openFileLayout->addStretch();
    QLabel *openFileIcon=new QLabel(this);
    openFileIcon->setFixedSize(64,64);
    openFileIcon->setScaledContents(true);
    openFileIcon->setPixmap(QPixmap(":/WelcomeWindow/image/Welcome/OpenFile.png"));
    openFileLayout->addWidget(openFileIcon);

    openFileCaption=new QLabel(this);
    openFileCaption->setFont(titleFont);
    openFileCaption->setText(openFileTitleCaption);
    openFileLayout->addWidget(openFileCaption);

    openFileLayout->addStretch();
}

void KCWelcomeWindowOpenFile::retranslate()
{
    openFileTitleCaption="Open Source File";
}

void KCWelcomeWindowOpenFile::retranslateAndSet()
{
    retranslate();
}

void KCWelcomeWindowOpenFile::setBackgroundAlpha(int newAlpha)
{
    backgroundColor.setAlpha(newAlpha);
    pal.setColor(QPalette::Window, backgroundColor);
    setPalette(pal);
}

void KCWelcomeWindowOpenFile::enterEvent(QEvent *e)
{
    QWidget::enterEvent(e);
    setBackgroundAlpha(255);
}

void KCWelcomeWindowOpenFile::leaveEvent(QEvent *e)
{
    QWidget::leaveEvent(e);
    setBackgroundAlpha(0);
}

void KCWelcomeWindowOpenFile::setBackgroundColor(const QColor &value)
{
    backgroundColor = value;
}

KCWelcomeWindow::KCWelcomeWindow(QWidget *parent) :
    QWidget(parent)
{
    //Get translate
    retranslate();

    //Set properties
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
    welcomeBanner->setFixedHeight(125);

    bannerBackground=new QLabel(welcomeBanner);
    bannerBackground->setFixedHeight(125);
    bannerBackground->setPixmap(QPixmap(":/img/image/Banner.png"));
    bannerBackground->setScaledContents(true);

    QHBoxLayout *bannerLayout=new QHBoxLayout(welcomeBanner);
    bannerLayout->setContentsMargins(0,0,0,0);
    bannerLayout->setSpacing(10);
    welcomeBanner->setLayout(bannerLayout);

    QLabel *cutiesLogo=new QLabel(welcomeBanner);
    cutiesLogo->setContentsMargins(0,0,0,0);
    cutiesLogo->setFixedSize(100,100);
    cutiesLogo->setScaledContents(true);
    cutiesLogo->setPixmap(QPixmap(":/mainicon/image/Cuties.png"));
    bannerLayout->addWidget(cutiesLogo);

    QFont titleFont=font();
    titleFont.setBold(true);
    titleFont.setPixelSize(30);

    QLabel *cutiesCaption=new QLabel(this);
    cutiesCaption->setFont(titleFont);
    cutiesCaption->setText("Cuties");
    pal=cutiesCaption->palette();
    pal.setColor(QPalette::WindowText, QColor(255,255,255));
    cutiesCaption->setPalette(pal);
    bannerLayout->addWidget(cutiesCaption);
    bannerLayout->addStretch();

    welcomeLayout->addWidget(welcomeBanner);

    contentsLayout=new QHBoxLayout();
    contentsLayout->setContentsMargins(0,0,0,0);
    contentsLayout->setSpacing(0);

    KCWelcomeWindowNewFile *newFileContentWidget=new KCWelcomeWindowNewFile(this);
    contentsLayout->addWidget(newFileContentWidget);

    KCWelcomeWindowOpenFile *openFileContentWidget=new KCWelcomeWindowOpenFile(this);
    contentsLayout->addWidget(openFileContentWidget);

    welcomeLayout->addLayout(contentsLayout,1);
}

KCWelcomeWindow::~KCWelcomeWindow()
{
    contentsLayout->deleteLater();
}

void KCWelcomeWindow::retranslate()
{

}

void KCWelcomeWindow::retranslateAndSet()
{
    retranslate();
}

void KCWelcomeWindow::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    bannerBackground->resize(e->size());
}
