#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <chrono>
#include <iostream>

#include <opencv2/opencv.hpp>

#include "OtsuBinarizer.h"

int main()
{
    // testing
    COtsuBinarizer binarizer;
    const int numImages = 15;

    double totalTime = 0;
    long long numPixels = 0;

    for( int i = 1; i <= numImages; ++i ) {
        std::string imageName = std::string( i < 10 ? "0" : "" ) + std::to_string( i );

        cv::Mat image = cv::imread( imageName + ".jpg", CV_LOAD_IMAGE_COLOR );
        cv::Mat binarizedImage;

        auto start = std::chrono::steady_clock::now();
        binarizedImage = binarizer.Binarize( image );
        auto finish = std::chrono::steady_clock::now();

        totalTime += std::chrono::duration_cast<std::chrono::duration<double>>( finish - start ).count();
        numPixels += image.rows * image.cols;

        cv::imwrite( imageName + ".bmp", binarizedImage );
    }

    std::cout << totalTime / ( numPixels / 1'000'000) << std::endl;
    system( "pause" );

    return EXIT_SUCCESS;
}