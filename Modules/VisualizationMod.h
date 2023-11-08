#pragma once

#include "Subscriber.h"

class VisualizationMod : public Subscriber {
private:
    bool openCV = false;
    cv::Mat cvFrame;
    shared_ptr<open3d::geometry::RGBDImage> depth;
    open3d::visualization::Visualizer vis;

public:
    VisualizationMod();
    void onEvent(shared_ptr<open3d::geometry::RGBDImage> img) override;
    void onEvent(cv::Mat publishedFrame) override;
    void display();

};

