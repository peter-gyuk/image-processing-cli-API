#ifndef REGION_H
#define REGION_H

#include "pixel.h"
#include <set>

using namespace std;

class region
{

private:
    set<pixel> _area;

public:
    region();
    region(set<pixel> area);
    set<pixel> getArea() const;
    void setArea(const set<pixel> &value);
};

#endif // REGION_H
