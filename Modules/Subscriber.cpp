#include "Subscriber.h"

void Subscriber::onEvent(ImageSet publishedFrame) {
	//frameQueue.push(publishedFrame);
	publishedFrame.copyTo(newFrame);
}

void Subscriber::onEvent(cv::Mat publishedFrame) {
	openCvFrame = publishedFrame.clone();
	isOpenCVFrame = true;
}
