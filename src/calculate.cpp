//
// Created by minzhao on 18-12-31.
//

#include <cmath>
#include "calculate.h"

using namespace cv;
namespace ranging {
    point<double> Calculate::calculate(point<int> &laser_marker, eclipse<int> eclipse) {

        ratio_ = (eclipse.height / realEclipseHeight_ + eclipse.width / realEclipseWidth_) / 2.0;
        if (ratio_ == 0)
            std::cerr << "ratio is zero!!!" << std::endl;
        point<double> output; //in mm

        output.x = (RESOLUTION_CENTER_WIDTH - eclipse.x - eclipse.width / 2) / ratio_;
        output.y = (RESOLUTION_CENTER_HEIGHT - eclipse.y - eclipse.height / 2) / ratio_;
        output.z = (laser_marker.x - RESOLUTION_CENTER_WIDTH) * tan(M_PI / 3.0) / ratio_ + realStandard_;
        cout << "x: " << output.x << " y: " << output.y << " z: " << output.z << endl;
        return output;

    }

    eclipse<int> Calculate::detect_eclipse(cv::Mat srcImg) {
        eclipse<int> eclipse;
//        Mat srcImg = imread("/home/minzhao/Document/laser_scan_classfication/dataset/15.jpg");
//        cout << srcImg.rows << " " << srcImg.cols << endl;
        vector<vector<Point>> contours;    //储存轮廓
        vector<Vec4i> hierarchy;
        double FACTOR = 2.5;
        double cannyThr = 200;
        cv::Mat currImg, cannyImg;
        cvtColor(srcImg, currImg, COLOR_BGR2GRAY);
//        imshow("GRAY", currImg);
        medianBlur(currImg, currImg, 7);
//        imshow("media", currImg);
        threshold(currImg, currImg, 80, 255, THRESH_BINARY);
//        imshow("binary", currImg);
        Canny(currImg, cannyImg, cannyThr, cannyThr * FACTOR);
//        imshow("canny", cannyImg);
        findContours(cannyImg, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
        if (contours.size() == 0)
            cout << "find no contours" << endl;
        Mat lineSrc = Mat::zeros(cannyImg.rows, cannyImg.cols, CV_8UC3);
        for (int index = 0; index < contours.size(); index++) {
            drawContours(lineSrc, contours, index, Scalar(rand() & 255, rand() & 255, rand() & 255), 1, 8/*, hierarchy*/);
        }
//        imshow("line", lineSrc);

        //find the max contours
        double areaMax = 0;
        int areaMaxIndex = 0;
        for (size_t i = 0; i < contours.size(); i++) {
            double area = contourArea(contours[i]);
            if (area > areaMax) {
                areaMax = area;
                areaMaxIndex = i;//记录最大轮廓的索引号
            }
        }
        vector<cv::Point> contourMax = contours[areaMaxIndex];
        vector<vector<cv::Point>> contours_poly(1);
        approxPolyDP(cv::Mat(contourMax), contours_poly[0], 3, true);
        cv::Rect boundRect = cv::boundingRect(cv::Mat(contours_poly[0]));
        cv::Mat drawing = cv::Mat::zeros(srcImg.size(), CV_8UC3);
        drawContours(drawing, contours_poly, 0, cv::Scalar(0, 0, 255), 1, 8, vector<cv::Vec4i>(), 0, cv::Point());
        rectangle(drawing, boundRect.tl(), boundRect.br(), cv::Scalar(0, 0, 255), 1, 8, 0);

        eclipse.x = boundRect.x; //椭圆左上的坐标x
        eclipse.y = boundRect.y; //椭圆左上的坐标y
        eclipse.height = boundRect.height;
        eclipse.width = boundRect.width;

//        cout << boundRect.x << " " << boundRect.y << " " << boundRect.width << " " << boundRect.height << endl;
//        imshow("pointImg", srcImg);
//        imshow("contour", drawing);
//        waitKey();
        return eclipse;
    }
}