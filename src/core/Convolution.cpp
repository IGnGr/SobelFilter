#include "Convolution.h"
#include <iostream>
#include <opencv2/core.hpp>

void Convolution::apply(const cv::Mat& src, cv::Mat& dst) const
{



	dst = cv::Mat::zeros(src.size(), CV_16S);

	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{

			float sum = 0.0f;

			for (int k = 0; k < m_kernel.rows; k++)
			{
				for (int l = 0; l < m_kernel.cols; l++)
				{
					int x = i - (m_kernel.rows / 2) + k;
					int y = j - (m_kernel.cols / 2) + l;

					if (x >= 0 && x < src.rows && y >= 0 && y < src.cols)
						sum += src.at<uint8_t>(x, y) * m_kernel[k][l];
				

				}
			}


			dst.at<int16_t>(i, j) = cv::saturate_cast<int16_t>(sum);

		}
	}




}
