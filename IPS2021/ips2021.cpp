#include "ips2021.h"
#include "ui_ips2021.h"

IPS2021::IPS2021(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IPS2021)
{
    ui->setupUi(this);
    initConnect();
    init();
}

IPS2021::~IPS2021(){
    deleteConnect();
    delete ui;
}

void IPS2021::initConnect(){
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(clickStartButton()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(clickStopButton()));
}

void IPS2021::deleteConnect(){
    disconnect(ui->startButton, SIGNAL(clicked()), this, SLOT(clickStartButton()));
    disconnect(ui->stopButton, SIGNAL(clicked()), this, SLOT(clickStopButton()));
}

void IPS2021::initForm(){

}

void IPS2021::init(){
    controller = new MainController();
}

void IPS2021::clickStartButton(){
    cout << "ok! clicked START ..." << endl;
    controller->threadsStart();
}

void IPS2021::clickStopButton(){
    cout << "ok! clicked STOP ..." << endl;
    controller->threadsStop();
}


