cmake_minimum_required( VERSION 2.8 )
project( laser_scan_classfication )

# 添加c++ 11标准支持
set( CMAKE_CXX_FLAGS "-std=c++11" )

# 寻找OpenCV库
find_package(OpenCV 2.4.8 REQUIRED core imgproc highgui objdetect)
# 添加头文件
include_directories(${OpenCV_INCLUDE_DIRS})
message( ${OpenCV_INCLUDE_DIRS} )
message(${OpenCV_LIBS})

add_executable( laser_scan_classfication main.cpp)
# 链接OpenCV库
target_link_libraries( laser_scan_classfication /usr/local/lib/
                        ${OpenCV_LIBS})