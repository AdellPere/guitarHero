#include <stdio.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main( int argc, const char** argv )
{
  // 1. Read Input Image
  Mat frame = imread("dart15.jpg", CV_LOAD_IMAGE_COLOR);
  
  rectangle(frame, Point(548, 121) , Point(602, 175), Scalar( 0, 255, 0 ), 2);
  rectangle(frame, Point(534, 130) , Point(614, 210), Scalar( 255, 0, 0 ), 2);
  
  // 4. Save Result Image
  imwrite( "intersection.jpg", frame );
  
  return 0;
}