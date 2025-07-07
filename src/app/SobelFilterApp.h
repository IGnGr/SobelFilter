#pragma once

#include <opencv2/core.hpp>

class SobelFilterApp
{
public:
	SobelFilterApp(const cv::String& inputPath, const cv::String& outputPath, int mode) : 
		m_inputPath(inputPath), m_outputPath(outputPath), m_mode(mode) {};
	int regularRun();
	int benchRun();
	int run();


private:
	cv::String m_inputPath, m_outputPath;
	int  m_mode;

	cv::Mat loadImage();
	void saveImage(const cv::Mat& img);

};
