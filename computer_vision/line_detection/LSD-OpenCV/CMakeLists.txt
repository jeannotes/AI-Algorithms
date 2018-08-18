cmake_minimum_required(VERSION 2.8)
project(demo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_DIRS})

aux_source_directory(. lsd_library)
add_library(lsd_functions ${lsd_library})
include_directories(${PROJECT_SOURCE_DIR})

add_executable(lsd main.cpp)
target_link_libraries(lsd lsd_functions ${OpenCV_LIBS})