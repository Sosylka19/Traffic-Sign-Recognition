cmake_minimum_required(VERSION 3.10)
project(Yolov8OnnxRuntimeCPPInference)

set(CMAKE_CXX_STANDARD 17)

# === ONNX Runtime ===
# Укажи путь к ONNX Runtime вручную или через переменную окружения
set(ONNXRUNTIME_ROOT "/usr/local/onnxruntime-osx-arm64-1.20.1")

include_directories(${ONNXRUNTIME_ROOT}/include)
link_directories(${ONNXRUNTIME_ROOT}/lib)

# === OpenCV ===
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# === Источники ===
set(SOURCES
    main.cpp
    inference.cpp
    inference.h
)

add_executable(Yolov8OnnxRuntimeCPPInference ${SOURCES})

# === Линковка ===
target_link_libraries(Yolov8OnnxRuntimeCPPInference
    ${OpenCV_LIBS}
    onnxruntime  # имя библиотеки без префикса lib и расширения
)