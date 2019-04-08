# VSS NoVision

This program is in development to integrate a wide solution for the competition task of robot soccer in the IEEE Very Small Size Soccer. 

More information about the competition can be found in the site http://www.cbrobotica.org/?page_id=81&lang=pt

This is a work in progress!

# Compiling instructions for a linux environment
In order to compile this program you will need the opencv 3.0.1 and the jsoncpp librarys installed in your system. IN the Terminal go to the root folder of the program and type:

`cmake <path to the root folder>`
`make`

# Usage
After finishing the compillation process go to /build/exes/bDetect, run the program by typing in the terminal:

`./main.exe`

After execution of the program it will show it's output in three separated windows: The binary one is the mask used to filter the original image, the other two is the original source image in the natural color space and in a HSV color space. You'll have access to a control panel used to change the filter's configuration for the threshold color mask respectively to the HUE, SATURATION and VALUE of the HSV colors and its interval range.

Further information will be added according to the project evolution.
