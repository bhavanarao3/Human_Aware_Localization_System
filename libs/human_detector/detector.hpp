#ifndef DETECTOR_HPP
#define DETECTOR_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <string>
#include <vector>

/**
 * @brief Class to handle YOLOv5-based object detection.
 */
class Detector {
 public:
  /**
   * @brief Constructor to load the YOLO model and class names.
   * @param model_path Path to the YOLO ONNX model.
   * @param class_names_path Path to the file containing class names.
   */
  Detector(const std::string& model_path, const std::string& class_names_path);

  /**
   * @brief Method to perform object detection on an image.
   * @param input_image The input image on which to perform detection.
   * @return Image with bounding boxes drawn.
   */
  cv::Mat Detect(const cv::Mat& input_image);

 private:
  cv::dnn::Net net_;  ///< The deep learning model.
  std::vector<std::string> class_names_;  ///< Class names for object detection.

  /**
   * @brief Preprocesses the image for YOLO input.
   * @param input_image The input image.
   * @return The blob from the image.
   */
  cv::Mat PreProcess(const cv::Mat& input_image);

  /**
   * @brief Post-process the network's output.
   * @param input_image The original image.
   * @param outputs The network's output.
   * @return The image with bounding boxes drawn.
   */
  cv::Mat PostProcess(cv::Mat& input_image, const std::vector<cv::Mat>& outputs);

  /**
   * @brief Draws the bounding box and label on the image.
   * @param input_image The image to draw on.
   * @param label The label text to draw.
   * @param left The x-coordinate of the top-left corner.
   * @param top The y-coordinate of the top-left corner.
   */
  void DrawLabel(cv::Mat& input_image, const std::string& label, int left, int top);
};

#endif  // DETECTOR_HPP
