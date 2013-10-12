#include "kcmessagebox.h"

//Message Box Title
KCMessageBoxTitle::KCMessageBoxTitle(QWidget *parent) :
    QWidget(parent)
{
    //Set Properties.
    setFixedHeight(30);

    //Set Pixmap Scale Layout.
    mainLayout=new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    setLayout(mainLayout);

    //Set Pixmap
    backPixDisplay=new QLabel(this);
    backPixDisplay->setFixedHeight(30);
    backPixDisplay->setScaledContents(true);
    backPixDisplay->setPixmap(QPixmap(":/MsgBox/image/MessageBox/Title.png"));
    mainLayout->addWidget(backPixDisplay);
}

//Message Box Button Panel
KCMessageBoxPanel::KCMessageBoxPanel(QWidget *parent) :
    QWidget(parent)
{
    //Set Properties.
    //setFixedHeight();

    //Set Pixmap Scale Layout.
    mainLayout=new QVBoxLayout(this);
}

//Message Box Dialog
KCMessageBox::KCMessageBox(QWidget *parent) :
    QDialog(parent)
{
    //Set Window Flags
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    //Set Properties.
    setMinimumWidth(0);

    //Set Parent Geometry
    parentGeometry=parent->geometry();

    //Set Layout.
    mainLayout=new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    //Set Title Widget
    titleWidget=new KCMessageBoxTitle(this);
    mainLayout->addWidget(titleWidget);
}

void KCMessageBox::startAnime()
{
    //Set the first Animation
    QPropertyAnimation *widthAnime=new QPropertyAnimation(this, "geometry");
    QRect StartGeo=QRect(parentGeometry.x() + parentGeometry.width() / 2,
                         parentGeometry.y() + parentGeometry.height() / 2 - 60,
                         1,
                         120);
    QRect EndGeo=StartGeo;

    qDebug()<<StartGeo.top();

    int nWidth=250;
    //I have no idea why I should set Left First.
    //But...If I don't do this, Width will be so strange.
    EndGeo.setLeft(StartGeo.left() - nWidth / 2);
    EndGeo.setWidth(nWidth);

    widthAnime->setStartValue(StartGeo);
    widthAnime->setEndValue(EndGeo);

    connect(widthAnime, SIGNAL(finished()),
            this, SLOT(heightExpandAnime()));

    widthAnime->start(QAbstractAnimation::DeleteWhenStopped);
}

void KCMessageBox::heightExpandAnime()
{
    QPropertyAnimation *heightAnime=new QPropertyAnimation(this, "geometry");
    QRect StartGeo=this->rect();
    QRect EndGeo=StartGeo;

    int nHeight=150;
    //Just like above.
    EndGeo.setHeight(nHeight);
    EndGeo.setTop(StartGeo.top() - 60);

    qDebug()<<EndGeo.top()<<EndGeo.width();

    heightAnime->setStartValue(StartGeo);
    heightAnime->setEndValue(EndGeo);

    heightAnime->start(QAbstractAnimation::DeleteWhenStopped);
}
