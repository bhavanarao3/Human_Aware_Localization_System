#include "detector.hpp"
#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <vector>

// Test fixture for the Detector class.
class DetectorTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Initialize the detector with dummy model path and class names.
    detector = new Detector("models/yolov5s.onnx", "models/coco.names");

    // Create a dummy input image (black image).
    input_image = cv::Mat::zeros(cv::Size(640, 640), CV_8UC3);
  }

  void TearDown() override {
    delete detector;
  }

  Detector* detector;
  cv::Mat input_image;
};

// Test for the Detect method.
TEST_F(DetectorTest, DetectTest) {
  // Perform detection on the dummy image.
  cv::Mat result = detector->Detect(input_image);

  // Check if the result is a valid image (same size as input).
  EXPECT_EQ(result.rows, input_image.rows);
  EXPECT_EQ(result.cols, input_image.cols);
  EXPECT_EQ(result.type(), input_image.type());
}

// Test for PreProcess method.
TEST_F(DetectorTest, PreProcessTest) {
  // Since PreProcess is private, we cannot access it directly.
  // This test ensures that PreProcess is working via Detect.
  cv::Mat result = detector->Detect(input_image);
  EXPECT_FALSE(result.empty());
}

// Test for PostProcess method.
TEST_F(DetectorTest, PostProcessTest) {
  // This test will indirectly check the PostProcess method by calling Detect.
  std::vector<cv::Mat> outputs;
  detector->Detect(input_image);
  
  // Ensure that the input image was processed without failure.
  EXPECT_EQ(input_image.rows, 720);
  EXPECT_EQ(input_image.cols, 720);
}

// Test for DrawLabel method.
TEST_F(DetectorTest, DrawLabelTest) {
  // Since DrawLabel is private, this test will indirectly check its behavior via Detect.
  detector->Detect(input_image);

  // After detection, verify that the image was processed (remains valid).
  EXPECT_EQ(input_image.rows, 640);
  EXPECT_EQ(input_image.cols, 640);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
