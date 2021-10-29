#ifndef MESSAGE_H
#define MESSAGE_H

#include <src/myinclude.h>

class Message
{
public:
    Message(vector<queue<string>> *inputQueueList, const char *plcIp, int plcPort);
    ~Message();
    void init_coil_addrs(vector<int> addrs);
    int writeModbusBatch(const char *ip_address, int port, vector<string> labels);
    void runSending();
    void freeModbus();
    void start();
    void stop();

private:
    modbus_t *ctx;
    vector<int> coil_addrs;
    vector<queue<string>> *resultQueueList;
    bool isRunning = false;

    const char *ip_address;
    int port;

};

#endif // MESSAGE_H
