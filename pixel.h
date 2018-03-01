#ifndef PIXEL_H
#define PIXEL_H

#include <utility>

using namespace std;

//Pixel class, were the coordinates are integer (could be template class later)
class pixel{

private:
    int _x, _y;

public:
    pixel(){}
    pixel(int x, int y);
    int x() const;
    int y() const;

    bool operator<(const pixel& p) const;
    bool operator==(const pixel& p) const;

    pixel left(int step = 1);
    pixel right(int step = 1);
    pixel up(int step = 1);
    pixel down(int step = 1);
};

#endif // PIXEL_H
