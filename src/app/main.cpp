#include "SobelFilterApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>


int main(int argc, char** argv)
{

    cv::CommandLineParser parser(argc, argv,
        "{@input   |.\\..\\..\\..\\lena.jpg | input image }"
        "{@output  |out.jpg | result image }"
        "{@mode    |0       | mode select 0 - Regular output generation; 1 - Benchmark}");


    const cv::String window_name = "Custom Sobel filter";

    SobelFilterApp app(parser.get<cv::String>("@input"), parser.get<cv::String>("@output"), parser.get<int>("@mode"));




    return app.regularRun();
}