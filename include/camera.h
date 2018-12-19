//
// Created by minzhao on 18-12-9.
//

#ifndef LASER_SCAN_CLASSFICATION_CAMERA_H
#define LASER_SCAN_CLASSFICATION_CAMERA_H

#include "opencv2/opencv.hpp"
#include <opencv2/opencv.hpp>
#include <fstream>
using namespace cv;
using namespace std;
namespace ranging {
    class Camera {
    public:
        bool captureImg(const int extract_rate);

        void testImg();

        int openCam(VideoCapture&);

        bool closeCam();

    private:
        Mat frame;
        VideoCapture cap;
        ofstream outfile;
    };
}
#endif //LASER_SCAN_CLASSFICATION_CAMERA_H
