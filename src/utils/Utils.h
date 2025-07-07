#pragma once

#include<opencv2/opencv.hpp>

class Utils
{

public:
    static void imageToGrey(const cv::Mat& src, cv::Mat& dst);
    static void calculateMagnitude(const cv::Mat& srcX, const cv::Mat& srcY, cv::Mat& dst);
    static void ConvertS16To8U(const cv::Mat& src, cv::Mat& dst);
};