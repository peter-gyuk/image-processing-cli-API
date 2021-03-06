#include "cl_interface.h"

//---Converts string to integer with error handling
bool cl_interface::stringToInt(const string &s, int &num){

    stringstream ss (s);
    ss >> num;

    if(ss.fail())
    {
        return false;
    }

    return true;
}

//---Converts string to double with error handling
bool cl_interface::stringToDouble(const string &s, double &num){

    stringstream ss (s);
    ss >> num;

    if(ss.fail())
    {
        return false;
    }

    return true;
}

//---Help message display
void cl_interface::help(){

    cout<<"---ip_api HELP PAGE---"<<endl<<endl;
    cout<<"usage: ip_api input_image <operation>"<<endl;
    cout<<"\t input_image - initial image for which the list of operations should be performed"<<endl;
    cout<<"\t <operation> - list of operations with arguments"<<endl<<endl;
    cout<<"There are seversal operations that can be performed on the initial image consecutively:"<<endl;
    cout<<"FIND_REGION x y [sens] \t Finds a region of similar pixels starting from pixel (x,y) using the given sensitivity (sens is optional, 1 by default)"<<endl;
    cout<<"FIND_PERIMETER\t\t Finds the contiguous border pixels of the region"<<endl;
    cout<<"FIND_SMOOTH_PERIMETER [tolerance]\t\t Finds a smooth perimeter of the region using Gaussian blur with tolerance (default tolerance is 0.1)"<<endl;
    cout<<"DISPLAY_IMAGE\t\t Displays the input image"<<endl;
    cout<<"DISPLAY_PIXELS\t\t Displays the image of the region after the previous operations on the initial image"<<endl;
    cout<<"SAVE_PIXELS filename \t Saves the image of the region after the previous operations on the initial image"<<endl;
}

//---Parsing the whole command
int cl_interface::clParser(int argc, char *argv[]){

    //Check minimum parameter count
    if (argc == 1) {
        cout<<"No parameters. For more information, type: ip_api --help"<<endl;
        return -1;
    }

    //Help page
    if (strcmp(argv[1],"--help")==0){
        help();
        return 0;
    }

    image_process ip;

    //Input image
    if (!ip.loadImage(argv[1])){
        cout<<"No image data. Please use a correct input image. For more information, type: ip_api --help"<<endl;
        return -1;
    }

    //Opeartions (commands)
    for (int i=2;i<argc;++i){
        if (strcmp(argv[i],"DISPLAY_IMAGE")==0){
            if(!ip.displayImage()){
                cout<<"Error: cannot display image"<<endl;
                return -1;
            }

        } else if (strcmp(argv[i],"FIND_REGION")==0){
            if (i+3>=argc){
                cout<<"Error: Not enough parameter for FIND_REGION (usage: FIND_REGION x y sens)"<<endl;
                return -1;
            }
            int x,y,sens;
            if (!(stringToInt(argv[i+1],x) && stringToInt(argv[i+2],y))){
                cout<<"Error: One of the coordinated for FIND_REGION is not an integer"<<endl;
                return -1;
            }
            if (stringToInt(argv[i+3],sens)){
                ip.findRegion(pixel(x,y),sens);
            }else{
                ip.findRegion(pixel(x,y));
            }

        } else if (strcmp(argv[i],"FIND_PERIMETER")==0){
            ip.findPerimeter();

        } else if (strcmp(argv[i],"DISPLAY_PIXELS")==0){
            ip.displayPixels();

        } else if (strcmp(argv[i],"SAVE_PIXELS")==0){
            if (i+1>=argc){
                cout<<"Error: Not enough parameter for SAVE_PIXELS (usage: SAVE_PIXELS filename)"<<endl;
                return -1;
            }
            ip.savePixels(argv[i+1]);

        } else if (strcmp(argv[i],"FIND_SMOOTH_PERIMETER")==0){
            double smooth_tol;
            if (stringToDouble(argv[i+1],smooth_tol)){
                ip.findSmoothPerimeter(smooth_tol);
            }else{
                ip.findSmoothPerimeter();
            }
        }
    }

    return 0;
}
