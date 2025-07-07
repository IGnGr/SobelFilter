#pragma once

#include "Convolution.h"


class HorizontalSobelConvolution : public Convolution
{
public:
	HorizontalSobelConvolution() : Convolution((cv::Mat_<float>(3, 3) << -1, 0, 1,
																		 -2, 0, 2,
																		 -1, 0, 1)) {
	};

};