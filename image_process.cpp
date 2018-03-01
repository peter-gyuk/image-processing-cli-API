#include "image_process.h"

//Calculate the color distance in hsv color space
int image_process::distance (Vec3b a, Vec3b b){
    return min(abs(a(0)-b(0)),180-abs(a(0)-b(0)));
}

//Recursive backtrack flood fill
void image_process::walk(region &area, image img, pixel loc, int sens){
    set<pixel> reg=area.getArea();
    if (find(reg.begin(),reg.end(),loc)==reg.end()){
        area.addPixel(loc);
        if ((loc.y()-1>=0) && (distance(img.pixelColor(loc),img.pixelColor(loc.left()))<sens)) walk(area,img,loc.left(),sens);
        if ((loc.y()+1<=img.width()-1) && (distance(img.pixelColor(loc),img.pixelColor(loc.right()))<sens)) walk(area,img,loc.right(),sens);
        if ((loc.x()-1>=0) && (distance(img.pixelColor(loc),img.pixelColor(loc.up()))<sens)) walk(area,img,loc.up(),sens);
        if ((loc.x()+1<=img.height()-1) && (distance(img.pixelColor(loc),img.pixelColor(loc.down()))<sens)) walk(area,img,loc.down(),sens);
    }
}

region image_process::find_region(image img, const pixel &location, int sensitivity)
{
    region area;


    if (sensitivity==0){
        area.addPixel(location);
        return area;
    }

    walk(area,img,location,sensitivity);

    return area;
}

region image_process::find_perimeter(region area)
{
    set<pixel> reg=area.getArea();
    region perim;

    //Sides
    pixel prev=pixel(-1,-1);
    for (auto i=reg.begin();i!=reg.end();++i){
        if (i->x()!=prev.x()){
            perim.addPixel(*i);
            perim.addPixel(prev);
        }
        prev=*i;
    }

    //Last row
    for (auto i=reg.begin();i!=reg.end();++i){
        if (i->x()==prev.x()){
            perim.addPixel(*i);
        }
    }

    //First row
    auto i=reg.begin();
    prev=*i;
    perim.addPixel(prev);
    ++i;
    while (i!=reg.end() && i->x()==prev.x()){
        perim.addPixel(*i);
        prev=*i;
        ++i;
    }


    return perim;
}

