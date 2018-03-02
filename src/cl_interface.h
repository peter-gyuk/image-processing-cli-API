#ifndef CL_INTERFACE_H
#define CL_INTERFACE_H

#include <iostream>
#include "image_process.h"

//---The cl_interface handles the Command Line arguments
class cl_interface
{
private:
    cl_interface(){}

    static bool stringToInt(const string &s, int &num);
    static void help();
public:
    static int clParser(int argc, char *argv[]);
};

#endif // CL_INTERFACE_H
