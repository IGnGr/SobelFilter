#pragma once

#include<opencv2/opencv.hpp>

class Utils
{

public:
    static void imageToGrey(const cv::Mat& src, cv::Mat& dst);
    static void combineWeighted(const cv::Mat& srcX, double weight1, const cv::Mat& srcY, double weight2, cv::Mat& dst);
    static void ConvertS16To8U(const cv::Mat& src, cv::Mat& dst);
    static void ConvertS16To8UOpenMP(const cv::Mat& src, cv::Mat& dst);

};