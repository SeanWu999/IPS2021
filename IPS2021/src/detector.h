#ifndef DETECTOR_H
#define DETECTOR_H

#include <src/myinclude.h>

class Detector
{
public:
    Detector(vector<queue<Mat>> *imgQueuePtrList);
    ~Detector();

    void initModel();
    void runInference();
    void start();
    void stop();
    void release();

private:
    bool isRunning = false;
    vector<queue<Mat>> *imgPtrList;

};

#endif // DETECTOR_H
