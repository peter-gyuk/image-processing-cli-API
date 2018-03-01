#ifndef CL_INTERFACE_H
#define CL_INTERFACE_H

#include <iostream>
#include "image_process.h"


class cl_interface
{
private:
    cl_interface(){}

    static void help();
public:
    static int cl(int argc, char *argv[]);
};

#endif // CL_INTERFACE_H
