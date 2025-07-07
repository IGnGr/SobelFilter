#include "GaussianBlur.h"
#include <omp.h>


void GaussianBlur::apply(const cv::Mat& src, cv::Mat& dst)
{
	//TODO: Generalize using binomialCoefficient to generate kernels of size 5,7,etc...
	cv::Mat_<float> oneDKernel = (cv::Mat_<float>(3,1) << 0.25, 0.5, 0.25);

	std::vector<cv::Mat> channels;
	cv::split(src, channels);

	for (auto& channel : channels)
	{
		cv::Mat temp = channel.clone();

		//Horizontal pass
		for (int i = 0; i < temp.rows; i++)
		{
			uint8_t* srcRow = temp.ptr<uint8_t>(i);
			uint8_t* dstRow = channel.ptr<uint8_t>(i);

			for (int j = 1; j < temp.cols - 1; j++)
			{
				double sum = 0.0;
				for (int k = 0; k < oneDKernel.rows; k++)
				{
					sum += srcRow[j + k - 1] * oneDKernel[k][0];
				}
				dstRow[j] = cv::saturate_cast<uint8_t>(sum);
			}
		}
		
		//Vertical pass
		for (int i = 0; i < temp.cols; i++)
		{
			for (int j = 1; j < temp.rows - 1; j++)
			{

				uint8_t* dstRow = channel.ptr<uint8_t>(j);

				double sum = 0.0;
				for (int k = 0; k < oneDKernel.rows; k++)
				{

					uint8_t* srcRow = temp.ptr<uint8_t>(j + k - 1);

					sum += srcRow[i] * oneDKernel[k][0];
				}
				dstRow[i] = cv::saturate_cast<uint8_t>(sum);
			}
		}
		
	}
	

	cv::merge(channels, dst);


}

void GaussianBlur::applyOpenMP(const cv::Mat& src, cv::Mat& dst)
{
	
	//TODO: Generalize using binomialCoefficient to generate kernels of size 5,7,etc...
	cv::Mat_<float> oneDKernel = (cv::Mat_<float>(3, 1) << 0.25, 0.5, 0.25);

	std::vector<cv::Mat> channels;
	cv::split(src, channels);





	for (int c = 0; c < channels.size(); c++)
	{
		cv::Mat& channel = channels[c];


		cv::Mat temp = channel.clone();

		//Horizontal pass
		#pragma omp parallel for
		for (int i = 0; i < temp.rows; i++)
		{
			uint8_t* srcRow = temp.ptr<uint8_t>(i);
			uint8_t* dstRow = channel.ptr<uint8_t>(i);

			for (int j = 1; j < temp.cols - 1; j++)
			{
				double sum = 0.0;
				for (int k = 0; k < oneDKernel.rows; k++)
				{
					sum += srcRow[j + k - 1] * oneDKernel[k][0];
				}
				dstRow[j] = cv::saturate_cast<uint8_t>(sum);
			}
		}

		//Vertical pass
		#pragma omp parallel for
		for (int i = 0; i < temp.cols; i++)
		{
			for (int j = 1; j < temp.rows - 1; j++)
			{

				uint8_t* dstRow = channel.ptr<uint8_t>(j);

				double sum = 0.0;
				for (int k = 0; k < oneDKernel.rows; k++)
				{

					uint8_t* srcRow = temp.ptr<uint8_t>(j + k - 1);

					sum += srcRow[i] * oneDKernel[k][0];
				}
				dstRow[i] = cv::saturate_cast<uint8_t>(sum);
			}
		}

	}


	cv::merge(channels, dst);


}
