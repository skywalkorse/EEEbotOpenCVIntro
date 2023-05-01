// Include files for required libraries
#include <stdio.h>

#include "opencv_aee.hpp"
#include "main.hpp"     // You can use this file for declaring defined values and functions
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void setup(void)
{
    /// Setup camera won't work if you don't have a compatible webcam
    //setupCamera(320, 240);  // Enable the camera for OpenCV
}

int main( int argc, char** argv )
{
    // Load the image
    Mat image = imread("BlueCar.bmp");

    // Convert the image to the HSV color space
    Mat hsv_image;
    cvtColor(image, hsv_image, COLOR_BGR2HSV);

    // Define the range of blue color in HSV
    Scalar lower_blue = Scalar(100, 50, 50);
    Scalar upper_blue = Scalar(130, 255, 255);

    // Define the range of red color in HSV
    Scalar lower_red1 = Scalar(0, 50, 50);
    Scalar upper_red1 = Scalar(10, 255, 255);
    Scalar lower_red2 = Scalar(170, 50, 50);
    Scalar upper_red2 = Scalar(180, 255, 255);

    // Define the range of green color in HSV
    Scalar lower_green = Scalar(40, 50, 50);
    Scalar upper_green = Scalar(70, 255, 255);

    // Threshold the image to find the main body
    Mat mask_blue, mask_red, mask_green, mask_red2;
    inRange(hsv_image, lower_blue, upper_blue, mask_blue);
    inRange(hsv_image, lower_red1, upper_red1, mask_red);
    inRange(hsv_image, lower_red2, upper_red2, mask_red2);
    inRange(hsv_image, lower_green, upper_green, mask_green);

    // Count the number of pixels in each color range
    int blue_pixels = countNonZero(mask_blue);
    int red_pixels = countNonZero(mask_red) + countNonZero(mask_red2);
    int green_pixels = countNonZero(mask_green);

    // Determine the color of the main body
    if (blue_pixels > red_pixels && blue_pixels > green_pixels)
    {
        cout << "The main body is blue." << endl;
    }
    else if (red_pixels > blue_pixels && red_pixels > green_pixels)
    {
        cout << "The main body is red." << endl;
    }
    else if (green_pixels > blue_pixels && green_pixels > red_pixels)
    {
        cout << "The main body is green." << endl;
    }
    else
    {
        cout << "The color of the main body could not be determined." << endl;
    }

    return 0;
}



