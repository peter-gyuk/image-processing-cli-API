#include "image.h"

image::image()
{

}

bool image::load_image(string img_file)
{
    img = imread(img_file);

    if (!img.data) {
        return false;
    }

    return true;
}

bool image::display_image(string window_name)
{
    if (img.empty()){
        return false;
    }

    namedWindow(window_name);
    imshow(window_name, img);
    return true;
}


Vec3b image::pixelColor(pixel p)
{
    Mat hsv;
    cvtColor(img,hsv,cv::COLOR_RGB2HSV);
    Vec3b c = hsv.at<Vec3b>(Point(p.y(),p.x()));
    return c;
}

void image::display_pixels(region area)
{
    Mat img2=img;

    set<pixel> pixels=area.getArea();
    for (auto i=pixels.begin();i!=pixels.end();++i){
        img2.at<cv::Vec3b>(i->x(),i->y())[0]=0;
        img2.at<cv::Vec3b>(i->x(),i->y())[1]=0;
        img2.at<cv::Vec3b>(i->x(),i->y())[2]=0;
    }

    namedWindow("2");
    imshow("2", img);
}


void image::save_pixels(region area, string filename)
{
    Mat img2=img;

    set<pixel> pixels=area.getArea();
    for (auto i=pixels.begin();i!=pixels.end();++i){
        img2.at<cv::Vec3b>(i->x(),i->y())[0]=0;
        img2.at<cv::Vec3b>(i->x(),i->y())[1]=0;
        img2.at<cv::Vec3b>(i->x(),i->y())[2]=0;
    }

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
