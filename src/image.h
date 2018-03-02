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

    bool load_image(string img_file);
    bool display_image(string window_name = "DISPLAY_IMAGE");
    void display_pixels(region area, string window_name = "DISPLAY_PIXELS");
    void save_pixels(region area, string filename);

    Vec3b pixelColor(pixel p);
    int width();
    int height();

};

#endif // IMAGE_H
