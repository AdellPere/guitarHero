#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;
using namespace cv;

/**
 * @function main
 */
int main( int argc, char** argv )
{
  Mat image, dst;

  /// Load image
  image = imread( "mandrill.jpg", 1 );

  if( !image.data )
    { return -1; }

  // Convert to grey scale
  Mat gray_image;
  cvtColor(image, gray_image, CV_BGR2GRAY);

  /*
  char kernel[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  
  // Threshold by looping through all pixels
  for (int y = 1; y<gray_image.rows - 1; y++) {
    for (int x = 1; x<gray_image.cols - 1; x++) {
        uchar new_value = (gray_image.at<uchar>(y-1, x-1) * kernel[0]
          + gray_image.at<uchar>(y-1, x) * kernel[1]
          + gray_image.at<uchar>(y-1, x+1) * kernel[2]
          + gray_image.at<uchar>(y, x-1) * kernel[3]
          + gray_image.at<uchar>(y, x) * kernel[4]
          + gray_image.at<uchar>(y, x+1) * kernel[5]
          + gray_image.at<uchar>(y+1, x-1) * kernel[6]
          + gray_image.at<uchar>(y+1, x) * kernel[7]
          + gray_image.at<uchar>(y+1, x+1) * kernel[8]) / ((uchar) 9);

        gray_image.at<uchar>(y, x) = new_value;
      } 
    }
    
  imwrite("convolution.jpg", gray_image);*/
  
  Mat sample_image, kernel;
  
  kernel = Mat::ones( 3, 3, CV_32F )/ (float) 9;
  
  filter2D(gray_image, sample_image, -1, kernel);
  
  imwrite("convolution_sample.jpg", sample_image);

  waitKey(0);

  return 0;
}