#include "Utils.h"

void Utils::imageToGrey(const cv::Mat& src, cv::Mat& dst)
{
    std::vector<cv::Mat> channels;
    cv::split(src, channels);

    //gray = 0.299 R + 0.587 G + 0.114 B
    dst = 0.299 * channels[2] + 0.587 * channels[1] + 0.114 * channels[0];

}


template <typename T>
T clamp(const T& n, const T& lower, const T& upper) {
    return std::max(lower, std::min(n, upper));
}

void Utils::combineWeighted(const cv::Mat& srcX, double weight1, const cv::Mat& srcY, double weight2, cv::Mat& dst)
{
    dst = srcX * clamp<double>(weight1,0 , 1) + srcY * clamp<double>(weight2, 0, 1);
}



void Utils::ConvertS16To8U(const cv::Mat& src, cv::Mat& dst)
{
    assert(src.type() == CV_16S);

    dst = cv::Mat(src.size(), CV_8U);

    for (int i = 0; i < src.rows; ++i)
    {
        const int16_t* srcRow = src.ptr<int16_t>(i);
        uint8_t* dstRow = dst.ptr<uint8_t>(i);

        for (int j = 0; j < src.cols; ++j)
        {
            int v = srcRow[j];
            dstRow[j] = cv::saturate_cast<uint8_t>(std::abs(v));
        }
    }

}
