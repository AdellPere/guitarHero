#include <opencv2/highgui/highgui.hpp>
using namespace cv;

int main()
{

    Mat img = imread("/home/jannik/Documents/CV/augaertner.jpg",CV_LOAD_IMAGE_COLOR);
    imshow("opencvtest",img);
    waitKey(0);

    return 0;
}