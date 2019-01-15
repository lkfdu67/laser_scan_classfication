#include <iostream>
#include <calculate.h>
#include "opencv2/opencv.hpp"
#include "camera.h"
#include "classify.h"
#include "common.h"
#include "cross_center.h"

#define CAPTURE
int main(int argc, char **argv) {
    ranging::Camera camera;
    ranging::Classify classify;
    ranging::Calculate calculate(ECLIPSEWIDTH,ECLIPSEHEIGHT,STANDARDLENGTH);
    ranging::Cross_center cross_center(RESOLUTION_WIDTH,RESOLUTION_HEIGHT);
    VideoCapture capture;
    Mat frame;

#ifndef CAPTURE
    unsigned long total_count = 0;
    int ret = camera.openCam(capture);
    if (ret != 0) {
        std::cout << "open cam failed" << std::endl;
        return -1;
    }
    ret = classify.init_svm();
    if (ret != 0) {
        std::cout << "init svm failed" << std::endl;
        return -1;
    }
    std::cout << "开始识别..." << std::endl;
    for (;;) {
        total_count++;
        capture >> frame;
        if (frame.empty()) break; // end of video stream
        ranging::point<int> laser_marker = cross_center.Get_center(frame);
        cv::Rect cross_center(laser_marker.x, laser_marker.y,2,2);
        rectangle(frame, cross_center, cv::Scalar(255, 0, 0), 4);
        ranging::eclipse<int> eclipse = calculate.detect_eclipse(frame);
        cv::Rect rect_point(eclipse.x + eclipse.width / 2, eclipse.y + eclipse.height / 2,2,2);
        rectangle(frame, rect_point, cv::Scalar(0, 255, 0), 3);
        cv::Rect rect_center(RESOLUTION_CENTER_WIDTH,RESOLUTION_CENTER_HEIGHT,2,2);
        rectangle(frame, rect_center, cv::Scalar(0, 0, 255), 3);
        calculate.calculate(laser_marker,eclipse);
        imshow("this is you, smile! :)", frame);
        classify.start_classfication(frame);
        int c = waitKey(1);
        switch (c) {
            case 'q' : {
                cout << "stop capture" << endl;
                // release the camera
                camera.closeCam();
                return 0;
//                break;
            }
            /*print current succeed ratio*/
            case 'p': {
                classify.print_ratio(total_count);
                break;
            }
            default: {
                break;
            }
        }

    }
#else
    /*to capture img and produce dataset*/
    camera.captureImg(10);
#endif
    return 0;
}