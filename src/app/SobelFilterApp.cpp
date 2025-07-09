#include "SobelFilterApp.h"

#include "Utils.h"
#include "SobelFilter.h"
#include <omp.h>


int SobelFilterApp::run()
{
	if (m_mode == "r") return regularRun();
	if (m_mode == "b") return benchRun();
    if (m_mode == "o") return openMPRun();

	return EXIT_FAILURE;
	

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

int SobelFilterApp::openMPRun()
{
    cv::Mat image, output;

    image = loadImage();

    if (image.empty())
    {
        printf("Error opening image: %s\n", m_inputPath.c_str());
        return EXIT_FAILURE;
    }


    SobelFilter::customOpenMP(image, output);

    saveImage(output);

    return EXIT_SUCCESS;
}

void SobelFilterApp::saveImage(const cv::Mat& img)
{
	cv::imwrite(m_outputPath, img);
}


int dummy_error_handler(int status
	, char const* func_name
	, char const* err_msg
	, char const* file_name
	, int line
	, void* userdata)
{
	//Do nothing -- will suppress console output
	return 0;   //Return value is not used
}

void set_dummy_error_handler()
{
	cv::redirectError(dummy_error_handler);
}

void reset_error_handler()
{
	cv::redirectError(nullptr);
}

int SobelFilterApp::benchRun()
{
	
    cv::Mat image = loadImage();

    if (image.empty())
    {
        std::cerr << "Error opening image: " << m_inputPath << "\n";
        return EXIT_FAILURE;
    }

    double serialCustomTotalMs = 0.0;

    for (int i = 0; i < m_iters; ++i)
    {
        cv::Mat output;
        cv::Mat current_image = image.clone();

        auto t1 = std::chrono::high_resolution_clock::now();
        SobelFilter::custom(current_image, output);
        auto t2 = std::chrono::high_resolution_clock::now();

        double ms = std::chrono::duration<double, std::milli>(t2 - t1).count();
        serialCustomTotalMs += ms;
    }

    double avgSerialCustomMs = serialCustomTotalMs / m_iters;
    std::cout << "(Implemented Sobel) Average time over " << m_iters << " runs: "
        << std::fixed << std::setprecision(2) << avgSerialCustomMs << " ms\n";

    double openCVTotalMs = 0.0;

    //To avoid info from openCV in cout messing with our text
    set_dummy_error_handler();

    for (int i = 0; i < m_iters; ++i)
    {
        cv::Mat output;
        cv::Mat current_image = image.clone();

        auto t1 = std::chrono::high_resolution_clock::now();
        SobelFilter::nativeOpenCVSobelFilter(current_image, output, 3, 1, 0, CV_16S);
        auto t2 = std::chrono::high_resolution_clock::now();

        double ms = std::chrono::duration<double, std::milli>(t2 - t1).count();
        openCVTotalMs += ms;
    }

    double avgOpenCVTotalMs = openCVTotalMs / m_iters;
    std::cout << "(OpenCV Sobel) Average time over " << m_iters << " runs: "
        << std::fixed << std::setprecision(2) << avgOpenCVTotalMs << " ms\n";

    double openMPTotalMs = 0.0;

    for (int i = 0; i < m_iters; ++i)
    {
        cv::Mat output;
        cv::Mat current_image = image.clone();

        auto t1 = std::chrono::high_resolution_clock::now();
        SobelFilter::customOpenMP(current_image, output);
        auto t2 = std::chrono::high_resolution_clock::now();

        double ms = std::chrono::duration<double, std::milli>(t2 - t1).count();
        openMPTotalMs += ms;
    }

    double avgOpenMPMs = openMPTotalMs / m_iters;
    std::cout << "(OpenMP implemented Sobel with "<< omp_get_max_threads() <<" thread(s)) Average time over " << m_iters << " runs: "
        << std::fixed << std::setprecision(2) << avgOpenMPMs << " ms\n";

    double speedupSerialToOpenMP = avgSerialCustomMs / avgOpenMPMs;
    double speedupOpenCVToOpenMP = avgOpenCVTotalMs / avgOpenMPMs;


    std::cout << "\n--- Speedup Analysis ---" << std::endl;
    std::cout << "Speedup (Implemented Sobel / OpenMP Implemented Sobel): "
        << std::fixed << std::setprecision(2) << speedupSerialToOpenMP << "x\n";
    std::cout << "Speedup (Native OpenCV Sobel / OpenMP Implemented Sobel): "
        << std::fixed << std::setprecision(2) << speedupOpenCVToOpenMP << "x\n";
    std::cout << "------------------------\n" << std::endl;

    return EXIT_SUCCESS;

}

cv::Mat SobelFilterApp::loadImage()
{
	return cv::imread(m_inputPath, cv::IMREAD_COLOR);
}
