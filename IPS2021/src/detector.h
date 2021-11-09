#ifndef DETECTOR_H
#define DETECTOR_H

#include <src/myinclude.h>

typedef long int(* ModelInitHandle)();
typedef void (* GetModelDescHandle)(const long int, char []);
typedef int (* ModelDeinitHandle)(const long int);
typedef int (* ModelProcessHandle)(const long int,const unsigned char [], const int, char []);

class Detector
{
public:
    Detector(vector<queue<Mat>> *inputQueuePtrList, vector<queue<string>> *inputResultQueueList);
    ~Detector();

    void initRockontrolModel(string model_path);
    void runInference();
    void start();
    void stop();
    void release();

private:
    bool isRunning = false;
    vector<queue<Mat>> *imgPtrList;
    vector<queue<string>> *resultQueueList;

    ModelInitHandle model_init_ptr;
    ModelDeinitHandle model_deinit_ptr;
    ModelProcessHandle model_process_ptr;
    GetModelDescHandle model_desc_ptr;

    long int handle;
    std::string net_type;
    std::string model_type;
    int batch_size;
    std::string img_format;
    float pet_threshold;

    int input_channel;
    int input_height;
    int input_width;
    int buffer_size;

    unsigned char* input_buffer;

};

#endif // DETECTOR_H
