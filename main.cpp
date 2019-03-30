#include <iostream>
#include <assert.h>


#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "FisheyeCvtPano.h"

using namespace std;
using namespace cv;

int main ()
{
    const int pano_h = 1024;
    const int pano_w = 2048;
    const int srcFov = 200;
    Size srcCenter(2316, 1727);
    int srcRadius = 2266;

    Mat srcImg = imread("2.jpg");
    assert(srcImg.data != NULL);
    Mat dstImg(pano_h, pano_w, CV_8UC3);

    Fisheye_Covert_Panorama fisheye_cvt_panorama(pano_w, pano_h, srcImg.cols, srcImg.rows, srcFov, srcCenter, srcRadius);
    fisheye_cvt_panorama.covertPano(srcImg, dstImg, 45, 45, 45);// r p y

    imwrite("panorama.jpg", dstImg);
    return 0;
}
