#include "detector.hpp"
#include <opencv2/opencv.hpp>
#include <fstream>
#include <opencv2/dnn.hpp>
#include <iostream>

using namespace cv;
using namespace dnn;
using namespace std;

// Constants.
const float INPUT_WIDTH = 640.0;
const float INPUT_HEIGHT = 640.0;
const float SCORE_THRESHOLD = 0.5;
const float NMS_THRESHOLD = 0.45;
const float CONFIDENCE_THRESHOLD = 0.45;

const Scalar BLACK = Scalar(0, 0, 0);
const Scalar BLUE = Scalar(255, 178, 50);
const Scalar YELLOW = Scalar(0, 255, 255);
const Scalar RED = Scalar(0, 0, 255);

/**
 * @brief Constructor for the Detector class. Initializes the YOLO model and loads class names.
 * @param model_path Path to the ONNX model file.
 * @param class_names_path Path to the file containing class names.
 */

Detector::Detector(const string& model_path, const string& class_names_path) {
    // Load YOLO model.
    net_ = readNet(model_path);

    // Load class names.
    ifstream ifs(class_names_path);
    string line;
    while (getline(ifs, line)) {
        class_names_.push_back(line);
    }
}

/**
 * @brief Preprocesses the input image by creating a blob to feed into the neural network.
 * @param input_image The image to be preprocessed.
 * @return Blob for neural network input.
 */

Mat Detector::PreProcess(const Mat& input_image) {
    Mat blob;
    blobFromImage(input_image, blob, 1. / 255., Size(INPUT_WIDTH, INPUT_HEIGHT), Scalar(), true, false);
    net_.setInput(blob);
    return blob;
}

/**
 * @brief Postprocesses the neural network output and draws bounding boxes on the input image.
 * @param input_image The image on which bounding boxes will be drawn.
 * @param outputs Output from the YOLO neural network.
 * @return Image with bounding boxes drawn around detected objects.
 */

Mat Detector::PostProcess(Mat& input_image, const vector<Mat>& outputs) {
    bounding_boxes_.clear();  // Clear previous detections
    class_ids_.clear();
    confidences_.clear();

    vector<int> class_ids;
    vector<float> confidences;
    vector<Rect> boxes;
    
    float x_factor = input_image.cols / INPUT_WIDTH;
    float y_factor = input_image.rows / INPUT_HEIGHT;
    
    float* data = (float*)outputs[0].data;
    const int rows = 25200;
    const int dimensions = 85;

    for (int i = 0; i < rows; ++i) {
        float confidence = data[4];
        if (confidence >= CONFIDENCE_THRESHOLD) {
            float* classes_scores = data + 5;
            Point class_id;
            double max_class_score;
            minMaxLoc(Mat(1, class_names_.size(), CV_32FC1, classes_scores), 0, &max_class_score, 0, &class_id);

            // Check if detected class is "human" (class_id 0).
            if (max_class_score > SCORE_THRESHOLD && class_id.x == 0) {
                confidences.push_back(confidence);
                class_ids.push_back(class_id.x);

                float cx = data[0];
                float cy = data[1];
                float w = data[2];
                float h = data[3];

                int left = int((cx - 0.5 * w) * x_factor);
                int top = int((cy - 0.5 * h) * y_factor);
                int width = int(w * x_factor);
                int height = int(h * y_factor);
                boxes.push_back(Rect(left, top, width, height));
            }
        }
        data += dimensions;
    }

    vector<int> indices;
    NMSBoxes(boxes, confidences, SCORE_THRESHOLD, NMS_THRESHOLD, indices);

    for (int i = 0; i < indices.size(); ++i) {
        int idx = indices[i];
        Rect box = boxes[idx];
        bounding_boxes_.push_back(box);  // Store bounding box
        class_ids_.push_back(class_ids[idx]);
        confidences_.push_back(confidences[idx]);

        rectangle(input_image, box, BLUE, 3);
        string label = format("%.2f", confidences[idx]);
        label = class_names_[class_ids[idx]] + ":" + label;
        DrawLabel(input_image, label, box.x, box.y);
    }

    return input_image;
}

/**
 * @brief Draws a label above the detected bounding box.
 * @param input_image The image on which to draw the label.
 * @param label The label to draw.
 * @param left The x-coordinate of the bounding box.
 * @param top The y-coordinate of the bounding box.
 */

void Detector::DrawLabel(Mat& input_image, const string& label, int left, int top) {
    int baseLine;
    Size label_size = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.7, 1, &baseLine);
    top = max(top, label_size.height);
    Point tlc(left, top);
    Point brc(left + label_size.width, top + label_size.height + baseLine);
    rectangle(input_image, tlc, brc, BLACK, FILLED);
    putText(input_image, label, Point(left, top + label_size.height), FONT_HERSHEY_SIMPLEX, 0.7, YELLOW, 1);
}

/**
 * @brief Detects objects in the input image using YOLO and returns the image with bounding boxes.
 * @param input_image The image in which to detect objects.
 * @return The input image with bounding boxes drawn around detected objects.
 */

Mat Detector::Detect(const Mat& input_image) {
    Mat processed_image = input_image.clone();
    vector<Mat> outputs;
    PreProcess(processed_image);
    net_.forward(outputs, net_.getUnconnectedOutLayersNames());
    return PostProcess(processed_image, outputs);
}
// Implementation of GetBoundingBoxes() to retrieve bounding boxes
std::vector<cv::Rect> Detector::GetBoundingBoxes() const {
    return bounding_boxes_;
}


