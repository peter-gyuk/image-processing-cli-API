#include "region.h"

set<pixel> region::getArea() const
{
    return _area;
}

//---Converts the area into a matrix of logical values (1-foreground, 0-background) - 1-bit monochrome
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

    height+=AREA_BORDER*2;
    width+=AREA_BORDER*2;

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
        img[i->x()-shift_x+AREA_BORDER][i->y()-shift_y+AREA_BORDER]=true;
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
    int i=AREA_BORDER;
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
            perim.addPixel(pixel(i+shift_x-AREA_BORDER,j+shift_y-AREA_BORDER));
            if (dir>1) dir-=2;
            else dir+=2;
        }else{
            dir = (dir+1)%4;
        }
    }while (!(start_i == i && start_j == j && dir == 1));

    return perim;
}

//---Discrete convolution with Gaussian kernel
region region::smooth(double smooth_tol)
{
    region smooth_region;

    //Gaussian kernel
    double kernel[5][5]=
    {{1,4,7,4,1},
     {4,16,26,16,4},
     {7,26,41,26,7},
     {4,16,26,16,4},
     {1,4,7,4,1}};

    for (int i=0;i<5;++i){
        for (int j=0;j<5;j++){
            kernel[i][j]/=273;
        }
    }

    int shift_x;
    int shift_y;
    vector<vector<bool>> img = convertToLogicalImage(shift_x,shift_y);

    int n=img.size();
    int m=img[0].size();

    for (int i=0;i<n;++i){
        for (int j=0;j<m;++j){
            double newvalue=0.0;
            for (int z=-2;z<=2;++z){
                for (int u=-2;u<=2;++u){

                    int z_corr=z;
                    int u_corr=u;
                    if (i+z<0) z_corr=0;
                    else if (i+z>=n) z_corr=n-i-1;
                    if (j+u<0) u_corr=0;
                    else if (j+u>=m) u_corr=m-j-1;

                    newvalue+=img[i+z_corr][j+u_corr]*kernel[z+2][u+2];
                }
            }
            if (newvalue>smooth_tol) smooth_region.addPixel(pixel(i+shift_x-AREA_BORDER,j+shift_y-AREA_BORDER));
        }
    }

    return smooth_region;

}


