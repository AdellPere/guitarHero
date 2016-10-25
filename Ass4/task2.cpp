#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
//#include <string>
#include <math.h>

using namespace std;
using namespace cv;

int main( int argc, char** argv ) {
  
  /// Parameters
  const int R_MIN = 20;
  const int R_MAX = 100;
  const int INITIAL_THRESHOLD = 20;
  const int VOTER_THRESHOLD = 50;
  const int DISTANCE_BETWEEN_CENTERS = 60;
  
  
  Mat image, image2, original;
  
  image = imread("gradient.png", 1);
  image2 = imread("phi.png", 1);
  original = imread("coins1.png", 1);
  
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
    if(gray_image.at<uchar>(y, x) > INITIAL_THRESHOLD)
      th_image.at<uchar>(y, x) = 255;
    else
      th_image.at<uchar>(y, x) = 0;
    }
  }
  
  imwrite("threshold.png", th_image);
  
  cout << "create Accumulator array" << endl;
  
  int*** Accumulator = new int**[th_image.rows];
  for(int i = 0; i < th_image.rows; i++)
  {
    Accumulator[i] = new int*[th_image.cols];
    for(int j = 0; j < th_image.cols; j++)
    {
      //FIXME: Max Raius half as much
      Accumulator[i][j] = new int[R_MAX - R_MIN];
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
      
      for(int radius = R_MIN; radius < R_MAX; radius++)
      {
        int a = radius * sin(phi);
        int b = radius * cos(phi);
        
        int x0 = x + b;
        int y0 = y + a;
        
        int x1 = x - b;
        int y1 = y - a;
        
        /// vote
        if(x0 > 0 && x0 < th_image.cols && y0 > 0 && y0 < th_image.rows) {
          Accumulator[y0][x0][radius - R_MIN] += 1;
          // cout << "Added y " << y0 << " and x " << x0 << " with radius " << radius << endl;
        }
        if(x1 > 0 && x1 < th_image.cols && y1 > 0 && y1 < th_image.rows) {
          Accumulator[y1][x1][radius - R_MIN] += 1;
          // cout << "Added y " << y1 << " and x " << x1 << " with radius " << radius << endl;
        }
      }
    }
  }
  
  Mat hough_transform;
  
  hough_transform.create(th_image.size(), th_image.type());
  
  int max_radii_sum = 0;
  int x_max = 0;
  int y_max = 0;
  
  for (int y = 1; y<hough_transform.rows - 1; y++) {
    for (int x = 1; x < hough_transform.cols - 1; x++) {
      int radii_sum = 0;
      for(int i = 0; i < R_MAX -R_MIN; i++)
      {
        radii_sum += Accumulator[y][x][i];
      }
      
      if(radii_sum > max_radii_sum)
      {
        max_radii_sum = radii_sum;
        x_max = x;
        y_max = y;
      }
      
      if(radii_sum > 255)
        radii_sum = 255;
      
      // cout << "radii_sum: " << radii_sum << " log: " << log(radii_sum) << endl;
      hough_transform.at<uchar>(y, x) = radii_sum;
    }
  }
  
  cout << "maximum radius sum: " << max_radii_sum << " at x: " << x_max << " and y: " << y_max << endl;
  
  imwrite("houghspace.png", hough_transform);
  
  while(1) {
    x_max = 0;
    y_max = 0;
    max_radii_sum = 0;
    
    for (int y = 1; y<hough_transform.rows - 1; y++) {
      for (int x = 1; x < hough_transform.cols - 1; x++) {
        if(hough_transform.at<uchar>(y, x) > max_radii_sum)
        {
          x_max = x;
          y_max = y;
          max_radii_sum = hough_transform.at<uchar>(y, x);
        }
      }
    }
    
    if(max_radii_sum < VOTER_THRESHOLD)
      break;
    
    
    int considered_radius = 0;
    int radius_count = 0;
  
    for (int i = 0; i < R_MAX - R_MIN; i++) {
      if (Accumulator[y_max][x_max][i] > radius_count) {
        radius_count = Accumulator[y_max][x_max][i];
        considered_radius = i + R_MIN;
      }
    }
    
    //delete Square around peak
    for (int y = 1; y<hough_transform.rows - 1; y++) {
      for (int x = 1; x < hough_transform.cols - 1; x++) {
        if(abs(y - y_max) < DISTANCE_BETWEEN_CENTERS && abs(x - x_max) < DISTANCE_BETWEEN_CENTERS)
        {
          hough_transform.at<uchar>(y, x) = 0;
        }
      }
    }
    
  
    cout << "Radius: " << considered_radius << " with count " << radius_count << " at x " << x_max << " y " << y_max << endl;
  
    circle(original, Point(x_max, y_max), considered_radius, cvScalar(0, 0, 255), 2);
  }
  imwrite("detected.png", original);
  
  for(int i = 0; i < th_image.rows; i++)
  {
    for(int j = 0; j < th_image.cols; j++)
    {
      delete Accumulator[i][j];
    }
    delete Accumulator[i];
  }
  delete Accumulator;
    
  
  return 0;
}
