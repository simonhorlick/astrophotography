#include <iostream>

int usage() {
    std::cout << "usage: astrophotography --stack exposure0.png exposure1.png ...\n";
    return 1;
}

int main( int argc, char** argv ) {
    if( argc == 1 ) {
        return usage();
    }

    // TODO: Lens distortion removal
    
    // TODO: Load exposures

    // TODO: Calculate transformations

    // TODO: Stack exposures

    return 0;
}

