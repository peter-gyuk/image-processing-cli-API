#ifndef REGION_H
#define REGION_H

#include "pixel.h"
#include <set>
#include <algorithm>

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

    void addPixel(const pixel &p);
    bool isEmpty();

    set<pixel> getArea() const;
};

#endif // REGION_H
