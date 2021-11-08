#ifndef GLOBAL_H
#define GLOBAL_H

#include <src/myinclude.h>

struct Config{
    const char *ip;
    int port;
};

extern void __stdcall ImageCallBackEx(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* cImageQueue);
extern Config readYamlConfig(const std::string path);
extern bool file_exists(const std::string& path);

#endif // GLOBAL_H
