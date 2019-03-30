#include "FisheyeCvtPano.h"

Fisheye_Covert_Panorama::Fisheye_Covert_Panorama(int panoWidth, int panoHeigth, int srcWidth, int srcHeigth, int srcFov, cv::Size srcCenter, int _srcRadius)
{
    pano_w = panoWidth;
    pano_h = panoHeigth;
    srcFOV = srcFov;
    src_w = srcWidth;
    src_h = srcHeigth;
    srcCenter_x = srcCenter.width;
    srcCenter_y = srcCenter.height;
    srcRadius = _srcRadius;

    halfPano_w = panoWidth / 2;
    halfPano_h = panoHeigth / 2;
    panoPixelOfRad = panoHeigth / PI;
    srcPixelOfRad = _srcRadius / (DEGREE_TO_RAD(srcFOV / 2.0));
    scale = srcPixelOfRad / panoPixelOfRad;
}

void Fisheye_Covert_Panorama::covertPano(cv::Mat &src, cv::Mat &dst, int r, int p, int y)
{
    roll = r;
    pitch = p;
    yaw = y;


    setRotationMatrix(DEGREE_TO_RAD(roll), DEGREE_TO_RAD(pitch), DEGREE_TO_RAD(yaw), R);


    for (int i = 0; i < pano_h; i++)
    {
        for (int j = 0; j < pano_w; j++)
        {
            double x = 0.0, y = 0.0;//src x,y

            bool isvalid = remap(x, y, j, i);

            if (isvalid == true)
                dst.at<cv::Vec3b>(i, j) = src.at<cv::Vec3b>((uint)y, (uint)x);
            else
            {
                dst.at<cv::Vec3b>(i, j)[0] = 0;
                dst.at<cv::Vec3b>(i, j)[1] = 0;
                dst.at<cv::Vec3b>(i, j)[2] = 0;
            }
        }
    }

}

bool Fisheye_Covert_Panorama::remap(double &srcX, double &srcY, int panoX, int panoY)
{
    // convert coordinate to Image cneter
    panoX -= halfPano_w - 0.5;
    panoY -= halfPano_h - 0.5;

    double theta, phi; // theta is zenith, phi is Azimuth, r default 1
    theta =  -panoY / panoPixelOfRad + PI / 2;
    phi = panoX / panoPixelOfRad;

    double v[3]; // sphere coordinate : x(turn right), y(turn down), z(turn forward)
    v[0] = sin(theta) * sin(phi); // x
    v[1] = cos(theta); // y
    v[2] = sin(theta) * cos(phi); //z

    //world coordinate to camera coordinate system

    double v0, v1, v2;
    v0 =v[0];
    v1 =v[1];
    v2 =v[2];

    for (int i = 0; i < 3; ++i) {
        v[i] = R[i][0] * v0 + R[i][1] * v1 + R[i][2] * v2;
    }

    //camera coordinate system to pixel coordinate system
    //theta is incident angle
    double r;
    r = sqrt(v[0] * v[0] + v[1] * v[1]);
    theta = atan2(r, v[2]);

    srcX = panoPixelOfRad * theta * v[0] / r;
    srcY = panoPixelOfRad * theta * v[1] / r;
    //scale
    srcX *= scale;
    srcY *= scale;
    //return to pixel coordinate system
    srcX += src_w / 2;
    srcY += src_h / 2;

    bool pixelvalid = false;
    if (srcX > 0 && srcX < src_w && srcY > 0 && srcY < src_h)
        pixelvalid = true;

    return pixelvalid;
}

