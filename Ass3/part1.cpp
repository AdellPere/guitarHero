#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup
#include <cmath>


using namespace cv;

uchar validatePixel(int pixel)
{
  if(pixel < 0)
  {
    return 0;
  }
  if(pixel > 255)
  {
    return 255;
  }
}

int main( int argc, char** argv ) {
  Mat image;
  image = imread("car1.png", 1);
  
  Mat gray_image;
  cvtColor(image, gray_image, CV_BGR2GRAY);
  
  Mat blurredImage;
  blurredImage.create(gray_image.size(), gray_image.type());
  
  imwrite("gray1.png", gray_image);
  
  Size ksize(3, 3);
  
  GaussianBlur(gray_image, blurredImage, ksize, -1);
  imwrite("blur1.png", blurredImage);
  
  Mat outputImage;
  outputImage.create(gray_image.size(), gray_image.type());
  
  int iterations = 8;
  double amount = 0;
  //for(int i=0; i<iterations; i++) {
    for (int y = 0; y < image.rows; y++) { //go through all rows (or scanlines)
      for (int x = 0; x < image.cols; x++) { //go through all columns
        
        int new_pixel = (int) gray_image.at<uchar>(y, x)
                        + ((int) gray_image.at<uchar>(y, x) - (int) blurredImage.at<uchar>(y, x))*iterations;
        outputImage.at<uchar>(y, x) = validatePixel(new_pixel);
      }
    }
    //gray_image = outputImage;
  
  //}
  
  imwrite("recovered1.png", outputImage);

  
  return 0;
}
