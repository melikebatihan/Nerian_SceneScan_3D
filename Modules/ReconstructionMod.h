#pragma once

//#include "Subscriber.h"
#include "Publisher.h"


class ReconstructionMod : public Subscriber, public Publisher {
private:
    Reconstruct3D recon3d;

    // There has to be a shared pointer, otherwise the video stream is freezing.
    std::shared_ptr<open3d::geometry::RGBDImage> rgbdImage;
public:
    ReconstructionMod() : rgbdImage(std::make_shared<open3d::geometry::RGBDImage>()) {}
    void captureDepthMap();
    
};

