#include "ips2021.h"
#include "ui_ips2021.h"

IPS2021::IPS2021(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IPS2021)
{
    ui->setupUi(this);
}

IPS2021::~IPS2021()
{
    delete ui;
}

