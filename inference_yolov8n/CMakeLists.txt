cmake_minimum_required(VERSION 3.10)
project(Yolov8OnnxRuntimeCPPInference)

set(CMAKE_CXX_STANDARD 20)


set(ONNXRUNTIME_ROOT "/usr/local/onnxruntime-osx-arm64-1.20.1")



file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/yolov8n.onnx
        ${CMAKE_CURRENT_SOURCE_DIR}/classes.yaml
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    )

include_directories(${ONNXRUNTIME_ROOT}/include)
link_directories(${ONNXRUNTIME_ROOT}/lib)

find_package(Qt6 6.5)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


set(SOURCES
    main_inference.cpp
    inference.cpp
    inference.h
)

add_executable(Yolov8OnnxRuntimeCPPInference ${SOURCES})

target_link_libraries(Yolov8OnnxRuntimeCPPInference
    ${OpenCV_LIBS}
    onnxruntime  
)