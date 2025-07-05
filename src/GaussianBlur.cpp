#include "GaussianBlur.h"


void GaussianBlur::apply(const cv::Mat& src, cv::Mat& dest)
{
	//TODO: Generalize using binomialCoefficient to generate kernels of size 5,7,etc...
	cv::Vec<double,3> oneDKernel = cv::Vec<double,3>(0.25, 0.5, 0.25);

	cv::Mat output;
	std::vector<cv::Mat> channels;
	cv::split(src, channels);

	for (auto& channel : channels)
	{
		cv::Mat temp = channel.clone();

		//Horizontal pass
		for (int i = 0; i < temp.rows; i++)
		{
			for (int j = 1; j < temp.cols - 1; j++)
			{
				double sum = 0.0;
				for (int k = 0; k < oneDKernel.rows; k++)
				{
					sum += temp.at<uint8_t>(i, j + k - 1) * oneDKernel[k];
				}
				temp.at<uint8_t>(i, j) = cv::saturate_cast<uint8_t>(sum);
			}
		}
		
		//Vertical pass
		for (int i = 0; i < temp.cols; i++)
		{
			for (int j = 1; j < temp.rows - 1; j++)
			{
				double sum = 0.0;
				for (int k = 0; k < oneDKernel.rows; k++)
				{
					sum += temp.at<uint8_t>(j + k - 1, i) * oneDKernel[k];
				}
				channel.at<uint8_t>(j, i) = cv::saturate_cast<uint8_t>(sum);
			}
		}
		
	}
	

	cv::merge(channels, dest);


}
