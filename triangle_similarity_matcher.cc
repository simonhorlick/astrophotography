#include "triangle_similarity_matcher.h"
#include <iostream>
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

struct Point {
    float x, y;
};

struct Triangle {
    Point a,b,c;
};

namespace {
    // Euclidean distance between points a and b
    float norm( Point a, Point b ) {
        float dx = a.x - b.x;
        float dy = a.y - b.y;
        return std::sqrt( dx*dx + dy*dy );
    }

    // Compute the point this triangle represents in a 2d triangle similarity space.
    Point ToSimilaritySpace( const Triangle* t ) {
        float ab, ac, bc;
        ab = norm(t->a, t->b);
        ac = norm(t->a, t->c);
        bc = norm(t->b, t->c);

        // Order the sides from longest to shortest
        float sides[3] = {ab, ac, bc};
        if(sides[0] < sides[1]) std::swap(sides[0], sides[1]);
        if(sides[1] < sides[2]) std::swap(sides[1], sides[2]);

        Point sp;
        sp.x = sides[1]/sides[0];
        sp.y = sides[2]/sides[0];
        return sp;
    }

    // The distance in similarity space of the triangles.
    float Similarity( const Triangle* a, const Triangle* b ) {
        return norm( ToSimilaritySpace(a), ToSimilaritySpace(b) );
    } 
} // namespace

cv::Mat TriangleSimilarityMatcher::Match( const Features& a, const Features& b ) {
    // Corresponding points in a and b.
    std::vector<std::pair<Point,Point> > correspondence;

    // Search for triangles that are "good enough".
    // FIXME: This is really dumb, it should use information about the
    // positions of all of the stars and jointly optimise for that.
    const float eps = 0.00001f; // completely arbitrary
    const float* ab = &a.GetFeatures()[0];
    const float* bb = &b.GetFeatures()[0];
    for( const float* i = ab; i<ab+a.GetFeatures().size(); i+=6 ) {
        for( const float* j=bb; j<bb+b.GetFeatures().size(); j+=6 ) {
            const Triangle* ti = reinterpret_cast<const Triangle*>(i);
            const Triangle* tj = reinterpret_cast<const Triangle*>(j);
            if( Similarity( ti, tj ) < eps ) {
                correspondence.push_back( std::make_pair( ti->a, tj->a ) );
                correspondence.push_back( std::make_pair( ti->b, tj->b ) );
                correspondence.push_back( std::make_pair( ti->c, tj->c ) );
            }
        }
    }

    for( int i=0; i<correspondence.size(); i++ ) {
        std::cout << "(" << correspondence[i].first.x << ","<<correspondence[i].first.y<<") == "
                  << "(" << correspondence[i].second.x << ","<<correspondence[i].second.y<<")\n";
    }
    
    // TODO: Find homography matrix from the correspondences.

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

