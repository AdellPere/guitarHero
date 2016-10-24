#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
//#include <string>
#include <math.h>

using namespace std;
using namespace cv;

int main( int argc, char** argv ) {
  int r_min = 20;
  int r_max = 200;
  
  Mat image, image2;
  
  image = imread("gradient.png", 1);
  image2 = imread("phi.png", 1);
  
  if (!image.data) { return -1; }
  if (!image2.data) { return -1; }
  
  Mat gray_image;
  cvtColor(image, gray_image, CV_BGR2GRAY);
  
  Mat phi_image;
  cvtColor(image2, phi_image, CV_BGR2GRAY);
  
  Mat th_image;
  th_image.create(gray_image.size(), gray_image.type());
  
  for (int y = 0; y<gray_image.rows; y++) {
    for (int x = 0; x < gray_image.cols; x++) {
    if(gray_image.at<uchar>(y, x) > 25)
      th_image.at<uchar>(y, x) = 255;
    else
      th_image.at<uchar>(y, x) = 0;
    }
  }
  
  imwrite("threshold.png", th_image);
  
  cout << "create Accumulator array" << endl;
  
  int*** Accumulator = new int**[341];
  for(int i = 0; i < 341; i++)
  {
    Accumulator[i] = new int*[441];
    for(int j = 0; j < 441; j++)
    {
      Accumulator[i][j] = new int[180];
    }
  }
  
  cout << "Accumulator created" << endl;
  
  for (int y = 0; y<th_image.rows; y++) {
    for (int x = 0; x < th_image.cols; x++) {
      // only consider white points
      if(th_image.at<uchar>(y, x) == 0)
        continue;
      
      uchar img_phi = phi_image.at<uchar>(y, x);
      float phi = ((float) img_phi * M_PI) / 255 - M_PI / 2;
      
      for(int radius = r_min; radius <= r_max; radius++)
      {
        int a = radius * sin(phi);
        int b = radius * cos(phi);
        
        int x0 = x + b;
        int y0 = y + a;
        
        if(x0 > 0 && x0 < th_image.cols && y0 > 0 && y0 < th_image.rows) {
          Accumulator[y0][x0][radius - r_min] += 1;
          // cout << "Added y " << y0 << " and x " << x0 << " with radius " << radius << endl;
        }
      }
      
    }
  }
  
  for(int i = 0; i < 341; i++)
  {
    for(int j = 0; j < 441; j++)
    {
      delete Accumulator[i][j];
    }
    delete Accumulator[i];
  }
  delete Accumulator;
  
  return 0;
}
