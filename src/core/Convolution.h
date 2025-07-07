#pragma once
#include <opencv2/core.hpp>

class Convolution
{
public:
    virtual ~Convolution() = default;
    virtual void apply(const cv::Mat& src, cv::Mat& dst) const;


protected:

    cv::Mat_<float> m_kernel;

    Convolution(const cv::Mat_<float>& kernel) : m_kernel(kernel) { }

};