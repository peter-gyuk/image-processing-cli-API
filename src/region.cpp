#include "region.h"

set<pixel> region::getArea() const
{
    return _area;
}

//---Converts the area into a matrix of logical values (1-foreground, 0-background)
vector<vector<bool>> region::convertToLogicalImage(int &shift_x, int &shift_y)
{
    //Calculate dimensions
    int height=0;
    int width=0;

    int min_y=-1;
    int min_x=-1;
    for (auto i=_area.begin();i!=_area.end();++i){
        if (i->y()<min_y || min_y==-1){
            min_y=i->y();
        }
        if (i->y()>width){
            width=i->y();
        }
        if (i->x()<min_x || min_x==-1){
            min_x=i->x();
        }
        if (i->x()>height){
            height=i->x();
        }
    }

    height-=min_x-1;
    width-=min_y-1;

    height+=2;
    width+=2;

    shift_x=min_x;
    shift_y=min_y;

    vector<vector<bool>> img;


    for (int i=0;i<height;++i){
        img.push_back(vector<bool>());
        for (int j=0;j<width;++j){
            img[i].push_back(false);
        }
    }

    for (auto i=_area.begin();i!=_area.end();++i){
        img[i->x()-shift_x+1][i->y()-shift_y+1]=true;
    }

    return img;
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

//--Implements FIND_PERIMETER operation (Bug follow backtracking algorithm)
region region::perimeter()
{
    region perim;

    int shift_x;
    int shift_y;

    vector<vector<bool>> img = convertToLogicalImage(shift_x,shift_y);

    //Find top left corner
    int i=1;
    int j=img[i][0];
    while (!img[i][j]) ++j;
    --i;

    int start_i=i;
    int start_j=j;

    //Bug follow with backtrack
    int dir=1; //0 - right, 1 - down, 2 - left, 3 - up
    bool prev;
    do{
        prev=img[i][j];
        if (dir==0) j++;
        else if (dir==1) i++;
        else if (dir==2) j--;
        else i--;

        if (i>=0 && j>=0 && i<img.size() && j<img[0].size() && img[i][j] && !prev){
            perim.addPixel(pixel(i+shift_x-1,j+shift_y-1));
            if (dir>1) dir-=2;
            else dir+=2;
        }else{
            dir = (dir+1)%4;
        }
    }while (!(start_i == i && start_j == j && dir == 1));

    return perim;
}


