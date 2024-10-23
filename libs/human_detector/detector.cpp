#include "detector.hpp"
#include <opencv2/opencv.hpp>
#include <fstream>
#include <opencv2/dnn.hpp>
#include <iostream>

using namespace cv;
using namespace dnn;
using namespace std;




Detector::Detector(const string& model_path, const string& class_names_path) {
    // Load YOLO model.

    // Load class names.

}



Mat Detector::PreProcess(const Mat& input_image) {
    // Return the input image as-is
    return cv::Mat();
}


Mat Detector::PostProcess(Mat& input_image, const vector<Mat>& outputs) {

    return input_image;
}



void Detector::DrawLabel(Mat& input_image, const string& label, int left, int top) {
    
}


Mat Detector::Detect(const Mat& input_image) {

    return input_image;

}
