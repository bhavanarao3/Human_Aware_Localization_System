#include "tracker.hpp"
#include <cmath>
#include <string>
#include <sstream>

Tracker::Tracker(float height, float focal_length, float hfov, float vfov, std::vector<int> resolution, float pixel_size, const std::string& droidcam_url)
    : height_{height}, focal_length_{focal_length}, hfov_{hfov}, vfov_{vfov}, resolution_{resolution}, pixel_size_{pixel_size} {
    // Initialize the capture with the DroidCam RTSP URL
    cap_.open(droidcam_url);
    if (!cap_.isOpened()) {
        throw std::runtime_error("Failed to open the DroidCam stream.");
    }
}

Tracker::~Tracker() {
    cap_.release(); // Release the camera on destruction
}

bool Tracker::initializeCapture() {
    return cap_.isOpened();
}

bool Tracker::captureFrame(cv::Mat& frame) {
    return cap_.read(frame); // Capture a frame from the stream
}

float Tracker::degreesToRadians(float degrees) {
    return degrees * M_PI / 180.0;
}

float Tracker::radiansToDegrees(float radians) {
    return radians * (180.0 / M_PI);
}

std::vector<std::vector<float>> Tracker::pixelToCameraFrame(const std::vector<cv::Point>& prediction_pixels) {
    std::vector<std::vector<float>> coordinates;
    for (const auto& pixel : prediction_pixels) {
        float offset_y = (pixel.y - (static_cast<float>(resolution_[1]) / 2)) * pixel_size_;
        float dip_angle = (vfov_ / 2) - radiansToDegrees(std::atan2(offset_y, focal_length_));
        float z = height_ / std::tan(degreesToRadians((vfov_ / 2) - dip_angle));
        float x_offset = (pixel.x - static_cast<float>(resolution_[0]) / 2) * pixel_size_;
        float x = (x_offset * z) / focal_length_;

        coordinates.push_back({x, height_, z});
    }
    return coordinates;
}

cv::Mat Tracker::plotCoordinates(const std::vector<cv::Point>& prediction_pixels, const std::vector<std::vector<float>>& coordinates, cv::Mat& frame) {
    for (size_t i = 0; i < prediction_pixels.size(); ++i) {
        cv::Point pt = prediction_pixels[i];
        cv::circle(frame, pt, 3, cv::Scalar(0, 255, 0), 2);
        std::string text = "(" + std::to_string(coordinates[i][0]) + ", " + std::to_string(coordinates[i][1]) + ", " + std::to_string(coordinates[i][2]) + ")";
        cv::putText(frame, text, pt, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(125, 246, 55), 1);
    }
    return frame;
}
