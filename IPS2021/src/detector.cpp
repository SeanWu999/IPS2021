#include "detector.h"

Detector::Detector(vector<queue<Mat>> *inputQueuePtrList, vector<queue<string>> *inputResultQueueList):imgPtrList(inputQueuePtrList), resultQueueList(inputResultQueueList){

}

Detector::~Detector(){

}

void Detector::initModel(){
    cout << "init PET Model ..." << endl;
}

void Detector::runInference(){
    int number = 0;
    while(isRunning){
        for(size_t i=0; i<imgPtrList->size(); i++){
            if(imgPtrList->at(i).size() > 0){
                Mat image = imgPtrList->at(i).front();
                imgPtrList->at(i).pop();
                /*
                   ***************************
                   *** inference code here ***
                   ***************************
                */
                cout << "Queue " << i << " inferencing ...... left: " << imgPtrList->at(i).size() << endl;
                number ++;
                imwrite("./save/" + to_string(number) + ".jpg",image);
                string label = "";
            }
        }

        usleep(100 * 1000);
    }

    // release all left images
    for(size_t i=0; i<imgPtrList->size(); i++){
        if(imgPtrList->at(i).size() > 0){
            imgPtrList->at(i).pop();
        }
    }

}

void Detector::start(){
    cout << "start inference work ......" << endl;
    isRunning = true;
    thread t(&Detector::runInference,this);
    t.detach();
}

void Detector::stop(){
    cout << "stop inference work ......" << endl;
    isRunning = false;
}

void Detector::release(){

}
