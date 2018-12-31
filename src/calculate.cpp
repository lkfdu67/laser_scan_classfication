//
// Created by minzhao on 18-12-31.
//

#include <cmath>
#include "calculate.h"

namespace ranging {
    point<double> Calculate::calculate(point<int> &center, point<int> &laser_marker, eclipse<int> eclipse) {

        ratio_ = (eclipse.height / realEclipseHeight_ + eclipse.width / realEclipseWidth_) / 2.0;
        if (ratio_ == 0)
            std::cerr << "ratio is zero!!!" << std::endl;
        point<double> output; //in mm

        output.x = (eclipse.x - laser_marker.x) / ratio_;
        output.y = (eclipse.y - laser_marker.y) / ratio_;
        output.z = (laser_marker.x - center.x) * tan(M_PI / 3.0) / ratio_ + realStandard_;

        return output;

    }

    eclipse<int> Calculate::detect_eclipse(cv::Mat frame) {

    }
}