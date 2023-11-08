#pragma once
#include "Publisher.h"

using namespace cv;

class DetectionMod : public Subscriber , public Publisher {
private:
    Ptr<FaceDetectorYN> detector;
    map<string, std::vector<Mat>> detectedPeople;
    Ptr<FaceRecognizerSF> faceRecognizer;
    TickMeter tm;
    int personCounter = 1;
    float scale = 1.0;
    double cosine_similar_thresh = 0.363;
    double l2norm_similar_thresh = 1.128;

public:   
    DetectionMod();  
    void detectAndRecognizeFaces();
    void recognizeBodies() {};
    void detectDimensions() {};

   
    // Initialize FaceDetectorYN
    

};