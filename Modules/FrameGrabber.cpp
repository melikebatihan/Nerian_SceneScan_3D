#include "FrameGrabber.h"

FrameGrabber::FrameGrabber() {

		// Search for Nerian stereo devices
		DeviceEnumeration deviceEnum;
		devices = deviceEnum.discoverDevices();

		if (devices.size() == 0) { //throw std::exception("No devices discovered!");
			cap.open(0); // Initialize the default camera (index 0)	

			if (!cap.isOpened()) {
				std::cerr << "Error: Could not open the camera." << std::endl;
				exit(EXIT_FAILURE);
			}
		} else {
			//AsyncTransfer obj(devices[0]);
			//transferObj = &obj;
			// Print devices
			cout << "Discovered devices:" << endl;
			for (unsigned int i = 0; i < devices.size(); i++) cout << devices[i].toString() << endl;
			Sleep(5000);
		}
}

void FrameGrabber::grabFrame() {
	if (cap.isOpened()) {
		cv::Mat frame;
		cap >> frame;  // Capture a frame from the webcam

		if (frame.empty()) {
			std::cerr << "Error: Video stream ended." << std::endl;
			exit(EXIT_FAILURE);
		}
		publish(frame);
	}
	else {
		AsyncTransfer obj(devices[0]);
		// loop until a frame is captured.
		while (!obj.collectReceivedImageSet(frame, 0.1 /*timeout*/));
		publish(frame);
	}
}