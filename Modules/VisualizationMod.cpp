#include "VisualizationMod.h"

VisualizationMod::VisualizationMod() {
    printf("Visualization starts!!!");
    
   // vis.CreateVisualizerWindow("Nerian 3D viewer", 1024, 768);
    //vis.PrintVisualizerHelp();
    //vis.GetRenderOption().SetPointSize(2);
}
void VisualizationMod::onEvent(shared_ptr<open3d::geometry::RGBDImage> img) {
    depth = std::move(img);
    img.reset();
}

void VisualizationMod::onEvent(cv::Mat publishedFrame) {
    cvFrame = publishedFrame;
    openCV = true;
}

void VisualizationMod::display() {
    // Start viewing
    //std::lock_guard<std::mutex> lock(mtx);
    if (!cvFrame.empty()) {
        cv::imshow("Live", cvFrame);
    } 
    int key = cv::waitKey(1);
    if (key == ' ') key = 0;  // handled
    if (key > 0) exit(EXIT_SUCCESS);
    //}
    //if (!vis.HasGeometry()) vis.AddGeometry(depth);
    //vis.UpdateGeometry();
    /*if (!vis.PollEvents()) exit(EXIT_SUCCESS);
    vis.UpdateRender();*/


}
