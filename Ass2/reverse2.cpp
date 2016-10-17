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
  image = imread( "mandrill2.jpg", 1 );

  if( !image.data )
    { return -1; }

  for (int y = 0; y < image.rows; y++) //go through all rows (or scanlines)
    for (int x = 0; x < image.cols; x++) { //go through all columns
      image.at<Vec3b>(y, x)[0] = 255 - image.at<Vec3b>(y, x)[0]; //set blue component
      image.at<Vec3b>(y, x)[1] = 255 - image.at<Vec3b>(y, x)[1]; //set green component  
      image.at<Vec3b>(y, x)[2] = 255 - image.at<Vec3b>(y, x)[2]; //set red component
    }

  imwrite("recovered2.jpg", image);

  waitKey(0);

  return 0;
}