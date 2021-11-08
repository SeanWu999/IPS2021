#include "maincontroller.h"

MainController::MainController(){
    cout << "init PET controller ..." << endl;
    initController();
    initDetector();
    initCamera();
    initMessage();
}

MainController::~MainController(){

}

void MainController::initConnect(){

}

void MainController::deleteConnect(){

}

void MainController::initController(){
    for(size_t i=0; i<CHANNEL_NUMBER; i++){
        queue<Mat> imgTemp;
        imgQueuePtrList.push_back(imgTemp);

        queue<string> resultTemp;
        resultQueueList.push_back(resultTemp);
    }

    const string configPath = "./config.yaml";
    if(file_exists(configPath)){
        Config myConfig = readYamlConfig(configPath);
        ip = myConfig.ip;
        port = myConfig.port;
    }else{
        exit(1);
    }
}

void MainController::initDetector(){
    myDetector = new Detector(&imgQueuePtrList, &resultQueueList);
    myDetector->initModel();
}

void MainController::initCamera(){
    for(size_t i=0; i<CHANNEL_NUMBER; i++){
        myCameraPtr[i] = new Camera();
        myCameraPtr[i]->initCamera(i,&imgQueuePtrList[i]);
        usleep(1000 * 300);
    }
}

void MainController::initMessage(){
    myMessage = new Message(&resultQueueList, ip, port);
}

void MainController::threadsStart(){
    myDetector->start();
    for(size_t i=0; i<CHANNEL_NUMBER; i++){
        myCameraPtr[i]->start();
    }
    myMessage->start();
}

void MainController::threadsStop(){
    myDetector->stop();
    for(size_t i=0; i<CHANNEL_NUMBER; i++){
        myCameraPtr[i]->stop();
    }
    myMessage->stop();
}
