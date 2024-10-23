#include <opencv2/opencv.hpp>
#include "detector.hpp"

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: ./app <model_path> <class_names_path> <image_path>" << std::endl;
        return -1;
    }

    // Parse arguments.
    std::string model_path = argv[1];
    std::string class_names_path = argv[2];
    std::string image_path = argv[3];

    // Create detector instance.
    Detector detector(model_path, class_names_path);

    // Load image.
    cv::Mat image = cv::imread(image_path);
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return -1;
    }

    // Perform detection.
    cv::Mat output_image = detector.Detect(image);

    // Display output.
    cv::imshow("Detected Image", output_image);
    cv::waitKey(0);

    return 0;
}
