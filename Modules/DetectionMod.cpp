#include "DetectionMod.h"

DetectionMod::DetectionMod() {
    try {
        std::string relativePath;
    #ifdef VARNAME
        relativePath = VARNAME;
    #endif
        std::string detectionModel = relativePath + "face_detection_yunet_2023mar.onnx";
        std::string recognitionModel = relativePath + "face_recognition_sface_2021dec.onnx";

        // Initialize Face Detector and Face Recognizer:
        detector = cv::FaceDetectorYN::create(detectionModel, "", Size(1024, 768), 0.9, 0.3, 5000);
        faceRecognizer = cv::FaceRecognizerSF::create(recognitionModel, "");
    } catch (cv::Exception& e) { std::cerr << "OpenCV Exception: " << e.what() << std::endl; }
}

void DetectionMod::detectAndRecognizeFaces() {
    try {
        cv::Mat frame;
        if (isOpenCVFrame) {
            frame = openCvFrame.clone();
        } else newFrame.toOpenCVImage(0, frame);

        // Inference
        Mat faces;
        tm.start();
        detector->detect(frame, faces);
        tm.stop();
        Mat result = frame.clone();

        for (int i = 0; i < faces.rows; i++) {                
               
            Mat aligned_face, feature;
            cv::String name;

            // Aligning and cropping facial image through the first face of faces detected.
            faceRecognizer->alignCrop(frame, faces.row(i), aligned_face);
            // Extract feature with given aligned_face
            faceRecognizer->feature(aligned_face, feature);
            feature = feature.clone();

            if (!detectedPeople.empty()) {
                for (auto person : detectedPeople) {
                    double cos_score = faceRecognizer->match(feature, person.second[1], FaceRecognizerSF::DisType::FR_COSINE);
                    double L2_score = faceRecognizer->match(feature, person.second[1], FaceRecognizerSF::DisType::FR_NORM_L2);

                    /* Cosine Similarity : higher value means higher similarity, max 1.0
                        * NormL2 Distance: lower value means higher similarity, min 0.0 */
                    if (cos_score >= cosine_similar_thresh || L2_score <= l2norm_similar_thresh) {
                        name = person.first;
                        break;
                    }
                }
            }
            if (detectedPeople.empty() || detectedPeople.find(name) == detectedPeople.end()) {
                name = cv::format("Person %d", personCounter);
                std::vector<Mat> val{ faces.row(i), feature };
                detectedPeople[name] = val;
                personCounter++;
            }

                // Draw a bounding box and put label
            cv::rectangle(result, Rect2i(int(faces.at<float>(i, 0)), int(faces.at<float>(i, 1)), int(faces.at<float>(i, 2)), int(faces.at<float>(i, 3))), Scalar(0, 255, 0), 2);
            int labelCoordY = int(faces.at<float>(i, 1)) + int(faces.at<float>(i, 3)) + 15;
            cv::putText(result, name, Point(int(faces.at<float>(i, 0)), labelCoordY), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);

               
        }
        cv::putText(result, cv::format("FPS : %.2f", (float)tm.getFPS()), Point(0, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
        publish(result);
    } 
    catch (const std::exception& ex) { std::cerr << "Exception occurred: " << ex.what() << std::endl; }
}

