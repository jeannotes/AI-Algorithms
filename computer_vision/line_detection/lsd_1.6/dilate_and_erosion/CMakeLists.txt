cmake_minimum_required(VERSION 2.8)
project(dilate_and_erode)

find_package(OpenCV)
include_directories(${OpenCV_DIRS})
message(${OpenCV_LIBS})

add_executable(dilate_and_erode main.cpp)
target_link_libraries(dilate_and_erode ${OpenCV_LIBS})
