#ifndef IMAGE_PROCESS_H
#define IMAGE_PROCESS_H

#include "image.h"

//---Static class of operations
class image_process
{

private:
    image_process() {}
    static int distance (Vec3b a, Vec3b b);
    static void walk(region &area, image img, pixel loc, int sens);


public:
    static region find_region(image img, const pixel &location, int sensitivity = 1);
    static region find_perimeter(region area);

};

#endif // IMAGE_PROCESS_H
