#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include "region.h"

using namespace std;
using namespace cv;

class image
{
private:
    Mat img;
public:
    image();
    bool load_image(string img_file);
    bool display_image(string window_name = "image");
    Vec3b pixelColor(pixel p);
    void display_pixels(region area);
    void save_pixels(region area, string filename);
    int width();
    int height();

};

#endif // IMAGE_H