#ifndef DETECTOR_HPP
#define DETECTOR_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <string>
#include <vector>


class Detector {
 public:

  Detector(const std::string& model_path, const std::string& class_names_path);


  cv::Mat Detect(const cv::Mat& input_image);

 private:
  cv::dnn::Net net_;  ///< The deep learning model.
  std::vector<std::string> class_names_;  ///< Class names for object detection.

  cv::Mat PreProcess(const cv::Mat& input_image);


  cv::Mat PostProcess(cv::Mat& input_image, const std::vector<cv::Mat>& outputs);

 
  void DrawLabel(cv::Mat& input_image, const std::string& label, int left, int top);
};

#endif  // DETECTOR_HPP
