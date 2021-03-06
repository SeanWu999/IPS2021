#include "camera.h"

Camera::Camera(){

}

Camera::~Camera(){

}

void Camera::initCamera(size_t cid, queue<Mat> *inputQueue){
    camreaId = cid;
    imageQueue = inputQueue;
    enumCamera();
}

void Camera::enumCamera(){
    // 枚举设备
    // enum device
    nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
    if (MV_OK != nRet){
        printf("MV_CC_EnumDevices fail! nRet [%x]\n", nRet);
    }
    if (stDeviceList.nDeviceNum > 0){
        for (unsigned int i = 0; i < stDeviceList.nDeviceNum; i++){
            printf("[device %d]:\n", i);
            MV_CC_DEVICE_INFO* pDeviceInfo = stDeviceList.pDeviceInfo[i];
            //PrintDeviceInfo(pDeviceInfo);
        }
        devicesAvailable = true;
    }else{
        printf("Find No Devices!\n");
        devicesAvailable = false;
    }
}

bool Camera::PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo)
{
    if (NULL == pstMVDevInfo)
    {
        printf("The Pointer of pstMVDevInfo is NULL!\n");
        return false;
    }
    if (pstMVDevInfo->nTLayerType == MV_GIGE_DEVICE)
    {
        int nIp1 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
        int nIp2 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
        int nIp3 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
        int nIp4 = (pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);
        // ch:打印当前相机ip和用户自定义名字 | en:print current ip and user defined name
        printf("Device Model Name: %s\n", pstMVDevInfo->SpecialInfo.stGigEInfo.chModelName);
        printf("CurrentIp: %d.%d.%d.%d\n" , nIp1, nIp2, nIp3, nIp4);
        printf("UserDefinedName: %s\n\n" , pstMVDevInfo->SpecialInfo.stGigEInfo.chUserDefinedName);
    }
    else if (pstMVDevInfo->nTLayerType == MV_USB_DEVICE)
    {
        printf("Device Model Name: %s\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chModelName);
        printf("UserDefinedName: %s\n\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName);
    }
    else
    {
        printf("Not support.\n");
    }
    return true;
}

void Camera::openCamera(unsigned int deviceId){

    cameraId = deviceId;
    nRet = MV_CC_CreateHandle(&handle, stDeviceList.pDeviceInfo[deviceId]);
    if (MV_OK != nRet){
        printf("MV_CC_CreateHandle fail! nRet [%x]\n", nRet);
    }

    // 打开设备
    // open device
    nRet = MV_CC_OpenDevice(handle);
    if (MV_OK != nRet){
        printf("MV_CC_OpenDevice fail! nRet [%x]\n", nRet);
    }

    // ch:探测网络最佳包大小(只对GigE相机有效) | en:Detection network optimal package size(It only works for the GigE camera)
    if (stDeviceList.pDeviceInfo[deviceId]->nTLayerType == MV_GIGE_DEVICE){
        int nPacketSize = MV_CC_GetOptimalPacketSize(handle);
        if (nPacketSize > 0){
            nRet = MV_CC_SetIntValue(handle,"GevSCPSPacketSize",nPacketSize);
            if(nRet != MV_OK){
                printf("Warning: Set Packet Size fail nRet [0x%x]!\n", nRet);
            }
        }else{
            printf("Warning: Get Packet Size fail nRet [0x%x]!\n", nPacketSize);
        }
    }

    // 设置触发模式为on
    // set trigger mode as on
    nRet = MV_CC_SetEnumValue(handle, "TriggerMode", 0);
    if (MV_OK != nRet){
        printf("MV_CC_SetTriggerMode fail! nRet [%x]\n", nRet);
    }

    //设置可调节帧率为on
    nRet = MV_CC_SetEnumValue(handle, "AcquisitionFrameRateMode", 1);
    if (MV_OK != nRet){
        printf("MV_CC_SetAcquisitionFrameRateMode fail! nRet [%x]\n", nRet);
    }

    //设置帧率
    nRet = MV_CC_SetFloatValue(handle, "AcquisitionFrameRate", 1.0);
    if (MV_OK != nRet){
        printf("MV_CC_SetFrameRate fail! nRet [%x]\n", nRet);
    }


    // 设置触发源
    // set trigger source
    /*_MV_CAM_TRIGGER_SOURCE_ triger = MV_TRIGGER_SOURCE_LINE0;
    nRet = MV_CC_SetEnumValue(handle, "TriggerSource", triger);
    if (MV_OK != nRet){
        printf("MV_CC_SetTriggerSource fail! nRet [%x]\n", nRet);
    }*/

    // 设置曝光时间
    // set exposure time

    // 设置延时时间
    // set TriggerDelay time

    // 设置图像像素格式
    // set pixel format

    // 注册抓图回调
    // register image callback
    nRet = MV_CC_RegisterImageCallBackEx(handle, BayerImageCallBackEx, imageQueue);
    if (MV_OK != nRet){
        printf("MV_CC_RegisterImageCallBackEx fail! nRet [%x]\n", nRet);
    }

    // 开始取流
    // start grab image
    nRet = MV_CC_StartGrabbing(handle);
    if (MV_OK != nRet){
        printf("MV_CC_StartGrabbing fail! nRet [%x]\n", nRet);
    }


    while(isRunning){
        sleep(1);
    }

}

void Camera::closeCamera(){
    if(devicesAvailable){
        // 停止取流
        // end grab image
        nRet = MV_CC_StopGrabbing(handle);
        if (MV_OK != nRet){
            printf("MV_CC_StopGrabbing fail! nRet [%x]\n", nRet);
        }

        // 关闭设备
        // close device
        nRet = MV_CC_CloseDevice(handle);
        if (MV_OK != nRet){
            printf("MV_CC_CloseDevice fail! nRet [%x]\n", nRet);
        }

        // 销毁句柄
        // destroy handle
        nRet = MV_CC_DestroyHandle(handle);
        if (MV_OK != nRet){
            printf("MV_CC_DestroyHandle fail! nRet [%x]\n", nRet);
        }

        if (nRet != MV_OK){
            if (handle != NULL){
                MV_CC_DestroyHandle(handle);
                handle = NULL;
            }
        }
    }


}


void Camera::imageCreater(){
    Mat image = imread("/home/sean/wuzhe2/data/coco2017/test2017/000000000665.jpg");

    while(isRunning){
        cout << "CameraId: " << camreaId << " get one image ......." << endl;
        imageQueue->push(image);
        sleep(1);
    }
}

void Camera::grabImage(){
    openCamera(camreaId);
}

void Camera::start(){
    if(devicesAvailable){
        cout << "CameraId: " << camreaId << " start work ......" << endl;
        isRunning = true;
        thread t(&Camera::grabImage,this);
        t.detach();
    }else{
        cout << "CameraId: " << camreaId << " camera start failed ......" << endl;
    }

}

void Camera::stop(){
    cout << "CameraId: " << camreaId << " stop work ......" << endl;
    isRunning = false;
    closeCamera();
}




