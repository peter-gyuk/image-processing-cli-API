#include "cl_interface.h"

using namespace std;


int main(int argc, char *argv[])
{
    if (cl_interface::cl(argc,argv)!=0){
        return -1;
    }

    waitKey(0);

    return 0;
}
