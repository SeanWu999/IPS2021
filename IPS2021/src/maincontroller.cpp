#include "maincontroller.h"

MainController::MainController(){

}

MainController::~MainController(){

}

void MainController::initConnect(){

}

void MainController::deleteConnect(){

}

void MainController::initModule(){
    cout << "init PET controller ..." << endl;
    initController();
    initDetector();
    initCamera();
    initMessage();
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
        model_path = myConfig.model_path;
    }else{
        exit(1);
    }
}

void MainController::initDetector(){
    myDetector = new Detector(&imgQueuePtrList, &resultQueueList);
    myDetector->initRockontrolModel(model_path);
}

void MainController::initCamera(){
    size_t camera_number = get_camera_number();

    for(size_t i=0; i<camera_number; i++){
        myCameraPtr[i] = new Camera();
        myCameraPtr[i]->initCamera(i,&imgQueuePtrList[i]);
        usleep(1000 * 300);
    }

    emit(signal_update_ui_devices(camera_number));
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
