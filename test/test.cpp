#include <gtest/gtest.h>
#include <memory>
#include <opencv2/opencv.hpp>
#include "detector.hpp"
#include "tracker.hpp"

// Test fixture for the Tracker class.
class TrackerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Initialize the Tracker with test parameters and load an image instead of camera feed
    height = 1.5;             // Example height in meters
    focal_length = 0.5;       // Example focal length in meters
    hfov = 60.0;              // Horizontal field of view in degrees
    vfov = 45.0;              // Vertical field of view in degrees
    resolution = {640, 480};  // Resolution of the camera
    pixel_size = 0.000005;    // Example pixel size in meters
    test_image_path = "../../images/test_image.jpg";  // Path to the test image

    tracker = std::make_unique<Tracker>(height, focal_length, hfov, vfov,
                                        resolution, pixel_size, test_image_path);  // Load test image
  }

  std::unique_ptr<Tracker> tracker;
  float height;
  float focal_length;
  float hfov;
  float vfov;
  std::vector<int> resolution;
  float pixel_size;
  std::string test_image_path;
};

// Test to ensure a frame can be captured from a test image.
TEST_F(TrackerTest, CaptureFrameFromImageTest) {
  cv::Mat frame;
  EXPECT_TRUE(tracker->captureFrame(frame))
      << "Frame should be captured successfully from the test image.";
  EXPECT_FALSE(frame.empty()) << "Captured frame from the test image should not be empty.";
}

// Test to verify pixelToCameraFrame conversion
TEST_F(TrackerTest, PixelToCameraFrameTest) {
  std::vector<cv::Point> prediction_pixels = {cv::Point(320, 240),
                                              cv::Point(100, 200)};
  std::vector<std::vector<float>> coordinates =
      tracker->pixelToCameraFrame(prediction_pixels);

  // Check if the returned coordinates are in the expected range
  for (const auto& coord : coordinates) {
    EXPECT_EQ(coord.size(), 3)
        << "Each coordinate should have 3 dimensions (x, y, z).";
  }
}

// Test to ensure plotting coordinates does not crash
TEST_F(TrackerTest, PlotCoordinatesTest) {
  cv::Mat frame = cv::imread(test_image_path);  // Load the test image
  ASSERT_FALSE(frame.empty()) << "Test image should load successfully.";

  std::vector<cv::Point> prediction_pixels = {cv::Point(320, 240),
                                              cv::Point(100, 200)};
  std::vector<std::vector<float>> coordinates =
      tracker->pixelToCameraFrame(prediction_pixels);

  // Check if the plotting function executes without errors
  EXPECT_NO_THROW({
    cv::Mat plotted_frame =
        tracker->plotCoordinates(prediction_pixels, coordinates, frame);
    EXPECT_FALSE(plotted_frame.empty()) << "Plotted frame should not be empty.";
  });
}

// Test fixture for the Detector class.
class DetectorTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Initialize the detector with dummy paths.
    detector = std::make_unique<Detector>(
        "../../models/yolov5s.onnx",
        "../../models/coco.names");
  }

  std::unique_ptr<Detector> detector;  // Use unique_ptr
};

// Test to ensure the detector is initialized correctly.
TEST_F(DetectorTest, InitializationTest) {
  EXPECT_NE(detector, nullptr) << "Detector should be initialized.";
}

// Test to ensure the input image is loaded correctly.
TEST_F(DetectorTest, LoadInputImageTest) {
  cv::Mat input_image =
      cv::imread(
          "../../images/test_image.jpg");  // Replace with your input image path
  ASSERT_FALSE(input_image.empty())
      << "Input image should be loaded successfully.";

  EXPECT_EQ(input_image.rows,
            408);  // Update based on your expected image dimensions
  EXPECT_EQ(input_image.cols,
            612);  // Update based on your expected image dimensions
}

// Test for the Detect method to check if it returns a valid output.
TEST_F(DetectorTest, DetectReturnsSameImageSize) {
  cv::Mat input_image =
      cv::imread(
          "../../images/test_image.jpg");  // Replace with your input image path
  ASSERT_FALSE(input_image.empty())
      << "Input image should be loaded successfully.";

  cv::Mat result = detector->Detect(input_image);

  // Check that the result image has the same size as the input image.
  EXPECT_EQ(result.rows, input_image.rows);
  EXPECT_EQ(result.cols, input_image.cols);
}

// Test for a valid output from the Detect method (not empty).
TEST_F(DetectorTest, DetectReturnsNonEmptyImage) {
  cv::Mat input_image =
      cv::imread(
          "../../images/test_image.jpg");  // Replace with your input image path
  ASSERT_FALSE(input_image.empty())
      << "Input image should be loaded successfully.";

  cv::Mat result = detector->Detect(input_image);
  EXPECT_FALSE(result.empty()) << "Detection should not return an empty image.";
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
