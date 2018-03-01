#include "pixel.h"

int pixel::x() const
{
    return this->_x;
}

int pixel::y() const
{
    return this->_y;
}

pixel::pixel(int x, int y)
{
    this->_x=x;
    this->_y=y;
}
