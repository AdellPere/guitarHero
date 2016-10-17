#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;
using namespace cv;

uchar validate(int value);
void sobel(Mat image);

/**
 * @function main
 */
int main( int argc, char** argv )
{
  Mat image;
  
  /// Load image
  image = imread( "coins1.png", 1 );
  
  if( !image.data )
  { return -1; }
  
  sobel(image);
  
  return 0;
}


uchar validate(int value)
{
  if(value > 255)
    return 255;
  if(value < 0)
    return 0;
  
  return value;
}

void sobel(Mat image)
{
  Mat gray_image;
  cvtColor(image, gray_image, CV_BGR2GRAY);
  
  // ######################### delta x ################################
  Mat dx_image;
  dx_image.create(gray_image.size(), gray_image.type());
  
  char dx_kernel[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
  
  for (int y = 1; y<gray_image.rows - 1; y++) {
    for (int x = 1; x<gray_image.cols - 1; x++) {
      int new_value = (gray_image.at<uchar>(y-1, x-1) * dx_kernel[0]
                       + gray_image.at<uchar>(y-1, x) * dx_kernel[1]
                       + gray_image.at<uchar>(y-1, x+1) * dx_kernel[2]
                       + gray_image.at<uchar>(y, x-1) * dx_kernel[3]
                       + gray_image.at<uchar>(y, x) * dx_kernel[4]
                       + gray_image.at<uchar>(y, x+1) * dx_kernel[5]
                       + gray_image.at<uchar>(y+1, x-1) * dx_kernel[6]
                       + gray_image.at<uchar>(y+1, x) * dx_kernel[7]
                       + gray_image.at<uchar>(y+1, x+1) * dx_kernel[8]) / ((uchar) 9);
      
      dx_image.at<uchar>(y, x) = validate(new_value);
    }
  }
  
  imwrite("deltaX.png", dx_image);
  
  // ######################### delta y ################################
  Mat dy_image;
  dy_image.create(gray_image.size(), gray_image.type());
  
  char dy_kernel[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
  
  for (int y = 1; y<gray_image.rows - 1; y++) {
    for (int x = 1; x<gray_image.cols - 1; x++) {
      int new_value = (gray_image.at<uchar>(y-1, x-1) * dy_kernel[0]
                       + gray_image.at<uchar>(y-1, x) * dy_kernel[1]
                       + gray_image.at<uchar>(y-1, x+1) * dy_kernel[2]
                       + gray_image.at<uchar>(y, x-1) * dy_kernel[3]
                       + gray_image.at<uchar>(y, x) * dy_kernel[4]
                       + gray_image.at<uchar>(y, x+1) * dy_kernel[5]
                       + gray_image.at<uchar>(y+1, x-1) * dy_kernel[6]
                       + gray_image.at<uchar>(y+1, x) * dy_kernel[7]
                       + gray_image.at<uchar>(y+1, x+1) * dy_kernel[8]) / ((uchar) 9);
      
      dy_image.at<uchar>(y, x) = validate(new_value);
    }
  }
  
  imwrite("deltaY.png", dy_image);
}