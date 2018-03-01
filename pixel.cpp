#include "pixel.h"

int pixel::x() const
{
    return this->_x;
}

int pixel::y() const
{
    return this->_y;
}

bool pixel::operator<(const pixel &p) const
{
    return (make_pair(_x,_y) < make_pair(p._x,p._y));
}

bool pixel::operator==(const pixel &p) const
{
    return ( (_x==p._x) && (_y==p._y) );
}


pixel pixel::left(int step)
{
    return pixel(_x,_y-step);
}

pixel pixel::right(int step)
{
    return pixel(_x,_y+step);
}

pixel pixel::up(int step)
{
    return pixel(_x-step,_y);
}

pixel pixel::down(int step)
{
    return pixel(_x+step,_y);
}

pixel::pixel(int x, int y)
{
    this->_x=x;
    this->_y=y;
}

