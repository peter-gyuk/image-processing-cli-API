#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include "region.h"

using namespace std;
using namespace cv;

//---Stores the input image and includes functions connected to it
class image
{
private:
    Mat img;

    Mat overlay_region(region arena);
public:
    image(){}

    bool loadImage(const string &img_file);
    bool displayImage(const string &window_name = "DISPLAY_IMAGE");
    void displayPixels(region area, const string &window_name = "DISPLAY_PIXELS");
    void savePixels(region area, const string &filename);

    Vec3b pixelColor(pixel p);
    int width();
    int height();

};

#endif // IMAGE_H
