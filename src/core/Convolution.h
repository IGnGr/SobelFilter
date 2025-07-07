#pragma once
#include <opencv2/core.hpp>

class Convolution
{
public:
    virtual ~Convolution() = default;
    virtual void apply(const cv::Mat& src, cv::Mat& dst) const;


protected:

    cv::Mat_<float> m_kernel;

    Convolution(const cv::Mat_<float>& kernel)
    {
        //Flipping the kernel

        cv::Mat_<float> dst(kernel.size());

        for (int i = 0; i < kernel.rows; ++i)
        {
            for (int j = 0; j < kernel.cols; ++j)
            {
                dst(i, j) = kernel(kernel.rows - 1 - i, kernel.cols - 1 - j);
            }
        }

        m_kernel = dst;

    }

};