#include "region.h"

set<pixel> region::getArea() const
{
    return this->_area;
}

void region::setArea(const set<pixel> &value)
{
    this->_area = value;
}

void region::addPixel(const pixel &p)
{
    _area.insert(p);
}

bool region::isEmpty()
{
    return _area.empty();
}

region::region(){
}

region::region(set<pixel> area)
{
    this->_area=area;
}


