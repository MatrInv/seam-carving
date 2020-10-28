#include "image_processor.hpp"
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;

int main()
{
    Mat img = imread("img/hill.jpg", IMREAD_GRAYSCALE);
    image_processor ip = image_processor();

    Mat res = Mat(img.rows, img.cols, img.type());
    ip.gradient_map(&img, &res);

    imshow("result", res);
    waitKey(0);
    
    destroyAllWindows(); 
    return 0;
}