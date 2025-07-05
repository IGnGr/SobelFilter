// SobelFilter.cpp : Defines the entry point for the application.
//

#include "SobelFilter.h"
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "GaussianBlur.h"

static void imageToGrey(const cv::Mat& src, cv::Mat& dst)
{

    std::vector<cv::Mat> channels;
    cv::split(src, channels);

    
    
    

    
}


static void NativeOpenCVSobelFilter(const cv::Mat & src, cv::Mat& dst, int ksize, int scale, int delta, int ddepth)
{

    // First we declare the variables we are going to use
    cv::Mat src_gray;
    cv::Mat grad;

    cv::GaussianBlur(src, dst, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
    /*
    // Convert the image to grayscale
    cvtColor(dst, src_gray, COLOR_BGR2GRAY);

    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    Sobel(src_gray, grad_x, ddepth, 1, 0, ksize, scale, delta, BORDER_DEFAULT);

    Sobel(src_gray, grad_y, ddepth, 0, 1, ksize, scale, delta, BORDER_DEFAULT);

    // converting back to CV_8U
    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);

    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    */
}


int main(int argc, char** argv)
{

    cv::CommandLineParser parser(argc, argv,
        "{@input   |..\\..\\..\\lena.jpg | input image }"
        "{ksize   k|1|ksize (hit 'K' to increase its value at run time)}"
        "{scale   s|1|scale (hit 'S' to increase its value at run time)}"
        "{delta   d|0|delta (hit 'D' to increase its value at run time)}"
        "{help    h|false|show help message}");

    std::cout << "The sample uses Sobel or Scharr OpenCV functions for edge detection\n\n";
    parser.printMessage();
    std::cout << "\nPress 'ESC' to exit program.\nPress 'R' to reset values ( ksize will be -1 equal to Scharr function )";


    const cv::String window_name = "Sobel Demo - Simple Edge Detector";
    int ksize = parser.get<int>("ksize");
    int scale = parser.get<int>("scale");
    int delta = parser.get<int>("delta");
    int ddepth = CV_16S;

    cv::String imageName = parser.get<cv::String>("@input");
    // As usual we load our source image (src)
    cv::Mat image = cv::imread(cv::samples::findFile(imageName), cv::IMREAD_COLOR); // Load an image

    cv::Mat output;

    // Check if image is loaded fine
    if (image.empty())
    {
        printf("Error opening image: %s\n", imageName.c_str());
        return EXIT_FAILURE;
    }

    for (;;)
    {
        output = image;



        char key = (char)cv::waitKey(0);

        if (key == 27)
        {
            return EXIT_SUCCESS;
        }


        if (key == 's')
        {
            NativeOpenCVSobelFilter(image, output, ksize, scale, delta, ddepth);
        }

        if (key == 'd')
        {
            GaussianBlur::apply(image, output);
        }

        if (key == 'f')
        {
            image = cv::imread(cv::samples::findFile(imageName), cv::IMREAD_COLOR);
        }



        imshow(window_name, output);

    }
    return EXIT_SUCCESS;
}

