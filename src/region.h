#ifndef REGION_H
#define REGION_H

#include "pixel.h"
#include <set>
#include <algorithm>
#include <iostream>

#define AREA_BORDER 1 //Background border around the region when converting to logical image
#define SMOOTH_TOL 0.1

using namespace std;

//---Stores and handles a region of pixels
class region
{

private:
    set<pixel> _area;

    vector<vector<bool>> convertToLogicalImage(int &shift_x, int &shift_y);

public:
    region(){}
    region(const set<pixel>& area);

    bool containsPixel(const pixel& p);
    region perimeter();
    region smooth();

    void addPixel(const pixel &p);
    bool isEmpty();

    set<pixel> getArea() const;
};

#endif // REGION_H
