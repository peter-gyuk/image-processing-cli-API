#include "region.h"

set<pixel> region::getArea() const
{
    return _area;
}

region::region(const set<pixel>& area)
{
    this->_area=area;
}

void region::addPixel(const pixel &p)
{
    _area.insert(p);
}

bool region::isEmpty()
{
    return _area.empty();
}

bool region::containsPixel(const pixel &p)
{
    return (find(_area.begin(),_area.end(),p)==_area.end());
}

//--Implements FIND_PERIMETER operation (works for only convex object)
region region::perimeter()
{
    region perim;

    //Sides
    pixel prev=pixel(-1,-1);
    for (auto i=_area.begin();i!=_area.end();++i){
        if (i->x()!=prev.x()){
            perim.addPixel(*i);
            perim.addPixel(prev);
        }
        prev=*i;
    }

    //Last row
    for (auto i=_area.begin();i!=_area.end();++i){
        if (i->x()==prev.x()){
            perim.addPixel(*i);
        }
    }

    //First row
    auto i=_area.begin();
    prev=*i;
    perim.addPixel(prev);
    ++i;
    while (i!=_area.end() && i->x()==prev.x()){
        perim.addPixel(*i);
        prev=*i;
        ++i;
    }

    return perim;
}


