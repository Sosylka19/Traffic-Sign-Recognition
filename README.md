## Project struct

### Description


### Getting started


#### 1. Prerequisities

1. [Download ONNXRuntime from here](https://github.com/microsoft/onnxruntime/releases)
   - Unpack in `C:/` on Windows
   - Unpach in `usr/local/` on MacOS/Linux

2. [Download Docker from official source](https://www.docker.com)

3. [Download QT from official source](https://www.qt.io/download-dev)

#### 2. Installation

1. Make directory for project

    ```bash
    mkdir sign_detection && cd sign_detection
    ```  
2. Copy repo

    ```bash
    git clone https://github.com/Sosylka19/Traffic-Sign-Recognition.git
    ```

3. Move to the project directory
    ```
    cd traffic-sign-detection
    ```

3.  Start the project
    ```bash
    make
    ```


### Project structure
```traffic_sign_detection/
├── backend/
│   ├── Dockerfile
│   ├── requirements.txt
│   └── app/
│       ├── dataset
│       │     └── init.sql
│       ├── auth.py
│       ├── db.py
│       ├── main.py
│       ├── models.py
│       └── schemas.py  
│
├── inference_yolov8n/
│   ├── inference.cpp
│   ├── inference.h
│   ├── main_inference.h
│   └── main_inference.cpp
│
├── notebook/
│   ├── eda_resnet34.ipynb                                  
│   └── EDA_YOLO.ipynb  
│    
├── qt/
│   ├── resources
│   │     ├── icon.icns
│   │     ├── icon.ico
│   │     └── icon.png
│   ├── classes.yaml
│   ├── CMakeLists.txt
│   ├── imagewindow.cpp
│   ├── imagewindow.h
│   ├── imagewindow.ui
│   ├── loginwindow.cpp
│   ├── loginwindow.h
│   ├── loginwindow.ui
│   ├── main.cpp
│   ├── Resource.qrc
│   ├── rounded_label.h
│   ├── rounded_label.cpp
│   ├── sign_detection_en_US.tx
│   └── yolov8n.onnx
│
├── docker-compose.yml
├── Makefile
└── README.md  
