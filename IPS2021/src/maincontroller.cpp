#include "maincontroller.h"

MainController::MainController(){
    cout << "init PET controller ..." << endl;
    initController();
    initDetector();
    initCamera();
}

MainController::~MainController(){

}

void MainController::initConnect(){

}

void MainController::deleteConnect(){

}

void MainController::initController(){
    for(size_t i=0; i<CHANNEL_NUMBER; i++){
        queue<Mat> temp;
        imgQueuePtrList.push_back(temp);
    }
}

void MainController::initDetector(){
    myDetector = new Detector(&imgQueuePtrList);
    myDetector->initModel();
}

void MainController::initCamera(){
    for(size_t i=0; i<CHANNEL_NUMBER; i++){
        myCameraPtr[i] = new Camera();
        myCameraPtr[i]->initCamera(i,&imgQueuePtrList[i]);
        usleep(1000 * 300);
    }


}

void MainController::threadsStart(){
    myDetector->start();
    for(size_t i=0; i<CHANNEL_NUMBER; i++){
        myCameraPtr[i]->start();
    }
}

void MainController::threadsStop(){
    myDetector->stop();
    for(size_t i=0; i<CHANNEL_NUMBER; i++){
        myCameraPtr[i]->stop();
    }
}
