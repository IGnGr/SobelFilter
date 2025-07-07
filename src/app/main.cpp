#include "SobelFilterApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>


int main(int argc, char** argv)
{

    cv::CommandLineParser parser(argc, argv,
        "{@input   |lena.jpg | input image }"
        "{@output  |out.jpg | result image }");


    const cv::String window_name = "Sobel Demo - Simple Edge Detector";

    cv::String imageName = parser.get<cv::String>("@input");


    SobelFilterApp app(parser.get<cv::String>("@input"), parser.get<cv::String>("@output"));


    return app.run();
}