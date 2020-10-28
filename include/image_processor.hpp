#include <opencv2/core/mat.hpp>

using namespace cv;

class image_processor
{
    public:
    image_processor();
    void convolve(Mat* img, Mat* dst, Mat* kernel);
};