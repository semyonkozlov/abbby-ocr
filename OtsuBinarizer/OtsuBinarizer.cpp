#include "OtsuBinarizer.h"

int COtsuBinarizer::findThreshold( const cv::Mat& image )
{
    std::vector<int> hist( 256, 0 );

    for( int i = 0; i < image.rows; ++i ) {
        for( int j = 0; j < image.cols; ++j ) {
            ++hist[image.at<uchar>( i, j )];
        }
    }

    int m = 0;
    int n = 0;
    for( int i = 0; i < hist.size(); ++i ) {
        m += i * hist[i];
        n += hist[i];
    }

    double maxSigma = -1;
    int threshold = 0;

    int alpha1 = 0;
    int beta1 = 0;

    for( int i = 0; i < hist.size(); ++i ) {
        alpha1 += i * hist[i];
        beta1 += hist[i];

        double w1 = double( beta1 ) / n;
        double a = double( alpha1 ) / beta1 - double( m - alpha1 ) / (n - beta1);
        double sigma = w1 * (1 - w1) * a * a;

        if( sigma > maxSigma ) {
            maxSigma = sigma;
            threshold = i;
        }
    }

    return threshold;
}

cv::Mat COtsuBinarizer::grayscale( const cv::Mat& image )
{
    cv::Mat grayscaledImage = cv::Mat( image.rows, image.cols, CV_8UC1 );

    // grayscaling constants
    const double c1 = 0.2125;
    const double c2 = 0.7154;
    const double c3 = 0.0721;

    for( int i = 0; i < image.rows; ++i ) {
        for( int j = 0; j < image.cols; ++j ) {
            cv::Vec3b pixel = image.at<cv::Vec3b>( i, j );
            grayscaledImage.at<uchar>( i, j ) = c1 * pixel.val[0] + c2 * pixel.val[1] + c3 * pixel.val[2];
        }
    }

    return grayscaledImage;
}

cv::Mat COtsuBinarizer::Binarize( const cv::Mat& image )
{
    auto binarizedImage = grayscale( image );
    int threshold = findThreshold( binarizedImage );

    for( int i = 0; i < binarizedImage.rows; ++i ) {
        for( int j = 0; j < binarizedImage.cols; ++j ) {
            binarizedImage.at<uchar>( i, j ) = binarizedImage.at<uchar>( i, j ) < threshold ? 0 : 255;
        }
    }

    return binarizedImage;
}
