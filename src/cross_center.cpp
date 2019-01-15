//
// Created by liukai on 18-12-31.
//
#include <iostream>
#include "cross_center.h"
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

namespace ranging{
    Cross_center::Cross_center(int width, int height) : H(height), W(width) {
        if (height == 720)
        {
            WCrop.push_back(360);
            WCrop.push_back(960);
            HCrop.push_back(180);
            HCrop.push_back(480);
        }
        else if(height == 480)
        {
            WCrop.push_back(120);
            WCrop.push_back(540);
            HCrop.push_back(120);
            HCrop.push_back(320);
        }
        else if(height == 1080)
        {
            WCrop.push_back(600);
            WCrop.push_back(1280);
            HCrop.push_back(360);
            HCrop.push_back(960);
        }
        NTemp = 80;
        WCross = 3;
        stride = 3;
        center.assign(2,0);
            //img = Mat::zeros(3,3, CV_8UC1);
            //cross_simi.assign();
    };

    Cross_center::~Cross_center(){
    };

    point<int> Cross_center::Get_center(Mat& img)
    {
        point<int> output;
        // 提取红色通道, BGR, mv[2]为红色通道
        Mat mv[3];
        split(img,mv);
        Mat imgbw;
        threshold(mv[2],imgbw,190,255,CV_THRESH_BINARY);
//        imshow("imbw",imgbw);
        // 根据WCrop和HCrop进行裁剪
        Mat image;
        image = Crop_img(imgbw);
//        imshow("imcrop",image);
//        waitKey(0);
        // 计算输出的模板维度
        uint16_t Ow, Oh;
        vector<uint16_t > out_dim = Out_dim(image.cols,image.rows);
        vector<uint8_t > temp_iter = Temp_iter();
        Ow = out_dim[0];
        Oh = out_dim[1];
//        cout<<"Ow: "<<Ow<<endl;
//        cout<<"Oh: "<<Oh<<endl;
        uint8_t istart;
        istart = temp_iter[0];
        // 用十字模板匹配原图像，截取激光十字图像
        Rect wrect(0,istart,NTemp,WCross);
        Rect hrect(istart,0,WCross,NTemp);
        vector<int> tmp_out(Ow*Oh);
        for (int ih=0;ih<Oh;ih++)
        {
            for (int iw=0;iw<Ow;iw++)
            {
                Rect tmprect(iw*stride,ih*stride,NTemp,NTemp);
                Mat tmpmat = Mat(image,tmprect);
                Mat tmpw = Mat(tmpmat,wrect);
                Mat tmph = Mat(tmpmat,hrect);
                int sumtemp = 0;
                Scalar tmpsum = sum(tmpw);
                sumtemp += tmpsum[0];
                tmpsum = sum(tmph);
                sumtemp += tmpsum[0];
                tmp_out[ih*Ow+iw] = sumtemp;
            }
        }
        // 计算十字图像的左上坐标
        auto maxvalue = max_element(tmp_out.begin(),tmp_out.end());
        int maxpos = maxvalue - tmp_out.begin();
        int hidx = maxpos/Ow;
        int widx = maxpos%Ow;
        int left = widx*stride;
        int top = hidx*stride;
//        cout<<maxpos<<endl;
//        cout<<hidx<<endl<<widx<<endl<<left<<endl<<top<<endl;
        // 计算十字图像在水平和垂直方向的投影，估计中心坐标
        Rect rect_select(left,top,NTemp,NTemp);
        Mat mat_select(image,rect_select);
//        for(int idxh=0;idxh<mat_select.rows;idxh++)
//        {
//            for(int idxw=0;idxw<mat_select.cols;idxw++)
//            {
//                cout<<mat_select.at<uchar>(idxw,idxh)<<" ";
//            }
//            cout<<endl;
//        }
        Mat mat_select_trans;
        transpose(mat_select,mat_select_trans);
        vector<int> hhist = Mat_sum_dim(mat_select);
        vector<int> whist = Mat_sum_dim(mat_select_trans);
        vector<int>::iterator maxvalue2 = max_element(begin(whist),end(whist));
        int wcenter = distance(begin(whist),maxvalue2);
        vector<int>::iterator maxvalue3 = max_element(begin(hhist),end(hhist));
        int hcenter = distance(begin(hhist),maxvalue3);
//        cout<<"wcenter: "<<wcenter<<endl;
//        for(int i=0;i<whist.size();i++)
////            cout<<whist[i]<<endl;
//        cout<<"hcenter: "<<hcenter<<endl;
//        for(int i=0;i<hhist.size();i++)
////            cout<<hhist[i]<<endl;
        output.x = wcenter+left+WCrop[0];
        output.y = hcenter+top+HCrop[0];
//        cout<<output[0]<<endl;
//        cout<<output[1]<<endl;
        return output;
    };

    vector<int> Cross_center::Mat_sum_dim(Mat& image)
    {
        vector<int> sumtemp;
        for (int ih=0;ih<image.rows;ih++)
        {
            int tmp = 0;
            for (int iw=0;iw<image.cols;iw++)
            {
                tmp += image.at<uchar>(iw,ih);
            }
            sumtemp.push_back(tmp);
        }
        return sumtemp;
    };

    vector<uint8_t > Cross_center::Temp_iter()
    {
        vector<uint8_t > iter;
        int tmp = NTemp/2;
        iter.push_back(tmp-1);
        iter.push_back(tmp+1);
        return iter;
    };

    vector<uint16_t > Cross_center::Out_dim(int W, int H){
        vector<uint16_t > tmp;
        uint16_t tmpw, tmph;
        tmpw = (W-NTemp)/stride+1;
        tmph = (H-NTemp)/stride+1;
        tmp.push_back(tmpw);
        tmp.push_back(tmph);
        return tmp;
    };

    Mat Cross_center::Crop_img(Mat& img)
    {
        uint16_t wstart,w,hstart,h;
        wstart = WCrop[0];
        w = WCrop[1]-wstart;
        hstart = HCrop[0];
        h = HCrop[1]-hstart;
        Rect rect(wstart,hstart,w,h);
        Mat outimg = Mat(img,rect);
        return outimg;
    };

    void Cross_center::test() {
        std::cout<<H<<std::endl;
    }
}

