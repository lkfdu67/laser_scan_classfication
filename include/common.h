//
// Created by minzhao on 18-12-31.
//

#ifndef LASER_SCAN_CLASSFICATION_COMMON_H
#define LASER_SCAN_CLASSFICATION_COMMON_H
namespace ranging {
    template<class T>
    struct point {
        inline point() : x(0), y(0), z(0) {}

        inline point(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

        inline ~point() {}

        T x, y, z;

        std::string DebugString() const {
            return "[ " + std::to_string(x) + " , " + std::to_string(y) + " , " + std::to_string(z) + " ]";
        }
    };

    template<class T>
    struct eclipse : public point<T> {
        inline eclipse() : point<T>(0), width(0), height(0) {}

        inline eclipse(T _x, T _y, T _z, T _width, T _height) : point<T>(_x, _y, _z), width(_width), height(_width) {}

        std::string DebugEclipse() const {
            return "[ " + std::to_string(point<T>::x) + " , " + std::to_string(point<T>::y) + " , " + std::to_string(point<T>::z) + " , " + std::to_string(width) + " , " +
                   std::to_string(height) + " ]";
        }

        T width, height;
    };

}
#endif //LASER_SCAN_CLASSFICATION_COMMON_H
