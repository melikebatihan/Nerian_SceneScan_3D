#include "Publisher.h"

void Publisher::addSubscriber(Subscriber* subscriber) {
    subscribers.push_back(subscriber);
}

void Publisher::publish(ImageSet newframe) {
    for (Subscriber* subscriber : subscribers) subscriber->onEvent(newframe);
    //condition.notify_all();
}

void Publisher::publish(cv::Mat newframe) {
    for (Subscriber* subscriber : subscribers) subscriber->onEvent(newframe);
    //condition.notify_all();
}

void Publisher::publish(std::shared_ptr<open3d::geometry::RGBDImage> img) {
    for (Subscriber* subscriber : subscribers) subscriber->onEvent(img);
}