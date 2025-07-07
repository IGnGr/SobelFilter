#pragma once

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

class SobelFilter
{
public:
	static void custom(const cv::Mat& src, cv::Mat& dst);
	static void customOpenMP(const cv::Mat& src, cv::Mat& dst);
	static void nativeOpenCVSobelFilter(const cv::Mat& src, cv::Mat& dst, int ksize, int scale, int delta, int ddepth);
};