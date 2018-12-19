//
// Created by minzhao on 18-12-18.
//

#ifndef LASER_SCAN_CLASSFICATION_CLASSIFY_H
#define LASER_SCAN_CLASSFICATION_CLASSIFY_H
#include <opencv2/opencv.hpp>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
namespace ranging {
    class Classify {
    public:
        Classify();
        int start_classfication(const cv::Mat&);
        int init_svm();
        void print_ratio(unsigned long);
        void Train_svm_hog();

    private:
        cv::HOGDescriptor hog_;
        cv::Ptr<cv::ml::SVM> svm_;
        unsigned long succeed_count_;
        unsigned long failed_count_;
    };
}

#endif //LASER_SCAN_CLASSFICATION_CLASSIFY_H
