#include <opencv2/opencv.hpp>
#include "detector.hpp"
#include "tracker.hpp"

int main(int argc, char** argv) {
    if (argc != 5) {
        std::cerr << "Usage: ./shell-app <model_path> <class_names_path> <droidcam_ip> <droidcam_port>" << std::endl;
        return -1;
    }

    // Parse arguments.
    std::string model_path = argv[1];
    std::string class_names_path = argv[2];
    std::string droidcam_ip = argv[3];
    std::string droidcam_port = argv[4];

    // Construct the DroidCam URL.
    std::string droidcam_url = "http://" + droidcam_ip + ":" + droidcam_port + "/video"; // Adjust the path if necessary.

    // Create a Detector instance.
    Detector detector(model_path, class_names_path);

    // Tracker parameters.
    float height = 0.65;  // Height of camera from the ground in meters.
    float focal_length = 0.00425;  // Focal length in meters (example value).
    float hfov = 75.0;  // Horizontal field of view in degrees.
    float vfov = 61.0;  // Vertical field of view in degrees.
    float pixel_size = 0.0017;  // Pixel size in meters.
    std::vector<int> resolution = {640, 480};  // Set resolution manually.

    // Create a Tracker instance with the DroidCam URL.
    Tracker tracker(height, focal_length, hfov, vfov, resolution, pixel_size, droidcam_url);

    // Ensure capture is initialized.
    if (!tracker.initializeCapture()) {
        std::cerr << "Error: Could not initialize capture from DroidCam." << std::endl;
        return -1;
    }

    while (true) {
        // Capture frame-by-frame from DroidCam.
        cv::Mat frame;
        if (!tracker.captureFrame(frame)) {
            std::cerr << "Error: Failed to capture frame from DroidCam!" << std::endl;
            break;  // Break the loop if the frame is not captured successfully.
        }

        if (frame.empty()) {
            std::cerr << "Error: Empty frame captured!" << std::endl;
            break;  // Break the loop if the frame is empty.
        }

        // Perform detection.
        cv::Mat output_image = detector.Detect(frame);

        // Assume predictions are returned as bounding boxes; extract their center points.
        std::vector<cv::Point> prediction_pixels;
        std::vector<cv::Rect> bounding_boxes = detector.GetBoundingBoxes();

        // Extract the center points from each bounding box.
        for (const auto& box : bounding_boxes) {
            int center_x = box.x + box.width / 2;
            int center_y = box.y + box.height / 2;
            prediction_pixels.emplace_back(center_x, center_y);
        }

        // Convert pixel coordinates to camera frame.
        std::vector<std::vector<float>> coordinates = tracker.pixelToCameraFrame(prediction_pixels);

        // Plot coordinates on the frame.
        output_image = tracker.plotCoordinates(prediction_pixels, coordinates, output_image);

        // Display the resulting frame.
        cv::imshow("DroidCam Detection and Tracking", output_image);

        // Break the loop if 'Esc' key is pressed.
        char key = static_cast<char>(cv::waitKey(1));
        if (key == 27) {  // ASCII code for 'Esc' key is 27.
            break;
        }
    }

    // Release the resources.
    cv::destroyAllWindows();

    return 0;
}
