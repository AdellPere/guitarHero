#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup

using namespace cv;

int main() {

    // Read image from file
    Mat image = imread("mandrill.jpg", 1);

    // Convert to grey scale
    Mat gray_image;
    cvtColor(image, gray_image, CV_BGR2GRAY);

    // Threshold by looping through all pixels
    for (int y = 0; y<gray_image.rows; y++) {
        for (int x = 0; x<gray_image.cols; x++) {
            uchar pixel = gray_image.at<uchar>(x, y);
            if(pixel > 128)
                gray_image.at<uchar>(x,y) = 255;
            else
                gray_image.at<uchar>(x,y) = 0;
        }
    }

    //Save thresholded image
    imwrite("grey_thr.jpg", gray_image);

    return 0;
}
