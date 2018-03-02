# image-processing-cli-API
Image processing API with command line interface

## How to compile and execute
The API is developed on Ubuntu 16.04 with cmake and opencv. In order to compile you should have these installed. Simply:
```
cmake.
make
./ip_api
```
Example:
```
./ip_api data/test1.png DISPLAY_IMAGE FIND_REGION 150 50 5 FIND_PERIMETER DISPLAY_PIXELS
```

## How to use
The image processing API has a command line interface with full functionality. For detailed information about the commands, just type `ip_api --help`

usage: 
```
ip_api input_image <operation>
```
The input_image is necessary, this is the initial image for which the list of operations should be performed.

There are several operations that can be performed on the initial image consecutively:

**FIND_REGION x y [sens]** - Finds a region of similar pixels starting from pixel (x,y) using the given sensitivity (sens). The sensitivity, which is optional, means the color distance in HSV color space (1 by default). By increasing this parameter, the algorithm becomes more "tolerant" possibly filling bigger areas. Setting this value to 0 results in only 1 point of region: (x,y), setting it to 1 results in finding only the same color.

**FIND_PERIMETER** - Finds the contiguous border pixels of the region. No additional parameters needed. This is performed on the previous region. It is possible to find more regions and then the perimeter, but in this phase this only works for 1 convex object.

**FIND_SMOOTH_PERIMETER [tolerance]** - Finds the contiguous border pixels of the smoothed region. The tolerance is an optional parameter, which is 0.1 by default. Decrease tolerance to to remove small artifacts, jagged contours. The algorithm uses discrete convolution with Gaussian blur kernel of kernel size 5.

**DISPLAY_IMAGE** - Displays the input image without any operations

**DISPLAY_PIXELS** - Displays the image of the region overlay on the original image after the previous operations

**SAVE_PIXELS** filename - Saves the image of the region after the previous operations as an overlay in color black on the initial image in the given file

## Testing

To run test, simply type `ctest` or `make test` after compiling.

New tests can be added to the CMakeLists.txt file.

*Smoothing* - The results of smoothing can be easily seen with running a smooth perimeter finder on test3.png with 0.1 and then 0.05 tolerance. The latter totally removes the small object inside:
```
ip_api data/test3.png FIND_REGION 100 100 1 FIND_SMOOTH_PERIMETER 0.2 SAVE_PIXELS out_smooth_2.png
ip_api data/test3.png FIND_REGION 100 100 1 FIND_SMOOTH_PERIMETER 0.05 SAVE_PIXELS out_smooth_05.png
```

## Classes

**cli_interface** - responsible for the CLI interactions with error handling

**image** - stores the input image and performs operations with it

**image_process** - responsible for processing the whole sequence of operations on the initial image, implements the operations

**pixel** - the representation of one pixel without color with some helper function (step to right, up, left, down), the class can be extended to increase color depth

**region** - a set of pixels and functions

## References and making choices

For the backtracking algorithm to find a region starting from the given middle point, I haven't used any references, I implemented it on my own. The recursive method is not very effective, it can be later improved using dynamic programming.

For finding perimeter, the Bug Following algorithm was used with backtracking, as an own implementation. I tried to use algorithms that I have learned and already used before. These are maybe less effective (other edge detection algorithms could be used, like Canny), but the implementation was more straightforward and also avoided using complex libraries.

For smoothing, I also implemented an own 2D discrete convolution. I used Gaussian blur as a basic solution, where I chose the 5x5 kernel. Other methods, such as spline, curve fitting could be used, but I have the experience with this method. It would be also a good improvement to use some kind of noise reduction convolution to eliminate small object (e.g. the small dots on test3.png), like Median or Outlier filtering. The approximated 5x5 Gaussian kernel is taken from here:
[https://homepages.inf.ed.ac.uk/rbf/HIPR2/gsmooth.htm](https://homepages.inf.ed.ac.uk/rbf/HIPR2/gsmooth.htm)
