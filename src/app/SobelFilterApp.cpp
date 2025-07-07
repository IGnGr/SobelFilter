#include "SobelFilterApp.h"

#include "Utils.h"
#include "SobelFilter.h"



int SobelFilterApp::run()
{
	switch (m_mode)
	{
		case 0: return regularRun();
		case 1: return benchRun();

		default: return EXIT_FAILURE;
	}

}

int SobelFilterApp::regularRun()
{
	cv::Mat image, output;

	image = loadImage();

	if (image.empty())
	{
		printf("Error opening image: %s\n", m_inputPath.c_str());
		return EXIT_FAILURE;
	}


	SobelFilter::custom(image, output);
	
	saveImage(output);

	return EXIT_SUCCESS;
}

void SobelFilterApp::saveImage(const cv::Mat& img)
{
	cv::imwrite(m_outputPath, img);
}


int SobelFilterApp::benchRun()
{
	return 0;
}

cv::Mat SobelFilterApp::loadImage()
{
	return cv::imread(m_inputPath, cv::IMREAD_COLOR);
}
