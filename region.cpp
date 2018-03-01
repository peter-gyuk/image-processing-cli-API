#include "region.h"

set<pixel> region::getArea() const
{
    return this->_area;
}

void region::setArea(const set<pixel> &value)
{
    this->_area = value;
}

region::region()
{

}

region::region(set<pixel> area)
{
    this->_area=area;
}
