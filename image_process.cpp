#include "image_process.h"


region image_process::find_region(image img, const pixel &location, int sensitivity)
{
    region area;
    area.addPixel(location);

    if (sensitivity==0){
        return area;
    }

    //TODO: The algorithm

    return area;
}

region image_process::find_perimeter(region area)
{
    //TODO: The algorithm

    return area;
}

void image_process::display_pixels(region area)
{
    //TODO
}

void image_process::save_pixels(region area, string filename)
{
    //TODO
}
