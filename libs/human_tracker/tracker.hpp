#ifndef TRACKER_HPP
#define TRACKER_HPP

#include <opencv2/opencv.hpp>
#include <vector>

/**
 * @brief Tracker class to convert pixel coordinates from detection to real-world camera coordinates
 */
class Tracker {
 private:
  float height_;  ///< Height of the camera from the ground.
  float focal_length_;  ///< Focal length of the camera.
  float hfov_;  ///< Horizontal Field of View.
  float vfov_;  ///< Vertical Field of View.
  float pixel_size_;  ///< Pixel size for conversion.
  const std::vector<int> resolution_;  ///< Resolution of the camera.
  cv::VideoCapture cap_;  ///< OpenCV VideoCapture object for the DroidCam stream.

  float degreesToRadians(float degrees);
  float radiansToDegrees(float radians);

 public:
  Tracker(float height, float focal_length, float hfov, float vfov, std::vector<int> resolution, float pixel_size, const std::string& droidcam_url);
  ~Tracker();

  /**
   * @brief Initializes the video capture from DroidCam.
   * @return true if successful, false otherwise.
   */
  bool initializeCapture();

  /**
   * @brief Captures a frame from the DroidCam.
   * @param frame Output frame captured from the DroidCam.
   * @return true if frame captured successfully, false otherwise.
   */
  bool captureFrame(cv::Mat& frame);

  /**
   * @brief Converts pixel coordinates from detection to camera coordinate frame.
   * @param prediction_pixels Coordinates from detection.
   * @return 3D coordinates relative to camera.
   */
  std::vector<std::vector<float>> pixelToCameraFrame(const std::vector<cv::Point>& prediction_pixels);

  /**
   * @brief Plots the coordinates of detected objects on the given frame.
   * @param prediction_pixels Coordinates of the detected objects.
   * @param coordinates 3D coordinates relative to camera.
   * @param frame Frame to draw on.
   * @return Frame with coordinates plotted.
   */
  cv::Mat plotCoordinates(const std::vector<cv::Point>& prediction_pixels, const std::vector<std::vector<float>>& coordinates, cv::Mat& frame);
};

#endif
