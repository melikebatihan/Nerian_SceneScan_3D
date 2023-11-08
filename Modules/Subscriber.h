#pragma once

// OpenCV headers must be included first!
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>

#include <open3d/Open3D.h>  // Open3D headers must be included before visiontransfer!

#include "deviceparameters.h"  // FOR TRIGGER!!!
#include "deviceenumeration.h"
#include "asynctransfer.h"
#include "imagetransfer.h"
#include "imageset.h"
#include "reconstruct3d.h"
#include "datachannelservice.h"

#include <iostream>
#include <fstream>
#include <exception>
#include <stdio.h>
#include <vector>
#include <cstdio>
#include <cstring>
#include <thread>

#include <queue>
#include <mutex>
#include <condition_variable>
#include <windows.h>
#include <optional>

using namespace std;
using namespace visiontransfer;

class Subscriber {
public:
	void onEvent(ImageSet publishedFrame);
	virtual void onEvent(cv::Mat publishedFrame);
	virtual void onEvent(shared_ptr<open3d::geometry::RGBDImage> img) {};

protected:
	bool isOpenCVFrame = false;
	ImageSet newFrame;
	cv::Mat openCvFrame;
	mutex mtx;
	queue<ImageSet> frameQueue;
	condition_variable condition;
};
