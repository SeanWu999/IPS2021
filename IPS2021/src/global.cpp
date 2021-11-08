#include <src/global.h>

void __stdcall ImageCallBackEx(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* cImageQueue)
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

Config readYamlConfig(const string path){
    Config yamls;
    YAML::Node config = YAML::LoadFile(path);
    yamls.port = config["port"].as<int>();
    yamls.ip = config["ip"].as<string>().c_str();
    return yamls;
}

bool file_exists(const std::string& path){
    return (access(path.c_str(), F_OK )!=-1);
}
