#include "image.h"

//---Creates and overlay of black region over the original image
Mat image::overlay_region(region area)
{
    Mat img2=img;

    set<pixel> pixels=area.getArea();
    for (auto i=pixels.begin();i!=pixels.end();++i){
        img2.at<cv::Vec3b>(i->x(),i->y())[0]=0;
        img2.at<cv::Vec3b>(i->x(),i->y())[1]=0;
        img2.at<cv::Vec3b>(i->x(),i->y())[2]=0;
    }

    return img2;
}

//---Load image from file
bool image::loadImage(const string &img_file)
{
    img = imread(img_file);

    if (!img.data) {
        return false;
    }

    return true;
}

//---Diplay loaded image
bool image::displayImage(const string &window_name)
{
    if (img.empty()){
        return false;
    }

    namedWindow(window_name);
    imshow(window_name, img);
    return true;
}

//---Returns the color of a pixel in HSV color space
Vec3b image::pixelColor(pixel p)
{
    Mat hsv;
    cvtColor(img,hsv,cv::COLOR_RGB2HSV);
    Vec3b c = hsv.at<Vec3b>(Point(p.y(),p.x()));
    return c;
}

//--Displays the region over the image
void image::displayPixels(region area, const string &window_name)
{
    Mat img2=overlay_region(area);

    namedWindow(window_name);
    imshow(window_name, img2);
}

//--Saves the region over the image
void image::savePixels(region area, const string &filename)
{
    Mat img2=overlay_region(area);

    imwrite(filename, img2);
}

int image::width()
{
    return img.cols;
}

int image::height()
{
    return img.rows;
}
