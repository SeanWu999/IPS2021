#ifndef MYINCLUDE_H
#define MYINCLUDE_H

#include <iostream>
#include <unistd.h>
#include <thread>
#include <queue>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "MvCameraControl.h"
#include "modbus/modbus.h"

#define MODBUS_WRITE_SIZE 4
#define CHANNEL_NUMBER 2
#define SEND_GAP_TIME 30


using namespace std;
using namespace cv;

#endif // MYINCLUDE_H
