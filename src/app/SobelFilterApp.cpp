#include "SobelFilterApp.h"
#include "GaussianBlur.h"
#include "HorizontalSobelConvolution.cpp"
#include "VerticalSobelConvolution.cpp"
#include "Utils.h"

int SobelFilterApp::run()
{
	cv::Mat image, output, gauss, grey, sobelH, sobelV, sobelAbsH, sobelAbsV, out;

	image = loadImage();

	if (image.empty())
	{
		printf("Error opening image: %s\n", m_inputPath.c_str());
		return EXIT_FAILURE;
	}


	GaussianBlur::apply(image, gauss);
	Utils::imageToGrey(gauss, grey);

	HorizontalSobelConvolution horizontal;
	horizontal.apply(grey, sobelH);
	Utils::ConvertS16To8U(sobelH, sobelAbsH);

	VerticalSobelConvolution vertical;
	vertical.apply(grey, sobelV);
	Utils::ConvertS16To8U(sobelV, sobelAbsV);

	Utils::calculateMagnitude(sobelAbsH, sobelAbsV, out);

	output = out;

	saveImage(output);

	return EXIT_SUCCESS;
}

void SobelFilterApp::saveImage(const cv::Mat& img)
{
	cv::imwrite(m_outputPath, img);
}


cv::Mat SobelFilterApp::loadImage()
{
	return cv::imread(m_inputPath, cv::IMREAD_COLOR);
}
