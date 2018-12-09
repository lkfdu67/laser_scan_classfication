#include <iostream>
#include "opencv2/opencv.hpp"
#include "camera.h"
int main(int argc, char **argv) {
    ranging::Camera camera;
    camera.captureImg(10);
    return 0;
}