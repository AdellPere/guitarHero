#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using namespace cv;

/**
 * @function main
 */
int main( int argc, char** argv )
{
  Mat image;
  
  /// Load image
  image = imread( "car2.png", 1 );
  
  if( !image.data )
  {
    printf("SHIAT!\n");
    return -1; }
  
  // Convert to grey scale
  Mat gray_image, outputImage;
  cvtColor(image, gray_image, CV_BGR2GRAY);
  outputImage.create(gray_image.size(), gray_image.type());
  
  // Threshold by looping through all pixels
  for (int y = 1; y<gray_image.rows - 1; y++) {
    for (int x = 1; x<gray_image.cols - 1; x++) {
      
      vector<uchar> pixels;
      
      pixels.push_back(gray_image.at<uchar>(y-1, x-1));
      pixels.push_back(gray_image.at<uchar>(y-1, x));
      pixels.push_back(gray_image.at<uchar>(y-1, x+1));
      pixels.push_back(gray_image.at<uchar>(y, x-1));
      pixels.push_back(gray_image.at<uchar>(y, x));
      pixels.push_back(gray_image.at<uchar>(y, x+1));
      pixels.push_back(gray_image.at<uchar>(y+1, x-1));
      pixels.push_back(gray_image.at<uchar>(y+1, x));
      pixels.push_back(gray_image.at<uchar>(y+1, x+1));
  
      pixels.push_back(gray_image.at<uchar>(y+2, x+2));
      pixels.push_back(gray_image.at<uchar>(y+2, x+1));
      pixels.push_back(gray_image.at<uchar>(y+2, x));
      pixels.push_back(gray_image.at<uchar>(y+2, x-1));
      pixels.push_back(gray_image.at<uchar>(y+2, x-2));
  
      pixels.push_back(gray_image.at<uchar>(y-2, x+2));
      pixels.push_back(gray_image.at<uchar>(y-2, x+1));
      pixels.push_back(gray_image.at<uchar>(y-2, x));
      pixels.push_back(gray_image.at<uchar>(y-2, x-1));
      pixels.push_back(gray_image.at<uchar>(y-2, x-2));
  
      pixels.push_back(gray_image.at<uchar>(y-1, x+2));
      pixels.push_back(gray_image.at<uchar>(y, x+2));
      pixels.push_back(gray_image.at<uchar>(y+1, x+2));
  
      pixels.push_back(gray_image.at<uchar>(y-1, x-2));
      pixels.push_back(gray_image.at<uchar>(y, x-2));
      pixels.push_back(gray_image.at<uchar>(y+1, x-2));
      
      sort(pixels.begin(), pixels.end());
      
      uchar new_value = pixels[12];
      
      
        /*uchar new_value = (gray_image.at<uchar>(y-1, x-1) * kernel[0]
          + gray_image.at<uchar>(y-1, x) * kernel[1]
          + gray_image.at<uchar>(y-1, x+1) * kernel[2]
          + gray_image.at<uchar>(y, x-1) * kernel[3]
          + gray_image.at<uchar>(y, x) * kernel[4]
          + gray_image.at<uchar>(y, x+1) * kernel[5]
          + gray_image.at<uchar>(y+1, x-1) * kernel[6]
          + gray_image.at<uchar>(y+1, x) * kernel[7]
          + gray_image.at<uchar>(y+1, x+1) * kernel[8]) / ((uchar) 9);*/

      outputImage.at<uchar>(y, x) = new_value;
    }
  }
    
  imwrite("recovered2_2.jpg", outputImage);
  
  
  waitKey(0);
  
  return 0;
}