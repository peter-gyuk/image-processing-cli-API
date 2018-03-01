#include "cl_interface.h"

void cl_interface::help()
{
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

int cl_interface::cl(int argc, char *argv[])
{
    //Check parameter count
    if (argc == 1) {
        cout<<"No parameters. For more information, type: ip_api --help"<<endl;
        return -1;
    }

    //Help page
    if (strcmp(argv[1],"--help")==0){
        help();
        return -1;
    }

    //Input image
    image img;
    if (!img.load_image(argv[1])){
        cout<<"No image data. Please use a correct input image. For more information, type: ip_api --help"<<endl;
        return -1;
    }

    //Commands
    region tmp; //This is the current region of the sequence of operations
    for (int i=2;i<argc;++i){

        if (strcmp(argv[i],"DISPLAY_IMAGE")==0){
            if(!img.display_image()){
                cout<<"Error displaying image"<<endl;
                return -1;
            }

        } else if (strcmp(argv[i],"FIND_REGION")==0){
            if (i+3>=argc){
                cout<<"Not enough parameter for FIND_REGION (usage: FIND_REGION x y sens)"<<endl;
                return -1;
            }
            //TODO: error handling
            tmp=image_process::find_region(img,pixel(atoi(argv[i+1]),atoi(argv[i+2])),stod(argv[i+3]));

        } else if (strcmp(argv[i],"FIND_PERIMETER")==0){
            tmp=image_process::find_perimeter(tmp);

        } else if (strcmp(argv[i],"DISPLAY_PIXELS")==0){
            img.display_pixels(tmp);

        } else if (strcmp(argv[i],"SAVE_PIXELS")==0){
            if (i+1>=argc){
                cout<<"Not enough parameter for SAVE_PIXELS (usage: SAVE_PIXELS filename)"<<endl;
                return -1;
            }
            img.save_pixels(tmp,argv[i+1]);

        }
    }

    return 0;
}
