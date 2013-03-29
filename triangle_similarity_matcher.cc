#include "triangle_similarity_matcher.h"
#include <opencv2/features2d/features2d.hpp>

// Features are expected to be a triple of 2d coordinates, representing the
// triangles.
Features TriangleSimilarityMatcher::FindFeatures( const cv::Mat& exposure ) {
    std::vector<cv::KeyPoint> stars;

    cv::FAST( exposure, stars, 9, true );

    std::vector<float> features;

    // Return every possible distinct triangle as a feature
    const int N = stars.size();
    for( int i=0; i<N; i++ ) {
        cv::Point2f& a = stars[i].pt;
        for( int j=i; j<N; j++ ) {
            cv::Point2f& b = stars[j].pt;
            for( int k=j; j<N; k++ ) {
                cv::Point2f& c = stars[k].pt;
                EncodeFeature( features, a, b, c );
            }
        }
    }

    return Features(features);
}

cv::Mat TriangleSimilarityMatcher::Match( const Features& a, const Features& b ) {
    float data[] = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1,
    };
    return cv::Mat( 4,4, CV_32F, data );
}

void TriangleSimilarityMatcher::EncodeFeature( std::vector<float>& features,
        const cv::Point2f& a, const cv::Point2f& b, const cv::Point2f& c ) {
    features.push_back( a.x );
    features.push_back( a.y );
    features.push_back( b.x );
    features.push_back( b.y );
    features.push_back( c.x );
    features.push_back( c.y );
}

