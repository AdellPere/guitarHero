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
  Mat src, dst;

  /// Load image
  src = imread( "mandrill0.jpg", 1 );

  if( !src.data )
    { return -1; }

  /// Separate the image in 3 places ( B, G and R )
  vector<Mat> bgr_planes;
  split( src, bgr_planes );

  vector<Mat> rbg_planes;

  rbg_planes.push_back(bgr_planes[2]);
  rbg_planes.push_back(bgr_planes[0]);
  rbg_planes.push_back(bgr_planes[1]);

  Mat recImage;
  merge(rbg_planes, recImage);

  imwrite("recovered0.jpg", recImage);

  waitKey(0);

  return 0;
}