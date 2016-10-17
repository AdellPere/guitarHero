//
// Created by jannik on 03/10/16.
//

#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup

using namespace cv;

int main() {

    // Read image from file
    Mat image = imread("mandrillRGB.jpg", 1);


    // Threshold by looping through all pixels
    for (int y = 0; y<image.rows; y++) {
        for (int x = 0; x<image.cols; x++) {
            if(image.at<Vec3b>(x, y)[0] > 128)
                image.at<Vec3b>(x, y)[0] = 255;
            else
                image.at<Vec3b>(x, y)[0] = 0;

            if(image.at<Vec3b>(x, y)[1] > 128)
                image.at<Vec3b>(x, y)[1] = 255;
            else
                image.at<Vec3b>(x, y)[1] = 0;

            if(image.at<Vec3b>(x, y)[2] > 128)
                image.at<Vec3b>(x, y)[2] = 255;
            else
                image.at<Vec3b>(x, y)[2] = 0;

        }
    }

    //Save thresholded image
    imwrite("colour_thr.jpg", image);

    return 0;
}