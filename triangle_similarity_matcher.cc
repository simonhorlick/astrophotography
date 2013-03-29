#include "triangle_similarity_matcher.h"

Features TriangleSimilarityMatcher::FindFeatures( const cv::Mat& exposure ) {
    return Features(std::vector<float>());
}

cv::Mat TriangleSimilarityMatcher::Match( const Features& a, const Features& b ) {
    return cv::Mat();
}

