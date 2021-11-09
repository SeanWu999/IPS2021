#ifndef GLOBAL_H
#define GLOBAL_H

#include <src/myinclude.h>

struct Config{
    const char *ip;
    int port;
    std::string model_path;
};

extern void __stdcall BayerImageCallBackEx(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* cImageQueue);
extern void __stdcall BGRImageCallBackEx(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* cImageQueue);
extern Config readYamlConfig(const std::string path);
extern bool file_exists(const std::string& path);
extern int get_camera_number();

#endif // GLOBAL_H
