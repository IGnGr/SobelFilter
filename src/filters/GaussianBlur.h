#pragma once

#include <opencv2/opencv.hpp>

class GaussianBlur 
{


public:
	// TODO: Add ksize
	static void apply(const cv::Mat& src, cv::Mat& dest);


};
