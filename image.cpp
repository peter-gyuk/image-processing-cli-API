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
    //waitKey(0);
    return true;
}
