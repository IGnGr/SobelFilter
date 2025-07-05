#pragma once

#include <iostream>

/*
+Denoiser (Gaussian)
-Convert to greyscale (OpenCV usa BGR)
-Sobel vertical
//	cv::Mat kernel = cv::Mat(ksize, ksize, CV_64F);
-Sobel horizontal
-Rescale (Convert back to unsigned 8bit integer)
-Add both sobel weighted 50% each
-save it (and/or show it)
*/

