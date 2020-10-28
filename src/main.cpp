#include "image_processor.hpp"
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;

int main()
{
    Mat img = imread("img/hill.jpg", IMREAD_GRAYSCALE);
    image_processor ip = image_processor();

    int sobel[9] = 
    {
        -1,-2,-1,
        -2, 0, 2,
         1, 2, 1
    };

    Mat kernel = Mat( 3, 3, CV_32S, sobel );

    Mat res = Mat(img.rows, img.cols, img.type());
    ip.convolve(&img, &res, &kernel);

    imshow("result", res);
    waitKey(0);
    
    destroyAllWindows(); 
    return 0;
}