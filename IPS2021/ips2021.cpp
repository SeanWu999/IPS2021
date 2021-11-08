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
    if(switch_on){
        cout << "the progress has started ..." << endl;
    }else{
        cout << "ok! clicked START ..." << endl;
        controller->threadsStart();
        switch_on = true;
    }
}

void IPS2021::clickStopButton(){
    if(switch_on){
        cout << "ok! clicked STOP ..." << endl;
        controller->threadsStop();
        switch_on = false;
    }else{
        cout << "the progress has stop ..." << endl;
    }

}


