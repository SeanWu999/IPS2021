#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <src/detector.h>
#include <src/camera.h>
#include <src/myinclude.h>
#include <src/message.h>
#include <QMainWindow>

//MCamera: address to Camera
typedef Camera *MCamera;

class MainController : public QMainWindow
{
    Q_OBJECT
public:
    MainController();
    ~MainController();
    void initModule();
    void threadsStart();
    void threadsStop();

signals:
    void signal_update_ui_devices(int devices_number);


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
    string model_path;

};

#endif // MAINCONTROLLER_H
