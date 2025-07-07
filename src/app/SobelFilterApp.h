#pragma once

#include <opencv2/core.hpp>

class SobelFilterApp
{
public:
	SobelFilterApp(const cv::String& inputPath, const cv::String& outputPath, const cv::String& mode, int iters) : 
		m_inputPath(inputPath), m_outputPath(outputPath), m_mode(mode), m_iters(iters) {};
	int regularRun();
	int benchRun();
	int openMPRun();
	int run();


private:
	cv::String m_inputPath, m_outputPath, m_mode;
	int m_iters;

	cv::Mat loadImage();
	void saveImage(const cv::Mat& img);

};
