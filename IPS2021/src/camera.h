#ifndef CAMERA_H
#define CAMERA_H

#include <src/myinclude.h>

static void __stdcall ImageCallBackEx(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* cImageQueue)
{

    queue<Mat> *tempImageQueue = (queue<Mat>*)cImageQueue;
    if (pFrameInfo){
        printf("GetOneFrame, Width[%d], Height[%d], nFrameNum[%d]\n", pFrameInfo->nWidth, pFrameInfo->nHeight, pFrameInfo->nFrameNum);
        cv::Mat steamImg(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC3, pData);
        tempImageQueue->push(steamImg);
    }
}

class Camera
{
public:
    Camera();
    ~Camera();
    void initCamera(size_t cid, queue<Mat> *inputQueue);
    void enumCamera();
    void openCamera(unsigned int deviceId);

    void imageCreater();
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

    bool PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo);

};

#endif // CAMERA_H
