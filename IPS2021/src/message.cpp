#include "message.h"

Message::Message()
{

}

Message::~Message()
{

}

void Message::init_coil_addrs(std::vector<int> addrs){
    coil_addrs.assign(addrs.begin(), addrs.end());
}


//批量写入plc线圈
int Message::writeModbusBatch(const char *ip_address, int port, std::vector<std::string> labels){
    int rc = 1;
    ctx = NULL;
    ctx = modbus_new_tcp(ip_address, port);
    if (ctx == NULL){
        std::cout << "Unable to allocate libmodbus context" << std::endl;
        return -1;
    }

    if (modbus_connect(ctx) == -1){
        std::cout << "Connection failed: " << modbus_strerror(errno) << std::endl;
        modbus_free(ctx);
        return -1;
    }

    uint8_t modbus_value[MODBUS_WRITE_SIZE];
    for(unsigned int i=0;i<labels.size();i++){
        if(0==labels[i].compare("none")){
            modbus_value[0] = 0;
            modbus_value[1] = 0;
            modbus_value[2] = 0;
            modbus_value[3] = 0;
        }else if(0==labels[i].compare("PET-white")){
            modbus_value[0] = 1;
            modbus_value[1] = 0;
            modbus_value[2] = 0;
            modbus_value[3] = 0;
        }else if(0==labels[i].compare("PET-blue")){
            modbus_value[0] = 0;
            modbus_value[1] = 1;
            modbus_value[2] = 0;
            modbus_value[3] = 0;
        }else if(0==labels[i].compare("PET-green")){
            modbus_value[0] = 1;
            modbus_value[1] = 1;
            modbus_value[2] = 0;
            modbus_value[3] = 0;
        }else if(0==labels[i].compare("PET-orange")){
            modbus_value[0] = 0;
            modbus_value[1] = 0;
            modbus_value[2] = 1;
            modbus_value[3] = 0;
        }else if(0==labels[i].compare("PET-red")){
            modbus_value[0] = 1;
            modbus_value[1] = 0;
            modbus_value[2] = 1;
            modbus_value[3] = 0;
        }else if(0==labels[i].compare("PET-black")){
            modbus_value[0] = 0;
            modbus_value[1] = 1;
            modbus_value[2] = 1;
            modbus_value[3] = 0;
        }else if(0==labels[i].compare("HDPE-white")){
            modbus_value[0] = 1;
            modbus_value[1] = 1;
            modbus_value[2] = 1;
            modbus_value[3] = 0;
        }else if(0==labels[i].compare("HDPE-orange")){
            modbus_value[0] = 0;
            modbus_value[1] = 0;
            modbus_value[2] = 0;
            modbus_value[3] = 1;
        }else if(0==labels[i].compare("HDPE-green")){
            modbus_value[0] = 1;
            modbus_value[1] = 0;
            modbus_value[2] = 0;
            modbus_value[3] = 1;
        }else if(0==labels[i].compare("HDPE-blue")){
            modbus_value[0] = 0;
            modbus_value[1] = 1;
            modbus_value[2] = 0;
            modbus_value[3] = 1;
        }else if(0==labels[i].compare("HDPE-red")){
            modbus_value[0] = 1;
            modbus_value[1] = 1;
            modbus_value[2] = 0;
            modbus_value[3] = 1;
        }else if(0==labels[i].compare("HDPE-black")){
            modbus_value[0] = 0;
            modbus_value[1] = 0;
            modbus_value[2] = 1;
            modbus_value[3] = 1;
        }else{
            modbus_value[0] = 1;
            modbus_value[1] = 0;
            modbus_value[2] = 1;
            modbus_value[3] = 1;
        }

        if(modbus_write_bits(ctx, coil_addrs[i], MODBUS_WRITE_SIZE, modbus_value) < 1){
            std::cout << "ERROR modbus_write_bit  " << rc << std::endl;
            return -1;
        }

        //Reset plc
        modbus_value[0] = 0;
        modbus_value[1] = 0;
        modbus_value[2] = 0;
        modbus_value[3] = 0;
        if(modbus_write_bits(ctx, coil_addrs[i], MODBUS_WRITE_SIZE, modbus_value) < 1){
            std::cout << "ERROR modbus_write_bit  " << rc << std::endl;
            return -1;
        }

    }

    modbus_close(ctx);
    modbus_free(ctx);
    usleep(20 * 1000);
    return 1;

}


void Message::freeModbus(){
    modbus_close(ctx);
    modbus_free(ctx);
}
