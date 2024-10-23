/* tracker.cpp */
#include "tracker.hpp"
#include <cmath>
#include <string>
#include <sstream>

// Constructor to initialize Tracker parameters.
Tracker::Tracker(float height, float focal_length, float hfov, float vfov, std::vector<int> resolution, float pixel_size)
    : height_{height}, focal_length_{focal_length}, hfov_{hfov}, vfov_{vfov}, resolution_{resolution}, pixel_size_{pixel_size} {}

// Destructor.
Tracker::~Tracker() {}

// Converts degrees to radians.
float Tracker::degreesToRadians(float degrees) {
    return degrees * M_PI / 180.0;
}

// Converts radians to degrees.
float Tracker::radiansToDegrees(float radians) {
    return radians * (180.0 / M_PI);
}

// Converts prediction pixels to camera frame coordinates.
std::vector<std::vector<float>> Tracker::pixelToCameraFrame(const std::vector<cv::Point>& prediction_pixels) {
    std::vector<std::vector<float>> coordinates;
    for (const auto& pixel : prediction_pixels) {
        // Stub implementation 
        coordinates.push_back({0.0f, 0.0f, 0.0f});
    }
    return coordinates;
}

// Plots the coordinates on the given frame.
cv::Mat Tracker::plotCoordinates(const std::vector<cv::Point>& prediction_pixels, const std::vector<std::vector<float>>& coordinates, cv::Mat& frame) {
    for (size_t i = 0; i < prediction_pixels.size(); ++i) {
        cv::Point pt = prediction_pixels[i];
        cv::circle(frame, pt, 3, cv::Scalar(0, 255, 0), 2);
        // Stub implementation 
        std::string text = "(x, y, z)";
        cv::putText(frame, text, pt, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(125, 246, 55), 1);
    }
    return frame;
}
