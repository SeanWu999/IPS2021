#include <src/global.h>

void __stdcall BayerImageCallBackEx(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* cImageQueue)
{
    queue<Mat> *tempImageQueue = (queue<Mat>*)cImageQueue;
    if (pFrameInfo){
        printf("GetOneFrame, Width[%d], Height[%d], nFrameNum[%d]\n", pFrameInfo->nWidth, pFrameInfo->nHeight, pFrameInfo->nFrameNum);
        Mat steamImg(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC1, pData);
        Mat dstImg;
        cvtColor(steamImg,dstImg,CV_BayerRG2BGR);
        tempImageQueue->push(dstImg);
    }
}

void __stdcall BGRImageCallBackEx(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* cImageQueue)
{
    queue<Mat> *tempImageQueue = (queue<Mat>*)cImageQueue;
    if (pFrameInfo){
        printf("GetOneFrame, Width[%d], Height[%d], nFrameNum[%d]\n", pFrameInfo->nWidth, pFrameInfo->nHeight, pFrameInfo->nFrameNum);
        Mat steamImg(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC3, pData);
        tempImageQueue->push(steamImg);
    }
}

Config readYamlConfig(const string path){
    Config yamls;
    YAML::Node config = YAML::LoadFile(path);
    yamls.port = config["port"].as<int>();
    yamls.ip = config["ip"].as<string>().c_str();
    yamls.model_path = config["model_path"].as<string>();
    return yamls;
}

bool file_exists(const std::string& path){
    return (access(path.c_str(), F_OK )!=-1);
}

int get_camera_number(){
    MV_CC_DEVICE_INFO_LIST stDeviceList;
    int nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);

    if (MV_OK != nRet){
        printf("MV_CC_EnumDevices fail! nRet [%x]\n", nRet);
        return -1;
    }else{
        return stDeviceList.nDeviceNum;
    }
}
