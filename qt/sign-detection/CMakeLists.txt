cmake_minimum_required(VERSION 3.19)
project(sign-detection LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools Network)

find_package(OpenCV REQUIRED)


if(WIN32)
    set(
        ONNXRUNTIME_ROOT "C:/onnxruntime-win-x64-1.20.1"
    )
elseif(APPLE)
    set(
        ONNXRUNTIME_ROOT "/usr/local/onnxruntime-osx-arm64-1.20.1"
    )
elseif(UNIX)
    set(
        ONNXRUNTIME_ROOT "/usr/local/onnxruntime-linux-x64-1.20.1"
    )
endif()

link_directories(${ONNXRUNTIME_ROOT}/lib)


qt_standard_project_setup()


qt_add_translations(
    TARGETS sign-detection
    TS_FILES sign-detection_en_US.ts
)


set(resource_files
    yolov8n.onnx
    classes.yaml)


set(
    app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/resources/icon.icns"
)



qt_add_executable(sign-detection
    MACOSX_BUNDLE #only for MacOS, will be ignored on other OS
    main.cpp
    loginwindow.h loginwindow.cpp loginwindow.ui
    imagewindow.h imagewindow.cpp imagewindow.ui
    rounded_label.h rounded_label.cpp
    ../../inference_yolov8n/main_inference.cpp
    ../../inference_yolov8n/inference.cpp
    Resource.qrc
    $<$<PLATFORM_ID:Darwin>:${app_icon_macos}># macOS
    yolov8n.onnx
    classes.yaml

)

if(APPLE)
    set_source_files_properties(
        ${app_icon_macos} PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources"
    )
    set_target_properties(
        sign-detection PROPERTIES
    MACOSX_BUNDLE_ICON_FILE icon.icns
)
endif()



target_include_directories(sign-detection
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${OpenCV_INCLUDE_DIRS}
        ${ONNXRUNTIME_ROOT}/include
)

target_link_libraries(sign-detection
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
        ${OpenCV_LIBS}
        onnxruntime
)

include(GNUInstallDirs)


install(TARGETS sign-detection
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if(APPLE)
    file(COPY
        "${CMAKE_CURRENT_SOURCE_DIR}/yolov8n.onnx"
        "${CMAKE_CURRENT_SOURCE_DIR}/classes.yaml"
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/sign-detection.app/Contents/MacOS"
    )
else()
    file(COPY
        "${CMAKE_CURRENT_SOURCE_DIR}/yolov8n.onnx"
        "${CMAKE_CURRENT_SOURCE_DIR}/classes.yaml"
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
    )
endif()

qt_generate_deploy_app_script(
    TARGET sign-detection
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
