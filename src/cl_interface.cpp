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

//---Help message display
void cl_interface::help(){

    cout<<"---ip_api HELP PAGE---"<<endl<<endl;
    cout<<"usage: ip_api input_image <operation>"<<endl;
    cout<<"\t input_image - initial image for which the list of operations should be performed"<<endl;
    cout<<"\t <operation> - list of operations with arguments"<<endl<<endl;
    cout<<"There are seversal operations that can be performed on the initial image consecutively:"<<endl;
    cout<<"FIND_REGION x y sens \t Finds a region of similar pixels starting from pixel (x,y) using the given sensitivity (sens)"<<endl;
    cout<<"FIND_PERIMETER\t\t Finds the contiguous border pixels of the region"<<endl;
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

    //Input image
    image img;
    if (!img.load_image(argv[1])){
        cout<<"No image data. Please use a correct input image. For more information, type: ip_api --help"<<endl;
        return -1;
    }

    //Opeartions (commands)
    region tmp; //This is the current region resulting from the sequence of operations
    for (int i=2;i<argc;++i){

        if (strcmp(argv[i],"DISPLAY_IMAGE")==0){
            if(!img.display_image()){
                cout<<"Error: cannot display image"<<endl;
                return -1;
            }

        } else if (strcmp(argv[i],"FIND_REGION")==0){
            if (i+3>=argc){
                cout<<"Error: Not enough parameter for FIND_REGION (usage: FIND_REGION x y sens)"<<endl;
                return -1;
            }
            int x,y,sens;
            if (!(stringToInt(argv[i+1],x) && stringToInt(argv[i+2],y) && stringToInt(argv[i+3],sens))){
                cout<<"Error: One of the parameters is not an integer"<<endl;
                return -1;
            }
            tmp=image_process::find_region(img,pixel(x,y),sens);

        } else if (strcmp(argv[i],"FIND_PERIMETER")==0){
            tmp=image_process::find_perimeter(tmp);

        } else if (strcmp(argv[i],"DISPLAY_PIXELS")==0){
            img.display_pixels(tmp);

        } else if (strcmp(argv[i],"SAVE_PIXELS")==0){
            if (i+1>=argc){
                cout<<"Error: Not enough parameter for SAVE_PIXELS (usage: SAVE_PIXELS filename)"<<endl;
                return -1;
            }
            img.save_pixels(tmp,argv[i+1]);

        }
    }

    return 0;
}
