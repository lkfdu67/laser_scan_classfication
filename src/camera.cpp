//
// Created by minzhao on 18-12-9.
//
#include "camera.h"
namespace ranging{
    bool Camera::captureImg(const int extract_rate) {
        outfile.open("../dataset/data.txt", ios::binary | ios::in | ios::out | ios::trunc);
        // open the default camera, use something different from 0 otherwise;
        // Check VideoCapture documentation.
        if (!cap.open(0))
            return false;
        double frame_rate = cap.get(CV_CAP_PROP_FPS);
        int frame_idx = 0;
        string jpg_name;
        for (;;) {
            cap >> frame;
            if (frame.empty()) break; // end of video stream
            imshow("this is you, smile! :)", frame);
            int c = waitKey(1);
            switch (c) {
                case 27 : {
                    cout << "stop capture" << endl;
                    // release the camera
                    cap.release();
                    break;
                }
                case 'q': {
                    frame_idx++;
                    jpg_name = "../dataset/" + to_string(frame_idx) + ".jpg";
                    imwrite(jpg_name,frame);
                    outfile << jpg_name << endl;
                    outfile << "+" << endl;
                    cout << "p: " << frame_idx << endl;
                    break;
                }
                case 'w': {
                    frame_idx++;
                    jpg_name = "../dataset/" + to_string(frame_idx) + ".jpg";
                    imwrite(jpg_name,frame);
                    outfile << jpg_name << endl;
                    outfile << "-" << endl;
                    cout << "n: " << frame_idx << endl;
                    break;
                }
                default: {
                    break;
                }
            }

        }

        outfile.close();
    }
    bool Camera::closeCam() {

    }
    bool Camera::openCam() {

    }
    void Camera::testImg() {

    }
}