#ifndef MESSAGE_H
#define MESSAGE_H

#include <src/myinclude.h>

class Message
{
public:
    Message();
    ~Message();
    void init_coil_addrs(vector<int> addrs);
    int writeModbusBatch(const char *ip_address, int port, vector<string> labels);
    void freeModbus();

private:
    modbus_t *ctx;
    vector<int> coil_addrs;
};

#endif // MESSAGE_H
