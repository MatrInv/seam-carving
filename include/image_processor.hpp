#include <opencv2/core/mat.hpp>

using namespace cv;

class image_processor
{
    public:
    image_processor();
    void convolve(Mat* src, Mat* dst, Mat* kernel);
    void gradient_map(Mat* src, Mat* dst);
    void energy_map(Mat* src, Mat* dst);
};