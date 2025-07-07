#pragma once

#include <opencv2/core.hpp>

class SobelFilterApp
{
public:
	SobelFilterApp(const cv::String& inputPath, const cv::String& outputPath) : m_inputPath(inputPath), m_outputPath(outputPath) {};
	int run();


private:
	cv::String m_inputPath, m_outputPath;

	cv::Mat loadImage();
	void saveImage(const cv::Mat& img);

};
