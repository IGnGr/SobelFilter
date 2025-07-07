#include "Convolution.h"
#include <iostream>
#include <opencv2/core.hpp>

void Convolution::apply(const cv::Mat& src, cv::Mat& dst) const
{

	assert(src.type() == CV_8U);

	dst = cv::Mat::zeros(src.size(), CV_16S);

	for (int i = 0; i < src.rows; i++)
	{

		int16_t* dstRow = dst.ptr<int16_t>(i);

		for (int j = 0; j < src.cols; j++)
		{

			float sum = 0.0f;

			for (int k = 0; k < m_kernel.rows; k++)
			{
				int kflipped = m_kernel.rows - 1 - k;

				for (int l = 0; l < m_kernel.cols; l++)
				{
					int lflipped = m_kernel.cols - 1 - l;


					int x = i - (m_kernel.rows / 2) + k;
					int y = j - (m_kernel.cols / 2) + l;



					if (x >= 0 && x < src.rows && y >= 0 && y < src.cols)
					{
						const uint8_t* srcRow = src.ptr<uint8_t>(x);
						sum += srcRow[y] * m_kernel[kflipped][lflipped];
					}

				

				}
			}


			dstRow[j] = cv::saturate_cast<int16_t>(sum);

		}
	}




}
