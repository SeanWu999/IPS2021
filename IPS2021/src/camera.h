#ifndef CAMERA_H
#define CAMERA_H

#include <src/myinclude.h>

class Camera
{
public:
    Camera();
    ~Camera();
    void initCamera(size_t cid, queue<Mat> *inputQueue);
    void enumCamera();
    void openCamera(unsigned int deviceId);
    void closeCamera();

    void imageCreater();
    void grabImage();
    void start();
    void stop();

private:
    bool isRunning = false;
    size_t camreaId;
    queue<Mat> *imageQueue;
    Camera *cameraInstance;

    void* handle = NULL;
    unsigned int cameraId = -1;
    int nRet = MV_OK;
    MV_CC_DEVICE_INFO_LIST stDeviceList;
    bool devicesAvailable = false;

    bool PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo);

};

#endif // CAMERA_H
