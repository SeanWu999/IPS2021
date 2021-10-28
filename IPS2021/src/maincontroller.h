#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <src/detector.h>
#include <src/camera.h>
#include <src/myinclude.h>

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

    Detector *myDetector;
    vector<queue<Mat>> imgQueuePtrList;
    MCamera myCameraPtr[CHANNEL_NUMBER];

};

#endif // MAINCONTROLLER_H
