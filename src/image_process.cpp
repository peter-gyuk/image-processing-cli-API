#include "image_process.h"

//---Calculates the color distance in hsv color space
int image_process::distance (Vec3b a, Vec3b b){
    return min(abs(a(0)-b(0)),180-abs(a(0)-b(0)));
}

//---Recursive backtrack flood fill
void image_process::walk(region &area, image img, pixel loc, int sens){
    if (area.containsPixel(loc)){
        area.addPixel(loc);
        if ((loc.y()-1>=0) && (distance(img.pixelColor(loc),img.pixelColor(loc.left()))<sens)) walk(area,img,loc.left(),sens);
        if ((loc.y()+1<=img.width()-1) && (distance(img.pixelColor(loc),img.pixelColor(loc.right()))<sens)) walk(area,img,loc.right(),sens);
        if ((loc.x()-1>=0) && (distance(img.pixelColor(loc),img.pixelColor(loc.up()))<sens)) walk(area,img,loc.up(),sens);
        if ((loc.x()+1<=img.height()-1) && (distance(img.pixelColor(loc),img.pixelColor(loc.down()))<sens)) walk(area,img,loc.down(),sens);
    }
}

//---Loads the initial image
bool image_process::loadImage(string filename)
{
    if (!img.loadImage(filename)){
        return false;
    }
    return true;
}

//---Implements DISPLAY_IMAGE operation
bool image_process::displayImage()
{
    if(!img.displayImage()){
        return false;
    }
    return true;
}

//---Implements FIND_REGION operation
void image_process::findRegion(pixel location, int sensitivity)
{
    region area;

    if (sensitivity==0) area.addPixel(location);
    else walk(area,img,location,sensitivity);

    tmp=area;
}


//---Implements FIND_PERIMETER operation
void image_process::findPerimeter()
{
    tmp=tmp.perimeter();
}

//---Implements FIND_SMOOTH_PERIMETER operation
void image_process::findSmoothPerimeter(double smooth_tol)
{
    tmp=tmp.smooth(smooth_tol);
    findPerimeter();
}

//---Implements DISPLAY_PIXELS operation
void image_process::displayPixels()
{
    img.displayPixels(tmp);
}

//---Implements SAVE_PIXELS operation
void image_process::savePixels(const string &filename)
{
    img.savePixels(tmp,filename);
}


