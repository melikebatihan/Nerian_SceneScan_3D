#include "ReconstructionMod.h"

void ReconstructionMod::captureDepthMap() {
    if (isOpenCVFrame) {
        printf("A depth-sensing camera is needed to capture Depth Map. Ending the session..");
        Sleep(3000);

        // Save the depth map as an image in PNG format.
        //cv::Mat depthImage(imageSet.getHeight(), imageSet.getWidth(), CV_8UC1); // Convert depth values to an 8-bit image.
        //normalize(depthMap, depthImage, 0, 255, cv::NORM_MINMAX, CV_8U);
    } else {
        float* zMap = recon3d.createZMap(newFrame);

        // Create an OpenCV Mat to store the depth map
        cv::Mat depthMap(newFrame.getHeight(), newFrame.getWidth(), CV_32FC1, zMap);
        publish(depthMap);

        // Create rgb depth image:
        //std::lock_guard<std::mutex> lock(mtx);
        //(*rgbdImage) = *recon3d.createOpen3DImageRGBD(newFrame); // Get Depth image in RGB. 
        //publish(rgbdImage);
    }
}
    

