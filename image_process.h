#ifndef IMAGE_PROCESS_H
#define IMAGE_PROCESS_H

#include "image.h"

class image_process
{

private:
    image_process() {}
    static int distance (Vec3b a, Vec3b b);
    static void walk(region &area, image img, pixel loc, int sens);


public:
    static region find_region(image img, const pixel &location, int sensitivity = 1);
    static region find_perimeter(region area);
    static void save_pixels(region area, string filename);

};

#endif // IMAGE_PROCESS_H
