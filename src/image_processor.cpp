#include "image_processor.hpp"
#include <opencv2/imgproc.hpp>

#include <iostream>


image_processor::image_processor()
{};

void image_processor::convolve(Mat* src, Mat* dst, Mat* kernel)
{
    int height = src->rows;
    int width = src->cols;
    
    int offset_Y = kernel->rows / 2; 
    int offset_X = kernel->cols / 2;

    int value;
    for(int row=0 ; row<height ; row++)
        for(int col=0 ; col<width ; col++)
        {
            value = 0;
            for(int j=-offset_Y ; j<=offset_Y ; j++)
                for(int i=-offset_X ; i<=offset_X ; i++)
                    if(row+j<height && row+j>=0 && col+i<width && col+i>=0)
                        value += (int)src->at<uchar>(row+j,col+i) * kernel->at<int>(j+offset_Y,i+offset_X) ;
                    
            dst->at<uchar>(row,col) = (uchar)std::abs(value / 4);
        }
}

void image_processor::gradient_map(Mat* src, Mat* dst)
{
    int sobel[9] = 
    {
        -1,-2,-1,
        -2, 0, 2,
         1, 2, 1
    };

    Mat kernel = Mat( 3, 3, CV_32S, sobel );

    this->convolve(src, dst, &kernel);
}