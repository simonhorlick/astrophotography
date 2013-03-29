#include <gtest/gtest.h>
#include <opencv2/core/core.hpp>
#include "triangle_similarity_matcher.h"

TEST(TriangleSimilarityMatcher, Translation) {
    TriangleSimilarityMatcher m;

    std::vector<float> featuresA, featuresB;

    // Try matching a translation of (2,2)
    m.EncodeFeature( featuresA, cv::Point2f(0,0), cv::Point2f(1,0), cv::Point2f(0,1) );
    m.EncodeFeature( featuresB, cv::Point2f(2,2), cv::Point2f(3,2), cv::Point2f(2,3) );

    cv::Mat actual = m.Match( featuresA, featuresB );
    float data[] = {
        1,0,0,2,
        0,1,0,2,
        0,0,1,0,
        0,0,0,1,
    };
    cv::Mat expected( 4,4, CV_32F, data );

    // TODO: Find out how to compare cv::Mats
    // EXPECT_EQ( actual, expected );
    FAIL() << "Not implemented";
}

