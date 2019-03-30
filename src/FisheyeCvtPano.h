#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "Jmath.h"

class Fisheye_Covert_Panorama
{
public:
    Fisheye_Covert_Panorama(int panoWidth, int panoHeigth, int srcWidth, int srcHeigth, int srcFov, cv::Size srcCenter, int srcRadius);
    void covertPano(cv::Mat &src, cv::Mat &dst, int r, int p, int y);
    bool remap(double &srcX, double &srcY, int panoX, int panoY);


private:
    //panorama parameters
    int pano_w;
    int pano_h;
    int halfPano_w;
    int halfPano_h;
    double panoPixelOfRad;
    //src parameterss
    int srcFOV;
    int src_w;
    int src_h;
    int srcCenter_x;
    int srcCenter_y;
    int srcRadius;
    double srcPixelOfRad;
    //other paremeters
    double scale;
    double roll = 0;//x
    double pitch = 0;//y
    double yaw = 0;//z
    double R[3][3];
};



