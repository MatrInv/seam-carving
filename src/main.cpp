#include "image_processor.hpp"
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;

int main()
{
    Mat img = imread("img/hill.jpg", IMREAD_GRAYSCALE);
    image_processor ip = image_processor();

    Mat grad = Mat(img.rows, img.cols, CV_32S);
    ip.gradient_map(&img, &grad);

    Mat ener = Mat(img.rows, img.cols, CV_32S);
    ip.vertical_energy_map(&grad, &ener);

    //make the maps displayable
    Mat tmp = Mat(img.rows, img.cols, CV_32S);
    
    Mat img_grad = Mat(img.rows, img.cols, CV_8U);
    normalize(grad, tmp, 255, 0,NORM_MINMAX);
    tmp.convertTo(img_grad,CV_8U);

    Mat img_ener = Mat(img.rows, img.cols, CV_8U);
    normalize(ener, tmp, 255, 0,NORM_MINMAX);
    tmp.convertTo(img_ener,CV_8U);

    imshow("Image", img);
    imshow("Gradient", img_grad);
    imshow("Energy", img_ener);
    waitKey(0);
    
    destroyAllWindows();
    return 0;
}