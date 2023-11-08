#include "Scan3D.h"

int main() {
    // Create instances of the modules
    FrameGrabber frameGrabber;
    ReconstructionMod reconstructor;
    DetectionMod detector;
    VisualizationMod visualizer;


    // Subscribe modules to events
    frameGrabber.addSubscriber(&reconstructor);
    frameGrabber.addSubscriber(&detector);

    reconstructor.addSubscriber(&visualizer);
    detector.addSubscriber(&visualizer);
    
    while (true) {
        frameGrabber.grabFrame();
        //reconstructor.captureDepthMap();
        detector.detectAndRecognizeFaces();
        visualizer.display();
        // Create and start threads for each module
        //std::thread threadInput(&FrameGrabber::grabFrame, &frameGrabber);
        //std::thread threadDepth(&ReconstructionMod::captureDepthMap, &reconstructor);
        //std::thread threadFaceDetection(&DetectionMod::detectDimensions, &detector);
        //std::thread threadFaceRecognition(&DetectionMod::recognizeFaces, &detector);
        //std::thread threadBodyRecognition(&DetectionMod::recognizeBodies, &detector);
        //std::thread threadVisualization(&VisualizationMod::display, &visualizer);

        // Join threads
        //threadInput.join();
        //threadDepth.join();
        //threadFaceDetection.join();
        //threadFaceRecognition.join();
        //threadBodyRecognition.join();
        //threadVisualization.join();
    }
    return 0;
}
