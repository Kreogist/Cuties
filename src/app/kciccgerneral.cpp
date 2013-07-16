#include "kciccgerneral.h"
#include "ui_kciccgerneral.h"

kciCCGerneral::kciCCGerneral(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::kciCCGerneral)
{
    ui->setupUi(this);
}

kciCCGerneral::~kciCCGerneral()
{
    delete ui;
}
