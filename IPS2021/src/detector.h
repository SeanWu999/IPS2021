#ifndef DETECTOR_H
#define DETECTOR_H

#include <src/myinclude.h>

class Detector
{
public:
    Detector(vector<queue<Mat>> *inputQueuePtrList, vector<queue<string>> *inputResultQueueList);
    ~Detector();

    void initModel();
    void runInference();
    void start();
    void stop();
    void release();

private:
    bool isRunning = false;
    vector<queue<Mat>> *imgPtrList;
    vector<queue<string>> *resultQueueList;

};

#endif // DETECTOR_H
