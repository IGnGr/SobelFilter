#pragma once
#include "Convolution.h"


class VerticalSobelConvolution : public Convolution
{
public:
	VerticalSobelConvolution() : Convolution((cv::Mat_<float>(3, 3) << 1, 2, 1,
																	   0, 0, 0,
																	  -1,-2,-1)) {
	};
};