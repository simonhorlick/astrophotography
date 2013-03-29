#ifndef MATCHER_H
#define MATCHER_H

#include <vector>
#include <opencv2/core/core.hpp>

// A collection of features returned by a Matcher.
class Features {
public:
    Features( const std::vector<float>& features ) : features_(features) {}
    ~Features() {}

    const std::vector<float>& GetFeatures() {
        return features_;
    }

private:
    std::vector<float> features_;
};

// An interface for all image registration algorithms to use. Currently only
// two images can be matched at a time.
class Matcher {
public:
    virtual ~Matcher() { }

    // Computes a set of interesting features in an exposure.
    virtual Features FindFeatures( const cv::Mat& exposure ) = 0;

    // Matches features in feature sets a and b, and returns the computed
    // homography matrix transforming b into a.
    virtual cv::Mat Match( const Features& a, const Features& b ) = 0;
};

#endif // MATCHER_H

