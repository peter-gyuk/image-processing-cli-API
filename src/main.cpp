#include "cl_interface.h"

using namespace std;

#define WAIT_FOR_KEY

int main(int argc, char *argv[])
{
    if (cl_interface::clParser(argc,argv)!=0){
        return -1;
    }

    #ifdef WAIT_FOR_KEY
    waitKey(0);
    #endif

    return 0;
}
