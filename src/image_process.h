#ifndef IMAGE_PROCESS_H
#define IMAGE_PROCESS_H

#include "image.h"

//---Class representing the process of operations on the initial image
class image_process
{

private:
    region tmp; //This is the current region resulting from the sequence of operations
    image img;

    static int distance(Vec3b a, Vec3b b);
    static void walk(region &area, image img, pixel loc, int sens);

public:
    image_process() {}
    image_process(image img);
    bool loadImage(string filename);
    bool displayImage();
    void findRegion(pixel location, int sensitivity = 1);
    void findPerimeter();
    void findSmoothPerimeter(double smooth_tol = 0.1);
    void displayPixels();
    void savePixels(const string &filename);

};

#endif // IMAGE_PROCESS_H
