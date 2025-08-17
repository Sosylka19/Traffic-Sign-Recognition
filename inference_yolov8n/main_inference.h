#ifndef MAIN_INFERENCE_H
#define MAIN_INFERENCE_H
#include <opencv2/opencv.hpp>
#include <filesystem>
#include "inference.h"

cv::Mat DetectTest(std::filesystem::path img_path);
int ReadCocoYaml(YOLO_V8*& p);
cv::Mat Detector(YOLO_V8*& p, std::filesystem::path image_path);

#endif 