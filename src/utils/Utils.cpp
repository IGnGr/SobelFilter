#include "Utils.h"

void Utils::imageToGrey(const cv::Mat& src, cv::Mat& dst)
{
    std::vector<cv::Mat> channels;
    cv::split(src, channels);

    //gray = 0.299 R + 0.587 G + 0.114 B
    dst = 0.299 * channels[2] + 0.587 * channels[1] + 0.114 * channels[0];

}

void Utils::calculateMagnitude(const cv::Mat& srcX, const cv::Mat& srcY, cv::Mat& dst)
{
    dst = srcX * 0.5 + srcY * 0.5;
}



void Utils::ConvertS16To8U(const cv::Mat& src, cv::Mat& dst)
{
    dst = cv::Mat(src.size(), CV_8U);

    int rows = src.rows;
    int cols = src.cols;

    for (int i = 0; i < rows; ++i)
    {
        const int16_t* srcRow = src.ptr<int16_t>(i);
        uint8_t* dstRow = dst.ptr<uint8_t>(i);

        for (int j = 0; j < cols; ++j)
        {
            int v = srcRow[j];
            dstRow[j] = cv::saturate_cast<uint8_t>(std::abs(v));
        }
    }

}
