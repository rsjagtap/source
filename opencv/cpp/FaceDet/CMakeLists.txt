cmake_minimum_required(VERSION 2.8.9)
project( face_detection)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( face_detection face_detection.cpp )
target_link_libraries( face_detection ${OpenCV_LIBS} )
