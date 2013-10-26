#include "kcmessagebox.h"

KCMessageBoxTitle::KCMessageBoxTitle(QWidget *parent) :
    QWidget(parent)
{
    QLabel *background=new QLabel(this);
    background->setPixmap(QPixmap(":/MsgBox/image/MessageBox/Title.png"));
    setFixedHeight(background->sizeHint().height());
}

//Message Box Title
KCMessageBox::KCMessageBox(QWidget *parent) :
    QWidget(parent)
{
    //Set properties
    setWindowFlags(Qt::Window |
                   Qt::FramelessWindowHint);
    setMinimumSize(0,0);

    //Set main layout
    mainLayout=new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    //Set title widget
    KCMessageBoxTitle *newTitleWidget=new KCMessageBoxTitle(this);
    mainLayout->addWidget(newTitleWidget);

    //Start width expand animation
    widthExpand=new QPropertyAnimation(this, "geometry");

}
