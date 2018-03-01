#ifndef PIXEL_H
#define PIXEL_H

//Pixel class, were the coordinates are integer
class pixel{

private:
    int _x, _y;

public:
    pixel(int x = 0, int y = 0);
    int x() const;
    int y() const;
};

#endif // PIXEL_H
