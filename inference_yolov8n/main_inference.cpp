#include <iostream>
#include <iomanip>
#include "inference.h"
#include "main_inference.h"
#include <filesystem>
#include <fstream>
#include <random>
#include <QString>
#include <QCoreApplication>

cv::Mat Detector(YOLO_V8*& p, std::filesystem::path image_path)
{
    std::cout << "bla";

    std::string img_path = image_path;
    cv::Mat img = cv::imread(img_path);
    if (image_path.extension() == ".jpg" || image_path.extension() == ".png" || 
    image_path.extension() == ".jpeg")
    {
        std::vector<DL_RESULT> res;
        p->RunSession(img, res);

        for (auto& re: res)
        {
            cv::RNG rng(cv::getTickCount());
            cv::Scalar color(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));

            cv::rectangle(img, re.box, color, 3);

            float confidence = floor(100 * re.confidence) / 100;
            std::cout << std::fixed << std::setprecision(2);
            std::string label = p->classes[re.classId] + " " +
                std::to_string(confidence).substr(0, std::to_string(confidence).size() - 4);

            cv::rectangle(
                img, 
                cv::Point(re.box.x, re.box.y - 25),
                cv::Point(re.box.x + label.length() * 15, re.box.y),
                color,
                cv::FILLED
            );

            cv::putText(
                img, 
                label, 
                cv::Point(re.box.x, re.box.y - 5),
                cv::FONT_HERSHEY_SCRIPT_SIMPLEX,
                0.5,
                cv::Scalar(0, 0, 0),
                1
            );
        }
    }

    return img;
}

int ReadCocoYaml(YOLO_V8*& p)
{
    QString app_dir = QCoreApplication::applicationDirPath();
    QString model_path = app_dir + "/classes.yaml";
    std::ifstream file(model_path.toStdString());
    if (!file.is_open())
    {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::string> lines;
    while(std::getline(file, line))
    {
        lines.push_back(line);
    }

    std::size_t start = 0;
    std::size_t end = 0;
    for (std::size_t i = 0; i < lines.size(); i++)
    {
        if (lines[i].find("names:") != std::string::npos) 
        {
            start = i + 1;
        }
        else if (start > 0 && lines[i].find(':') == std::string::npos)
        {
            end = i;
            break;
        }
    }

    std::vector<std::string> names;
    for (std::size_t i = start; i < end; i++) 
    {
        std::stringstream ss(lines[i]);
        std::string name;
        std::getline(ss, name, ':');
        std::getline(ss, name);
        names.push_back(name);
    }

    p->classes = names;
    return 0;
}

cv::Mat DetectTest(std::filesystem::path img_path)
{
    YOLO_V8* yoloDetector = new YOLO_V8;
    ReadCocoYaml(yoloDetector);
    DL_INIT_PARAM params;
    params.rectConfidenceThreshold = 0.1;
    params.iouThreshold = 0.5;
    QString app_dir = QCoreApplication::applicationDirPath();
    QString model_path = app_dir + "/yolov8n.onnx";
    params.modelPath = model_path.toStdString();
    params.imgSize = { 640, 640 };
#ifdef USE_CUDA
    params.cudaEnable = true;
    params.modelType = YOLO_DETECT_V8;

#else
    params.modelType = YOLO_DETECT_V8;
    params.cudaEnable = false;

#endif
    yoloDetector->CreateSession(params);
    std::cerr << "Model path";
    return Detector(yoloDetector, img_path);
}



// int main()
// {
//     std::filesystem::path pth = "/Users/aleksandrandreev/Downloads/images-6.jpeg";
//     cv::Mat img = DetectTest(pth);
//     cv::imshow("", img);
//     cv::waitKey(0);
//     return 0;
// }
