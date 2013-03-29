#include <iostream>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include "matcher.h"
#include "triangle_similarity_matcher.h"

int usage() {
    std::cout << "usage: stack exposure0.png exposure1.png ...\n";
    return 1;
}

int main( int argc, char** argv ) {
    if( argc < 3 ) {
        return usage();
    }

    // TODO: Lens distortion removal
    
    // TODO: Load exposures
    Matcher* matcher = new TriangleSimilarityMatcher();

    cv::Mat reference = cv::imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE );
    Features refFeatures = matcher->FindFeatures( reference );

    // TODO: Calculate transformations
    // * Find points of interest in each exposure (large stars)
    // * Transform these points into a 2d triangle similarity space, as in
    //   http://adsabs.harvard.edu/cgi-bin/nph-bib_query?bibcode=1995PASP..107.1119V&db_key=AST&high=39463d35aa24090
    // * Calculate homography matrix between a reference exposure and each
    //   other exposure
    
    // The first exposure is taken as the reference
    std::vector<cv::Mat> transformations( argc-2 );

    // Compute transformation between each exposure and the reference
    for( int i=2; i<argc; i++ ) {
        cv::Mat image = cv::imread( argv[i], CV_LOAD_IMAGE_GRAYSCALE );
        Features features = matcher->FindFeatures( image );
        transformations[i-2] = matcher->Match( refFeatures, features );
    }

    // TODO: Stack exposures

    delete matcher;

    return 0;
}

