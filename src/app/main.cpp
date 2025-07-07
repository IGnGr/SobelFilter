#include "SobelFilterApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <omp.h>



int main(int argc, char** argv)
{


    cv::CommandLineParser parser(argc, argv,
        "{@input   |lena.jpg | input image }"
        "{@output  |out.jpg | result image }"
        "{@mode    |-o      | mode select '-r' - Regular output generation; '-b' - Benchmark; '-o' - OpenMP output generation}"
        "{@iters   |10      | iterations in benchmark mode, ignored in regular mode}"
    );


    const cv::String window_name = "Custom Sobel filter";

    SobelFilterApp app(parser.get<cv::String>("@input"), 
        parser.get<cv::String>("@output"), 
        parser.get<cv::String>("@mode"),
        parser.get<int>("@iters"));




    return app.run();
}