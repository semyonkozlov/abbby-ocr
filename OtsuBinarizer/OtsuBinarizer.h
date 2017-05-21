#pragma once

#include <opencv2/opencv.hpp>

class COtsuBinarizer {
public:
    cv::Mat Binarize( const cv::Mat& image );

private:
    int findThreshold( const cv::Mat& image );
    cv::Mat grayscale( const cv::Mat& image );
};