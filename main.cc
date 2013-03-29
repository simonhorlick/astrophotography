#include <iostream>

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

    // TODO: Calculate transformations
    // * Find points of interest in each exposure (large stars)
    // * Transform these points into a 2d triangle similarity space, as in
    //   http://adsabs.harvard.edu/cgi-bin/nph-bib_query?bibcode=1995PASP..107.1119V&db_key=AST&high=39463d35aa24090
    // * Calculate homography matrix between a reference exposure and each
    //   other exposure

    // TODO: Stack exposures

    return 0;
}

