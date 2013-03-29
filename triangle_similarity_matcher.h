#ifndef TRIANGLE_SIMILARITY_MATCHER_H
#define TRIANGLE_SIMILARITY_MATCHER_H

#include "matcher.h"
#include <opencv2/core/core.hpp>

class TriangleSimilarityMatcher : public Matcher {
public:

    Features FindFeatures( const cv::Mat& exposure );

    cv::Mat Match( const Features& a, const Features& b );

    void EncodeFeature( std::vector<float>& features, const cv::Point2f& a,
            const cv::Point2f& b, const cv::Point2f& c );

};

#endif // TRIANGLE_SIMILARITY_MATCHER_H

