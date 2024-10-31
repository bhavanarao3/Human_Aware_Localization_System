
# Human_Aware_Localization_System
ENPM700-MidTerm Project

# C++ Boilerplate v2 Badges
![CICD Workflow status](https://github.com/bhavanarao3/Human_Aware_Localization_System/actions/workflows/run-unit-test-and-upload-codecov.yml/badge.svg) [![codecov](https://codecov.io/gh/bhavanarao3/Human_Aware_Localization_System/graph/badge.svg?token=8o7v3LGmTM)](https://codecov.io/gh/bhavanarao3/Human_Aware_Localization_System) [![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

| Role / Part | Phase 1                   | Phase 2                 |
|-------------|---------------------------|-------------------------|
| Driver      | Bhavana B Rao             |Sri ram Prasad Kothapalli|
| Navigator   | Sri ram Prasad Kothapalli |Bhavana B Rao            |


A robust perception stack fot human detection and localization for autonomous vehicles 
THis repository contains deliverables for midterm project of Bhavana B Rao and Sriramprasad Kothapalli as a part of the course ENPM700: Software Development for Robotics at the University of Maryland.

## Phase 2

### Project Overview 
We introduce HALS (Human-Aware Localization System), a perception system developed for Acme Robotics’ autonomous vehicle fleet. HALS equips these vehicles with the capability to detect and localize humans moving in their path, ensuring safe and efficient navigation through pedestrian environments, such as sidewalks, while autonomously delivering packages to residences.

HALS achieves this functionality through its two core components: an object detector and an object tracker. The object detector employs a YOLO v5 model to recognize human presence within any camera’s field of view (FOV), while the object tracker leverages these detections to determine the human’s relative position to the vehicle’s camera using advanced geometric computer vision methods. To maintain accuracy, HALS operates under the assumption of a known fixed height for the camera relative to the ground.

HALS demonstrates high performance and reliability, even in CPU-bound environments, offering real-time human detection and localization with impressive precision. For demonstration purposes, HALS has been tested using the front camera of an iPhone 15 Pro, allowing easy replication of the demo setup on personal devices for hands-on testing and exploration.

### AIP WOrkflow
This project was developed using the Agile Development Process (AIP) along with pair programming (with a driver and navigator), with a focus on test-driven development (TDD). This sheet has the product backlog, iteration backlogs, and work log for each task done to develop HALS. The end of each iteration is even tagged to distinguish each sprint. Further, the link to the sprint planning and review meeting notes devised to overview each iteration sprint to develop HALS in the most efficient way possible is attached [here](https://docs.google.com/spreadsheets/d/1BkUKRTix_gpAeI8nEOIU-Vc7oSzQCU-JUhH3wqEv24I/edit?gid=0#gid=0).

A short video providing a brief overview of the project and the details explaining the AIP process used is embedded below. A direct link to the same can also be found [here]()

### Libraries used 

This project leverages the OpenCV library for a range of essential computer vision functionalities and tools. Additionally, HALS incorporates a YOLO v5 model, a deep-learning-based object detection system initially developed by Joseph Redmon . This model enables HALS to detect humans in real time from a continuous video feed, with further tracking achieved through specialized algorithms. The YOLO v5 model is accessed in its ONNX format, converted from a YOLO v5s model trained in PyTorch.

Each of these libraries is fundamental to HALS’s operation. OpenCV handles a variety of image processing tasks—such as resizing, reshaping, scaling, and formatting—crucial for pre-processing and managing video data. YOLO v5, a benchmark for object detection, provides accurate human localization capabilities, which HALS then uses to estimate the exact position of detected humans relative to the camera. Using the YOLO v5 model in ONNX format streamlines compatibility and provides flexibility for handling outputs in object detection tasks. Together, these tools form the backbone of HALS’s robust and efficient detection and localization system.
### Demo Output 
![Screenshot 2024-10-30 23:26:28](https://github.com/user-attachments/assets/25dc68aa-8391-4ae8-9343-b637d2e0aee8)
### Building and Running the Code
To install the dependencies for this project (ONNX and OpenCV), simply run the command below on an Ubuntu system (confirmed to work on Ubuntu 22.04).

```bash
# Install OpenCV with root privileges (has the required headers for ONNX as well):
  sudo apt install libopencv-dev
```
Before running any component of HALS, make sure you are in the main working directory. To build the project, execute the following commands.
```bash
# Create all the make files:
  cmake -S ./ -B build/
# Compile and build the code to the 'build' directory from scratch:
  cmake --build build/ --clean-first
# [When done with HDAL/need to rebuild] Clean the 'build' directory:
  cmake --build build/ --target clean
# [When done with HDAL/need to rebuild] Delete the 'build' directory:
  rm -rf build/
```
To generate and view the Doxygen documentation of the project, run the following commands.
```bash
# Build the documentation into the 'docs' directory using CMake:
  cmake --build build/ --target docs
# Open the documentation as a HTML file in your web browser:
  open docs/html/index.html
```

To run the program use the following command 
```
"Usage: ./shell-app <model_path> <class_names_path> "
                 "<droidcam_ip> <droidcam_port>"
```
where ```model_path``` refers to the yolo.onx model and ```class_name``` refers to the coco.names folder and ```droidcam_ip``` and ```driodcam_port``` refer to the camera hardware 

Example usage is shown below 
```bash
./build/app/shell-app models/yolov5s.onnx models/coco.names 10.0.0.116 4747
```

To run the unit tests and verify the working of the unit tests for HALS, execute the commands below.
```bash
# Manually run the unit tests:
  ctest --test-dir build/
```

### Test Coverage 
This section shows how to configure the code to enable code coverage. Note that this information can also be viewed in the code coverage report which can be accessed by clicking the codecov badge at the top of this file. Otherwise, you can build the report manually and view the HTML file in a web browser by running the commands below.

```bash
# If you don't have gcovr or lcov installed, run:
  sudo apt-get install gcovr lcov
# Set the build type to Debug and WANT_COVERAGE=ON:
  cmake -D WANT_COVERAGE=ON -D CMAKE_BUILD_TYPE=Debug -S ./ -B build/
# Do a clean compile, run unit test, and generate the coverage report:
  cmake --build build/ --clean-first --target all test_coverage
# Open a web browser to browse the test coverage report:
  open build/test_coverage/index.html
```

You can also get a code coverage report for the shell-app target, instead of the unit tests. To do so, repeat the previous two steps, but with the app_coverage target:

```bash
# Do another clean compile, run shell-app, and generate its coverage report:
  cmake --build build/ --clean-first --target all app_coverage
# Open a web browser to browse the test coverage report:
  open build/app_coverage/index.html
```

### Google COding Style 
To check how the written code conforms to the Google C++ style guide, look at the ```results/cpplint_output.png``` and file to see the output on using the Cpplint tool on this project. You should not be able to see any issues or problems, with all the files processed successfully.

This can be self-verified as well by running the following command in the highest-level directory of the project.
```bash
# Install Cpplint(ignore if already installed):
  sudo apt install cpplint
# Self-check Google code style conformity using Cpplint:
cpplint --fillter="-legal/copyright" $( find . -nam *.cpp | grep -v "/build/" )
```
## Phase 1

Phase 1 involves setting up the directory structure for the project, adding license and CI/CD badge. The .pt weight file for YOLOv5 is converted to .onnx file so that it is compatible with C++. 

The video explaining the Phase 1 status of the API process is as given: [Video](https://www.canva.com/design/DAGUb85ULqw/5sof80gLWsIjkFBiL5oSjw/view?utm_content=DAGUb85ULqw&utm_campaign=designshare&utm_medium=link&utm_source=recording_view)

## Phase 0

- Driver: Bhavana B Rao
- Navigator: Sriram Kothapalli

This project aims to design and develop a Human Aware Localization Module for Acme's autonomous robotic systems. Phase 0 involves proposing the design, the work flow, and the software development process for the project.

The proposal document and QuadChart is located in the proposal directory. The proposal document outlines the design and development of the HALS system. It discusses the design process, technologies, and algorithms that will be used, along with the testing and validation steps. It also identifies potential risks and mitigation strategies, ensuring a clear path toward high-quality deliverables. Additionally, the document describes the team's structure, pair programming approach, and final deliverables.

The quadchart is a concise, one-page graphical summary used to present key information about a project or proposal. It is divided into four quadrants, including sections such as project objectives, technical approach, activity diagram, and the schedule. This format is designed to provide decision-makers with a clear, high-level overview of the project at a glance.

Additionally a short video discussing the project overview, proposed design and methodology is as below:
[Video](https://www.canva.com/design/DAGTmxytqVQ/002m6bJGIoaTDRKGFH7m0Q/view?utm_content=DAGTmxytqVQ&utm_campaign=share_your_design&utm_medium=link&utm_source=shareyourdesignpanel)

![image](https://github.com/user-attachments/assets/22ce6b5f-0727-4427-b450-d9db92c255a9)

The initial product backlog is linked here: [Product Backlog](https://docs.google.com/spreadsheets/d/1BkUKRTix_gpAeI8nEOIU-Vc7oSzQCU-JUhH3wqEv24I/edit?usp=sharing)




