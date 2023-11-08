#pragma once
#include "Publisher.h"
#include <optional>

class FrameGrabber : public Publisher {
private:
    ImageSet frame;
    AsyncTransfer *transferObj;

    // Create an OpenCV VideoCapture object to capture video from the default camera
    cv::VideoCapture cap;
public:   
    DeviceEnumeration::DeviceList devices;
    FrameGrabber();
    void grabFrame();
};

