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
    return ( (_x<p._x) || ( (_x==p._x) && (_y<=p._y) ) );
}

pixel::pixel(int x, int y)
{
    this->_x=x;
    this->_y=y;
}
