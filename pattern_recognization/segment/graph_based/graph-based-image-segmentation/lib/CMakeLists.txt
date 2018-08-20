cmake_minimum_required(VERSION 2.8)
project(refh)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
add_library(refh graph_segmentation.cpp)
target_link_libraries(refh ${OpenCV_LIBS})