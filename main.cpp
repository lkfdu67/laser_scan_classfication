#include <iostream>
#include <calculate.h>
#include "opencv2/opencv.hpp"
#include "camera.h"
#include "classify.h"
#include "common.h"

int main(int argc, char **argv) {
    ranging::Camera camera;
    ranging::Classify classify;
    ranging::Calculate calculate(ECLIPSEWIDTH,ECLIPSEHEIGHT,STANDARDLENGTH);
    VideoCapture capture;
    Mat frame;

    ranging::point<int> center(RESOLUTION_WIDTH/2,RESOLUTION_HEIGHT/2,0);
    ranging::point<int> laser_marker(659,286,0);
    ranging::eclipse<int> eclipse = calculate.detect_eclipse();
    calculate.calculate(center,laser_marker,eclipse);
//    unsigned long total_count = 0;
//    int ret = camera.openCam(capture);
//    if (ret != 0) {
//        std::cout << "open cam failed" << std::endl;
//        return -1;
//    }
//    ret = classify.init_svm();
//    if (ret != 0) {
//        std::cout << "init svm failed" << std::endl;
//        return -1;
//    }
//    std::cout << "开始识别..." << std::endl;
//    for (;;) {
//        total_count++;
//        capture >> frame;
//        if (frame.empty()) break; // end of video stream
//        imshow("this is you, smile! :)", frame);
//        classify.start_classfication(frame);
//        int c = waitKey(1);
//        switch (c) {
//            case 'q' : {
//                cout << "stop capture" << endl;
//                // release the camera
//                camera.closeCam();
//                break;
//            }
//            /*print current succeed ratio*/
//            case 'p': {
//                classify.print_ratio(total_count);
//                break;
//            }
//            default: {
//                break;
//            }
//        }
//
//    }

    /*to capture img and produce dataset*/
//    camera.captureImg(10);
    return 0;
}