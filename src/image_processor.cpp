#include "image_processor.hpp"
#include <opencv2/imgproc.hpp>
#include <deque>

#include <iostream>

using namespace std;

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
                    
            dst->at<int>(row,col) = std::abs(value);
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

void image_processor::vertical_energy_map(Mat* src, Mat* dst)
{
    int height = src->rows;
    int width = src->cols;

    //initialization of the bottom line.
    for(int c=0 ; c<width ; c++)
        dst->at<int>(height-1,c) = src->at<uchar>(height-1,c);

    //lambda function for searching the minimum in a deque while preserving its structure.
    function<int (deque<int>)> min = [](deque<int> L) 
    { 
        int m = INT32_MAX;
        for(int i : L)
            if(i<m)
                m=i;
        return m;
    };

    deque<int> childs_energy;
    
    for(int row=height-2 ; row>=0 ; row--)
    {
        childs_energy.assign({dst->at<int>(row+1,1), dst->at<int>(row+1,0), INT32_MAX});
        for(int col=0 ; col<width; col++)
        {
            dst->at<int>(row,col) = src->at<int>(row,col) + min(childs_energy); //update the energy of the current pixel.

            //update the list with the energy values of the next right pixel's childs.
            childs_energy.pop_front();
            if(col+2<width){
                childs_energy.push_back(dst->at<int>(row+1,col+2));
            }
            else
                childs_energy.push_back(INT32_MAX);
        }
    }      

}