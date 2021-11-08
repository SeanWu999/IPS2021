#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <src/detector.h>
#include <src/camera.h>
#include <src/myinclude.h>
#include <src/message.h>

//MCamera: address to Camera
typedef Camera *MCamera;

class MainController
{
public:
    MainController();
    ~MainController();
    void threadsStart();
    void threadsStop();

private:
    void initConnect();
    void deleteConnect();
    void initController();
    void initDetector();
    void initCamera();
    void initMessage();

    Detector *myDetector;
    Message *myMessage;
    vector<queue<Mat>> imgQueuePtrList;
    vector<queue<string>> resultQueueList;
    MCamera myCameraPtr[CHANNEL_NUMBER];
    bool plcConnectFlag = false;
    const char *ip;
    int port;

};

#endif // MAINCONTROLLER_H
