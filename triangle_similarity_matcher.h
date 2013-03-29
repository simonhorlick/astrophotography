#ifndef TRIANGLE_SIMILARITY_MATCHER_H
#define TRIANGLE_SIMILARITY_MATCHER_H

#include "matcher.h"

class TriangleSimilarityMatcher : public Matcher {
public:

    Features FindFeatures( const cv::Mat& exposure );

    cv::Mat Match( const Features& a, const Features& b );
};

#endif // TRIANGLE_SIMILARITY_MATCHER_H

