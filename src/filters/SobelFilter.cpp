// SobelFilter.cpp : Defines the entry point for the application.
//

#include "SobelFilter.h"
#include "GaussianBlur.h"
#include "HorizontalSobelConvolution.h"
#include "VerticalSobelConvolution.h"
#include "Utils.h"



void SobelFilter::custom(const cv::Mat& src, cv::Mat& dst)
{

    cv::Mat  gauss, grey, sobelH, sobelV, sobelAbsH, sobelAbsV;

    GaussianBlur::apply(src, gauss);
    Utils::imageToGrey(gauss, grey);

    HorizontalSobelConvolution horizontal;
    horizontal.apply(grey, sobelH);
    Utils::ConvertS16To8U(sobelH, sobelAbsH);

    VerticalSobelConvolution vertical;
    vertical.apply(grey, sobelV);
    Utils::ConvertS16To8U(sobelV, sobelAbsV);

    Utils::combineWeighted(sobelAbsH, 0.5, sobelAbsV, 0.5, dst);

}

void SobelFilter::customOpenMP(const cv::Mat& src, cv::Mat& dst)
{

    cv::Mat  gauss, grey, sobelH, sobelV, sobelAbsH, sobelAbsV;

    GaussianBlur::applyOpenMP(src, gauss);
    Utils::imageToGrey(gauss, grey);

    HorizontalSobelConvolution horizontal;
    horizontal.applyOpenMP(grey, sobelH);
    Utils::ConvertS16To8U(sobelH, sobelAbsH);

    VerticalSobelConvolution vertical;
    vertical.applyOpenMP(grey, sobelV);
    Utils::ConvertS16To8U(sobelV, sobelAbsV);

    Utils::combineWeighted(sobelAbsH, 0.5, sobelAbsV, 0.5, dst);

}

void SobelFilter::nativeOpenCVSobelFilter(const cv::Mat& src, cv::Mat& dst, int ksize, int scale, int delta, int ddepth)
{

    // First we declare the variables we are going to use
    cv::Mat src_gray;
    cv::Mat grad;

    cv::GaussianBlur(src, dst, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);

    // Convert the image to grayscale
    cvtColor(dst, src_gray, cv::COLOR_BGR2GRAY);

    cv::Mat grad_x, grad_y;
    cv::Mat abs_grad_x, abs_grad_y;

    Sobel(src_gray, grad_x, ddepth, 1, 0, ksize, scale, delta, cv::BORDER_DEFAULT);

    Sobel(src_gray, grad_y, ddepth, 0, 1, ksize, scale, delta, cv::BORDER_DEFAULT);

    // converting back to CV_8U
    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);

    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
}
