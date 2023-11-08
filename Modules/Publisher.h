#pragma once
#include "Subscriber.h"

// Forward declaration of Subscriber
//class Subscriber;

class Publisher {
protected:
    std::vector<Subscriber*> subscribers;
    std::condition_variable condition;

public:
    void addSubscriber(Subscriber* subscriber);
    void publish(ImageSet newframe);
    void publish(cv::Mat newframe);
    void publish(std::shared_ptr<open3d::geometry::RGBDImage> img);
};



